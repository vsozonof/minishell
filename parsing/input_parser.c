/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 10:48:05 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * Input basique trouvable dans data.input
// * Env trouvable dans data.envp
// TODO: Mettre sous liste args + flags (fait à 70% - juste gérer certains cas)

void	input_parser(t_prompt *prompt)
{
	t_data	data;

	init_str(&data, prompt);
	get_cmd(&data, prompt);
}

void	get_cmd(t_data *data, t_prompt *prompt)
{
	int		i;
	int		c;

	i = 0;
	while (prompt->input[i] && ft_is_whitespace(prompt->input[i]))
		i++;
	c = i;
	while (prompt->input[c] && !ft_is_whitespace(prompt->input[c]))
		c++;
	data->input = ft_substr(prompt->input, i, c);
	command_manager(data);
	// while (prompt->input[c])
	// {
	// 	while (prompt->input[c] && ft_is_whitespace(prompt->input[c]))
	// 		c++;
	// 	if (prompt->input[c] == '-')
	// 		get_flags(data, prompt, c);
	// 	else
	// 		get_args(data, prompt, c);
	// }
}

// int	get_flags(t_data *data, t_prompt *prompt, int start)
// {
// 	int	end;

// 	end = start;
// 	while (prompt->input[end] && !ft_is_whitespace(prompt->input[end]))
// 		end++;
	
// 	return (end);
// }

// void	get_args(t_data *data, t_prompt *prompt, int start)
// {
// 	(void)data;
// 	(void)prompt;
// 	(void)start;
	
// }
