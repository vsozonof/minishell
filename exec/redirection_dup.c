/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:15:17 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 15:40:23 by tpotilli         ###   ########.fr       */
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

int	*redirection_create(t_cmd *cmd, t_data *data)
{
	int			file;
	int			*file_tab;
	t_redir		*nav;
	int			i;

	nav = cmd->redirs;
	file = ((i = 0));
	file_tab = creating_file(nav, data, cmd);
	if (!file_tab)
		return (NULL);
	while (nav)
	{
		file_tab[i] = create_file(nav, file);
		if (file_tab[i] == -1 || nav->file == NULL)
		{
			write(2, nav->file, ft_strlen(nav->file));
			write(2, ": No such file or directory\n", 29);
			redir_failed(data, file_tab, i);
			return (NULL);
		}
		i++;
		nav = nav->next;
	}
	return (file_tab);
}

int	*creating_file(t_redir *nav, t_data *data, t_cmd *cmd)
{
	int	*file_tab;

	file_tab = malloc(sizeof(int) * len_list(nav));
	if (!file_tab)
	{
		write(2, "a problem append with a malloc\n", 32);
		free_problem(data, NULL, cmd);
		return (NULL);
	}
	return (file_tab);
}

int	create_file(t_redir *nav, int file)
{
	if (nav->type == 2)
	{
		file = ft_create_fd(nav->file, O_RDONLY);
		if (file == -1)
			return (-1);
		if (redirection_dup1_in(file) == -1)
			return (-1);
	}
	else if (nav->type == 1)
	{
		file = ft_create_fd(nav->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (file == -1)
			return (-1);
		if (redirection_dup1_out(file) == -1)
			return (-1);
	}
	else
	{
		if (other_type_redir(nav, file) == -1)
			return (-1);
	}
	return (file);
}

int	other_type_redir(t_redir *nav, int file)
{
	if (nav->type == 3)
	{
		if (file == -1)
			return (-1);
		if (redirection_dup1_in(file) == -1)
			return (-1);
	}
	else if (nav->type == 4)
	{
		file = ft_create_fd(nav->file, O_WRONLY | O_APPEND | O_CREAT);
		if (file == -1)
			return (-1);
		if (redirection_dup1_out(file) == -1)
			return (-1);
	}
	return (file);
}

int	redirection_dup1_in(int file)
{
	if (dup2(file, 0) < 0)
	{
		close(file);
		return (printf("problem with dup2 infile"), -1);
	}
	return (0);
}

int	redirection_dup1_out(int file)
{
	if (dup2(file, 1) < 0)
	{
		close(file);
		return (printf("problem with dup2 1"), -1);
	}
	return (0);
}
