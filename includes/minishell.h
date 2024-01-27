/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:35:12 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/27 00:46:59 by tpotilli         ###   ########.fr       */
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
	char			*name;
	char			*pid;
	char			*input;
	char			*user;
	char			*post;
	char			*w_d;
	char			**nv;
	struct s_parse	*data;
	struct s_env	*env;
}	t_prompt;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	t_prompt		*pr;
	t_env			*env;
	char			*input;
	char			*head;
	char			*new_head;
	char			*tail;
	char			*to_add;
	char			**cmds;
	int				n_cmds;
	int				i_status;
	char			*c_status;
	int				**tab;
	int				n_redirs;
	int				i;
	int				index_redirs;
	struct s_parse	*next;
}	t_data;	

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int		main(int argc, char **argv, char *envp[]);
void	get_input(char **envp);
int		init_sbase(t_prompt *prompt, char **env);
void	init_extras(t_prompt *ptr, char **envp);
int		init_str(t_data *data, t_prompt *prompt);
int		init_str_pipe(t_data *data, t_prompt *prompt);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

void	input_parser(t_prompt *prompt);
int		get_cmd(t_data *data);
int		invalid_character_checker(int c);
int		is_input_valid(char *str);
int		is_piped_input_valid(char *str);
int		exception_checker(char *str);
int		unclosed_quote_detector(char *str);

void	expand_handler(t_data *data);
int		is_valid_char(int c);
void	reg_expander(t_data *data);
void	reg_expand_splitter(t_data *data, int i);
void	reg_expand_joiner(t_data *data);
void	search_and_split(t_data *data, int i);
char	*quote_remover(t_data *data);
void	quote_flagger(char *str, int i, int q_flag);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

void	ft_printlst(t_env *L);

char	*ft_get_env(t_env *env, char *str);
t_env	*ft_get_env_node(t_env *env, char *str);
int		put_env_to_lst(t_env *env, char **envp);
int		is_there_pipe(t_prompt *prompt);
int		is_there_dollar(char *str);
int		is_there_backslash(char *str);
int		is_there_quotes(char *str);
int		is_there_redirs(char *str);
int		ispipe(int c);
int		is_valid_pipe(char *str);
int		is_in_quotes(char *str, int c);
int		is_pipe_content_valid(char *str);
char	**pipes_splitter(char const *s, char c, t_data *data);
int		n_args(char *str);
int		quote_skipper(char *str, int c);
int		is_valid_redir(char *str);
int		redir_checker(char *str, int i);
void	redirection_counter(t_data *data);
void	redirection_parser(t_data *data);
int		redirection_and_expand_handler(t_data *data);

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

int		pipex_exec(t_data *data);
int		ft_pipex(t_data	*data);
int		**alloc_pipe(int i, int **pipefd);
int		**parent_process(int **pipefd, int i);
int		len_fd_tab(char	**str, int i);
int		found_max(char **argv);
int		verif_arg_fd(char *argv[], int i);
char	*str_join_free(char *path, char *cmd);
void	ft_freedb(char **str);
void	free_pipe_argv(int **pipefd, char	*argv[]);
int		check_dup(int pipe, int token, int pipe2, t_data *data);
char	*child_process_in(int **pipefd, t_data *data, int i, int token);
char	*arg(char *str, t_data *data);
int		ft_create_fd(char *argv, int flag);
char	**ft_get_path(char **env);
char	*ft_do_process(char *envp[], char *cmd);
int		single_arg(t_data *data);
int		exec_single(char **cmd_argument, char *fre, t_data *data);
int		child_process_in_or_out(int **pipefd, t_data *data, int i, int token);
int		child_process_middle(int **pipefd, t_data *data, int token);
int		redirection_manager(int **pipefd, int token, t_data *data, int i);
char	*check_redirection(int pipe, int pipe2, t_data *data);
int		is_any_redirection(t_data *data);
int		redirection_case(int redirect, t_data *data, int i, int **pipefd);
int		ft_recup_fd(int token, t_data *data, int redirect);
int		redirection_case_1(int fd, t_data *data, int **pipefd);
int		redirection_case_2(int fd, int fd2, t_data *data, int **pipefd);
int		redirection_case_3(int fd, int fd2, t_data *data, int **pipefd);

// ! ---------------------------------------------------------------------------
// ?							Builtin && Tools
// ! ---------------------------------------------------------------------------

void	execute_cd(t_data *data);
char	*extract_arg(char *str);
int		quoted_arg_util(char *str, int c);
void	change_directory(t_data *data, char *path);
void	go_back_one_level(t_data *data);
void	update_vars(t_data *data);
void	error_handling(int err, char *str);

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
// ?							Utils Free
// ! ---------------------------------------------------------------------------

void	free_manager(t_data *data, int key);
void	free_data_struct(t_data *data);
void	free_data_envp(t_data *data, int i);
void	free_cmds(t_data *data);
void	free_env(t_env	*env);
void	free_pwd(t_data *data);
void	free_end_of_program(t_prompt *p);
char	*strjoin_and_free(char *s1, char *s2);

#endif