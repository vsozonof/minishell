/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:35:01 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 10:50:21 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sbase(t_prompt *ptr, char **env)
{
	if (!init_sig(ptr))
		return (0);
	if (getenv("HOME"))
	{
		if (!init_if_env(ptr, env))
			return (0);
	}
	else
	{
		if (!init_if_no_env(ptr, env))
			return (0);
	}
	return (1);
}

int	init_if_no_env(t_prompt *ptr, char **envp)
{
	t_env	*env_l;

	env_l = malloc(sizeof(t_env));
	if (!env_l)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	if (!put_env_to_lst(env_l, envp))
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->env = env_l;
	ptr->user = ft_strdup("???");
	if (!ptr->user)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->post = ft_strdup("???");
	if (!ptr->post)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->w_d = getcwd(NULL, 0);
	if (!ptr->w_d)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	return (1);
}

int	init_if_env(t_prompt *ptr, char **env)
{
	t_env				*env_l;

	env_l = malloc(sizeof(t_env));
	if (!env_l)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	else
	{
		if (!put_env_to_lst(env_l, env))
			return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
		ptr->env = env_l;
		ptr->user = ft_strdup(getenv("LOGNAME"));
		if (!ptr->user)
			return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
		ptr->post = ft_substr(getenv("SESSION_MANAGER"), 6, 12);
		if (!ptr->post)
			return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
		ptr->w_d = getcwd(NULL, 0);
		if (!ptr->w_d)
			return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	}
	return (1);
}

int	init_extras(t_prompt *ptr)
{
	ptr->name = ft_strdup("minishell");
	if (!ptr->name)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->pid = ft_itoa((int)getpid());
	if (!ptr->pid)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->data->i_status = 0;
	ptr->data->c_status = ft_itoa(ptr->data->i_status);
	if (!ptr->data->c_status)
		return (set_status(ptr->data, 12, "malloc error.", NULL), 0);
	ptr->data->exited = 0;
	if (!create_side_env(ptr))
		return (0);
	return (1);
}

int	init_str(t_data *data, t_prompt *prompt)
{
	data->head = NULL;
	data->new_head = NULL;
	data->tail = NULL;
	data->to_add = NULL;
	data->redir_tab = NULL;
	data->n_redirs = 0;
	data->input = prompt->input;
	data->pr = prompt;
	data->env = prompt->env;
	data->tab = NULL;
	return (1);
}

int	init_sig(t_prompt *prompt)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = handle_signals;
	sa_quit.sa_handler = handle_signals;
	if (sigaction(SIGINT, &sa_int, NULL) == -1
		|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (set_status(prompt->data, 1, NULL, "signal error"), 0);
	return (1);
}
