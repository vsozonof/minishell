/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/25 00:31:03 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(char **env)
{
	t_prompt	prompt;

	init_sbase(&prompt, env);
	while (42)
	{
		printf("%s@%s:%s", prompt.user, prompt.post, prompt.w_d);
		prompt.input = readline(" $> ");
		if (prompt.input)
		{
			add_history(prompt.input);
			input_parser(&prompt);
		}
		else
			break ;
	}
	clear_history();
}
