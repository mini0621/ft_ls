/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:43:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/02 18:34:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_list	*ft_lstsub(t_list *before, t_list **cur)
{
	t_list	*ptr;

	if (!cur || *cur == NULL)
		return (NULL);
	before->next = (*cur)->next;
	(*cur)->next = NULL;
	ptr = *cur;
	*cur = before;
	ptr->next = NULL;
	return (ptr);
}
