/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:11:16 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/01 17:48:37 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	print_error(char *message, char *ver, char usage)
{
	if (ver == NULL || message == NULL)
		return (0);
	ft_printf(message, ver);
	if (usage == 'y')
		ft_printf("usage: ft_ls [-Radflrtu1] [file ...]");
	return (0);
}

int	print_output(char **output)
{
	if (output == NULL || *output == NULL)
		return (0);
	ft_printf(*output);
	ft_strdel(output);
	return (0);
}
