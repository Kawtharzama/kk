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

static int	ft_itoa_fill(char *str, long num, int length)
{
	str[length] = '\0';
	if (num == 0)
	{
		str[0] = '0';
		return (0);
	}
	while (num > 0)
	{
		str[--length] = (num % 10) + '0';
		num /= 10;
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;
	long	num;

	num = (long)n;
	length = num_length(num);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	ft_itoa_fill(str, num, length);
	return (str);
}
