/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils-2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 02:54:33 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/27 05:41:14 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash_expander(t_data *data, int i)
{
	if (data->input[i] == '\\' && data->input[i + 1] == '\\')
	{
		data->head = ft_substr(data->input, 0, i);
		data->to_add = ft_strdup("\\");
		data->tail = ft_substr(data->input, (i + 2), ft_strlen(data->input));
		reg_expand_joiner(data);
	}
	else if (data->input[i] == '\\' && data->input[i + 1] != '\\')
	{
		data->head = ft_substr(data->input, 0, i);
		data->to_add = NULL;
		data->tail = ft_substr(data->input, (i + 1), ft_strlen(data->input));
		reg_expand_joiner(data);
	}
}

void	tilde_expander(t_data *data, int i)
{
	data->head = ft_substr(data->input, 0, i);
	data->to_add = ft_get_env(data->env, "HOME");
	data->tail = ft_substr(data->input, (i + 1), ft_strlen(data->input));
	reg_expand_joiner(data);
}

int	is_there_tilde(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '~')
			return (1);
	return (0);
}
