/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:35:12 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 05:06:42 by vsozonof         ###   ########.fr       */
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

// ! ---------------------------------------------------------------------------
// ?							STRUCTURES DECLARATION
// ! ---------------------------------------------------------------------------
typedef struct s_struct
{
	char	*input;
	char	*user;
	char	*post;
	char	*w_d;
	char	**envp;
}	t_prompt;

typedef struct s_parse
{
	t_prompt		*pr;
	char			*input;
	char			**flag;
	char			**envp;
	int				n_args;
	int				n_flags;
	struct s_parse	*next;
}	t_data;	

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int		main(int argc, char **argv, char *envp[]);
void	get_input(char **env);
void	init_sbase(t_prompt *prompt, char **env);
void	init_str(t_data *data, t_prompt *p);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

void	input_parser(t_prompt *prompt);
void	get_cmd(t_data *data, t_prompt *prompt);
int		get_flags(t_data *data, t_prompt *prompt, int start);
void	get_args(t_data *data, t_prompt *prompt, int start);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

int		flags_counter(char *str);
int		args_counter(char *str);

// ! ---------------------------------------------------------------------------
// ?							SIGNAL HANDLER
// ! ---------------------------------------------------------------------------

void	handle_signals(int signum);

int		command_manager(char *input);
void	command_exec(char *input);
void	builtin_manager(char *input);
int		get_kind_input(char *input, int token);

void	execute_echo();
void	execute_unset();
void	execute_pwd();
void	execute_export();
void	execute_cd();
void	execute_env();
int		execute_exit();

#endif