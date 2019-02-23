/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:41:03 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/23 03:47:46 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_output(char *path, t_list **files, t_lsflags *flags)
{
	t_list	*dirs;

	dirs = NULL;
	if (flags->cr == 'R')
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

int		output_arg_files(t_list **path, t_lsflags *flags)
{
	t_list		*dir;

	dir = NULL;
	get_sym_dir(path);
	if (flags->d != 'd')
		separate_dir(&dir, path, NULL);
	if (*path == NULL)
	{
		*path = dir;
		return (0);
	}
	if (flags->l == 'l')
		prcs_files_l(NULL, path, flags);
	else
		prcs_files(path, flags, flags->fmt);
	ft_lstdel(path, &ft_ldel);
	*path = dir;
	return (1);
}

void	print_files_simple(t_list **files, t_lsflags *flags)
{
	t_list	*cur;

	cur = *files;
	if (flags->n1 == '1')
	{
		while (cur)
		{
			ft_printf("%s\n", ((t_file *)(cur->content))->d_name);
			cur = cur->next;
		}
	}
	else
	{
		while (cur)
		{
			ft_printf("%-*s", flags->fmt->name,
			((t_file *)(cur->content))->d_name);
			cur = cur->next;
		}
		ft_printf("\n");
	}
}

void	prcs_files(t_list **files, t_lsflags *flags, t_fmt *fmt)
{
	t_list	*cur;
	int		mod;
	int		i;

	get_fmt(files, fmt, flags);
	if (flags->n1 == '1' || fmt->row == 1)
		return (print_files_simple(files, flags));
	mod = 1;
	cur = *files;
	i = 0;
	while (mod <= fmt->row)
	{
		if (cur == NULL)
		{
			i = 0;
			cur = *files;
			mod++;
			ft_printf("\n");
		}
		if (i % fmt->row == mod - 1)
			ft_printf("%-*s", fmt->name, ((t_file *)(cur->content))->d_name);
		cur = cur->next;
		i++;
	}
}

void	prcs_files_l(char *path, t_list **files, t_lsflags *flags)
{
	t_list	*cur;
	t_file	*file;

	if (files == NULL || *files == NULL)
		return ;
	cur = *files;
	get_fmt(files, flags->fmt, flags);
	if (flags->fmt->blkcnt != -1)
		ft_printf("total %llu\n", flags->fmt->blkcnt);
	while (cur)
	{
		file = (t_file *)(cur->content);
		fmt_reg(path, file->d_name, &(file->stat), flags);
		cur = cur->next;
	}
}
