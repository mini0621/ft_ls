/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:43:47 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 22:54:11 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ldel(void *ptr, size_t size)
{
	if (ptr == NULL || size == 0)
		return ;
	free(((t_file *)ptr)->d_name);
	free(ptr);
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
	tmp = NULL;
	cur = *path;
	while (cur)
	{
		get_newfile(&tmp, &last, (char *)(cur->content),
			(char *)(cur->content));
		pre = cur;
		cur = cur->next;
	}
	ft_lstdel(path, &ft_chardel);
	fmt->len = len;
	if (flags->n1 == '1' && flags->l != 'l')
		flags->fmt->name = 1;
	fmt->row = fmt->len;
	*path = tmp;
	return (path);
}
