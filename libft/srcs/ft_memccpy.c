/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:32:38 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:32:39 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*sd;
	char			*sr;
	unsigned char	uc;

	sd = dst;
	sr = (void*)src;
	uc = c;
	i = 0;
	while (i < n)
	{
		sd[i] = sr[i];
		i++;
		if (sr[i - 1] == uc)
			return (dst + i);
	}
	return (NULL);
}
