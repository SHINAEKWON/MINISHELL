/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:34:12 by shikwon           #+#    #+#             */
/*   Updated: 2023/12/03 14:42:29 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Erase the current command line and replace by empty string.
// string is now the 1st param "", and 2nd param '0' erase the content.
// Move the cursur to the next line for a new input
// This f() reprints the current command line
// It is used to show the modification of command line

#include "minishell.h"

void	sig_ctrlc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
