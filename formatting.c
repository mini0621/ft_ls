/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:01:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/06 23:06:20 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_fmt_name(t_list	*files, t_lsflags *flags, t_fmt *fmt)
{
	t_list			*cur;

	if (flags->n1 == '1')
	{
		fmt->name = 1;
		fmt->row = fmt->len;
		return ;
	}
	if (fmt->len == 0 || fmt->name == 0)
	{
		cur = files;
		while (cur != NULL)
		{
			if (cur->content_size > fmt->name)
				fmt->name = cur->content_size;
			fmt->len += 1;
			cur = cur->next;
		}
	}
	if (fmt->len != 0 && fmt->name != 0)
		fmt->row = 1 + fmt->len / (flags->w_col / fmt->name);
}

blkcnt_t	get_fmt(char *path, t_list *files, t_lsflags *flags, t_fmt *fmt)
{
	t_list		*cur;
	t_list		*ptr;
	char		*tpath;
	blkcnt_t		size;
	struct stat	sttbuff;

	cur = files;
	size = 0;
	init_fmt(fmt);
	get_fmt_name(files, flags, fmt);
	while (cur && (tpath = add_path(path, (char *)(cur->content))) != NULL
			&& lstat(tpath, &sttbuff) == 0)
	{
		size += fmt_cmp(fmt, &sttbuff);
		cur = cur->next;
		ft_strdel(&tpath);
	}
	return (size);
}

void	init_fmt(t_fmt *fmt)
{
	fmt->nlink = 0;
	fmt->user = 0;
	fmt->group = 0;
	fmt->size = 0;
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
