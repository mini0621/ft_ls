/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:32:41 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/12 22:24:17 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*p1;

	p1 = *alst;
	while (p1 != NULL)
	{
		del(p1->content, p1->content_size);
		*alst = p1->next;
		free(p1);
		p1 = *alst;
	}
	*alst = NULL;
}
