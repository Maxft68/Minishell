/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:17:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/18 16:45:37 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*read;
	char	**read_array;
	t_all	all;

	if (argc != 1)
		return (1);
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);
	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, SIG_DFL); // a remettre dans chaque enfant 
	//signal(SIGINT, SIG_IGN);
	while (1)
	{
		read = readline("WriteOnMe ");
		if (!read)
			ft_exit("exit avec ctrl + D\n", &all, 0);
		if (ft_strncmp(read, "aaa", 3) == 0)// a remplacer par le signal CTRL + C
		{	
			free(read);							// a remplacer par le signal CTRL + C
			ft_exit("FINISH\n", &all, 0);// a remplacer par le signal CTRL + C
		}									// a remplacer par le signal CTRL + C
		if (ft_strncmp(read, "env", 3) == 0)
		{
			print_node_env(all.env);
		}
		if (read && read[0] != '\0')
			add_history(read);
		read_array = ft_split(read, ' ');	// a modifier par une vrai fonction qui parse tout les cas possible
		do_node(read_array, &all);
		free(read);
		free_array(read_array);
		//ft_lstclear(&all.token);
		// do_everything
	}
	(void)argv;
}

