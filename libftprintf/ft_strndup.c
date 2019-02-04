/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:15:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 18:28:06 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*ptr;

	if ((ptr = ft_memalloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_strncpy(ptr, s1, size);
	return (ptr);
}
