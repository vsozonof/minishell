/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:35:12 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/21 18:23:17 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_struct
{
	char	*input;
	char	*user;
	char	*post;
	char	*w_d;
}	t_data;

int		main(void);
void	init_sbase(t_data *ptr);
void	get_input(void);
void	input_parser(t_data *ptr);

void	handle_sigint(int signum);
void	handle_sigquit(int signum);

int		command_manager(char *input);
void	command_exec(char *input);
void	builtin_manager(char *input);
int		get_kind_input(char *input,  int token);

#endif