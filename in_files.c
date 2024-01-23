/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:24:24 by anouri            #+#    #+#             */
/*   Updated: 2023/12/02 16:16:48 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

void	ft_close(int *fd)
{
	if (fd && *fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

static int	open_input_file(t_exec *exec, t_sub_pre_execcmd *infile)
{
	int	fd_in;

	fd_in = 0;
	if (exec->heredoc_filename)
	{
		unlink(exec->heredoc_filename);
		exec->heredoc_filename = NULL;
	}
	if (!infile->type)
	{
		ft_close(&fd_in);
		fd_in = get_input_file(infile->content);
		if (fd_in == -1 && exec->save_failed_file == NULL)
			exec->save_failed_file = ft_strdup(infile->content);
	}
	else
	{
		ft_close(&fd_in);
		exec->heredoc_filename = generate_heredoc_filename();
		fd_in = get_heredoc_input_file(exec->heredoc_filename, infile->content);
		if (infile->next)
			unlink(exec->heredoc_filename);
	}
	return (fd_in);
}

int	open_all_keep_last_in(t_exec *exec, t_pre_execcmd *node)
{
	t_sub_pre_execcmd	*lst_infile;
	int					fd_in;
	int					is_neg;

	lst_infile = node->redir_in;
	fd_in = 0;
	is_neg = 0;
	while (lst_infile)
	{
		fd_in = open_input_file(exec, lst_infile);
		if (is_neg == 0 && fd_in == -1)
			is_neg = 1;
		lst_infile = lst_infile->next;
	}
	if (exec->save_failed_file)
		return (-1);
	return (fd_in);
}
