/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_first_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:08:26 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/04 19:11:23 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	store_dp(DIR *dirp, t_list **files, t_fmt *fmt, t_lsflags *flags)
{
	t_list			*new;
	struct dirent	*dp;
	t_list			*last;
	int				len;
	size_t			name;

	*files = NULL;
	len = 0;
	name = 0;
	while ((dp = skip_hid_files(dirp, flags->a)) != NULL)
	{
		if (!(new = ft_lstnew(dp->d_name, sizeof(char) * (ft_strlen(dp->d_name) + 1))))
			return (-1);
		if (*files == NULL)
			*files = new;
		else
			last->next = new;
		last = new;
		if (new->content_size > name)
			name = new->content_size;
		len++;
	}
	fmt->name = name;
	fmt->len = len;
	return (0);
}

int	search_file(t_lsflags *flags, char *name, char **output)
{
	DIR		*dirp;
	struct dirent	*dp;
	char			*path;
	int				i;

	i = ft_strlen(name) - 1;
	while (i > -1 && name[i] != '/')
		i--;
	if (i == -1)
		path = strdup(".");
	else
		path = strndup(name, i + 1);
	ft_printf("created path is %s i is %i name s %s\n",path, i, name);
	if ((dirp = opendir(path)) == NULL)
		return (-1);
	free(path);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dp->d_name, name) == 0)
		{
			ft_printf("%s\n", dp->d_name);
			return (0);
		}
	}
	closedir(dirp);
	return (-1);
}

struct dirent	*skip_hid_files(DIR *dirp, char a)
{
	struct dirent	*ret;

	if (a == 'a')
		return (readdir(dirp));
	while ((ret = readdir(dirp)) != NULL)
	{
		if (ret->d_name[0] != '.')
			return (ret);
	}
	return (NULL);
}

