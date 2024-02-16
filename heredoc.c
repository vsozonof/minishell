/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:37:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/16 08:13:44 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int main(int argc, char **argv, char **env)
// {
//     t_shell     shell;
//     ft_parse_envs_to_lst(&envs, env); // transform env to linked list
//     shell.tmpfile = "path to tmpfile";
//     while (1)
//     {
//         char *buf = readline("bash: ");
//         add_history(buf);
//         shell.std_in = dup(0);
//         shell.std_out = dup(1);
//         shell.f_in = dup(0);
//         shell.f_out = dup(1);
//         /* Token is represented by linked list. "cat << eof" translates into "cat" -> ">>" -> "eof",
//         with token pointing to "cat" */
//         t_token *token = parse_buffer(buf); // parse_buffer will return pointer to the first token
//         ft_execute_token(shell, token, env);
//         free(buf);
//     }
// }

char	*get_name_heredoc(void)
{
	char		*str;
	int			i;
	int			fd;

	fd = open("/dev/random", O_RDONLY);
	str = malloc(sizeof(char) * 21);
	if (!fd)
		return (fprintf(stderr, "problem with fd in here_doc\n"), NULL);
	read(fd, str, 14);
	i = 1;
	str[0] = '.';
	while (i <= 15)
	{
		str[i] = (str[i] % 25) + 'a';
		i++;
	}
	str[16] = '.';
	str[17] = 't';
	str[18] = 'x';
	str[19] = 't';
	str[20] = '\0';
	close(fd);
	return (str);
}

char	*extract_delimiter(char *input)
{
	int	i;
	int	c;

	c = ((i = 0));
	while (input[i])
	{
		if (input[i] == '<')
		{
			i += 2;
			break ;
		}
		i++;
	}
	while (input[i] && ft_is_whitespace(input[i]))
		i++;
	c = i;
	while (input[c] && !ft_is_whitespace(input[c]))
		c++;
	return (ft_substr(input, i, (c - i)));
}

void	heredoc_handler(char *delimiter)
{
	char	*input;
	int		fd;
	char	*fname;

	fname = get_name_heredoc();
	fd = open(fname, O_APPEND | O_WRONLY | O_CREAT, 0644);
	while (42)
	{
		input = readline("> ");
		if (!ft_strncmp(input, delimiter, ft_strlen(delimiter)))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*delimiter;

	input = readline("minishell:");
	if (strstr(input, "<<"))
	{
		delimiter = extract_delimiter(input);
		heredoc_handler(delimiter);
	}
}