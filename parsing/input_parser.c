/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/28 22:03:30 by tpotilli         ###   ########.fr       */
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
	init_str(&data, prompt);
	if (!is_piped_input_valid(prompt->input))
		return (free_manager(&data, 0));
	if (!redirection_and_expand_handler(&data))
		return (free_manager(&data, 0));
	if (is_there_pipe(prompt))
	{
		data.cmds = pipes_splitter(prompt->input, '|', &data);
		if (!data.cmds)
			return (free_manager(&data, 2));
		command_manager(&data);
		free_manager(&data, 2);
	}
	else if (!is_there_pipe(prompt))
	{
		if (!get_cmd(&data))
			return (free_manager(&data, 0));
		// printf("FINAL UPDATE = %s ENFINNNNNN\n", data.input);
		command_manager(&data);
		free_manager(&data, 1);
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
		return (pr_error("malloc error."));
	else
		return (data->n_cmds = 1, 1);
}
