/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:31:20 by anouri            #+#    #+#             */
/*   Updated: 2023/12/01 17:32:53 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_pipes(t_tools *tools)
{
	tools->pipes[0][0] = 0;
	tools->pipes[0][1] = 1;
	tools->pipes[1][0] = 0;
	tools->pipes[1][1] = 1;
	return (true);
}

bool	close_pipes(t_tools *tools, t_exec *exec, int i)
{
	if (exec->next == NULL)
	{
		ft_close(&tools->pipes[(i + 1) % 2][0]);
		ft_close(&tools->pipes[(i + 1) % 2][1]);
		ft_close(&tools->pipes[i % 2][0]);
		ft_close(&tools->pipes[i % 2][1]);
	}
	if (i)
	{
		ft_close(&tools->pipes[(i + 1) % 2][0]);
		ft_close(&tools->pipes[(i + 1) % 2][1]);
	}
	return (true);
}
