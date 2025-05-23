/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	p;

	p = c;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == p)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
/*int	main(void)
{
	printf("%s\n",ft_strrchr("teste", 1125));
}*/
