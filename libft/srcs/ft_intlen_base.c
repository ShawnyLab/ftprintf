/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:30:58 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:30:59 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(uintmax_t n, char *base)
{
	size_t		len;
	uintmax_t	base_len;

	len = 1;
	base_len = ft_strlen(base);
	while (n >= base_len)
	{
		n = n / base_len;
		len++;
	}
	return (len);
}
