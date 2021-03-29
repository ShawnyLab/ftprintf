/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:28:32 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:47 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_size_int(va_list ap, t_printf *bu)
{
	if (bu->l_count >= 2)
		bu->n = (intmax_t)va_arg(ap, long long);
	else if (bu->l_count == 1)
		bu->n = (intmax_t)va_arg(ap, long);
	else if (bu->h_count && ((bu->h_count % 2) == 0))
		bu->n = (intmax_t)((char)va_arg(ap, int));
	else if (bu->h_count && ((bu->h_count % 2) != 0))
		bu->n = (intmax_t)((short)va_arg(ap, int));
	else
		bu->n = (intmax_t)va_arg(ap, int);
}

void	ft_size_u(va_list ap, t_printf *bu)
{
	if (bu->l_count >= 2)
		bu->u = (uintmax_t)va_arg(ap, unsigned long long);
	else if (bu->l_count == 1)
		bu->u = (uintmax_t)va_arg(ap, unsigned long);
	else if (bu->h_count && ((bu->h_count % 2) == 0))
		bu->u = (uintmax_t)((unsigned char)va_arg(ap, int));
	else if (bu->h_count && ((bu->h_count % 2) != 0))
		bu->u = (uintmax_t)((unsigned short)va_arg(ap, int));
	else
		bu->u = (uintmax_t)va_arg(ap, unsigned int);
}

void	ft_convert_int(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	bu->is_int = 1;
	ft_size_int(ap, bu);
	str = itoa_printf(bu->n);
	bu->len = ft_intlen(bu->n);
	str = ft_num_precision(str, bu);
	bu->len = ft_strlen(str);
	(bu->n < 0) ? bu->len++ : 0;
	(bu->n >= 0) && (bu->plus || bu->space) ? bu->len++ : 0;
	if (bu->n == 0 && bu->precision && bu->precision_width == 0
		&& !bu->width)
	{
		free(str);
		return ;
	}
	if (bu->n == 0 && bu->precision && bu->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}

void	ft_convert_uint(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	bu->is_int = 1;
	ft_size_u(ap, bu);
	str = ft_uitoa(bu->u);
	bu->len = ft_strlen(str);
	str = ft_num_precision(str, bu);
	bu->len = ft_strlen(str);
	if (bu->u == 0 && bu->precision && bu->precision_width == 0
		&& !bu->width)
	{
		free(str);
		return ;
	}
	if (bu->u == 0 && bu->precision && bu->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}
