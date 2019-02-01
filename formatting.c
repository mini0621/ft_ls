/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:20:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/01 19:21:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	add_output(char	*d_name, struct stat *stat, t_lsflags *flags)
{
	if ((stat->st_mode & S_IFMT) == S_IFDIR)
		fmt_dir(d_name, stat, flags);
 	else if ((stat->st_mode & S_IFMT) == S_IFLNK)
		fmt_lnk(d_name, stat, flags);
	else if ((stat->st_mode & S_IFMT) == S_IFREG)
		fmt_reg(d_name, stat, flags);
	else
		ft_printf("error: %s %u\n",d_name, stat->st_size);

	return(1);
}

void	fmt_dir(char *d_name, struct stat *stat, t_lsflags *flags)
{
	ft_printf("check: %i, %u, %u, %li\n", stat->st_nlink, stat->st_uid, stat->st_gid, stat->st_mtime);
}

void	fmt_lnk(char *d_name, struct stat *stat, t_lsflags *flags)
{
	ft_printf("check: %i, %u, %u, %li\n", stat->st_nlink, stat->st_uid, stat->st_gid, stat->st_mtime);

}

void	fmt_reg(char *d_name, struct stat *stat, t_lsflags *flags)
{
	ft_printf("check: %i, %u, %u, %li\n", stat->st_nlink, stat->st_uid, stat->st_gid, stat->st_mtime);

}
