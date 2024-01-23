/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:32:20 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 18:22:00 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*unset name / names
	unsets values and attributes of variables and functions
	unset PATH HOME
	
*/

int	built_in_unset(char **cmd, t_tools *tools)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (cmd[i])
	{
		if (invalid_option(cmd[i]))
			return (2);
		if (!is_valid_var(cmd[i]))
			ret = err_msg("unset", cmd[i], " : not a valid identifier",
					EXIT_FAILURE);
		delete_variable(tools, cmd[i]);
		i++;
	}
	return (ret);
}

static void	free_node(t_env *tmp)
{
	free(tmp->k_eq_v);
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

static void	delete(t_env *tmp)
{
	t_env	*to_delete;
	t_env	*previous;

	to_delete = NULL;
	previous = tmp;
	to_delete = tmp->next;
	previous->next = tmp->next->next;
	to_delete->next = NULL;
	free_node(to_delete);
	to_delete = NULL;
}

void	delete_variable(t_tools *tools, char *key)
{
	t_env	*tmp;

	tmp = *(tools->chl_env);
	if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
	{
		*tools->chl_env = tmp->next;
		free_node(tmp);
		return ;
	}
	while (tmp)
	{
		if (tmp->next && !ft_strncmp(tmp->next->key, key, ft_strlen(key)))
		{
			delete (tmp);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	update_arr_env(tools);
}
