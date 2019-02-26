/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/26 23:34:41 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	prcs_dirs(char *path, t_list **dir, t_lsflags *flags)
{
	t_list	*tmp;
	char	*tpath;

	flags->rflag = 'y';
	while (*dir != NULL)
	{
		ft_printf("\n");
		tpath = add_path(path, (((t_file *)((*dir)->content))->d_name));
		if (manage_path(tpath, flags, 'n') == 2)
			print_error(NULL, (((t_file *)((*dir)->content))->d_name), 'n');
		tmp = *dir;
		free(tpath);
		*dir = (*dir)->next;
		ft_lstdelone(&tmp, &ft_ldel);
	}
}

void	get_sym_dir(t_list *lst)
{
	char		*buff;
	ssize_t		buff_size;
	struct stat	*stat;
	struct stat	tmp;

	if (lst == NULL)
		return ;
	stat = &(((t_file *)(lst->content))->stat);
	buff_size = stat->st_size + 1;
	if ((buff = ft_strnew(buff_size)) == NULL)
		return ;
	readlink(((t_file *)(lst->content))->d_name, buff, buff_size);
	lstat(buff, &tmp);
	if (get_type(tmp.st_mode) == 'd')
	{
		free(((t_file *)(lst->content))->d_name);
		((t_file *)(lst->content))->d_name = buff;
		ft_memcpy(stat, &tmp, sizeof(struct stat));
	}
	else
		free(buff);
}

int		prcs_first_dir(t_list **path, t_lsflags *flags)
{
	t_fmt	fmt;

	sort_inputs(path, flags->r);
	if (*path == NULL && flags->d != 'd')
		return (manage_path(".", flags, 'y'));
	init_fmt(&fmt);
	flags->fmt = &fmt;
	if (flags->d == 'd' && flags->l == 'l' && *path == NULL)
	{
		get_newfile(path, path, ".", ".");
		prcs_files_l(NULL, path, flags);
		ft_lstdel(path, &ft_ldel);
		return (0);
	}
	if (flags->d == 'd' && *path == NULL)
	{
		ft_printf("%s.%s\n", CDIR, CDEF);
		return (0);
	}
	sort_files(re_list(path, &fmt, flags), flags);
	if (output_arg_files(path, flags) == 0)
		return (-1);
	if (*path != NULL)
		ft_printf("\n");
	return ((*path == NULL) ? 0 : 1);
}

t_list	*separate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*ptr;
	t_list	*last;
	t_file	*file;

	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur != NULL)
	{
		file = (t_file *)(cur->content);
		if ((!path || (ft_strcmp(file->d_name, ".") != 0
			&& ft_strcmp(file->d_name, "..") != 0))
			&& (file->stat.st_mode & S_IFMT) == S_IFDIR)
		{
			ptr = cur;
			cur = cur->next;
			ptr = ft_lstsub(files, ptr);
			ft_lstappend(dirs, &last, ptr);
			last = ptr;
		}
		else
			cur = cur->next;
	}
	return (*dirs);
}

t_list	*duplicate_dir(t_list **dirs, t_list **files)
{
	t_list	*cur;
	t_list	*ptr;
	t_list	*last;
	t_file	*file;

	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur)
	{
		file = (t_file *)(cur->content);
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, "..")
			&& (file->stat.st_mode & S_IFMT) == S_IFDIR)
		{
			if ((ptr = ft_lstnew(cur->content, cur->content_size)) != NULL)
			{
				file = (t_file *)(ptr->content);
				file->d_name = ft_strdup(file->d_name);
				ft_lstappend(dirs, &last, ptr);
				last = ptr;
			}
		}
		cur = cur->next;
	}
	return (*dirs);
}
