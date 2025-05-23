/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = '\0';
}
/*void print_buffer(const char *buffer, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%02x ", (unsigned char)buffer[i]);
	}
	printf("\n");
}

int	main(void) {
	char buffer[20] = "Hello, World!";

	// Print buffer before calling my_bzero
	printf("Before my_bzero: ");
	print_buffer(buffer, sizeof(buffer));

	// Zero out the first 5 bytes of the buffer
	ft_bzero(buffer, 5);

	// Print buffer after calling my_bzero
	printf("After my_bzero: ");
	print_buffer(buffer, sizeof(buffer));

	return (0);
}*/
