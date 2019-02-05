/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:43:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/05 16:47:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstsub(t_list **alst, t_list *cur)
{
	t_list	*ptr;

	if (!cur || alst == NULL|| *alst == NULL)
		return (NULL);
	if (*alst == cur)
	{
		*alst = cur->next;
		cur->next = NULL;
		return (cur);
	}
	ptr = *alst;
	while (ptr->next != cur)
		ptr = ptr->next;
	if (ptr == NULL)
		return (NULL);
	ptr->next = cur->next;
	cur->next = NULL;
	return (cur);
}
