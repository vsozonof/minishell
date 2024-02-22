/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 09:35:25 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_prompt *pr, t_data *data)
{
	t_cmd	*cmd;

	cmd = data->exec;
	init_str(data, pr);
	if (!is_piped_input_valid(pr->input, data))
		return (free_master(data));
	if (!is_there_pipe(pr))
		single_node_handler(data);
	else if (is_there_pipe(pr))
		multi_node_handler(data);
	command_manager(cmd, data);
	free_master(data);
}

void	single_node_handler(t_data *data)
{
	char	**tab;
	t_cmd	*ptr;

	ptr = malloc(sizeof(t_cmd));
	if (!ptr)
		return ;
	data->exec = ptr;
	tab = input_to_lst(data);
	if (!tab)
		return (free_master(data));
	put_input_to_lst(data->inp, tab);
	identify_nodes(data->inp);
	format_node(ptr, data->inp, data); // j'ajoute data pour l'env
	
}

void	format_node(t_cmd *pr, t_input *inp, t_data *data)
{
	int	n;

	n = get_word_count(inp);
	pr->cmd = extract_command_name(inp);
	pr->param = malloc (sizeof(char *) * (n + 1));
	pr->param[n] = NULL;
	pr->env = data->pr->nv;
	// ajoute un compteur du nombre de cmd total (tous les maillons)
	// ajoute un compteur du nombre de redirection dans la node
	// ajoute un compteur du nombre de redir total (tous les maillons)
	extract_params(inp, pr);
	n = get_redir_count(inp) + 1;
	if (n > 1)
	{
		pr->redirs = malloc(sizeof(t_redir));
		if (!pr->redirs)
			return ;
		alloc_redir_list(pr, n);
		extract_redirs(inp, pr);
	}
	node_printer(pr);
}

void	node_printer(t_cmd *pr)
{
	printf("_______________________\n");
	printf("CMD = \t [%s]\n", pr->cmd);
	printf("_______________________\n");
	int i = 0;
	printf("_______________________\n");
	printf("-------- PARAMS -------\n");
	while (pr->param[i])
	{
		printf("[%i] -> %s\n", i, pr->param[i]);
		i++;
	}
	printf("_______________________\n");
	printf("--------- REDIRS ------\n");
	t_redir	*nav = pr->redirs;
	while (nav)
	{
		printf("REDIR ID -> %i\n", nav->type);
		printf("FILNAME  -> %s\n", nav->file);
		printf("next = %p\n\n", nav->next);
		nav = nav->next;
	}
	printf("_______________________\n");
}

void	alloc_redir_list(t_cmd *pr, int n)
{
	int		i;
	t_cmd	*nav;
	t_redir	*p;

	nav = pr;
	p = pr->redirs;
	i = 1;
	while (i < n - 1)
	{
		printf("%i --- %i\n", i, n);
		p->next = malloc(sizeof(t_redir));
		if (!p)
			return ;
		p = p->next;
		i++;
	}
	p = NULL;
}

void	extract_redirs(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	t_redir	*red;

	nav = inp;
	red = pr->redirs;
	while (nav)
	{
		if (nav->i == 1 && red)
		{
			red->type = set_redir_type(inp->str);
			nav = nav->next;
			red->file = nav->str;
			red = red->next;
		}
		else
			nav = nav->next;
	}
}
int	set_redir_type(char *token)
{
	printf("->-> %s\n", token);
	if (token[0] == '>' && !token[1])
		return (1);
	else if (token[0] == '<' && !token[1])
		return (2);
	else if (token[0] == '<' && token[1] == '<' && !token[3])
		return (3);
	else if (token[0] == '>' && token[1] == '>' && !token[3])
		return (4);
	printf("Error with redir type\n");
	return (-1);
}
int	get_redir_count(t_input *inp)
{
	t_input	*nav;
	int		i;

	i = 0;
	nav = inp;
	while (nav)
	{
		if (nav->i == 1)
			i++;
		nav = nav->next;
	}
	return (i);
}

void	extract_params(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	int		i;

	nav = inp;
	i = 0;
	while (nav)
	{
		if (nav->i == 0)
		{
			pr->param[i] = nav->str;
			i++;
		}
		nav = nav->next;
	}
}

char	*extract_command_name(t_input *inp)
{
	t_input	*nav;

	nav = inp;
	while (nav)
	{
		if (nav->i == 0)
			return (nav->str);
		nav = nav->next;
	}
	return (NULL);
}

int	get_word_count(t_input *inp)
{
	t_input	*nav;
	int		i;

	i = 0;
	nav = inp;
	while (nav)
	{
		if (nav->i == 0)
			i++;
		nav = nav->next;
	}
	return (i);
}

void	multi_node_handler(t_data *data)
{
	char	***tab;
	int		i;

	i = 0;
	data->inp->cmds = pipes_splitter(data->input, '|', data);
	if (!data->inp->cmds)
		return ;
	tab = malloc(sizeof(char **) * (data->n_cmds + 1));
	if (!tab)
		return ;
	while (data->inp->cmds[i])
	{
		free(data->input);
		data->input = data->inp->cmds[i];
		tab[i] = input_to_lst(data);
		i++;
	}
	tab[i] = NULL;
	data->multi_inp = alloc_struct(data->multi_inp, (data->n_cmds + 1));
	if (!data->multi_inp)
		return ;
	multi_input_to_lst(data->multi_inp, tab, 0, 0);
	i = -1;
	while (data->multi_inp[++i])
		identify_nodes(data->multi_inp[i]);
	i = -1;
	while (data->multi_inp[++i])
		ft_printlst(data->multi_inp[i]);
}

