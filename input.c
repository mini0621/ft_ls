/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:11:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/23 02:40:55 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	read_input(t_lsflags *flags, t_list **path, int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	init_flags(flags);
	while (i < argc)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == '\0')
				|| (ft_strcmp(argv[i], "--") == 0))
			break ;
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (store_flag(flags, argv[i][j]) == -1)
				return (argv[i][j]);
			j++;
		}
		i++;
	}
	store_arg_paths(i, argc, path, argv);
	return (solve_flagconf(flags));
}

void	store_arg_paths(int i, int argc, t_list **path, char **argv)
{
	t_list	*new;

	if (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
		i++;
	while (i < argc)
	{
		if ((new = ft_lstnew(argv[i], ft_strlen(argv[i]) + 1)) != NULL)
			ft_lstpushback(path, new);
		i++;
	}
}

int		validate_input(t_list **path)
{
	t_list		*cur;
	t_list		*tmp;
	int			empty;
	struct stat	stat;

	sort_inputs(path, '\0');
	empty = 0;
	if (*path == NULL)
		return (0);
	cur = *path;
	while (cur != NULL)
	{
		if (lstat((char *)(cur->content), &stat) != 0)
		{
			print_error(NULL, (char *)cur->content, 'n');
			tmp = cur;
			cur = cur->next;
			tmp = ft_lstsub(path, tmp);
			ft_lstdelone(&tmp, &ft_chardel);
			empty++;
		}
		else
			cur = cur->next;
	}
	return ((empty != 0) ? -1 : 0);
}

void	sort_inputs(t_list **files, char r)
{
	t_list	*cur;
	t_list	*index;
	t_list	*sorted;
	int		ret;

	if (files == NULL || *files == NULL || (*files)->next == NULL)
		return ;
	sorted = *files;
	cur = *files;
	while (cur != NULL && *files != NULL)
	{
		index = sorted;
		while (cur != NULL)
		{
			ret = ft_strcmp((char *)(cur->content), (char *)(index->content));
			if ((r == 'r' && ret > 0) || (r != 'r' && ret < 0))
				index = cur;
			cur = cur->next;
		}
		cur = insertion_swap(index, &sorted);
	}
}
