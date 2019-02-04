/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:17:03 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 01:01:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void sort_files(char *path, t_list **files, t_lsflags *flags)
{
	if (files == NULL || *files == NULL || flags->f == 'f')
		return ;
	if (flags->t == 't')
		sort_by_time(path, files, flags->r);
	else
		sort_by_name(files, flags->r);
}

void	sort_by_name(t_list **files, char r)
{
	t_list	*cur;
	t_list	*pre;

	pre = *files;
	cur = pre->next;
	while (cur->next != NULL)
	{
		if (pre == *files
			&& ft_strcmp((char *)(pre->content), (char *)(cur->content)) < 0)
		{
			pre->next = cur->next;
			cur->next = pre;
			*files = cur;
		}
		if (ft_strcmp((char *)(cur->content), (char *)(cur->next->content)) < 0)
		{
			swap_lst(pre, cur);
			pre = *files;
			cur = pre->next;
		}
		cur = cur->next;
		pre = pre->next;
	}
}

void	swap_lst(t_list *pre, t_list *cur)
{
	t_list	*tmp;

	tmp = cur->next;
	cur->next = cur->next->next;
	pre->next = tmp;
	tmp->next = cur;
}

void	sort_by_time(char *path, t_list **files, char r)
{
	/*	t_list			*new;
		t_list			*last;
		t_list			*max;
		struct stat		sttbuff;
		char	*tpath;

		cur = *files;
		tpath = add_path(path, (char *)(cur->content));
		while (cur && tpath && lstat(tpath, &sttbuff) == 0)
		{
		if ((sttbuff.st_mtime > max)
		store_(dirs, files, &cur, pre);
		pre = cur;
		if (cur != *files)
		cur = cur->next;
		ft_strdel(&tpath);
		tpath = add_path(path, (char *)(cur->content));
		}
		return (*dirs);
		*/
}
