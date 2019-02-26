/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsflags.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:32:31 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/26 23:30:30 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		store_flag(t_lsflags *flags, char c)
{
	if (c == '1' && flags->l == 'l')
		flags->l = '\0';
	if (c == 'a')
		flags->a = 'a';
	else if (c == 'l')
		flags->l = 'l';
	else if (c == 'r')
		flags->r = 'r';
	else if (c == 'R')
		flags->cr = 'R';
	else if (c == 't')
		flags->t = 't';
	else if (c == 'f')
		flags->f = 'f';
	else if (c == 'd')
		flags->d = 'd';
	else if (c == 'u')
		flags->u = 'u';
	else if (c == '1')
		flags->n1 = '1';
	else
		return (-1);
	return (0);
}

char	solve_flagconf(t_lsflags *flags)
{
	struct winsize	w;

	if (flags->f == 'f')
		flags->a = 'a';
	if (flags->d == 'd')
		flags->cr = '\0';
	if (flags->n1 != '1' && flags->l != 'l')
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		flags->w_col = w.ws_col;
		if (w.ws_col == 0)
			flags->w_col = 1;
	}
	return ('\0');
}

void	init_flags(t_lsflags *flags)
{
	flags->a = '\0';
	flags->l = '\0';
	flags->r = '\0';
	flags->t = '\0';
	flags->cr = '\0';
	flags->f = '\0';
	flags->d = '\0';
	flags->u = '\0';
	flags->n1 = '\0';
	flags->rflag = '\0';
	flags->w_col = 0;
}
