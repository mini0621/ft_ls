/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/03 21:53:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	prcs_files_l(char *path, t_list **files, t_lsflags *flags, char **output)
{
	t_fmt	fmt;
	t_list	*cur;
	char	*tpath;
	struct stat	stat;

	if (files == NULL || *files == NULL)
		return ;
	//get name width
	get_fmt(*files, flags, &fmt);
	cur = *files;
	tpath = add_path(path, (char *)(cur->content));
	while (cur != NULL && tpath && lstat(tpath, &stat) == 0)
	{
		if ((stat.st_mode & S_IFMT) == S_IFDIR)
			fmt_dir((char *)(cur->content), &stat, flags);
		else if ((stat.st_mode & S_IFMT) == S_IFLNK)
			fmt_lnk(path, (char *)(cur->content), &stat, flags);
		else if ((stat.st_mode & S_IFMT) == S_IFREG)
			fmt_reg((char *)(cur->content), &stat, flags);
		cur = cur->next;
		ft_strdel(&tpath);
		tpath = add_path(path, (char *)(cur->content));
	}
}

//TODO
//for the long format
void	fmt_dir(char *d_name, struct stat *stat, t_lsflags *flags)
{
	ft_printf("check: %i, %s, %s, %s\n", stat->st_nlink,(getpwuid(stat->st_uid))->pw_name, (getgrgid(stat->st_gid))->gr_name, ctime(&(stat->st_mtime)));
}

void	fmt_lnk(char *path, char *d_name, struct stat *stat, t_lsflags *flags)
{
	char	*buf;
	ssize_t	buff_size;
	char	*tpath;

	tpath = add_path(path, d_name);
	buff_size = stat->st_size + 1;
	ft_printf("get the len of %u", buff_size);
	if ((buf = ft_strnew(buff_size)) == NULL)
		return ;
	readlink(tpath, buf, buff_size);
	ft_printf("link: %s\n", buf);
	free(buf);
	free(tpath);
	ft_printf("check: %i, %s, %s, %s\n", stat->st_nlink,(getpwuid(stat->st_uid))->pw_name, (getgrgid(stat->st_gid))->gr_name, ctime(&(stat->st_mtime)));
}

void	fmt_reg(char *d_name, struct stat *stat, t_lsflags *flags)
{
	char	*attr;

	if ((attr = fmt_attr(stat->st_mode, '-')) == NULL)
		return ;
	ft_printf("%s\t", attr);
	free(attr);
	ft_printf("check: %i, %s, %s, %s\n", stat->st_nlink,(getpwuid(stat->st_uid))->pw_name, (getgrgid(stat->st_gid))->gr_name, ctime(&(stat->st_mtime)));
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
