/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/26 20:35:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fmt_lnk(char *path, struct stat *stat)
{
	char	*buf;
	ssize_t	buff_size;

	if ((stat->st_mode & S_IFMT) != S_IFLNK)
	{
		ft_printf("\n");
		return ;
	}
	buff_size = stat->st_size + 1;
	if ((buf = ft_strnew(buff_size)) == NULL)
		return ;
	readlink(path, buf, buff_size);
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
	if (time(&now) - 15778458 > *t || now + 3600 < *t)
	{
		year = ft_strsub(tmp, 19, 10);
		ret = ft_strsub(tmp, 4, 7);
		tmp = year;
		year = ft_strtrim(year);
		free(tmp);
		tmp = ft_strdup(" ");
		ret = ft_strjoinfree(&ret, &tmp, 3);
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
	char	*tpath;

	fmt = flags->fmt;
	type = get_type(stat->st_mode);
	tpath = add_path(path, d_name);
	if ((ret = fmt_attr(tpath, stat->st_mode, type)) == NULL)
		return ;
	ft_printf("%s %*llu", ret, fmt->nlink, stat->st_nlink);
	free(ret);
	fmt_id(stat, fmt, type);
	if (flags->u == 'u')
		t = fmt_time(&(stat->st_atime));
	else
		t = fmt_time(&(stat->st_mtime));
	ft_printf("%s ", t);
	free(t);
	ft_printf("%s%s%s", get_lsclr(stat->st_mode), d_name, CDEF);
	fmt_lnk(tpath, stat);
	ft_strdel(&tpath);
}

void	fmt_id(struct stat *stat, t_fmt *fmt, char type)
{
	struct group	*gr;
	struct passwd	*pw;

	if ((pw = getpwuid(stat->st_uid)) == NULL)
		ft_printf(" %-*u", fmt->user, stat->st_uid);
	else
		ft_printf(" %-*s", fmt->user, pw->pw_name);
	if (type != 'b' && type != 'c'
		&& (gr = getgrgid(stat->st_gid)) == NULL)
		ft_printf("  %-*u  %*llu ", fmt->group, stat->st_gid,
				fmt->size, stat->st_size);
	else if (type != 'b' && type != 'c')
		ft_printf("  %-*s  %*llu ", fmt->group, gr->gr_name,
				fmt->size, stat->st_size);
	else if ((gr = getgrgid(stat->st_gid)) == NULL)
		ft_printf("  %-*u  %3u, %3u ", fmt->group, stat->st_gid,
				major(stat->st_rdev), minor(stat->st_rdev));
	else
		ft_printf("  %-*s  %3u, %3u ", fmt->group, gr->gr_name,
				major(stat->st_rdev), minor(stat->st_rdev));
}

char	*fmt_attr(char *path, mode_t mode, char type)
{
	char	*ret;

	if ((ret = ft_strnew(11)) == NULL)
		return (NULL);
	ret[0] = type;
	ret[1] = (mode & S_IRUSR) ? 'r' : '-';
	ret[2] = (mode & S_IWUSR) ? 'w' : '-';
	ret[3] = get_xattr(mode, 'u');
	ret[4] = (mode & S_IRGRP) ? 'r' : '-';
	ret[5] = (mode & S_IWGRP) ? 'w' : '-';
	ret[6] = get_xattr(mode, 'g');
	ret[7] = (mode & S_IROTH) ? 'r' : '-';
	ret[8] = (mode & S_IWOTH) ? 'w' : '-';
	ret[9] = get_xattr(mode, 'o');
	ret[10] = get_acl_attr(path);
	return (ret);
}
