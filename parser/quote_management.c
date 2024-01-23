/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:38:10 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 12:42:15 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

void	quote_init(t_quote	**quote)
{
	*quote = (t_quote *)malloc(sizeof(t_quote));
	(*quote)->in_dq = 0;
	(*quote)->in_sq = 0;
}

void	quote_toggler(char c, bool *in_sq, bool *in_dq)
{
	if (c == '\'' && !*in_dq)
		*in_sq = !*in_sq;
	else if (c == '\"' && !*in_sq)
		*in_dq = !*in_dq;
}
