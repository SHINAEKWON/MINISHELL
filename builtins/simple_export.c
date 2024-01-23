/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:15:55 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 11:08:43 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	table_size(char **table)
{
	int	size;

	size = 0;
	while (table[size])
		size++;
	return (size);
}

static void	ft_sort_table(char **table, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (++i < size)
	{
		j = 0;
		while (++j < size)
		{
			if (ft_strcmp(table[j - 1], table[j]) > 0)
			{
				temp = table[j - 1];
				table[j - 1] = table[j];
				table[j] = temp;
			}
		}
	}
}

int	simple_export(t_tools *tools)
{
	int	size;
	int	i;

	i = 0;
	size = table_size(tools->arr_env);
	ft_sort_table(tools->arr_env, size);
	while (i < size)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tools->arr_env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
