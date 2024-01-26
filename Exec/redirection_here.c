/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:47:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/26 23:18:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check s'il reste des redirections a faire

// int	redirection_manager(int **pipefd, int token, t_data *data, int i)
// {
// 	int	fd;
// 	int	fd2;
// 	int	i;
// 	int	redirect;

// 	redirect = is_any_redirection(data, i, fd, fd2);
// 	fd = ((fd = 0));
// 	i = 0;
// 	if (redirect == 1 || redirect == 2 || redirect == 3)
// 		redirection_case(redirect, data, i, pipefd);
// 	else
// 		return (-1);
// 	i = data->tab[0];
// 	data->n_redirs--;
// 	return (0);
// }

// int	redirection_case(int redirect, t_data *data, int i, int **pipefd)
// {
// 	int		fd;
// 	int		fd2;

// 	fd = ft_create_fd(ft_recup_fd(0, data, redirect), O_WRONLY | O_CREAT | O_TRUNC);
// 	fd2 = ft_create_fd(ft_recup_fd(1, data, redirect), O_WRONLY | O_CREAT | O_TRUNC);
// 	if (redirect == 1)
// 	{
// 		check_dup(data->tab[data->index_redirs][], 2, );
// 	}
// 	else if (redirect == 2)
// 	{

// 	}
// 	else if (redirect == 3)
// 	{
		
// 	}
	
// }

// char	*ft_recup_fd(int token, t_data *data, int redirect)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	if (redirection == 3)
// 	{
// 		while (data->cmds[i][j])
// 	}
// 	if (redirect == 1)
// 	{
// 		while (data->cmds[i][j])
// 		{
// 			str[j] = data->cmds[i][j];
// 			j++;
// 		}
// 	}
// }

// int	is_any_redirection(t_data *data, int i, int fd, int fd2)
// {
// 	int		j;

// 	while (data->cmds[i])
// 	{
// 		j = 0;
// 		while (data->cmds[i][j])
// 		{
// 			if (data->cmds[i][j] == '<'
// 			&& data->cmds[i][j + 1] != '<')
// 				fd = 1;
// 			else if (data->cmds[i][j] == '>'
// 			&& data->cmds[i][j + 1] != '>')
// 				fd2 = 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (fd == 1 && fd2 == 1)
// 		return (3);
// 	else if (fd == 1)
// 		return (1);
// 	else if (fd2 == 1)
// 		return (2);
// 	return (0);
// }

// int		check_redirection(int pipe, int pipe2, t_data *data)
// {
// 	int	fd;
// 	int	fd2;

// 	fd = NULL;
// 	fd2 = NULL;
// 	if (data->tab[data->index_redirs][1] == 1)
// 		fd = ft_create_fd(data->cmds[data->i][0] , O_WRONLY | O_CREAT | O_TRUNC);
// 	if (data->tab[data->index_redirs][1] == 3)
// 		fd2 = ft_create_fd(data->cmds[data->i][0] , O_WRONLY | O_CREAT | O_TRUNC);
// 	if (fd < 0 && fd2 < 0)
// 	{
// 		dup2(fd, 0);
// 		dup2(fd2, 1);
// 	}
// 	else if (fd < 0)
// 	{
// 		dup2(pipe, 0);
// 		dup2(fd2, 1);
// 	}
// 	else if (fd2 < 0)
// 	{
// 		dup2(fd, 0);
// 		dup2(pipe2, 1);
// 	}
// 	return (0);
	
// }


/*

char	*redirection_manager(int pipe, int token, int pipe2, t_data *data)
{
	char	*cmd;
	int		i;

	cmd = NULL;
	if (is_any_redirection(data) == 1)
		return (cmd);
	i = data->tab[0];
	data->n_redirs--;
	cmd = check_redirection(pipe, pipe2, data);
	if (cmd != NULL)
		return (cmd);
	// else if ()
	// if (data->tab[i][1] == 1)
	// {
	// 	if (dup2(0, 0) < 0)
	// 		return (printf("problem with dup2 1"), -1);
	// 	if (dup2(pipe2, 1) < 0)
	// 		return (printf("problem with dup2 2"), -1);
	// }
	// else if (data->tab[i][1] == 3)
	
	// else if (data->tab[i][1] == 2)

	else if (data->tab[i][1] == 4)
	
	return (cmd);
}

int		check_redirection(int pipe, int pipe2, t_data *data)
{
	int	fd;
	int	fd2;

	fd = NULL;
	fd2 = NULL;
	if (data->tab[data->index_redirs][1] == 1)
		fd = ft_create_fd(data->cmds[data->i][0] , O_WRONLY | O_CREAT | O_TRUNC);
	if (data->tab[data->index_redirs][1] == 3)
		fd2 = ft_create_fd(data->cmds[data->i][0] , O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0 && fd2 < 0)
	{
		dup2(fd, 0);
		dup2(fd2, 1);
	}
	else if (fd < 0)
	{
		dup2(pipe, 0);
		dup2(fd2, 1);
	}
	else if (fd2 < 0)
	{
		dup2(fd, 0);
		dup2(pipe2, 1);
	}
	return (0);
	
}

int	is_any_redirection(t_struct *data)
{
	if (data->n_redirs > 0)
		return (0);
	return (1);
}

*/