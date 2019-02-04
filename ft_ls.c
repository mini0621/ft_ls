/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 19:20:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	manage_path(char *path, t_lsflags *flags, char **output)
{
	DIR				*dirp;
	t_list			*files;
	t_fmt			fmt;
	struct dirent	*dp;
	char			*tmp;

	flags->fmt = &fmt;
	if (flags->d == 'd' || (dirp = opendir(path)) == NULL)
		return ((search_file(flags, path, output)) ? -1 : 0);
	if (ft_strcmp(".", path) != 0)
		ft_asprintf(&tmp, "%s:\n", path);
	*output = ft_strjoinfree(output, &tmp, 3);
	if (store_dp(dirp, &files, &fmt, flags) < 0)
		return (-1);
	sort_files(path, &files, flags);
	get_output(path, &files, flags, output);
	ft_lstdel(&files, &ft_ldel);
	closedir(dirp);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lsflags	flags;
	t_list		*path;
	t_list		*tmp;
	char		*output;
	char		c;

	output = NULL;
	path = NULL;
	if ((c = read_input(&flags, &path, argc, argv)) !=  '\0')
		return (print_error("ft_ls: illegal option -- %s\n", &c, 'y'));
	if (path == NULL && manage_path(".", &flags, &output) < 0)
			return (0);
	sort_files(NULL, &path, &flags);
	while (path != NULL)
	{
		if (manage_path((char **)&(path->content), &flags, &output) == -1)
			print_error("ft_ls: %s: No such file or directory\n", (char *)path->content, 'n');
		tmp = path;
		path = path->next;
		free(tmp->content);
		free(tmp);
	}
	print_output(&output);
	return (0);
}
