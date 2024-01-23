/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:37:03 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:18:00 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no option

bool	is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!ft_strncmp(built_in[i++], cmd, ft_strlen(cmd) + 1))
			return (true);
	}
	return (false);
}

/*used to check if a avariable is valid to be export or not*/

bool	is_valid_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_strlen(var))
		return (false);
	if (var[i] == '\'' && var[i + 1] == '\0')
		return (false);
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_var_unset(char *var)
{
	int	i;

	i = 0;
	if (!ft_strlen(var))
		return (false);
	if (var[i] == '\'' && var[i + 1] == '\0')
		return (false);
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
