/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv5-put_this_text.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:47:05 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:39:17 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

void	put_text_between_sq(char *token, size_t *i, t_envvar_elem **envvar)
{
	size_t	start;

	(*i)++;
	start = *i;
	while (token[*i])
	{
		if (token[*i + 1] == '\'')
			break ;
		(*i)++;
	}
	if (*i - start >= 0)
	{
		(*envvar)->content = malloc_position(token, start, *i);
		(*envvar)->translated_value = malloc_position(token, start, *i);
	}
}

void	putchar_and_see(char *token, size_t *i, t_envvar_elem **envvar)
{
	(*envvar)->content = malloc_position(token, *i, *i);
	(*envvar)->translated_value = malloc_position(token, *i, *i);
}

void	put_this_text_copystr(t_envvar_elem ***ev, \
char *token, size_t start, size_t end)
{
	t_envvar_elem	*envvar;

	envvar = **ev;
	envvar->content = malloc_position(token, start, end);
	envvar->translated_value = malloc_position(token, start, end);
}

void	put_this_text(char *token, size_t *i, \
t_envvar_elem **envvar, t_quote **quote)
{
	size_t	start;
	size_t	del;

	start = *i;
	del = 0;
	while (token[*i])
	{
		if (token[*i] == '\'' || token[*i] == '\"')
		{
			quote_toggler(token[*i], &(*quote)->in_sq, &(*quote)->in_dq);
			del = 1;
			break ;
		}
		else if (token[*i + 1] == '$')
			break ;
		(*i)++;
	}
	if (*i - start >= 0)
		put_this_text_copystr(&envvar, token, start, *i - del);
}
