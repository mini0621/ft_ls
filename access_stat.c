/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:38:20 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 17:34:17 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t		get_time(char *path, char *name, t_lsflags *flags)
{
	char		*tpath;
	struct stat	sttbuff;

	tpath = add_path(path, name);
	if (lstat(tpath, &sttbuff) != 0)
		return (-1);
	free(tpath);
	if (flags->u == 'u')
		return (sttbuff.st_atime);
	return (sttbuff.st_mtime);
}
