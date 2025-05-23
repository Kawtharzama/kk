/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
/*
#include <ctype.h>
#include <stdio.h>
*/
#include "libft.h"

int	ft_isdigit(int c)
{
	int	output;

	output = 1;
	if (c < '0' || c > '9')
		output = 0;
	return (output);
}
/*int	main(void)
{
	printf("%d",isdigit(49));
}*/
