/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:53:50 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 18:37:19 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*cd * [bonus] est sense acceder dans le dossier s'il y a un seul, 
	sinon; too many args
	no such file or directory*/

static int	update_vars(t_env **chl_env)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	buffer[PATH_MAX];
	char	*tmp;
	char	*cwd;

	pwd = get_env_variable(chl_env, "PWD");
	oldpwd = get_env_variable(chl_env, "OLDPWD");
	if (oldpwd && pwd)
	{
		tmp = oldpwd->value;
		oldpwd->value = ft_strdup(pwd->value);
		free(tmp);
	}
	if (pwd)
	{
		cwd = getcwd(buffer, PATH_MAX);
		if (!cwd)
			return (err_msg_cmd("getcwd", strerror(errno), EXIT_FAILURE));
		tmp = pwd->value;
		pwd->value = ft_strdup(cwd);
		free(tmp);
	}
	return (0);
}

int	change_directory(char *path, t_env **chl_env)
{
	if (chdir(path) == 0)
		return (update_vars(chl_env));
	else
		return (err_msg_cmd(path, strerror(errno), 1));
}

static int	cd_oldpwd(t_env **chl_env)
{
	char	*path;
	t_env	*var;

	path = NULL;
	var = get_env_variable(chl_env, "OLDPWD");
	if (!var)
		return (err_msg_cmd("cd", "OLDPWD not set", EXIT_FAILURE));
	path = var->value;
	return (change_directory(path, chl_env));
}

static int	cd_home(t_env **chl_env)
{
	char	*path;
	t_env	*var;

	path = NULL;
	var = get_env_variable(chl_env, "HOME");
	if (!var)
		return (err_msg_cmd("cd", "HOME not set", EXIT_FAILURE));
	path = var->value;
	return (change_directory(path, chl_env));
}

int	built_in_cd(char **cmd_args, t_env **chl_env)
{
	int	ret;

	ret = invalid_option(cmd_args[1]);
	if (ret)
		return (ret);
	if (!cmd_args[1] || ft_isspace(cmd_args[1][0]) || cmd_args[1][0] == '\0'
		|| ft_strncmp(cmd_args[1], "--", 3) == 0 || !ft_strncmp(cmd_args[1],
			"~", 1) || !ft_strncmp(cmd_args[1], "--", 3))
		return (cd_home(chl_env));
	if (cmd_args[2])
		return (err_msg_cmd("cd", "too many arguments", EXIT_FAILURE));
	if (!ft_strncmp(cmd_args[1], "-", 2))
		return (cd_oldpwd(chl_env));
	return (change_directory(cmd_args[1], chl_env));
}
