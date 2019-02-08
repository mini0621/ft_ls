/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 19:51:23 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	prcs_files_l(char *path, t_list **files, t_lsflags *flags)
{
	t_list	*cur;

	if (files == NULL || *files == NULL)
		return ;
	get_fmt(files, flags->fmt, flags);
	if (flags->fmt->blkcnt != -1)
		ft_printf("total %llu\n", flags->fmt->blkcnt);
	cur = *files;
	while (cur)
		fmt_reg(path, ((t_file *)(cur->content))->d_name, &(((t_file *)(cur->content))->stat), flags);
}

void	fmt_lnk(char *path, char *d_name, struct stat *stat)
{
	char	*buf;
	ssize_t	buff_size;
	char	*tmp;
	
	if ((stat->st_mode & S_IFMT) != S_IFLNK)
	{
		ft_printf("\n");
		return ;
	}
	tmp = add_path(path, d_name);
	buff_size = stat->st_size + 1;
	if ((buf = ft_strnew(buff_size)) == NULL)
		return ;
	readlink(tmp, buf, buff_size);
	ft_strdel(&tmp);
	ft_printf(" -> %s\n", buf);
	ft_strdel(&buf);
}

void	fmt_reg(char *path, char *d_name, struct stat *stat, t_lsflags *flags)
{
	char	type;
	char	*ret;
	t_fmt	*fmt;

	fmt = flags->fmt;
	type =  ((stat->st_mode & S_IFMT) == S_IFDIR) ? 'd' : '-';
	if ((stat->st_mode & S_IFMT) == S_IFLNK)
		type = 'l';
	if ((ret = fmt_attr(stat->st_mode, type)) == NULL)
		return ;
	ft_printf("%s %*llu %-*s  %-*s  %*llu ", ret, fmt->nlink, stat->st_nlink, fmt->user, (getpwuid(stat->st_uid))->pw_name, fmt->group, (getgrgid(stat->st_gid))->gr_name, fmt->size, stat->st_size);
	ft_printf(" %*s", fmt->name, d_name);
	free(ret);
	fmt_lnk(path, d_name, stat);
}


char	*fmt_attr(mode_t mode, char type)
{
	char	*ret;

	if ((ret = ft_strnew(11)) == NULL)
		return (NULL);
	ret[0] = type;
	ret[1] = ((mode & S_IRUSR) && (mode & S_IREAD)) ? 'r': '-';
	ret[2] = ((mode & S_IWUSR) && (mode & S_IWRITE)) ? 'w': '-';
	ret[3] = ((mode & S_IXUSR) && (mode & S_IEXEC)) ? 'x': '-';
	ret[4] = ((mode & S_IRGRP) && (mode & S_IREAD)) ? 'r': '-';
	ret[5] = ((mode & S_IWGRP) && (mode & S_IWRITE)) ? 'w': '-';
	ret[6] = ((mode & S_IXGRP) && (mode & S_IEXEC)) ? 'x': '-';
	ret[7] = ((mode & S_IROTH) && (mode & S_IREAD)) ? 'r': '-';
	ret[8] = ((mode & S_IWOTH) && (mode & S_IWRITE)) ? 'w': '-';
	ret[9] = ((mode & S_IXOTH) && (mode & S_IEXEC)) ? 'x': '-';
	ret[10] = ' ';
	return (ret);
}
