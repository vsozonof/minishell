/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:49:25 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/27 01:14:58 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_name_finder(t_data *data, int mode, int i, int c)
{
	if (mode == '<')
	{
		i--;
		while (ft_is_whitespace(data->input[i]) && i > 0)
			i--;
		c = i;
		while (!ft_is_whitespace(data->input[i]) && i > 0)
			i--;
		c++;
		return (ft_substr(data->input, i, (c - i)));
	}
	else if (mode == '>')
	{
		i++;
		while (ft_is_whitespace(data->input[i]) && data->input[i])
			i++;
		c = i;
		while (!ft_is_whitespace(data->input[i]) && data->input[i])
			i++;
		return (ft_substr(data->input, c, (i - c)));
	}
	return (NULL);
}

void	set_tab_values(t_data *data, int n, int i, int mode)
{
	char	*file_name;

	file_name = NULL;
	if (mode == 1)
	{
		file_name = file_name_finder(data, data->input[i], i, 0);
		if (data->input[i] == '<')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 1;
			data->tab[n][2] = ft_create_fd(file_name,
					O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (data->input[i] == '>')
		{
			data->tab[n][0] = i;
			data->tab[n][1] = 3;
			data->tab[n][2] = ft_create_fd(file_name,
					O_WRONLY | O_CREAT | O_TRUNC);
		}
	}
	else if (mode == 2)
		tab_value_setter_double(data, n, i);
	free(file_name);
}

void	get_redir_infos(t_data *data)
{
	int	i;
	int	n;

	i = ((n = 0));
	while (data->input[i])
	{
		if (!is_in_quotes(data->input, i)
			&& ((data->input[i] == '<' && data->input[i + 1] != '<')
				|| (data->input[i] == '>' && data->input[i + 1] != '>')))
		{
			set_tab_values(data, n, i, 1);
			n++;
			i++;
		}
		else if (!is_in_quotes(data->input, i)
			&& ((data->input[i] == '<' && data->input[i + 1] == '<')
				|| (data->input[i] == '>' && data->input[i + 1] == '>')))
		{
			set_tab_values(data, n, i, 2);
			n++;
			i += 2;
		}
		else
			i++;
	}
}

void	tab_value_setter_double(t_data *data, int n, int i)
{
	if (data->input[i] == '>' && data->input[i + 1] == '>')
	{
		data->tab[n][0] = i;
		data->tab[n][1] = 4;
		data->tab[n][2] = 0;
	}
	else if (data->input[i] == '<' && data->input[i + 1] == '<')
	{
		data->tab[n][0] = i;
		data->tab[n][1] = 2;
		data->tab[n][2] = 0;
	}
}