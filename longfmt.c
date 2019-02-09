/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/09 00:08:03 by mnishimo         ###   ########.fr       */
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
	{
		fmt_reg(path, ((t_file *)(cur->content))->d_name, &(((t_file *)(cur->content))->stat), flags);
		cur = cur->next;
	}
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

char	*fmt_time(time_t *t)
{
	char	*ret;
	char	*year;
	char	*tmp;
	time_t	now;

	tmp = ctime(t);
	if (time(NULL) - 2592000 > *t)
	{
		year = ft_strsub(tmp, 19, 5);
		ret = ft_strsub(tmp, 4, 7);
		ret = ft_strjoinfree(&ret, &year, 3);
	}
	else
		ret = ft_strsub(tmp, 4, 12);
	return (ret);
}

void	fmt_reg(char *path, char *d_name, struct stat *stat, t_lsflags *flags)
{
	char	type;
	char	*ret;
	t_fmt	*fmt;
	char	*t;

	fmt = flags->fmt;
	type =  get_type(stat->st_mode);
	if ((ret = fmt_attr(stat->st_mode, type)) == NULL)
		return ;
	ft_printf("%s %*llu %-*s  %-*s  %*llu ", ret, fmt->nlink, stat->st_nlink, fmt->user, (getpwuid(stat->st_uid))->pw_name, fmt->group, (getgrgid(stat->st_gid))->gr_name, fmt->size, stat->st_size);
	free(ret);
	t = fmt_time(&(stat->st_mtime));
	ft_printf("%s ", t);
	free(t);
	ft_printf("%s", d_name);
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
	ret[3] = get_xattr(mode, 'u');
	ret[4] = ((mode & S_IRGRP) && (mode & S_IREAD)) ? 'r': '-';
	ret[5] = ((mode & S_IWGRP) && (mode & S_IWRITE)) ? 'w': '-';
	ret[6] = get_xattr(mode, 'g');
	ret[7] = ((mode & S_IROTH) && (mode & S_IREAD)) ? 'r': '-';
	ret[8] = ((mode & S_IWOTH) && (mode & S_IWRITE)) ? 'w': '-';
	ret[9] = get_xattr(mode, 'o');
	ret[10] = ' ';
	return (ret);
}
