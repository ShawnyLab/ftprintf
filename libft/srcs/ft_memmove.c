/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:32:57 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:32:58 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*sd;
	char	*sr;

	sd = dst;
	sr = (void*)src;
	i = 0;
	if (sr < sd)
	{
		i++;
		while (i <= len)
		{
			sd[len - i] = sr[len - i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			sd[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
