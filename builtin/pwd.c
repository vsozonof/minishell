/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:09:39 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/25 11:36:11 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_data *data)
{
	char	*pwd;

	pwd = ft_get_env(data->env, "PWD");
	printf("%s\n", pwd);
	free(pwd);
}
