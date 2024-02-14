/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:37:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/14 12:18:25 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int main(int argc, char **argv, char **env)
// {
//     t_shell     shell;
//     ft_parse_envs_to_lst(&envs, env); // transform env to linked list
//     shell.tmpfile = "path to tmpfile";
//     while (1)
//     {
//         char *buf = readline("bash: ");
//         add_history(buf);
//         shell.std_in = dup(0);
//         shell.std_out = dup(1);
//         shell.f_in = dup(0);
//         shell.f_out = dup(1);
//         /* Token is represented by linked list. "cat << eof" translates into "cat" -> ">>" -> "eof",
//         with token pointing to "cat" */
//         t_token *token = parse_buffer(buf); // parse_buffer will return pointer to the first token
//         ft_execute_token(shell, token, env);
//         free(buf);
//     }
// }


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		*tab;

	tab = malloc(sizeof(int) * 3);
	input = readline("minishell:");
	if (strstr(input, "<<"))
	{
		int i = 0;
		while (input[i])
	}
	tab[0] = 
	tab[1] = 2;
}