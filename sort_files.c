/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:17:03 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/18 21:58:30 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_files(t_list **files, t_lsflags *flags)
{
	if (files == NULL || *files == NULL || flags->f == 'f')
		return ;
	sort_by_name(files, flags->r);
	if (flags->t == 't')
		sort_by_time(files, flags->r, flags);
}

void	sort_by_name(t_list **files, char r)
{
	t_list	*cur;
	t_list	*index;
	t_list	*sorted;
	int		ret;

	if (files == NULL || *files == NULL || (*files)->next == NULL)
		return ;
	sorted = *files;
	cur = *files;
	while (cur != NULL)
	{
		index = sorted;
		while (cur != NULL)
		{
			ret = ft_strcmp(((t_file *)(cur->content))->d_name,
					((t_file *)(index->content))->d_name);
			if ((r == 'r' && ret > 0) || (r != 'r' && ret < 0))
				index = cur;
			cur = cur->next;
		}
		cur = insertion_swap(index, &sorted);
	}
}

t_list	*insertion_sort(t_list *index, t_list **sorted, t_list **files)
{
	if (*sorted != NULL && index == (*sorted)->next)
	{
		*sorted = (*sorted)->next;
		return ((*sorted)->next);
	}
	index = ft_lstsub(files, index);
	if (*sorted == NULL)
	{
		index->next = *files;
		*files = index;
		*sorted = index;
		return ((*sorted)->next);
	}
	index->next = (*sorted)->next;
	(*sorted)->next = index;
	*sorted = index;
	return ((*sorted)->next);
}

t_list	*insertion_swap(t_list *index, t_list **sorted)
{
	void	*tmp;

	if (index == *sorted)
	{
		*sorted = (*sorted)->next;
		return (*sorted);
	}
	tmp = (*sorted)->content;
	(*sorted)->content = index->content;
	index->content = tmp;
	*sorted = (*sorted)->next;
	return ((*sorted));
}

void	sort_by_time(t_list **files, char r, t_lsflags *flags)
{
	t_list	*sorted;
	t_list	*index;
	t_list	*cur;
	time_t	val;

	if (files == NULL || *files == NULL || (*files)->next == NULL)
		return ;
	sorted = NULL;
	cur = *files;
	while (cur != NULL)
	{
		val = get_time(cur, flags);
		index = cur;
		while (cur != NULL)
		{
			if ((r == 'r' && get_time(cur, flags) < val)
				|| (r != 'r' && get_time(cur, flags) > val))
			{
				index = cur;
				val = get_time(index, flags);
			}
			cur = cur->next;
		}
		cur = insertion_sort(index, &sorted, files);
	}
}
