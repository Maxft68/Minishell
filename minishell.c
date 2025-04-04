/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:17:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/04 17:52:47 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	initialize(t_pipe *pipe)
// {
// 	if (!pipe)
// 		return;
// 	ft_memset(pipe, 0, sizeof(t_pipe));
// }

void	initialize_all(t_all **all)
{
	*all = malloc(sizeof(t_all));
	if (!(*all))
		return;
	ft_memset(*all, 0, sizeof(t_all));
	
	(*all)->pipe = malloc(sizeof(t_pipe));
	if(!((*all)->pipe))
		ft_exit("", *all, 1);
	ft_memset((*all)->pipe, 0, sizeof(t_pipe));
	
	(*all)->env = malloc(sizeof(t_env));
	
}

int	main(int argc, char **argv, char **env)
{
	char	*read;
	char	**read_array;
	t_all *all;
	if (argc != 1)
		return(1);
	initialize_all(&all);

	while (1)
	{
		read = readline("WriteOnMe ");
		printf("%s\n", read);
		read_array = ft_split(read, ' ');
		free(read);
	}
	

	(void)argc;
	(void)argv;
	(void)env;
}
