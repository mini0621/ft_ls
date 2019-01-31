/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:41:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/01/31 21:21:44 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(void)
{
	DIR *dirp;
	struct dirent *dp;

	if ((dirp = opendir(".")) == NULL)
		return (0);
	while ((dp = readdir(dirp)) != NULL)
	{
		ft_printf("entry: %s\n", dp->d_name);
	}
	closedir(dirp);
	return (0);
}
