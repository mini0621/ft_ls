/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 22:43:29 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(char *path, t_list **files, t_lsflags *flags)
{
	t_list	*dirs;

	dirs = NULL;
	if (flags->rflag != 'y' && flags->cr == 'R')
		separate_dir(&dirs, files, path);
	else if (flags->rflag == 'y')
		duplicate_dir(&dirs, files);
	if (flags->l == 'l')
		prcs_files_l(path, files, flags);
	else
		prcs_files(files, flags, flags->fmt);
	ft_lstdel(files, &ft_ldel);
	if (flags->cr == 'R')
		prcs_dirs(path, &dirs, flags);
	return (1);
}

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

void	prcs_files(t_list **files, t_lsflags *flags, t_fmt *fmt)
{
	t_list	*cur;
	int		mod;
	int		i;
	char	*tmp;

	if (files == NULL || *files == NULL)
		return ;
	get_fmt(files, fmt, flags);
	cur = *files;;
	mod = 0;
	i = 0;
	while (mod < fmt->row)
	{
		if (cur == NULL)
		{
			i = 0;
			ft_printf("\n");
			cur = *files;
			mod++;
		}
		if (i % fmt->row == mod)
			ft_printf("%-*s", fmt->name, ((t_file *)(cur->content))->d_name);
		cur = cur->next;
		i++;
	}
}

t_list	*separate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*ptr;
	t_list	*last;

	*dirs = NULL;
	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur != NULL)
	{
		if((path == NULL || (ft_strcmp(((t_file *)(cur->content))->d_name, ".") != 0
					&& ft_strcmp(((t_file *)(cur->content))->d_name, "..") != 0))
				&& (((t_file *)(cur->content))->stat.st_mode & S_IFMT) == S_IFDIR)
		{
			ptr = cur;
			cur = cur->next;
			ptr = ft_lstsub(files, ptr);
			if (*dirs == NULL)
				*dirs = ptr;
			else
				last->next = ptr;
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

	*dirs = NULL;
	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur)
	{
		if((ft_strcmp(((t_file *)(cur->content))->d_name, ".") != 0
					&& ft_strcmp(((t_file *)(cur->content))->d_name, "..") != 0)
				&& (((t_file *)(cur->content))->stat.st_mode & S_IFMT) == S_IFDIR)
		{
			if ((ptr = ft_lstnew(cur->content, cur->content_size)) != NULL)
			{
				((t_file *)(ptr->content))->d_name = strdup(((t_file *)(ptr->content))->d_name);
				if (*dirs == NULL)
					*dirs = ptr;
				else
					last->next = ptr;
				last = ptr;
			}
		}
		cur = cur->next;
	}
	return (*dirs);
}
