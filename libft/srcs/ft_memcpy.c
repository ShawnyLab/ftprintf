/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:32:50 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:32:51 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*sd;
	char		*sr;

	sd = dst;
	sr = (void*)src;
	i = 0;
	while (i < n)
	{
		sd[i] = sr[i];
		i++;
	}
	return (dst);
}
