/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sbustr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 * line 18: edge case for MKO,
	we want to adjust the value of len to handle the out_of-bounds check,
	ex: s_len 10, 6,10
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (start + len > s_len)
		len = s_len - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
/*int	main(void)
{
	printf("%s\n",ft_substr("lorem ipsum", 0, 10));
}*/
/*int main(void)
{
	char *result = ft_substr("string", 0, 10);
	if (result != NULL) {
		printf("%s\n", result);
		free(result);
	}
	return (0);
}*/
