/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:11:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/01 17:48:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	read_input(t_lsflags *flags, t_list **path, int argc, char **argv)
{
	//store the file name in path
	//store flags
	//in case of illegal option, return -1 and store the option in path(alloc)
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
	if (i == argc)
	{
		if ((new = ft_lstnew(ft_strdup("."), sizeof(char *))) == NULL)
			return ('\0');
		ft_lstpushback(path, new);
	}
	while (i < argc)
	{
		if ((new = ft_lstnew(ft_strdup(argv[i]), sizeof(char *))) == NULL)
			return ('\0');
		ft_lstpushback(path, new);
		i++;
	}
	return (solve_flagconf(flags));
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
