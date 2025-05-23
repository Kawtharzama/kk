/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/02/07 12:49:07 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*line 10 : handle overlapping by reading from the end*/
/*line 19 : copying normally if no overlaps are happening*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*des;
	const unsigned char	*sr;

	if (!dest && !src)
		return (dest);
	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (sr < des && des < sr + n)
	{
		sr += n;
		des += n;
		while (n--)
		{
			*(--des) = *(--sr);
		}
	}
	else
	{
		while (n--)
		{
			*des++ = *sr++;
		}
	}
	return (dest);
}
