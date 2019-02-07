/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:45:28 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 21:50:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	manage_path(char *path, t_lsflags *flags, char **output, char c)
{
	DIR				*dirp;
	t_list			*files;
	t_fmt			fmt;
	char			*tmp;

	files = NULL;
	if ((dirp = opendir(path)) == NULL)
		return (2);
	if (c == 'n' && ft_strcmp(".", path) != 0)
	{
		ft_asprintf(&tmp, "%s:\n", path);
		*output = ft_strjoinfree(output, &tmp, 3);
	}
	flags->fmt = &fmt;
	init_fmt(&fmt);
	if (store_dp(path, dirp, &files, flags) < 0)
		return (2);
	sort_files(path, &files, flags);
	get_output(path, &files, flags, output);
	closedir(dirp);
	return (0);
}

void	output_arg_files(t_list **path, char **output, t_lsflags *flags)
{
	t_list		*cur;
	t_list		*dir;

	dir = NULL;
	cur = *path;
	if (flags->d != 'd')
		separate_dir(&dir, path, NULL);
	if (flags->l == 'l')
		prcs_files_l(NULL, path, flags, output);
	else
		prcs_files(path, flags, output, flags->fmt);
	ft_lstdel(path, &ft_chardel);
	*path = dir;
}

int	prcs_first_dir(t_list **path, t_lsflags *flags, char **output)
{
	char	*tmp;
	t_fmt	fmt;

	if (path == NULL)
		return (0);
	if (*path == NULL && flags->d != 'd')
		return (manage_path(".", flags, output, 'y'));
	init_fmt(&fmt);
	if (flags->d == 'd' && flags->l == 'l' && *path == NULL)
	{
		get_newfile(path, NULL, ".", ".");
		get_output(NULL, path, flags, output);
		print_output(output);
		ft_lstdel(path, &ft_ldel);
		return (0);
	}
	if (flags->d == 'd' && *path == NULL)
	{
		ft_asprintf(&tmp, ".\n");
		*output = ft_strjoinfree(output, &tmp, 3);
		return (0);
	}
	sort_files(NULL, re_list(path, &fmt, flags), flags);
	flags->fmt = &fmt;
	output_arg_files(path, output, flags);
	return (1);
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
	if (validate_input(&path) < 0 || prcs_first_dir(&path, &flags, &output) == 0)
		return (0);
	c = (path != NULL && path->next == NULL) ? 'y' : 'n';
	while (path != NULL)
	{
		print_output(&output);
		if (manage_path(((t_file *)(path->content))->d_name, &flags, &output, c) == 2)
			print_error(NULL, (char *)path->content, 'n');
		tmp = path;
		path = path->next;
		ft_lstdelone(&tmp, &ft_ldel);
		if (path != NULL)
			ft_printf("\n");
	}
	print_output(&output);
	return (0);
}
