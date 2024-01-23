/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:06:21 by anouri            #+#    #+#             */
/*   Updated: 2023/11/25 18:44:56 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(pid_t last_pid)
{
	pid_t	wpid;
	int		wstatus;
	int		return_status;

	while (1)
	{
		wpid = wait(&wstatus);
		if (wpid < 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(wstatus))
				return_status = WEXITSTATUS(wstatus);
			else
				return_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (return_status);
}
