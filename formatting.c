/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:01:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 01:07:39 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_fmt_name(char *d_name, t_fmt *fmt)
{
	int	len;

	len = ft_strlen(d_name);
	if (len > fmt->name)
		fmt->name = len;
}

void	init_fmt(t_fmt *fmt)
{
	fmt->nlink = 0;
	fmt->user = 0;
	fmt->group = 0;
	fmt->size = 0;
	fmt->blkcnt = -1;
}

blkcnt_t	fmt_cmp(t_fmt *fmt, struct stat *stat)
{
	size_t len;
	nlink_t	nlink;
	off_t	size;

	len = 0;
	nlink = stat->st_nlink;
	while (nlink != 0)
	{
		nlink /= 10;
		len++;
	}
	if (len > fmt->nlink)
		fmt->nlink = len;
	if ((len = ft_strlen((getpwuid(stat->st_uid))->pw_name)) > fmt->user)
		fmt->user = len;
	if ((len = ft_strlen((getgrgid(stat->st_gid))->gr_name)) > fmt->group)
		fmt->group = len;
	len = 0;
	size = stat->st_size;
	while (size != 0)
	{
		size /= 10;
		len++;
	}
	if (len > fmt->size)
		fmt->size = len;
	return (stat->st_blocks);
}
