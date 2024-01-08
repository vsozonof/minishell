/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:35:12 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/08 10:25:18 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

// ! ---------------------------------------------------------------------------
// ?							STRUCTURES DECLARATION
// ! ---------------------------------------------------------------------------

struct	s_parse;
typedef struct s_struct
{
	char			*input;
	char			*user;
	char			*post;
	char			*w_d;
	char			**envp;
	struct s_parse	*data;
}	t_prompt;

typedef struct s_parse
{
	t_prompt		*pr;
	char			*input;
	char			**flag;
	char			**args;
	char			**cmds;
	char			**envp;
	int				n_args;
	int				n_flags;
	int				n_cmds;
	int				counter;
	int				c_args;
	struct s_parse	*next;
}	t_data;	

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int		main(int argc, char **argv, char *envp[]);
void	get_input(char **env);
void	init_sbase(t_prompt *prompt, char **env);
void	init_str(t_data *data, t_prompt *prompt);
void	init_str_pipe(t_data *data, t_prompt *prompt);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

void	input_parser(t_prompt *prompt);
void	get_cmd(t_data *data, t_prompt *prompt);
int		get_flags(t_data *data, t_prompt *prompt, int start);
int		get_args(t_data *data, t_prompt *prompt, int start);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

int		flags_counter(char *str);
int		flags_counter_pipe(char *str);
int		args_counter(char *str);
int		args_counter_pipe(char *str);
int		is_pipe(t_prompt *prompt);
int		is_valid_pipe(char *str, int i);
char	**pipes_splitter(char const *s, char c, t_data *data);

// ! ---------------------------------------------------------------------------
// ?							SIGNAL HANDLER
// ! ---------------------------------------------------------------------------

void	handle_signals(int signum);

// ! ---------------------------------------------------------------------------
// ?							Command
// ! ---------------------------------------------------------------------------

int		command_manager(t_data *data);
int		get_kind_input(t_data *data, int token);
void	command_exec(char *input);
int		builtin_checker(t_data *tmp);
void	builtin_manager(t_data *tmp, int token);
int		found_builtin(t_data *tmp);
int		not_builtin(t_data *data);
int		multi_pipe(t_data *data);
int		ft_pipex(char *argv[], int *file, char *env[], int argc);
int		process(char *cmd, char *env[], int token);
int		ft_create_fd(char *argv, int flag);
int		pipe_command(t_data *data);
char	**remake_argv(t_data *data);
void	exec_one_arg(char **cmd);

// ! ---------------------------------------------------------------------------
// ?							Builtin
// ! ---------------------------------------------------------------------------

void	execute_cd(t_data *data);
void	execute_echo(t_data *data);
void	execute_pwd(t_data *data);
void	execute_env(t_data *data);
void	execute_export(t_data *data);
void	execute_unset(t_data *data);
int		execute_exit(t_data *data);
void	execute_cd(t_data *data);

// void	execute_export();
// int		execute_exit();

// ! ---------------------------------------------------------------------------
// ?							Utils
// ! ---------------------------------------------------------------------------

void	free_data_struct(t_data *data);
void	free_data_envp(t_data *data, int i);
void	free_flags(t_data *data);
void	free_args(t_data *data);
void	free_cmds(t_data *data);
void	update_pwd(t_data *data);
void	free_pwd(t_data *data);

#endif