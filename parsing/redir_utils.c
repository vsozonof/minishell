/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:31:35 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/22 20:56:55 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_and_expand_handler(t_data *data)
{
	if (!is_there_backslash(data->input) || !is_there_dollar(data->input))
		expand_handler(data);
	redirection_counter(data);
	if (data->n_redirs != 0)
		redirection_parser(data);
}

void	redirection_counter(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!is_in_quotes(data->input, i) && data->input[i] == '<' && data->input[i + 1] != '<')
			data->n_redirs++;
		else if (!is_in_quotes(data->input, i) && data->input[i] == '<' && data->input[i + 1] == '<')
		{
			data->n_redirs++;
			i += 2;
		}
		else if (!is_in_quotes(data->input, i) && data->input[i] == '>' && data->input[i + 1] != '>')
			data->n_redirs++;
		else if (!is_in_quotes(data->input, i) && data->input[i] == '>' && data->input[i + 1] == '>')
		{
			data->n_redirs++;
			i += 2;
		}
		i++;
	}
}

void	get_redir_infos(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (data->input[i])
	{
		if (!is_in_quotes(data->input, i) && data->input[i] == '<' && data->input[i + 1] != '<')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 1;
			n++;
		}
		else if (!is_in_quotes(data->input, i) && data->input[i] == '<' && data->input[i + 1] == '<')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 3;
			n++;
		}
		else if (!is_in_quotes(data->input, i) && data->input[i] == '>' && data->input[i + 1] != '>')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 2;
			n++;
		}
		else if (!is_in_quotes(data->input, i) && data->input[i] == '>' && data->input[i + 1] == '>')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 4;
			n++;
		}
		i++;
	}
}

void	redirection_parser(t_data *data)
{
	int	i;

	i = 0;
	data->tab = malloc(sizeof (int *) * data->n_redirs);
	while (i < data->n_redirs)
	{
		data->tab[i] = malloc(sizeof (int) * 2);
		i++;
	}
	get_redir_infos(data);
	i = 0;
	while (i < data->n_redirs)
	{
		printf("%i - %i\n", data->tab[i][0], data->tab[i][1]);
		i++;
	}
}
