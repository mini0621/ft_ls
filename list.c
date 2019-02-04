/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:43:47 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 23:12:08 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ldel(void *ptr, size_t size)
{
	if (ptr == NULL)
		return ;
	free((char *)ptr);
	ft_bzero(ptr, size);
}
/*
t_list	*re_list_time(char *path, t_list **files)
{
	t_list	*new;
	t_file	file;
	t_list	*cur;
	t_list	*last;
	t_list	*new_files;

	new_files = NULL;
	cur = *files;
	while (cur != NULL)
	{
		if (get_file(path, (char *)(cur->content), &file) == -1
			|| (new = ft_lstnew(&file, sizeof(t_file))) == NULL)
			return (new_files);
		if (new_files == NULL)
		{
			new_files = new;
			last = new_files;
		}
		else
		{
			last->next = new;
			last = last->next;
		}
		cur = cur->next;
	}
	return (new_files);
}
*/
