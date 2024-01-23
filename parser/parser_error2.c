/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:24:11 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 19:50:31 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../includes/parser.h"
#include "../includes/structures.h"

bool	syntax_consec_pipe(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			while (isspace(cmd[i]))
				i++;
			if (cmd[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

bool	syntax_pipe_start_end(char *cmd)
{
	char	*trimmed;
	size_t	len;

	trimmed = ft_strtrim(cmd, " ");
	len = ft_strlen(trimmed);
	if (trimmed[0] == '|' || trimmed[len - 1] == '|')
		return (free(trimmed), 1);
	return (free(trimmed), 0);
}

bool	syntax_end_with_bracket(char *cmd)
{
	char	*trimmed;
	size_t	len;

	trimmed = ft_strtrim(cmd, " ");
	len = ft_strlen(trimmed);
	if (trimmed[len - 1] == '>')
		return (free (trimmed), 1);
	else if (trimmed[len - 1] == '<')
		return (free (trimmed), 1);
	return (free (trimmed), 0);
}

bool	syntax_dot(char *cmd)
{
	char	*trimmed;

	trimmed = ft_strtrim(cmd, " ");
	if (!ft_strncmp(trimmed, ".", 2))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}
