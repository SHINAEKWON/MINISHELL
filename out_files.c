/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:23:09 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 18:02:12 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_output_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd <= 0)
	{
		perror(file);
		return (EXIT_FAILURE);
	}
	return (fd);
}

static int	get_append_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd <= 0)
	{
		perror(file);
		return (EXIT_FAILURE);
	}
	return (fd);
}

int	open_all_keep_last_out(t_pre_execcmd *node)
{
	t_sub_pre_execcmd	*lst_outfile;
	int					fd_out;

	lst_outfile = node->redir_out;
	fd_out = 1;
	while (lst_outfile)
	{
		if (!lst_outfile->type)
		{
			ft_close(&fd_out);
			fd_out = get_output_file(lst_outfile->content);
		}
		else if (lst_outfile->type == 1)
		{
			ft_close(&fd_out);
			fd_out = get_append_file(lst_outfile->content);
		}
		lst_outfile = lst_outfile->next;
	}
	return (fd_out);
}
