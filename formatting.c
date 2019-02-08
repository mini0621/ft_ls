/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:01:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 20:16:43 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_fmt_name(char *d_name, t_fmt *fmt)
{
	size_t	len;

	if (fmt == NULL || d_name == NULL)
		return ;
	len = ft_strlen(d_name);
	if (len + 2 > fmt->name)
		fmt->name = len + 1;
}

void		init_fmt(t_fmt *fmt)
{
	fmt->name = 0;
	fmt->row = 0;
	fmt->len = 0;
	fmt->nlink = 0;
	fmt->user = 0;
	fmt->group = 0;
	fmt->size = 0;
	fmt->blkcnt = -1;
}

void		get_fmt(t_list **files, t_fmt *fmt, t_lsflags *flags)
{
	t_list	*cur;
	char	flag;
	int		row;

	cur = *files;
	flag = flags->l;
	if (flags->n1 == '1' && flag != 'l')
	{
		fmt->name = 1;
		return ;
	}
	while (flag == 'l' && cur)
	{
		get_fmt_name(((t_file *)(cur->content))->d_name, fmt);
		fmt_cmp(fmt, &(((t_file *)(cur->content))->stat));
		cur = cur->next;
	}
	while (flag != 'l' && cur)
	{
		get_fmt_name(((t_file *)(cur->content))->d_name, fmt);
		cur = cur->next;
	}
	if (flags->n1 != '1')
	{
		row = flags->fmt->len / (flags->w_col / flags->fmt->name);
		flags->fmt->row = (flags->fmt->name * flags->fmt->len < flags->w_col) ? 1: 1 + row;
	}
}

blkcnt_t	fmt_cmp(t_fmt *fmt, struct stat *stat)
{
	size_t	len;
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
