/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:29:10 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/06/22 17:53:56 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	// if (dst == NULL && size == 0)
	// 	return (ft_strlen(src));
	
	// Vérifier que src n'est pas NULL
    if (src == NULL)
        return (0);

    // Si dst est NULL, se comporter comme si size était 0
    if (dst == NULL)
    {
        return (ft_strlen(src));
    }
	while (dst[i] && i < size)
		i++;
	k = i;
	if (size <= i)
		return (size + ft_strlen(src));
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (k + ft_strlen(src));
}
