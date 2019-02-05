/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:02:14 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/05 16:41:50 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*current;

	if (alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	current = *alst;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = new;
}
