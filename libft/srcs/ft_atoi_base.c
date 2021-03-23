/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:30:26 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:30:28 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoi_base(char *str, char *base)
{
	int			i;
	intmax_t	atoi;
	int			negative;
	int			base_len;

	i = 0;
	atoi = 0;
	negative = 0;
	base_len = ft_strlen(base);
	if (!ft_check_base(base))
		return (FALSE);
	while (ft_is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	while (ft_is_in_stri(*str, base) >= 0)
	{
		atoi = atoi * base_len + ft_is_in_stri(*str, base);
		str++;
	}
	return (negative ? -atoi : atoi);
}
