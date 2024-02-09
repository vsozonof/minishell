/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:42:48 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/09 14:12:17 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	r_word_counter(t_data *data, int i, int j)
{
	while (data->input[i])
	{
		while (data->input[i] && ft_is_whitespace(data->input[i]))
			i++;
		if (!ft_is_whitespace(data->input[i]) && !is_token(data->input, i))
		{
			while (data->input[i] && !ft_is_whitespace(data->input[i])
				&& !is_token(data->input, i))
				i++;
			j++;
		}
		if (is_token(data->input, i))
		{
			while (data->input[i] && is_token(data->input, i))
				i++;
			j++;
		}
		i++;
	}
	return (j);
}

int	is_token(char *str, int i)
{
	if (((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '>' && str[i + 1] != '>'))
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (1);
	else
		return (0);
}

void	extract_redir_no_wspace(t_data *data, int n)
{
	char	**tab;
	int		i;
	int		j;
	int		c;

	j = ((c = 0));
	i = 0;
	tab = malloc(sizeof(char *) * n);
	if (!tab)
		return (set_status(data, 12, NULL, "malloc error."));
	while (data->input[i] && j < n)
	{
		while (data->input[i] && ft_is_whitespace(data->input[i]))
			i++;
		c = i;
		while (data->input[i] && !ft_is_whitespace(data->input[i])
			&& !is_token(data->input, i))
			i++;
		tab[j] = ft_substr(data->input, c, (ft_strlen(data->input) - i));
		j++;
	}
}
