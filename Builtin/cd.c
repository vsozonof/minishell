/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/25 15:34:42 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Update les var dans la struct prompt quand changement de dossier

// void execute_cd(t_data *data)
// {
// 	(void)data;
// 	printf("cd detected\n");
// 	if (data->input == NULL)
// 		chdir(HOME);
// 	// utiliser chdir pour mettre le nouveau repertoire
// 	if (data->n_args == 1)
// 		getcwd(data->envp, );
// 	if (chdir(data->input != 0))
// 		perror("cd\n");
// }
