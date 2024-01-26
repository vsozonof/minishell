/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:07:54 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/26 14:15:07 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}
