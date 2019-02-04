/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:01:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 22:51:31 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_fmt_name(t_list	*files, t_lsflags *flags, t_fmt *fmt)
{
	struct winsize	w;
	t_list			*cur;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (fmt->len == 0 || fmt->name == 0)
	{
		cur = files;
		while (cur != NULL)
		{
			if (cur->content_size > fmt->name)
				fmt->name = cur->content_size;
			fmt->len += 1;
			cur = cur->next;
		}
	}
	fmt->row = 1 + fmt->len / (w.ws_col / fmt->name);
}

void	get_fmt(t_list	*files, t_lsflags *flags, t_fmt *fmt)
{

}
