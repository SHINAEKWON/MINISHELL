/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:05:16 by anouri            #+#    #+#             */
/*   Updated: 2023/12/03 17:24:54 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*BASH MANUAL*/

/*
this is a redirection that instructs the shell to read input from the current 
source until a line containing only word (with no trailing blanks) in seen.
all the line read up to that point are then used as te standard input (or file 
descriptor n if n is speciied) for command.

did not understant n option -_-

*/

/*BASH MANUAL*/

/*ce que j'ai remarque :

<<eof <<ok <<lol

all tmp files are open
they are closed when delim is found and delim are considered only when order
in command line is respected

whith a command or pipe, the last file is the one that is considered :)))

example :
cat <<hola
cat << 'hola'
cat << "hola"
cat << ho"la"
heredoc		(delimiter = hola) is infile for cat

cat << $HOME
(delimiter = $HOME =>STR NOT env_VARIABLE) 
heredoc in structure will be : 
delim1->delin2>delim3->NULL
open all and create a tempfile for each heredoc
write to the first one and close it with delom
write to the second one and close it with delim
write to the third one and close it with dellim
if cmd, use only thelast one as input 
*/

#include "minishell.h"

char	*generate_heredoc_filename(void)
{
	static int	i;
	char		*num;
	char		*file_name;

	i = 0;
	num = ft_itoa(i++);
	file_name = ft_strjoin("tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

static void	write_to_heredoc(int fd, char *delim)
{
	char	*line;
	int		mem_in;

	mem_in = dup(STDIN_FILENO);
	signal(SIGINT, sig_ctrlc);
	line = readline("> ");
	if (!line)
		err_msg_cmd("warning",
			"here-document delimited by end-of-file (wanted `eof')",
			0);
	while (line && ft_strncmp(line, delim, ft_strlen(delim)))
	{
		if (g_exit_status == 130)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			err_msg_cmd("warning",
				"here-document delimited by end-of-file (wanted `eof')",
				0);
	}
	dup2(mem_in, STDIN_FILENO);
	free(line);
}

int	get_heredoc_input_file(char *heredoc_filename, char *delim)
{
	int	fd;

	fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		unlink(heredoc_filename);
		ft_putstr_fd("no such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	write_to_heredoc(fd, delim);
	close(fd);
	return (get_input_file(heredoc_filename));
}
