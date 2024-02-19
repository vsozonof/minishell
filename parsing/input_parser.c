/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 10:14:53 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * Input basique trouvable dans data.input
// * Flags et Args trouvable dans data.arg / data.flag
// * Env trouvable dans data.envp

void	input_parser(t_prompt *prompt, t_data *data)
{
	init_str(data, prompt);
	if (!is_piped_input_valid(prompt->input, data))
		return (free_manager(data, 0));
	if (is_there_pipe(prompt))
	{
		data->cmds = pipes_splitter(prompt->input, '|', data);
		if (!data->cmds)
			return (set_status(data, 12, "malloc error.", NULL),
				free_manager(data, 0));
	}
	if (!redirection_and_expand_handler(data))
		return (free_manager(data, 0));
	printf("-> %s\n", data->input);
	if (is_there_pipe(prompt))
	{
		command_manager(data);
		free_manager(data, 2);
	}
	else if (!is_there_pipe(prompt))
	{
		if (!get_cmd(data))
			return (free_manager(data, 0));
		command_manager(data);
		free_manager(data, 1);
	}
}

int	get_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] && ft_is_whitespace(data->input[i]))
		i++;
	data->input = ft_substr(data->pr->input, i, ft_strlen(data->pr->input));
	if (!data->input)
		return (set_status(data, 12, "malloc error.", NULL), 0);
	return (data->n_cmds = 1, 1);
}
