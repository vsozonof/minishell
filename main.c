/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 09:38:18 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --leak-check=full --suppressions=rl_leak_ignore.supp ./minishell
int	g_status;

int	main(int argc, char **argv, char *envp[])
{
	t_prompt	prompt;
	t_data		data;

	(void)argc;
	(void)argv;
	prompt.data = &data;
	if (!init_sbase(&prompt, envp) || !init_extras(&prompt))
	{
		free_end_of_program(&prompt);
		return (data.i_status);
	}
	return (get_input(&prompt, &data));
}
