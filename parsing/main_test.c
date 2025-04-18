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

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (16384);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (8);
	return (0);
}

int main()
{
    const char *input = "cat file.txt | tr '[:lower:]' '[:upper:]' > output.txt";
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