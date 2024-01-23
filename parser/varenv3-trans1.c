/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv3-trans1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:43:32 by shikwon           #+#    #+#             */
/*   Updated: 2023/11/30 17:00:32 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

t_envvar_elem	*translation_envvar(char **currtoken, t_env *env_chl)
{
	size_t			i;
	char			*token;
	t_envvar_elem	*envvar;
	t_envvar_elem	*head;
	t_quote			*quote;

	envvar = new_envvar_elem();
	head = envvar;
	i = 0;
	token = *currtoken;
	quote_init(&quote);
	translation_loop(token, env_chl, quote, &envvar);
	free(quote);
	return (head);
}
