/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:43:07 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/09 00:08:46 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h> 
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <string.h>
# include "libftprintf.h"

typedef struct	s_fmt
{
	size_t		nlink;
	size_t		user;
	size_t		group;
	size_t		size;
	size_t		name;
	int			row;
	int			len;
	blkcnt_t	blkcnt;
}				t_fmt;

typedef struct	s_lsflags
{
	t_fmt	*fmt;
	unsigned short	w_col;
	char	r;
	char	l;
	char	a;
	char	cr;
	char	t;
	char	f;
	char	d;
	char	u;
	char	n1;
	char	rflag;
}				t_lsflags;

typedef struct	s_file
{
	char		*d_name;
	struct stat	stat;
}				t_file;

int				manage_path(char *path, t_lsflags *flags, char c);
void			output_arg_files(t_list **path, t_lsflags *flags);
int	prcs_first_dir(t_list **path, t_lsflags *flags);

int				store_dp(char *path, DIR *dirp, t_list **files, t_lsflags *flags);
t_list	*get_newfile(t_list **files, t_list **last, char *path, char *d_name);
struct dirent	*skip_hid_files(DIR *dirp, char a);
int		add_homedir(char a, t_list **files);

t_list			*duplicate_dir(t_list **dirs, t_list **files);
t_list			*separate_dir(t_list **dirs, t_list **files, char *path);
void			prcs_files(t_list **dir, t_lsflags *flags, t_fmt *fmt);
void			prcs_dirs(char *path, t_list **dir, t_lsflags *flags);
int				get_output(char *path, t_list **files, t_lsflags *flags);

char 			solve_flagconf(t_lsflags *flags);
int 			store_flag(t_lsflags *flags, char c);
char			read_input(t_lsflags *flags, t_list **path, int argc, char **argv);
int				validate_input(t_list **path);
void    		init_flags(t_lsflags *flags);

char			*add_path(char *path, char *name);

void			prcs_files_l(char *path, t_list **files, t_lsflags *flags);
char			*fmt_time(time_t *t);
void			fmt_lnk(char *path, char *d_name, struct stat *stat);
void			fmt_reg(char *path, char *d_name, struct stat *stat, t_lsflags *flags);
char			*fmt_attr(mode_t mode, char type);

void			get_fmt_name(char *d_name, t_fmt *fmt);
void    		init_fmt(t_fmt *fmt);
void			get_fmt(t_list **files, t_fmt *fmt, t_lsflags *flags);
blkcnt_t		fmt_cmp(t_fmt *fmt, struct stat *stat);

void 			sort_files(t_list **files, t_lsflags *flags);
void			sort_by_name(t_list **files, char r);
void			sort_by_time(t_list **files, char r, t_lsflags *flags);
t_list			*insertion_sort(t_list **head, t_list *index, t_list **sorted, t_list *cur);
t_list			*sort_hid_files(t_list *files, t_list *sorted, t_list **cur);

int				print_error(char *message, char *ver, char usage);

time_t			get_time(t_list *cur, t_lsflags *flags);
char			get_xattr(mode_t mode, char c);
char			get_type(mode_t mode);

void			ft_ldel(void *ptr, size_t size);
void			ft_chardel(void *ptr, size_t size);
t_list			**re_list(t_list **path, t_fmt *fmt, t_lsflags *flags);
#endif
