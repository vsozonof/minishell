/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/10 16:34:51 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * Input basique trouvable dans data.input
// * Flags et Args trouvable dans data.arg / data.flag
// * Env trouvable dans data.envp

void	input_parser(t_prompt *prompt)
{
	t_data	data;

	prompt->data = &data;
	if (!is_input_valid(prompt->input))
		return (free(prompt->input));
	if (is_pipe(prompt))
	{
		init_str_pipe(&data, prompt);
		if (is_valid_pipe(prompt->input))
			return ;
		data.cmds = pipes_splitter(prompt->input, '|', &data);
		// command_manager(&data);
		free_cmds(&data);
		free(prompt->input);
	}
	else if (!is_pipe(prompt))
	{
		init_str(&data, prompt);
		get_cmd(&data, prompt);
		// command_manager(&data);
		free(data.input);
		free(prompt->input);
		free_args(&data);
		free_flags(&data);
	}
}

void	get_cmd(t_data *data, t_prompt *prompt)
{
	int		i;
	int		c;

	i = 0;
	printf("NFLAGS = %i - NARGS = %i\n", data->n_flags, data->n_args);
	while (prompt->input[i] && ft_is_whitespace(prompt->input[i]))
		i++;
	c = i;
	while (prompt->input[c] && !ft_is_whitespace(prompt->input[c]))
		c++;
	data->input = ft_substr(prompt->input, i, c);
	if (!data->args && !data->flag)
		return ;
	while (prompt->input[c])
	{
		while (prompt->input[c] && ft_is_whitespace(prompt->input[c]))
			c++;
		if (((prompt->input[c] == '-') && ft_isalpha(prompt->input[c + 1]))
			|| ((prompt->input[c] == '-') && (prompt->input[c + 1] == '-')
				&& (ft_isalpha(prompt->input[c + 2]))))
			c = get_flags(data, prompt, c);
		else
			c = get_args(data, prompt, c);
	}
}

int	get_flags(t_data *data, t_prompt *prompt, int start)
{
	int	end;
	printf("GET FLAGS\n");
	while (prompt->input[start] == '-')
		start++;
	end = start;
	while (prompt->input[end] && !ft_is_whitespace(prompt->input[end]))
		end++;
	data->flag[data->counter] = ft_substr(prompt->input, start, (end - start));
	data->counter++;
	return (end);
}

int	get_args(t_data *data, t_prompt *prompt, int start)
{
	int	end;
	printf("GET ARGS\n");
	end = start;
	while (prompt->input[end] && !ft_is_whitespace(prompt->input[end]))
		end++;
	if (data->n_args && data->c_args < data->n_args)
		data->args[data->c_args]
			= ft_substr(prompt->input, start, (end - start));
	data->c_args++;
	return (end);
}
