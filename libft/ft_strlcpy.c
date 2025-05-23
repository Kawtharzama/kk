/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*int main(void)
{
	char src[] = "Hello, World!";
	char dst[11];

	size_t len = ft_strlcpy(dst, src, sizeof(dst));

	printf("Destination: %s\n", dst);
	printf("Source length: %zu\n", len)

	return (0);
}*/
