/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/08 07:47:50 by vsozonof         ###   ########.fr       */
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
		prompt.input = readline("$> ");
		prompt.input = ft_strdup(prompt.input);
		if (prompt.input)
		{
			add_history(prompt.input);
			input_parser(&prompt);
		}
		else
			break ;
	}
	clear_history();
	free(prompt.w_d);
	free(prompt.post);
}
