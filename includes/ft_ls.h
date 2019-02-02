/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:43:07 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/02 21:08:20 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h> 
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <string.h>
# include "libftprintf.h"

typedef struct	s_lsflags
{
	char	r;
	char	l;
	char	a;
	char	cr;
	char	t;
	char	f;
	char	d;
	char	u;
	char	n1;
}				t_lsflags;

typedef struct	s_fmt
{
	int link;
	int	user;
	int group;
	int	size;
	int	name;
	int	col;
}				t_fmt;

typedef struct	s_file
{
	char			*d_name;
	struct stat		*stat;
}				t_file;

int				manage_path(char **path, t_lsflags *flags, char **output);

int	store_dp(DIR *dirp, t_list **files);
int				search_file(t_lsflags *flags, char *name, char **output);
struct dirent	*skip_hid_files(DIR *dirp, char a);
int				prcs_f_flag(char *path, DIR *dirp, t_lsflags *flags, char **output);

void	*store_dir(t_list **dirs, t_list **files, t_list **cur, t_list *pre);
t_list	*separate_dir(t_list **dirs, t_list **files, char *path);
void	prcs_files(char *path, t_list **dir, t_lsflags *flags, char **output);
void	prcs_dirs(char *path, t_list **dir, t_lsflags *flags, char **output);
int	get_output(char *path, t_list **files, t_lsflags *flags, char **output);

char 			solve_flagconf(t_lsflags *flags);
int 			store_flag(t_lsflags *flags, char c);
char			read_input(t_lsflags *flags, t_list **path, int argc, char **argv);

char			*add_path(char *path, char *name);

void	prcs_files_l(char *path, t_list **files, t_lsflags *flags, char **output);
void	fmt_dir(char *d_name, struct stat *stat, t_lsflags *flags);
void	fmt_lnk(char *path, char *d_name, struct stat *stat, t_lsflags *flags);
void	fmt_reg(char *d_name, struct stat *stat, t_lsflags *flags);
char	*fmt_attr(mode_t mode, char type);

void	get_fmt(t_list	*files, t_lsflags *flags, t_fmt *fmt);

int				print_output(char **output);
int				print_error(char *message, char *ver, char usage);

void	ft_ldel(void *ptr, size_t size);
#endif
