/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:35:01 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/26 07:40:58 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sbase(t_prompt *ptr, char **env)
{
	char				*tmp;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_signals;
	sa_quit.sa_handler = handle_signals;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	ptr->user = getenv("LOGNAME");
	tmp = getenv("SESSION_MANAGER");
	ptr->post = ft_substr(tmp, 6, 12);
	ptr->w_d = getcwd(NULL, 0);
	ptr->envp = env;
}

void	init_str(t_data *data, t_prompt *prompt)
{
	data->pr = prompt;
	data->envp = prompt->envp;
	data->n_flags = flags_counter(prompt->input);
	data->n_args = args_counter(prompt->input);
	data->flag = malloc(sizeof(char *) * data->n_flags);
	data->args = malloc(sizeof(char *) * data->n_args);
	data->counter = 0;
	data->c_args = 0;
}

void	init_str_pipe(t_data *data, t_prompt *prompt)
{
	data->pr = prompt;
	data->envp = prompt->envp;
	data->n_flags = flags_counter_pipe(prompt->input);
	data->n_args = args_counter_pipe(prompt->input);
	printf("%i - %i\n", data->n_flags, data->n_args);
	// data->flag = malloc(sizeof(char *) * data->n_flags);
	// data->args = malloc(sizeof(char *) * data->n_args);
	data->counter = 0;
	data->c_args = 0;
}
