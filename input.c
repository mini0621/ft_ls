/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:11:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 00:00:50 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	read_input(t_lsflags *flags, t_list **path, int argc, char **argv)
{
	int		i;
	int		j;
	t_list	*new;

	i = 1;
	init_flags(flags);
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
	while (i < argc && (new = ft_lstnew(argv[i], ft_strlen(argv[i]) + 1)) != NULL)
	{
		ft_lstpushback(path, new);
		i++;
	}
	return (solve_flagconf(flags));
}

int	validate_input(t_list **path)
{
	t_list	*cur;
	t_list	*pre;
	int		empty;
	struct stat	stat;

	empty = 0;
	if (*path == NULL)
		return (0);
	cur = *path;
	while (cur != NULL)
	{
		if (lstat((char *)(cur->content), &stat) != 0)
		{
			print_error(NULL, (char *)cur->content, 'n');
			if (cur == *path)
				*path = cur->next;
			else
				pre->next = cur->next;
			free(cur->content);
			free(cur);
			empty++;
		}
		pre = cur;
		cur = cur->next;
	}
	return ((empty != 0) ? -1 : 0);
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
	struct winsize	w;

	if (flags->f == 'f')
		flags->a = 'a';
	if (flags->l == 'l')
		flags->n1 = '1';
	if (flags->n1 != '1')
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		flags->w_col = w.ws_col;
	}
	return ('\0');
}

void	init_flags(t_lsflags *flags)
{
	flags->a = '\0';
	flags->l = '\0';
	flags->r = '\0';
	flags->t = '\0';
	flags->cr = '\0';
	flags->f = '\0';
	flags->d = '\0';
	flags->u = '\0';
	flags->n1 = '\0';
	flags->rflag = '\0';
	flags->w_col = 0;
}
