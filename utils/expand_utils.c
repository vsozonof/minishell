/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:35:58 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/26 21:54:01 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_there_backslash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\' && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_valid_char(int c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (1);
	else
		return (0);
}

char	*quote_remover(t_data *data)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	quote_flagger(data->input, -1, 0);
	splitted = ft_split(data->input, ']');
	tmp = strjoin_and_free(splitted[i], splitted[i + 1]);
	i += 2;
	if (splitted[i - 1] == NULL)
	{
		free(data->input);
		free(splitted);
		return (tmp);
	}
	while (splitted[i])
	{
		tmp = strjoin_and_free(tmp, splitted[i]);
		i++;
	}
	free(data->input);
	free(splitted);
	return (tmp);
}

void	quote_flagger(char *str, int i, int q_flag)
{
	while (str[++i])
	{
		if (q_flag == 0 && str[i] == 39)
		{
			q_flag = 1;
			str[i] = ']';
		}
		else if (q_flag == 1 && str[i] == 39)
		{
			q_flag = 0;
			str[i] = ']';
		}
		if (q_flag == 0 && str[i] == '"')
		{
			q_flag = 2;
			str[i] = ']';
		}
		else if (q_flag == 2 && str[i] == '"')
		{
			q_flag = 0;
			str[i] = ']';
		}
	}
}
