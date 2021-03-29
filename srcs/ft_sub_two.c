/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:08 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:20 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_printf(intmax_t n)
{
	char		*str;
	int			num_len;

	num_len = ft_intlen(n);
	if (!(str = ft_calloc((num_len + 1), sizeof(char))))
		return (NULL);
	str[num_len] = '\0';
	while (num_len)
	{
		if (n < 0)
		{
			str[--num_len] = -(n % 10) + 48;
			n = n / 10;
			n = -n;
		}
		else
		{
			str[--num_len] = n % 10 + 48;
			n = n / 10;
		}
	}
	return (str);
}

int		ft_atoi_printf(char *str, int *i)
{
	int		atoi;

	atoi = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		atoi = atoi * 10 + str[*i] - 48;
		(*i)++;
	}
	(*i)--;
	return (atoi);
}

char	*ft_strdup_l(char *s, t_printf *bu)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (bu->precision && bu->precision_width < len)
		len = bu->precision_width;
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_set_precision(t_printf *bu)
{
	bu->precision = 1;
	bu->precision_parsing = 1;
	bu->precision_width = 0;
}

void	ft_reset_flags(t_printf *bu)
{
	bu->width = 0;
	bu->precision = 0;
	bu->precision_width = 0;
	bu->precision_parsing = 0;
	bu->converter = 0;
	bu->minus = 0;
	bu->zero = 0;
	bu->plus = 0;
	bu->space = 0;
	bu->sharp = 0;
	bu->len = 0;
	bu->sp_len = 0;
	bu->is_int = 0;
	bu->h_count = 0;
	bu->l_count = 0;
	bu->n = 0;
	bu->u = 0;
}
