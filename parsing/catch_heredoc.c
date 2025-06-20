#include "../mandatory/minishell.h"

char	*append_hd(char* hd_eof, t_all *all)
{
	char	*str;
	char	*line;
	size_t	len;

	str = ft_strdup("");
	while (1)
	{
		line = readline("heredoc:");
		if (ft_strncmp(line, hd_eof, sizeof(hd_eof)) == 0)
		{
			free(line);
			break;
		}
		len = (ft_strlen(str) + ft_strlen(line));
        // printf("len = %zu\n", len);
		str = (char*)gc_realloc(all, str, (len + 2));
		//ajouter verif et message erreur
		ft_strlcat(str, line, len + 2);
		ft_strlcat(str, "\n", (ft_strlen(str) + 2));
        // printf("ligne:%s||\n", str);
		free(line);
	}
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

void    catch_heredoc(t_all *all)
{
    t_token *tmp;
    char    *str;
    
    tmp = all->token;
    while(tmp->next)
    {
        if (tmp->type == HEREDOC)
        {
            str = append_hd(tmp->next->str, all);
            printf("HD_input:\n%s\n###############\n", str);
            tmp->next->str = gc_strdup(str, all);
            
        }
        tmp = tmp->next;
    }
}