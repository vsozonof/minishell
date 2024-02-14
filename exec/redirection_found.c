/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_found.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:37:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/14 14:30:25 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		first_redirect(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	j = -1;
	check = -1;
	fprintf(stderr, "voici l'input %s\n", input);
	if (data->n_redirs > 0)
	{
		while (input[i])
		{
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] == '<' || input[i] == '>')
			{
				j++;
				fprintf(stderr, "donc la j'ai %c\n", input[i]);
				if (input[i] == '<')
					check = j;
				i++;
			}
			if (!input[i])
				break;
			i++;
		}
	}
	if (check == -1)
		return (-1);
	check = check + count;
	return (check);
} // si token = 0 ya r ,1 <, 2 <<, 3 >

// pour celui la c'est des <
int		last_redirect(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	j = -1;
	check = -1;
	fprintf(stderr, "voici l'input %s\n", input);
	if (data->n_redirs > 0)
	{
		while (input[i])
		{
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] == '<' || input[i] == '>')
			{
				j++;
				if (input[i] == '>')
					check = j;
				i++;
			}
			if (!input[i])
				break;
			i++;
		}
	}
	if (check == -1)
		return (-1);
	check = check + count;
	return (check);
} // si token = 0 ya r ,1 <, 2 <<, 3 >

int		first_redirect_begin(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = ((j = 0));
	check = 0;
	fprintf(stderr, "voici l'input %s\n", input);
	if (data->n_redirs > 0)
	{
		while (input[i])
		{
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] == '<' || input[i] == '>')
			{
				j++;
				if (input[i] == '<')
					check = j;
				i++;
			}
			if (!input[i])
				break;
			i++;
		}
	}
	if (check == 0)
		return (-1);
	if (check != 0)
		check += count - 1;
	return (check);
} // si token = 0 ya r ,1 <, 2 <<, 3 >

// pour celui la c'est des <
int		last_redirect_begin(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = ((j = 0));
	check = 0;
	fprintf(stderr, "voici l'input %s\n", input);
	if (data->n_redirs > 0)
	{
		while (input[i])
		{
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] == '<' || input[i] == '>')
			{
				j++;
				if (input[i] == '>')
					check = j;
				i++;
			}
			if (!input[i])
				break;
			i++;
		}
	}
	if (check == 0)
		return (-1);
	if (check != 0)
		check += count - 1;
	return (check);
} // si token = 0 ya r ,1 <, 2 <<, 3 >
