/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:43:47 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/31 22:26:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ldel(void *ptr, size_t size)
{
	if (size == sizeof(char *))
		free((char *)ptr);
	else
		free((t_file *)ptr);
}