t_input	**alloc_struct(t_input **ptr, int n)
{
	int	i;

	i = 0;
	ptr = malloc(sizeof(t_input *) * n);
	while (i < (n - 1))
	{
		ptr[i] = malloc(sizeof(t_input));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	multi_input_to_lst(t_input **ptr, char ***tab, int i, int n)
{
	t_input	*nav;

	while (ptr[i])
	{
		nav = ptr[i];
		while (tab[i][n])
		{
			nav->str = ft_strdup(tab[i][n]);
			if (tab[i][n + 1])
			{
				nav->next = malloc(sizeof(t_input));
				if (!nav->next)
					return (0);
				nav = nav->next;
			}
			else
				nav->next = NULL;
			n++;
		}
		n = 0;
		i++;
	}
	return (1);
}

void	identify_nodes(t_input *p)
{
	t_input	*nav;
	int		flag;
	int		i;

	flag = 0;
	nav = p;
	i = 0;
	while (nav)
	{
		if (flag)
		{
			nav->i = 2;
			flag = 0;
		}
		else
			nav->i = node_identifier(nav->str);
		if (nav->i == 1)
			flag = 1;
		nav->index = i;
		nav = nav->next;
		i++;
	}
}

int	node_identifier(char *str)
{
	int	i;

	i = 0;
	if (token_identifier(str, i))
		return (1);
	else
		return (0);
}

char	**input_to_lst(t_data *data)
{
	int		i;
	char	**tab;
	int		n;

	i = 0;
	n = lexer_counter(data->input, 0, 0);
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	while (data->input)
	{
		tab[i] = input_splitter(data);
		if (ft_strlen(data->input) == 0)
		{
			if (data->input)
				free(data->input);
			data->input = NULL;
		}
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

char	*input_splitter(t_data *data)
{
	int		i;
	int		c;
	char	*tmp;
	char	*ret;

	i = 0;
	while (data->input[i] && !is_in_quotes(data->input, i)
		&& ft_is_whitespace(data->input[i]))
		i++;
	c = get_next_split(data->input, i);
	if (c == i)
		return (free(data->input), data->input = NULL, NULL);
	tmp = ft_substr(data->input, c, ft_strlen(data->input));
	if (!tmp)
		return (NULL);
	ret = ft_substr(data->input, i, (c - i));
	if (!ret)
		return (NULL);
	free(data->input);
	data->input = tmp;
	return (ret);
}

int	get_next_split(char *str, int i)
{
	int			c;
	static int	flag;

	c = i;
	if ((str[c] == 39 || str[c] == '"') && !flag)
		c += (quote_skipper(str, c) - c);
	else if (token_identifier(str, c))
	{
		c += token_identifier(str, c);
		flag = 1;
	}
	else
	{
		c = get_next_split_helper(str, c, flag);
		if (flag)
			flag = 0;
	}
	return (c);
}

int	get_next_split_helper(char *str, int c, int flag)
{
	if (!flag)
	{
		while (str[c] && !ft_is_whitespace(str[c]))
		{
			if (token_identifier(str, c))
				break ;
			else if (str[c] == '"' || str[c] == 39)
				c += (quote_skipper(str, c) - c);
			else
				c++;
		}
	}
	else
	{
		while (str[c])
		{
			if (ft_is_whitespace(str[c]) && !is_in_quotes(str, c))
				break ;
			else
				c++;
		}
	}
	return (c);
}

int	put_input_to_lst(t_input *ptr, char **tab)
{
	int		i;
	t_input	*nav;

	i = 0;
	if (!tab)
		return (0);
	nav = ptr;
	while (tab[i])
	{
		nav->str = ft_strdup(tab[i]);
		if (tab[i + 1])
		{
			nav->next = malloc(sizeof(t_input));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	ft_split_free(tab);
	return (1);
}

int	is_special_char(char c)
{
	if (c == 39 || c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}


// void	input_parser(t_prompt *prompt, t_data *data)
// {
	// init_str(data, prompt);
	// if (!is_piped_input_valid(prompt->input, data))
// 		return (free_manager(data, 0));
// 	if (is_there_pipe(prompt))
// 	{
// 		data->cmds = pipes_splitter(prompt->input, '|', data);
// 		if (!data->cmds)
// 			return (set_status(data, 12, "malloc error.", NULL),
// 				free_manager(data, 0));
// 	}
// 	if (!redirection_and_expand_handler(data))
// 		return (free_manager(data, 0));
// 	if (is_there_pipe(prompt))
// 	{
// 		command_manager(data);
// 		free_manager(data, 2);
// 	}
// 	else if (!is_there_pipe(prompt))
// 	{
// 		if (!get_cmd(data))
// 			return (free_manager(data, 0));
// 		command_manager(data);
// 		free_manager(data, 1);
// 	}
// }

// int	get_cmd(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->input[i] && ft_is_whitespace(data->input[i]))
// 		i++;
// 	data->input = ft_substr(data->pr->input, i, ft_strlen(data->pr->input));
// 	if (!data->input)
// 		return (set_status(data, 12, "malloc error.", NULL), 0);
// 	return (data->n_cmds = 1, 1);
// }
