/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:53:44 by anouri            #+#    #+#             */
/*   Updated: 2023/11/30 16:42:37 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*copies the key=value details to a node of type t_env *   */

static void	copy_to_node(t_env *node, char *env_var)
{
	int		len;
	char	*eq_pos;

	node->k_eq_v = ft_strdup(env_var);
	eq_pos = ft_strchr(node->k_eq_v, '=');
	node->value = ft_strdup(eq_pos + 1);
	len = ft_strlen(node->k_eq_v) - ft_strlen(eq_pos);
	node->key = (char *)malloc(((len + 1)) * sizeof(char));
	node->key = ft_strncpy(node->key, node->k_eq_v, len);
	node->key[len] = '\0';
	node->next = NULL;
}

/*adds a node to the bach of a linked list environment*/
static int	insert_node(t_env **env_l, t_env *new)
{
	t_env	*tmp;

	if (!*env_l)
		*env_l = new;
	else
	{
		tmp = *env_l;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

/*creates the linked list environment from envp[] of bash*/
t_env	**cpy_chl_env(char *envp[])
{
	t_env	**env_l;
	t_env	*node;
	int		i;

	env_l = (t_env **)malloc(1 * sizeof(t_env *));
	if (!env_l)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	*env_l = NULL;
	while (envp[i])
	{
		node = malloc(1 * sizeof(t_env));
		if (!node)
		{
			perror("malloc");
			break ;
		}
		copy_to_node(node, envp[i++]);
		insert_node(env_l, node);
	}
	return (env_l);
}

/*creates the char **environment from envp[] of bash*/

char	**cpy_arr_env(char *envp[])
{
	int		i;
	char	**arr_env;

	i = 0;
	while (envp[i])
		i++;
	arr_env = (char **)malloc((i + 1) * sizeof(char *));
	if (!arr_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		arr_env[i] = ft_strdup(envp[i]);
		i++;
	}
	arr_env[i] = NULL;
	return (arr_env);
}

t_env	*get_env_variable(t_env **chl_env, char *var)
{
	t_env	*tmp;
	size_t	len;

	tmp = *chl_env;
	len = ft_strlen(var);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
