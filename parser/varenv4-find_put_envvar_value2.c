/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv4-find_put_envvar_value2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:50:20 by shikwon           #+#    #+#             */
/*   Updated: 2023/11/30 17:47:05 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

bool	exit_status_exists(char *token, size_t i)
{
	if (token[i] == '$' && token[i + 1] == '?')
		return (1);
	return (0);
}

static void	generate_uid_init(int *i, int *start, char **uid)
{
	*i = 0;
	*start = 0;
	*uid = NULL;
}

char	*generate_uid(t_env *env_chl)
{
	char	*uid;
	t_env	*temp;
	int		i;
	int		start;

	temp = env_chl;
	generate_uid_init(&i, &start, &uid);
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->key, "XDG_RUNTIME_DIR", ft_strlen(temp->key)))
		{
			start = ft_strlen(temp->value) - 1;
			i = start;
			while (temp->value[start] && ft_isdigit(temp->value[start]))
			{
				if (!ft_isdigit(temp->value[start - 1]))
					break ;
				start--;
			}
			uid = malloc_position(temp->value, start, i);
		}
		temp = temp->next;
	}
	return (uid);
}
