/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/09 07:35:22 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(char **envp)
{
	t_prompt	prompt;
	t_data		data;

	prompt.data = &data;
	init_sbase(&prompt, envp);
	init_extras(&prompt);
	while (42)
	{
		printf("%s at %s in: %s", prompt.user, prompt.post, prompt.w_d);
		prompt.input = readline("\n$> ");
		if (prompt.input)
		{
			add_history(prompt.input);
			if (!is_input_valid(prompt.input))
				free(prompt.input);
			else
				input_parser(&prompt, &data);
		}
		else
			break ;
	}
	clear_history();
	free_end_of_program(&prompt);
	return (data.i_status);
}
