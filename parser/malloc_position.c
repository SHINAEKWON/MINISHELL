/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:39:42 by shikwon           #+#    #+#             */
/*   Updated: 2023/11/29 16:11:43 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

char	*malloc_position(char *str, int start, int end)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	if (start > end || end > (int)ft_strlen(str))
		return (NULL);
	len = end - start + 2;
	new = (char *)malloc(len * sizeof(char));
	if (!new)
		return (NULL);
	while (start <= end)
		new[i++] = str[start++];
	new[i] = 0;
	return (new);
}
