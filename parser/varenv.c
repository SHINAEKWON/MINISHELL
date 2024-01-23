/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:31:50 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:38:37 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

bool	token_maybe_has_envvar(char *token)
{
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_envvar_elem	*new_envvar_elem(void)
{
	t_envvar_elem	*new;

	new = (t_envvar_elem *)malloc(sizeof(t_envvar_elem) * 1);
	if (!new)
		return (NULL);
	new->content = 0;
	new->translated_value = 0;
	new->next = NULL;
	return (new);
}

bool	valid_envvar(char *str, size_t i)
{
	if (exit_status_exists(str, i))
		return (1);
	else if (str[i] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		return (1);
	return (0);
}

void	envvar_parser(t_cmd **curr, t_tools *tools)
{
	t_cmd			*current;
	char			*temp;
	t_envvar_elem	*translated;
	t_env			*env_chl;

	current = *curr;
	temp = 0;
	env_chl = *tools->chl_env;
	translated = NULL;
	translated = translation_envvar(&current->token, env_chl);
	temp = envvar_elem_join(translated);
	free(current->token);
	current->token = ft_strdup(temp);
	free(temp);
}
