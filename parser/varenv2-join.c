/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv2-join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:20:20 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/02 19:37:14 by shikwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../minishell.h"
#include "../includes/structures.h"

size_t	calcul_translated_val_len(t_envvar_elem	*cur)
{
	size_t	len;

	len = 0;
	while (cur != NULL)
	{
		len += ft_strlen(cur->translated_value);
		cur = cur->next;
	}
	return (len);
}

static char	*envvar_elem_join_write(t_envvar_elem *cur, size_t nullpos)
{
	size_t	len;
	size_t	i;
	char	*new;

	len = 0;
	i = 0;
	new = (char *)malloc((sizeof(char) * nullpos) + 1);
	if (!new)
		return (NULL);
	new[nullpos] = '\0';
	while (cur != NULL)
	{
		len = ft_strlen(cur->translated_value);
		ft_memcpy (new + i, cur->translated_value, len);
		i += len;
		cur = cur->next;
	}
	return (new);
}

void	free_envvar_elem(t_envvar_elem *to_free)
{
	t_envvar_elem	*head;
	t_envvar_elem	*next;

	head = to_free;
	next = 0;
	while (head != NULL)
	{
		if (head->content)
			free(head->content);
		if (head->translated_value)
			free(head->translated_value);
		next = head->next;
		free(head);
		head = next;
	}
}

char	*envvar_elem_join(t_envvar_elem *translated)
{
	size_t			len;
	t_envvar_elem	*head;
	t_envvar_elem	*cur;
	char			*join;

	head = translated;
	cur = translated;
	join = NULL;
	len = calcul_translated_val_len(cur);
	cur = head;
	join = envvar_elem_join_write(cur, len);
	free_envvar_elem(head);
	return (join);
}
