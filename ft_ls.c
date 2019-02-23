/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/23 02:41:54 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	manage_path(char *path, t_lsflags *flags, char c)
{
	DIR		*dirp;
	t_list	*files;
	t_fmt	fmt;

	files = NULL;
	if (c == 'n')
		ft_printf("%s:\n", path);
	if ((dirp = opendir(path)) == NULL)
		return (2);
	flags->fmt = &fmt;
	init_fmt(&fmt);
	if (store_dp(path, dirp, &files, flags) < 0)
		return (2);
	sort_files(&files, flags);
	get_output(path, &files, flags);
	closedir(dirp);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lsflags	flags;
	t_list		*path;
	t_list		*tmp;
	char		c;
	int			ret;

	path = NULL;
	if ((c = read_input(&flags, &path, argc, argv)) != '\0')
		return (print_error("ft_ls: illegal option -- %s\n", &c, 'y'));
	if ((validate_input(&path) < 0 && path == NULL)
		|| (ret = prcs_first_dir(&path, &flags)) == 0)
		return (0);
	c = (path != NULL && path->next == NULL) ? 'y' : 'n';
	while (path != NULL)
	{
		if (manage_path(((t_file *)(path->content))->d_name, &flags, c) == 2)
			print_error(NULL, ((t_file *)(path->content))->d_name, 'n');
		tmp = path;
		path = path->next;
		ft_lstdelone(&tmp, &ft_ldel);
		if (path != NULL)
			ft_printf("\n");
	}
	return (0);
}
