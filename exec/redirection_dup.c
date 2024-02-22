/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:15:17 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 13:43:22 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// donc ici je dois:
// voir quel est le type de fd puis cree le fd, le garder en memoire
// et enfin le dup2

// 1 = simple quote vers la gauche <
// 2 = droite >
// 3 = db_gauche <<
// 4 = droite >>

int	redirection_create(t_cmd *cmd)
{
	int		file;

	file = 0;
	while (cmd->redirs)
	{
		file = create_file(cmd->redirs, file);
		if (file == 1)
			return (1);
		cmd->redirs = cmd->redirs->next;
	}
	return (0);
}

int	create_file(t_redir *tmp, int file)
{
	if (tmp->type == 2)
	{
		file = ft_create_fd(tmp->file, O_RDONLY);
		if (file == 1)
			return (1);
		if (redirection_dup1_in(file) == 1)
			return (1);
	}
	else if (tmp->type == 1)
	{
		file = ft_create_fd(tmp->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (file == 1)
			return (1);
		if (redirection_dup1_out(file) == 1)
			return (1);
	}
	else
	{
		if (other_type_redir(tmp, file) == 1)
			return (1);
	}
	return (0);
}

int	other_type_redir(t_redir *tmp, int file)
{
	if (tmp->type == 3)
	{
		file = ft_create_fd(tmp->file, O_RDONLY);
		if (file == 1)
			return (1);
		if (redirection_dup1_in(file) == 1)
			return 1;
	}
	else if (tmp->type == 4)
	{
		file = ft_create_fd(tmp->file, O_WRONLY | O_APPEND);
		if (file == 1)
			return (1);
		if (redirection_dup1_out(file) == 1)
			return (1);
	}
	return (0);
}

int	redirection_dup1_in(int file)
{
	if (dup2(file, 0) < 0)
	{
		close(file);
		return (printf("problem with dup2 infile"), 1);
	}
	return (0);
}

int	redirection_dup1_out(int file)
{
	if (dup2(file, 1) < 0)
	{
		close(file);
		return (printf("problem with dup2 1"), 1);
	}
	return (0);
}
