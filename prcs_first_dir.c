/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_first_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 22:08:26 by mnishimo          #+#    #+#             */
/*   Updated: 2019/02/01 18:48:54 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_output(t_list **files, t_lsflags *flags, char **output)
{
	//TODO
	return (1);	
}

int	prcs_f_flag(char *path, DIR *dirp, t_lsflags *flags, char **output)
{
	struct dirent	*dp;
	struct stat		statbuff;
	char			*tmp;

	if (path == NULL)
	{
		closedir(dirp);
		return (-1);
	}
	while ((dp = readdir(dirp)) != NULL && lstat(dp->d_name, &statbuff) == 0)
	{
		//read stat and check if it is dir or link
		//depending all of these print all of them
		add_output(dp->d_name, &statbuff, flags);
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
		if ((new = ft_lstnew(dp, sizeof(struct dirent *))))
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

