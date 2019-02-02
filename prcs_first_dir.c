/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_first_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:08:26 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/02 17:34:43 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	store_dpstat(char *path, DIR *dirp, t_list **files)
{
	struct dirent	*dp;
	struct stat		statbuff;
	char			*tmp;
	t_list			*new;
	t_file			*file;

	if (path == NULL)
	{
		closedir(dirp);
		return (-1);
	}
	while ((dp = readdir(dirp)) != NULL
			&& lstat((tmp = add_path(path, dp->d_name), &statbuff)) == 0)
	{
		if ((new = ft_lstnew(, sizeof(t_file *))))
			return (-1);
		ft_lstadd(files, new);
		add_output(path, dp->d_name, &statbuff, flags);
	}
	closedir(dirp);
	return (0);
}

int	store_dp(DIR *dirp, t_list **files)
{
	t_list	*new;
	struct dirent	*dp;


	while ((dp = readdir(dirp)) != NULL)
	{
		
		if ((new = ft_lstnew(dp->d_name, sizeof(char *))))
			return (-1);
		ft_lstadd(files, new);
	}
	return (0);
}

int	search_file(t_lsflags *flags, char *name, char **output)
{
	DIR		*dirp;
	struct dirent	*dp;

	if ((dirp = opendir(".")) == NULL)
		return (-1);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dp->d_name, name) == 0)
		{
			//TODO
			ft_printf("entry: %s\n", dp->d_name);
			return (0);
		}
	}
	closedir(dirp);
	return (-1);


}

struct dirent	*skip_hid_files(DIR *dirp, char a)
{
	struct dirent	*ret;

	if (a != 'a')
		return (readdir(dirp));
	while ((ret = readdir(dirp)) != NULL)
	{
		if (ret->d_name[0] != '.')
			return (ret);
	}
	return (NULL);
}

