/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:17:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/11 14:11:31 by mdsiurds         ###   ########.fr       */
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
		ft_exit("malloc fail", *all, 1);
	ft_memset(*all, 0, sizeof(t_all));
	(*all)->garbage = NULL;
	(*all)->pipe = gc_malloc(*all, sizeof(t_pipe));
	if (!((*all)->pipe))
		ft_exit("gc_malloc fail", *all, 1);
	ft_memset((*all)->pipe, 0, sizeof(t_pipe));
	(*all)->data = gc_malloc(*all, sizeof(t_data));
	if (!((*all)->data))
		ft_exit("gc_malloc fail", *all, 1);
	ft_memset((*all)->data, 0, sizeof(t_data));
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
	do_env(all, env);
	while (1)
	{
		read = readline("WriteOnMe ");
		if (ft_strncmp(read, "aaa", 3) == 0)// a remplacer par le signal CTRL + C
		{									// a remplacer par le signal CTRL + C
			free(read);						// a remplacer par le signal CTRL + C
			break ;							// a remplacer par le signal CTRL + C
		}									// a remplacer par le signal CTRL + C
		add_history(read);
		read_array = ft_split(read, ' ');	// a modifier par une vrai fonction qui parse tout les cas possible
		do_node(read_array, all);
		free_array(read_array);
		free(read);
		ft_lstclear(&all->token);
		// do_everything
	}
	ft_exit("FINISH\n", all, 0);// a remplacer par le signal CTRL + C ??
	(void)argv;
	(void)env;
}
