/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/02 19:17:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(char *path, t_list **files, t_lsflags *flags, char **output)
{
	t_list	*dirs;
	//TODO for R
	if (flags->cr == 'R')
		dirs = separate_dirs(&dirs, files, path);
	if (flags->l == 'l')
		prcs_files_l(path, *files, flags, output);
	else
		prcs_files(path, *files, flags, output);
	//output?
	if (flags->cr == 'R')
		prcs_dirs(path, *files, flags, output);
	return (1);
}

void	prcs_dirs(char *path, t_list **dir, t_lsflags *flags, char **output)
{

}

void	prcs_files(char *path, t_list **dir, t_lsflags *flags, char **output)
{
	t_fmt	fmt;
	t_list	*cur;
	char	*tpath;
	struct stat	stat;

	if (files == NULL || *files == NULL)
		return (0);
	//TODO
	fmt = get_fmt_name(*files, flags);
	cur = *files;
	while (cur != NULL)
	{
		ft_printf("%*s", w, (char *)(cur->content));
		cur = cur->next;
	}
	return(0);
}
}
t_list	*separate_dir(t_list **dirs, t_list **files, char *path)
{
	t_list	*cur;
	t_list	*pre;
	char	*tpath;
	struct stat	sttbuff;

	if (files == NULL || *files == NULL)
		return (NULL);
	cur = *files;
	pre = cur;
	tpath = add_path(path, (char *)(cur->content));
	while (cur && tpath && lstat(tpath, &sttbuff) == 0)
	{
		if ((sttbuff.st_mode & S_IFMT) == S_IFDIR)
			store_dir(dirs, files, cur);
		pre = cur;
		if (cur != *files)
			cur = cur->next;
		ft_strdel(tpath);
		tpath = add_path(path, (char *)(cur->content));
	}
	return (*dirs);
}

void	*store_dir(t_list **dirs, t_list **files, t_list **cur, t_list *pre)
{
	t_list	*dir;

	if (*cur == *files)
	{
		*files = cur->next;
		dir = *cur;
		*cur = (*cur)->next;
	}
	else
		dir = ft_lstsub(pre, cur);
	dir->next = NULL;
	ft_lstadd(dirs, dir);
}
