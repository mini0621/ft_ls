/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:06:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/08 19:15:19 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_asprintf(char **ret, const char *fmt, ...)
{
	va_list		ap;
	char		*tmp;
	size_t		len;
	char		*start;

	if (ret == NULL || fmt == NULL)
		return (-1);
	va_start(ap, fmt);
	start = (char *)fmt;
	len = 0;
	tmp = NULL;
	if (*fmt == '\0')
		return (0);
	if ((start = join_chars(&tmp, start, &len)) == NULL)
		return (asprinterror(&tmp));
	while (*start != '\0')
	{
		if ((tmp = join_cnvrt(&tmp, &start, &ap, &len)) == NULL)
			return (-1);
		if ((start = join_chars(&tmp, start, &len)) == NULL)
			return (asprinterror(&tmp));
	}
	va_end(ap);
	*ret = tmp;
	return (len);
}

int		asprinterror(char **ret)
{
	ret = NULL;
	return (-1);
}
