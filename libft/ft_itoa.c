/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

static int	num_length(long n)
{
	int	length;

	length = 1;
	if (n < 0)
	{
		length++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;
	long	num;

	num = n;
	length = num_length(num);
	str = malloc(length + 1);
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[--length] = (num % 10) + '0';
		num /= 10;
	}
	if (str[0] != '-' && length == 1)
		str[0] = '0';
	return (str);
}
