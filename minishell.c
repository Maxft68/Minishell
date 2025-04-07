/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:17:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/07 19:33:11 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	initialize(t_pipe *pipe)
// {
// 	if (!pipe)
// 		return ;
// 	ft_memset(pipe, 0, sizeof(t_pipe));
// }

void	initialize_all(t_all **all)
{
	*all = malloc(sizeof(t_all));
	if (!(*all))
		return ;
	ft_memset(*all, 0, sizeof(t_all));
	(*all)->pipe = malloc(sizeof(t_pipe));
	if (!((*all)->pipe))
		ft_exit("", *all, 1);
	ft_memset((*all)->pipe, 0, sizeof(t_pipe));
	(*all)->env = NULL;
	(*all)->token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*read;
	char	**read_array;
	t_all	*all;

	if (argc != 1)
		return (1);
	initialize_all(&all);
	while (1)
	{
		read = readline("WriteOnMe ");
		add_history(read);
		read_array = ft_split(read, ' ');
		do_node(read_array, all);
		// do_everything
		// free all structure
		ft_lstclear(&all->token);
		free_array(read_array);
		free(read);
	}
	(void)argv;
	(void)env;
}
