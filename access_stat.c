/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_stat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:38:20 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/07 19:05:27 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t		get_time(t_list *cur, t_lsflags *flags)
{
	if (flags->u == 'u')
		return (((t_file *)(cur->content))->stat.st_atime);
	return (((t_file *)(cur->content))->stat.st_mtime);
}
