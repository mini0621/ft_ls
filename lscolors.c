/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lscolors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:14:56 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/26 20:36:01 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_lsclr(mode_t mode)
{
	char	type;

	type = get_type(mode);
	if (type == 'd' && (mode & S_IWOTH) && mode & S_ISVTX)
		return (CDWS);
	else if (type == 'd')
		return ((mode & S_IWOTH) ? CDWOS : CDIR);
	else if (type == 's')
		return (CSOC);
	else if (type == 'p')
		return (CPIP);
	else if (type == 'l')
		return (CSYM);
	else if (type == 'b')
		return (CBLK);
	else if (type == 'c')
		return (CCHA);
	else if (type == '-' && get_xattr(mode, 'u') == 's')
		return (CXUI);
	else if (type == '-' && get_xattr(mode, 'g') == 's')
		return (CXGI);
	return (type == '-' && (get_xattr(mode, 'u') == 'x'
		|| get_xattr(mode, 'g') == 'x' || get_xattr(mode, 'o') == 'x')
		? CEXE : CDEF);
}
