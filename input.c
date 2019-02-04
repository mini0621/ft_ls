/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:11:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 19:20:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	read_input(t_lsflags *flags, t_list **path, int argc, char **argv)
{
	int	i;
	int	j;
	t_list	*new;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			break;
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (store_flag(flags, argv[i][j]) == -1)
				return (argv[i][j]);
			j++;
		}
		i++;
	}
	while (i < argc && (new = ft_lstnew(argv[i], ft_strlen(argv[i]))) != NULL)
	{
		ft_lstpushback(path, new);
		i++;
	}
	if (flags->cr == 'R')
		sort_input(path);
	return (solve_flagconf(flags));
}

void	sort_input(t_list **path)
{
	t_list	*cur;
	t_list	*last;
	t_list	*tmp;
	t_list	*pre;

	if (*path == NULL)
		return ;
	tmp = *path;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (cur != tmp)
	{
		if (opendir((char *)(cur->next->content)) != NULL)
		{
			last = tmp;
			while (last->next != NULL)
				last = last->next;
			pre = *path;
			while (pre->next != cur)
				pre = pre->next;
			last->next = cur;
			pre->next = cur->next;
			cur->next = NULL;
		}
		cur = pre->next;
	}

}

int store_flag(t_lsflags *flags, char c)
{
	if (c == 'a')
		flags->a = 'a';
	else if (c == 'l')
		flags->l = 'l';
	else if (c == 'r')
		flags->r = 'r';
	else if (c == 'R')
		flags->cr = 'R';
	else if (c == 't')
		flags->t = 't';
	else if (c == 'f')
		flags->f = 'f';
	else if (c == 'd')
		flags->d = 'd';
	else if (c == 'u')
		flags->u = 'u';
	else if (c == '1')
		flags->n1 = '1';
	else
		return (-1);
	return (0);
}

char solve_flagconf(t_lsflags *flags)
{
	if (flags->f == 'f')
		flags->a = 'a';
	return ('\0');
}
