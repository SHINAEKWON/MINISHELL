/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv4-find_put_envvar_value1.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:50:20 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:37:38 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

bool	key_found(char *key, t_env *env_chl)
{
	t_env	*temp;
	size_t	len;

	temp = env_chl;
	len = 0;
	while (temp != NULL)
	{
		len = ft_strlen(temp->key);
		if (!ft_strncmp(temp->key, key, len))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	copy_the_env_value(char *key, t_env *env_chl, \
t_envvar_elem **envvar_param)
{
	t_envvar_elem	*envvar;
	t_env			*temp;
	size_t			len;

	envvar = *envvar_param;
	temp = env_chl;
	len = 0;
	while (temp != NULL)
	{
		len = ft_strlen(key);
		if (!ft_strncmp(temp->key, key, len) && \
		!ft_strncmp(temp->key, key, ft_strlen(temp->key)))
		{
			envvar->translated_value = ft_strdup(temp->value);
		}
		temp = temp->next;
	}
}

void	generate_key_pos(char *token, size_t **ii)
{
	size_t	i;

	i = **ii;
	while (token[i] && (token[i] == '_' || ft_isalnum(token[i]) || \
	token[i] == '?'))
	{
		if (ft_isdigit(token[i]))
		{
			while (token[i] && ft_isdigit(token[i]))
			{
				if (!ft_isdigit(token[i + 1]))
					break ;
				(i)++;
			}
			break ;
		}
		else if (token[i] == '?' || !ft_isalnum(token[i + 1]))
			break ;
		(i)++;
	}
	**ii = i;
}

static void	put_value_init(size_t *start, size_t **i, char **key)
{
	(**i)++;
	*start = **i;
	*key = NULL;
}

void	put_value_if_key_exists(char *token, size_t *i, \
t_envvar_elem **envvar_param, t_env *env_chl)
{
	size_t			start;
	char			*key;
	t_envvar_elem	*envvar;
	char			*temp;

	temp = NULL;
	envvar = *envvar_param;
	put_value_init(&start, &i, &key);
	generate_key_pos(token, &i);
	key = malloc_position(token, start, *i);
	envvar->content = malloc_position(token, start - 1, *i);
	if (key_found(key, env_chl))
		copy_the_env_value(key, env_chl, &envvar);
	else if (exit_status_exists(token, *i - 1))
	{
		temp = ft_itoa(g_exit_status);
		envvar->translated_value = ft_strdup(temp);
		free(temp);
	}
	else if (!ft_strncmp(envvar->content, "$UID", 5))
		envvar->translated_value = generate_uid(env_chl);
	else
		envvar->translated_value = ft_strdup("");
	free(key);
}
