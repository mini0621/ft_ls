/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 01:07:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(char *path, t_list **files, t_lsflags *flags, char **output)
{
	t_list	*dirs;

	if (flags->rflag != 'y' && flags->cr == 'R')
		separate_dir(&dirs, files, path);
	else if (flags->rflag == 'y')
		duplicate_dir(&dirs, files, path);
	if (flags->l == 'l')
		prcs_files_l(path, files, flags, output);
	else
		prcs_files(files, flags, output, flags->fmt);
	print_output(output);
	if (flags->cr == 'R')
	{
		prcs_dirs(path, &dirs, flags, output);
		ft_lstdel(&dirs, &ft_ldel);
	}
	ft_lstdel(files, &ft_ldel);
	return (1);
}

void	prcs_dirs(char *path, t_list **dir, t_lsflags *flags, char **output)
{
	t_list	*tmp;
	char	*tpath;

	flags->rflag = 'y';
	while (*dir != NULL)
	{
		print_output(output);
		ft_printf("\n");
		tpath = add_path(path, ((t_file *)((*dir)->content)->d_name));
		if (manage_path(tpath, flags, output, 'n') == 2)
			print_error(NULL, ((t_file *)((*dir)->content)->d_name), 'n');
		tmp = *dir;
		free(tpath);
		*dir = (*dir)->next;
		ft_lstdelone(&tmp, &ft_ldel);
	}
	print_output(output);
}

void	prcs_files(t_list **files, t_lsflags *flags, char **output, t_fmt *fmt)
{
	t_list	*cur;
	int		mod;
	int		i;
	char	*tmp;

	if (files == NULL || *files == NULL)
		return ;
	cur = *files;;
	mod = 0;
	i = 0;
	while (mod < fmt->row)
	{
		if (cur == NULL)
		{
			i = 0;
			cur = *files;
			ft_asprintf(&tmp, "\n");
			*output = ft_strjoinfree(output, &tmp, 3);
			mod++;
		}
		if (i % fmt->row == mod)
		{
			ft_asprintf(&tmp, "%-*s", fmt->name, ((t_file *)(cur->content))->d_name);
			*output = ft_strjoinfree(output, &tmp, 3);
		}
		cur = cur->next;
		i++;
	}
}

t_list	*separate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*ptr;

	*dirs = NULL;
	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur != NULL)
	{
		if(ft_strcmp(((t_file *)(cur->content))->d_name, ".") != 0
			&& (((t_file *)(cur->content)).stat.st_mode & S_IFMT) == S_IFDIR)
		{
			ptr = cur;
			cur = cur->next;
			ptr = ft_lstsub(files, ptr);
			ft_lstpushback(dirs, ptr);
		}
		else
			cur = cur->next;
	}
	return (*dirs);
}

t_list	*duplicate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*ptr;

	*dirs = NULL;
	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	while (cur)
	{
		if(ft_strcmp(((t_file *)(cur->content))->d_name, ".") != 0
			&& (((t_file *)(cur->content)).stat.st_mode & S_IFMT) == S_IFDIR)
		{
			if ((ptr = ft_lstnew(cur->content, cur->content_size)) != NULL)
				ft_lstpushback(dirs, ptr);
		}
		cur = cur->next;
		ft_strdel(&tpath);
	}
	return (*dirs);
}

