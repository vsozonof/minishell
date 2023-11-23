/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/23 12:04:54 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_cd(liste_chaine);
{
	if (liste_chaine[1] == NULL)
		chdir = HOME;
	else
	{
		// utiliser chdir pour mettre le nouveau repertoire
		if (chdir(liste_chaine[1] != 0))
			perror(”cd\n”);
	}
}
