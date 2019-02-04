/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:27:39 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 00:24:11 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(char *path, t_list **files, t_lsflags *flags, char **output)
{
	t_list	*dirs;

	if (flags->a == 'a')
		ft_lstadd(files, ft_lstnew(".", 2));
	//TODO for R
	if (flags->cr == 'R')
		separate_dir(&dirs, files, path);
	if (flags->l == 'l')
		prcs_files_l(path, files, flags, output);
	else
		prcs_files(files, flags, output, flags->fmt);
	//output?
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
			ft_printf("\n");
			mod++;
		}
		if (i % fmt->row == mod)
			ft_printf("%-*s", fmt->name + 1, (char *)(cur->content));
		cur = cur->next;
		i++;
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
			store_dir(dirs, files, &cur, pre);
		pre = cur;
		if (cur != *files)
			cur = cur->next;
		ft_strdel(&tpath);
		tpath = add_path(path, (char *)(cur->content));
	}
	return (*dirs);
}

void	store_dir(t_list **dirs, t_list **files, t_list **cur, t_list *pre)
{
	t_list	*dir;

	if (*cur == *files)
	{
		*files = (*cur)->next;
		dir = *cur;
		*cur = (*cur)->next;
	}
	else
		dir = ft_lstsub(pre, cur);
	dir->next = NULL;
	ft_lstadd(dirs, dir);
}
