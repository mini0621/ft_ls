/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 22:08:37 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/18 22:18:18 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstappend(t_list **alst, t_list **last, t_list *new)
{
	if (!alst)
		return ;
	if (*alst == NULL || !last || *last == NULL)
		return (ft_lstpushback(alst, new));
	(*last)->next = new;
}
