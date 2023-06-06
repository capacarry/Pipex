/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:14:08 by gcapa-pe          #+#    #+#             */
/*   Updated: 2023/05/24 15:05:25 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;
	int				diff;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while ((c1[i] != '\0' || c2[i]) != '\0' && i < n)
	{
		if (c1[i] != c2[i])
		{
			diff = c1[i] - c2[i];
			return (diff);
		}
		i++;
	}
	if (i == n)
		return (0);
	return (c1[i] - c2[i]);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	char	*cpy;

	dst = NULL;
	cpy = NULL;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst && s1 && s2)
	{
		cpy = dst;
		while (*s1 != '\0')
			*dst++ = *s1++;
		while (*s2 != '\0')
			*dst++ = *s2++;
		*dst = '\0';
	}
	else
		return (NULL);
	return (cpy);
}
