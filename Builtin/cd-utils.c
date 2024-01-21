/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:27:00 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/21 05:39:03 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_path(char *str)
{
	int		i;
	int		c;
	char	*cd_path;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
		i++;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	c = i;
	while (str[c] && !ft_is_whitespace(str[c]))
		c++;
	cd_path = ft_substr(str, i, c);
	return (cd_path);
}
