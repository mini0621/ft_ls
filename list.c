/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:43:47 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 20:25:29 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ldel(void *ptr, size_t size)
{
	if (ptr == NULL || size == 0)
		return ;
	free(((t_file *)ptr)->d_name);
}

void	ft_chardel(void *ptr, size_t size)
{
	if (ptr == NULL || size == 0)
		return ;
	free((char *)ptr);
}


t_list	**re_list(t_list **path, t_fmt *fmt, t_lsflags *flags)
{
	t_list	*cur;
	t_list	*pre;
	t_list	*tmp;
	t_list	*last;
	int		len;

	len = 0;
	flags->fmt = fmt;
	cur = *path;
	while (cur)
	{
		get_newfile(&tmp, &last, (char *)((*path)->content),
			(char *)((*path)->content));
		get_fmt_name(((t_file *)(last->content))->d_name, fmt);
		if (flags->l == 'l')
			fmt_cmp(flags->fmt,
				&(((t_file *)(last->content))->stat));
		pre = cur;
		cur = cur->next;
	}
	ft_lstdel(path, &ft_chardel);
	fmt->len = len;
	if (flags->n1 == '1' && flags->l != 'l')
		flags->fmt->name = 1;
	fmt->row = (flags->n1 != '1') ?
	1 + fmt->len / (flags->w_col / fmt->name) : fmt->len;
	*path = tmp;
	return (path);
}
