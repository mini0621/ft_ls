/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:01:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/18 23:18:17 by mnishimo         ###   ########.fr       */
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
	fmt->name = 1;
	fmt->row = 1;
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
	if (flags->n1 == '1')
		return ;
	while (flag == 'l' && cur)
	{
		fmt_cmp(fmt, &(((t_file *)(cur->content))->stat));
		cur = cur->next;
		return ;
	}
	while (flag != 'l' && cur)
	{
		get_fmt_name(((t_file *)(cur->content))->d_name, fmt);
		cur = cur->next;
	}
	if ((row = flags->w_col / flags->fmt->name) == 0)
		flags->fmt->row = 1;
	else if ((row = flags->fmt->len / row) == 0)
		flags->fmt->row = 1;
	else
		flags->fmt->row = 1 + row;
}

blkcnt_t	fmt_cmp(t_fmt *fmt, struct stat *stat)
{
	size_t			len;
	struct group	*gr;
	struct passwd	*pw;

	if (!fmt || !stat)
		return (0);
	fmt->nlink = cmp_len_nbr(fmt->nlink, (long long)stat->st_nlink);
	if ((pw = getpwuid(stat->st_uid))
		&& (len = ft_strlen(pw->pw_name)) > fmt->user)
		fmt->user = len;
	if ((gr = getgrgid(stat->st_gid))
		&& (len = ft_strlen(gr->gr_name)) > fmt->group)
		fmt->group = len;
	if ((stat->st_mode & S_IFMT) == S_IFBLK
		|| (stat->st_mode & S_IFMT) == S_IFCHR)
		fmt->size = 8;
	else
		fmt->size = cmp_len_nbr(fmt->size, (long long)stat->st_size);
	return (stat->st_blocks);
}

size_t		cmp_len_nbr(size_t len1, long long nbr)
{
	size_t len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	if (len > len1)
		return (len);
	return (len1);
}
