/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/31 22:27:14 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	manage_path(char **path, t_lsflags *flags, char **output)
{
	DIR				*dirp;
	t_list			*fils;
	struct dirent	*dp;

	if (flags->d == 'd' || (dirp = opendir(*path)) == NULL)
		return ((search_file(flags, *path, output)) ? -1 : 0);
	if ((dp = skip_hid_files(dirp, flags->a)) == NULL)
		return (0);
	if (flags->f == 'f')
		return (prcs_f_flag(dirp));
	//store_dp(dirp, &files);
	//sort_files(&files, flags);
	//get_output(files, flags, output);
	//ft_lstdel(&files, &ft_ldel);
	closedir(dirp);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lsflags	flags;
	t_list	*path;
	t_list	*tmp;
	char	*output;
	char	c;

	output = NULL;
	//argv can be either flags or a path(dir or file) "-a -l" as one arg is forbidden
	//if the path is not specified open with "." else, specify
	//path is allocated
	if ((c = read_input(&flags, &path, argc, argv)) !=  '\0')
		return (print_error("ft_ls: illegal option -- %s\n", &c, 'y'));
	//sort input
	//path->content is freeed if it is not error
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
