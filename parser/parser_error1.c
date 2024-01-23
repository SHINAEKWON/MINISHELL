/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:24:11 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:37:16 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

int	three_bracket_checker(char *cmd)
{
	int		i;
	bool	in_dq;
	bool	in_sq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '\'') || cmd[i] == '\"')
			quote_toggler (cmd[i], &in_sq, &in_dq);
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && \
		cmd[i + 2] == '>' && !in_dq && !in_sq)
			return (1);
		else if (cmd[i] == '<' && cmd[i + 1] == '<' && \
		cmd[i + 2] == '<' && !in_dq && !in_sq)
			return (1);
		i++;
	}
	return (0);
}

bool	open_quote_finder(char *token)
{
	int		i;
	bool	sq;
	bool	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			if (!dq)
				sq = !sq;
		}
		else if (token[i] == '\"')
		{
			if (!sq)
				dq = !dq;
		}
		i++;
	}
	if (!dq && !sq)
		return (0);
	return (1);
}

bool	syntax_ruban(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>')
		{
			i++;
			while (cmd[i] && ft_isspace((unsigned char)cmd[i]))
				i++;
			if (cmd[i] == '<')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

bool	syntax_diamond(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

bool	syntax_big_diamond(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			i++;
			while (cmd[i] && ft_isspace((unsigned char)cmd[i]))
				i++;
			if (cmd[i] == '>')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
