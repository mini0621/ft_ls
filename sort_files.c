/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:17:03 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 19:40:50 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void sort_files(t_list **files, t_lsflags *flags)
{
	if (files == NULL || *files == NULL || flags->f == 'f')
		return ;
	if (flags->t == 't' || flags->u == 'u')
		sort_by_time(files, flags->r, flags);
	else
		sort_by_name(files, flags->r);
}

void	sort_by_name(t_list **files, char r)
{
	t_list	*cur;
	t_list	*index;
	t_list	*sorted;
	t_list	*tmp;
	int		ret;

	if (files == NULL || *files == NULL || (*files)->next == NULL)
		return ;
	sorted = NULL;
	cur = *files;
	while (cur->next != NULL)
	{
		index = NULL;
		tmp = cur;
		while (cur->next != NULL)
		{
			if (index == NULL)
				ret =  ft_strcmp(((t_file *)(cur->next->content))->d_name, ((t_file *)(tmp->content))->d_name);
			else
				ret =  ft_strcmp(((t_file *)(cur->next->content))->d_name, ((t_file *)(index->next->content))->d_name);
			if ((r == 'r' && ret > 0) || (r != 'r' && ret < 0))
				index = cur;
			cur = cur->next;
		}
		cur = insertion_sort(files, index, &sorted, cur);
	}
}

t_list	*insertion_sort(t_list **head, t_list *index, t_list **sorted, t_list *cur)
{
	if (*sorted == NULL)
	{
		if (index != NULL)
		{
			cur->next = *head;
			*head = index->next;
			index->next = NULL;
		}
		*sorted = *head;
		return ((*sorted)->next);
	}
	if (index == NULL)
	{
		*sorted = (*sorted)->next;
		return ((*sorted)->next);
	}
	cur->next = (*sorted)->next;
	(*sorted)->next = index->next;
	index->next = NULL;
	*sorted = (*sorted)->next;
	return ((*sorted)->next);
}
void	sort_by_time(t_list **files, char r, t_lsflags *flags)
{
	t_list	*sorted;
	t_list	*index;
	t_list	*cur;
	time_t		val;
	int		ret;

	
	if (files == NULL || *files == NULL || (*files)->next == NULL)
		return ;
	sorted = NULL;
	cur = *files;
	while (cur->next != NULL)
	{
		val = get_time(cur, flags);
		index = NULL;
		while (cur->next != NULL)
		{
			ret = get_time(cur->next, flags);
			if ((r == 'r' && ret > val) || (r != 'r' && ret < val))
				index = cur;
			cur = cur->next;
		}
		cur = insertion_sort(files, index, &sorted, cur);
	}
}
