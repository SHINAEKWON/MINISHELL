/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anouri <anouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:45:38 by anouri            #+#    #+#             */
/*   Updated: 2023/12/01 17:54:51 by anouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_built_in(char *cmd);

int		built_in_echo(char **cmd);
int		built_in_exit(t_tools *tools, char **cmd);
int		built_in_pwd(char **cmd_args, t_tools *tools);
int		built_in_cd(char **cmd_args, t_env **chl_env);
int		built_in_env(char **cmd_args, t_env **chl_env);
int		built_in_export(char **cmd_args, t_tools *tools);
int		simple_export(t_tools *tools);
int		built_in_unset(char **cmd, t_tools *tools);

/**********************************************************/

void	delete_variable(t_tools *tools, char *key);
void	update_arr_env(t_tools *tools);
void	update_chl_env(t_tools *tools, t_env *env_node);

#endif