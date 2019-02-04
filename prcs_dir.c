/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 23:44:06 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(char *path, t_list **files, t_lsflags *flags, char **output)
{
	t_list	*dirs;

	
	//TODO for R
	if (flags->cr == 'R')
		separate_dir(&dirs, files, path);
	if (flags->l == 'l')
		prcs_files_l(path, files, flags, output);
	else
		prcs_files(files, flags, output, flags->fmt);
	//output?
	print_output(output);
	if (flags->cr == 'R')
		prcs_dirs(path, files, flags, output);
	return (1);
}

void	prcs_dirs(char *path, t_list **dir, t_lsflags *flags, char **output)
{

}

void	prcs_files(t_list **files, t_lsflags *flags, char **output, t_fmt *fmt)
{
	t_list	*cur;
	int		mod;
	int		i;
	char	*tmp;

	if (files == NULL || *files == NULL)
		return ;
	get_fmt_name(*files, flags, fmt);
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
			ft_asprintf(&tmp, "%-*s", fmt->name, (char *)(cur->content));
			*output = ft_strjoinfree(output, &tmp, 3);
		}
		cur = cur->next;
		i++;
	}
}

t_list	*separate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*pre;
	t_list	*last;
	char	*tpath;
	struct stat	sttbuff;

	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	last = NULL;
	while (cur != NULL && (tpath = add_path(path, (char *)(cur->content))) != NULL
		&& lstat(tpath, &sttbuff) == 0)
	
	{
		if (last == NULL)
			*dirs = store_dir(((sttbuff.st_mode & S_IFMT) == S_IFDIR), files, &cur, &pre);
		else
			last->next = store_dir(((sttbuff.st_mode & S_IFMT) == S_IFDIR), files, &cur, &pre);
		if (*dirs != NULL)
			last = *dirs;
		if (last != NULL && last->next != NULL)
			last = last->next;
		ft_strdel(&tpath);
	}
	return (*dirs);
}

t_list	*store_dir(int d, t_list **files, t_list **cur, t_list **pre)
{
	t_list	*dir;
	if (d == 0)
	{
		*pre = *cur;
		*cur = (*cur)->next;
		return (NULL);
	}
	if (*cur == *files)
	{
		*files = (*cur)->next;
		dir = *cur;
	}
	else
		dir = ft_lstsub(*pre, cur);
	*pre = *cur;
	*cur = (*cur)->next;
	dir->next = NULL;
	return (dir);
}
