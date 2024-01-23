/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:11:28 by anouri            #+#    #+#             */
/*   Updated: 2023/11/16 16:00:51 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	size;
	char	*res;

	size = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	i = 0;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	while (i < ft_strlen_gnl(s1) || i < ft_strlen_gnl(s2))
	{
		if (i < ft_strlen_gnl(s1))
			res[i] = s1[i];
		if (i < ft_strlen_gnl(s2))
			res[i + ft_strlen_gnl(s1)] = s2[i];
		i++;
	}
	res[size] = '\0';
	return (res);
}
