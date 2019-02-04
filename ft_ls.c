/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 23:44:03 by mnishimo         ###   ########.fr       */
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
	if ((dirp = opendir(path)) == NULL)
		return (2);
	if (ft_strcmp(".", path) != 0)
	{
		ft_asprintf(&tmp, "%s:\n", path);
		*output = ft_strjoinfree(output, &tmp, 3);
	}
	if (store_dp(dirp, &files, &fmt, flags) < 0)
		return (2);
	sort_files(path, &files, flags);
	get_output(path, &files, flags, output);
	ft_lstdel(&files, &ft_ldel);
	closedir(dirp);
	return (0);
}

void	output_arg_files(t_list **path, char **output, t_lsflags *flags)
{
	t_list		*cur;
	t_list		*dir;
	struct stat	stat;
	t_fmt		fmt;

	fmt.len = 0;
	fmt.name = 0;
	dir = NULL;
	cur = *path;
	if (flags->d != 'd')
		separate_dir(&dir, path, NULL);
	if (flags->l == 'l')
	{
		get_fmt(*path, flags, &fmt);
		prcs_files_l(NULL, path, flags, output);
	}
	else
	{
		get_fmt_name(*path, flags, &fmt);
		prcs_files(path, flags, output, &fmt);
	}
	ft_lstdel(path, &ft_ldel);
	*path = dir;
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
	if (path == NULL)
		return (manage_path(".", &flags, &output));
	sort_files(NULL, &path, &flags);
	output_arg_files(&path, &output, &flags);
	while (path != NULL)
	{
		print_output(&output);
		ft_printf("\n");
		if (manage_path((char *)(path->content), &flags, &output) == 2)
			print_error("ft_ls: %s: No such file or directory\n", (char *)path->content, 'n');
		tmp = path;
		path = path->next;
		free(tmp->content);
		free(tmp);
	}
	print_output(&output);
	return (0);
}
