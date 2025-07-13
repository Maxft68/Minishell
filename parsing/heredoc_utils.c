#include "../mandatory/minishell.h"
#include <stdbool.h>

// char    *find_last_hd(int pipe, t_all *all)
// {
//     t_token *tmp;
//     char    *str;

//     str = NULL;
//     tmp = all->rdir_tkn;
//     while (tmp->pipe == pipe && tmp->next)
//     {
//         if (tmp->type == HEREDOC)
//             str = tmp->next->str;
//         tmp = tmp->next;
//     }
//     return (str);
// }

bool	as_quotes(char *str)
{
	bool	quote;

	quote = false;
	while (str && *str)
	{
		if (*str == 34 || *str == 39)
			quote = true;
		str++;
	}
	return (quote);
}

char	*find_last_hd(int pipe, t_all *all)
{
	t_token *tmp;
	char    *redir;

	tmp = all->rdir_tkn;
	redir = NULL;
	while (tmp && tmp->pipe != pipe)
			tmp = tmp->next;
	if (tmp && tmp->pipe == pipe)
	{
		while (tmp->next && tmp->next->pipe == pipe)
		{
			if (tmp->type == HEREDOC && tmp->next)
			{
				if (tmp->next->str == NULL)
					ft_putstr_fd("Error: NULL string in HEREDOC\n", 2); // a suppr
				redir = tmp->next->str;
			}
			if (tmp->type == REDIRECT_IN)
				redir = NULL;
			tmp = tmp->next;
		}  
	}
	return (redir);
}
