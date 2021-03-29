/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:08 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/28 23:14:35 by jinspark         ###   ########.fr       */
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

char	*ft_strdup_l(char *s, t_printf *backup)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (backup->precision && backup->precision_width < len)
		len = backup->precision_width;
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

void	ft_set_precision(t_printf *backup)
{
	backup->precision = 1;
	backup->precision_parsing = 1;
	backup->precision_width = 0;
}

void	ft_reset_flags(t_printf *backup)
{
	backup->width = 0;
	backup->precision = 0;
	backup->precision_width = 0;
	backup->precision_parsing = 0;
	backup->converter = 0;
	backup->minus = 0;
	backup->zero = 0;
	backup->plus = 0;
	backup->space = 0;
	backup->sharp = 0;
	backup->len = 0;
	backup->sp_len = 0;
	backup->is_int = 0;
	backup->h_count = 0;
	backup->l_count = 0;
	backup->n = 0;
	backup->u = 0;
}
