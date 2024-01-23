/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv3-trans2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:43:32 by shikwon           #+#    #+#             */
/*   Updated: 2023/11/30 17:00:20 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

void	dollar_sq_in_dq(char *token, size_t *i, t_envvar_elem **envvar)
{
	size_t	start;

	start = *i;
	if (token[*i + 1] == '\'')
	{
		(*i)++;
		if (token[*i + 1])
			(*i)++;
	}
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	if (token[*i] == '\'')
	{
		(*envvar)->content = malloc_position(token, start, *i);
		(*envvar)->translated_value = malloc_position(token, start, *i);
	}
}

void	other_dollars(char *token, size_t *ii, t_envvar_elem **ev, t_quote **q1)
{
	t_quote			*quote;
	size_t			i;
	t_envvar_elem	*envvar;

	quote = *q1;
	i = *ii;
	envvar = *ev;
	if (!quote->in_dq && (token[i + 1] == '\'' || token[i + 1] == '\"'))
	{
		i++;
		put_this_text(token, &i, &envvar, &quote);
	}
	else if (token[i + 1] == '\'' && quote->in_dq)
		dollar_sq_in_dq(token, &i, &envvar);
	else
		putchar_and_see(token, &i, &envvar);
	*ii = i;
}

void	quote_encountered(t_quote **qt, char *token, size_t *ii, \
t_envvar_elem **ev)
{
	t_quote			*quote;
	t_envvar_elem	*envvar;
	size_t			i;

	quote = *qt;
	envvar = *ev;
	i = *ii;
	quote_toggler(token[i], &quote->in_sq, &quote->in_dq);
	if (quote->in_sq && token[i + 1] != '\'')
		put_text_between_sq(token, &i, &envvar);
	else if (quote->in_dq && token[i] != '\"')
		putchar_and_see(token, &i, &envvar);
	*ii = i;
}

void	create_next_envvar_node(t_envvar_elem **envvar)
{
	(*envvar)->next = new_envvar_elem();
	(*envvar) = (*envvar)->next;
}

void	translation_loop(char *token, t_env *env_chl, \
t_quote *quote, t_envvar_elem **ev)
{
	size_t			i;
	t_envvar_elem	*envvar;

	i = 0;
	envvar = *ev;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			quote_encountered(&quote, token, &i, &envvar);
		else if (token[i] == '$' && !quote->in_sq)
		{
			if (valid_envvar(token, i))
				put_value_if_key_exists(token, &i, &envvar, env_chl);
			else
				other_dollars(token, &i, &envvar, &quote);
		}
		else
			putchar_and_see(token, &i, &envvar);
		if (token[i] != '\0')
			create_next_envvar_node(&envvar);
		else
			break ;
		i++;
	}
}
