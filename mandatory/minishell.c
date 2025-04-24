/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:17:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/24 17:45:04 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*read;
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
		create_lexer(read, &all);
		while (all.lexer->c)
			next_token(&all);
		print_node(all.token);
		list_to_tab(&all);
		free(read);
		ft_lstclear(&all.token);
		// do_everything
	}
	(void)argv;
}

