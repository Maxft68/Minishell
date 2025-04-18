#include "lex_pars.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*alloc;
	size_t	l;

	l = ft_strlen(s);
	alloc = malloc((l + 1) * sizeof(char));
	if (!alloc)
		return (NULL);
	ft_strlcpy(alloc, s, l + 1);
	return (alloc);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i])
		i++;
	return (i);
}

int main()
{
    const char *input = "echo \'1       3\'";
    t_lexer *lexr = create_lexer(input);

    t_token *tokn;
    while ((tokn = next_token(lexr))->type != ILLEGAL)
    {
        // Traitez le token
        printf("Type: %u, Literal: %s\n", tokn->type, tokn->str);
        free_token(tokn);
    }

    free_lexer(lexr);
    return (0);
}