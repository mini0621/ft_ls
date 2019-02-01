/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:43:07 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/01 19:20:59 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h> 
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
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

typedef struct	s_file
{
	struct dirent	*dp;
	struct stat		*stat;
}				t_file;

int				manage_path(char **path, t_lsflags *flags, char **output);

int				search_file(t_lsflags *flags, char *name, char **output);
struct dirent	*skip_hid_files(DIR *dirp, char a);
int				prcs_f_flag(char *path, DIR *dirp, t_lsflags *flags, char **output);

char 			solve_flagconf(t_lsflags *flags);
int 			store_flag(t_lsflags *flags, char c);
char			read_input(t_lsflags *flags, t_list **path, int argc, char **argv);

char			*add_path(char *path, char *name);

int				add_output(char	*d_name, struct stat *stat, t_lsflags *flags);
void	fmt_dir(char *d_name, struct stat *stat, t_lsflags *flags);
void	fmt_lnk(char *d_name, struct stat *stat, t_lsflags *flags);
void	fmt_reg(char *d_name, struct stat *stat, t_lsflags *flags);

int				print_output(char **output);
int				print_error(char *message, char *ver, char usage);

void			ft_ldel_char(t_list *path);
#endif
