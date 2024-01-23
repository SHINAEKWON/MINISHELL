/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:06:01 by anouri            #+#    #+#             */
/*   Updated: 2023/12/01 19:14:29 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*takes the char **environment
	returmns env var : PATH if it exists
	returns NULL if not*/

char	*get_variable_path(char **arr_env)
{
	char	*all_path;
	char	*path;
	int		i;
	int		len;

	path = NULL;
	i = 0;
	while (arr_env[i] != NULL)
	{
		if (ft_strnstr(arr_env[i], "PATH", 4))
		{
			all_path = arr_env[i];
			break ;
		}
		i++;
	}
	if (!arr_env[i])
		return (NULL);
	len = ft_strlen(all_path);
	path = ft_substr(all_path, 5, len);
	return (path);
}

char	*get_path_classic(char **cmd_args, char **path_split)
{
	char	*temp;
	char	*bin;
	int		i;

	temp = NULL;
	bin = NULL;
	i = 0;
	while (path_split[i])
	{
		temp = ft_strjoin(path_split[i], "/");
		bin = ft_strjoin(temp, cmd_args[0]);
		free(temp);
		if (access(bin, F_OK | X_OK) == 0)
		{
			free_table(path_split);
			return (bin);
			break ;
		}
		free(bin);
		i++;
	}
	free_table(path_split);
	return (NULL);
}

/*returns absolute path of the command*/
/*
	cmd_path = cmd_args[0] if it is in absolute path
	cmd_path = NULL if PATH is unset and cmd_args[0] is not absolute path
	cmd_args = NULL if command does not exist
	cmd_path = binary if variable PATH is found
*/
char	*get_absolute_path(char **cmd_args, t_tools *tools)
{
	char	*path;
	char	**path_split;

	if (cmd_args[0][0] == '/' || !ft_strncmp(cmd_args[0], "./", 2))
		return (ft_strdup(cmd_args[0]));
	if (tools->ig_env)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	else
		path = get_variable_path(tools->arr_env);
	if (path == NULL)
		return (ft_strdup(cmd_args[0]));
	else
	{
		path_split = NULL;
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		return (get_path_classic(cmd_args, path_split));
	}
}
