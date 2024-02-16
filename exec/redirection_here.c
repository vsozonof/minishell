/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:47:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/16 08:36:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check s'il reste des redirections a faire

int	check_redirection_now(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmds[i][j])
	{
		// fprintf(stderr, "voici ma string dans redirection_now %s et voici i %d\n", data->cmds[i], i);
		if (data->cmds[i][j] == '>' || data->cmds[i][j] == '<')
			return (0);
		j++;
	}
	// if (data->n_redirs > 0)
	// {
	// 	fprintf(stderr, "inde = %i i = %i\n", data->index_redirs, i);
	// 	if (data->index_redirs == i)
	// 		return (0);
	// }
	return (-1);
}

int	redirection_manager(t_data *data, int i)
{
	int		token;

	token = get_nb_redirs_ac(data->cmds[i]);
	if (token > 0)
		redirection_dup1_in(data, data->first[i], data->last[i]);
	return (0);
}

int	is_redirect_actual(char *input)
{
	int		i;
	int		token;

	i = ((token = 0));
	while (input[i])
	{
		if (input[i] == '>')
		{
			token++;
			if (input[i + 1] == '>')
				i++;
		}
		else if (input[i] == '<')
		{
			token++;
			if (input[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (token);
}
