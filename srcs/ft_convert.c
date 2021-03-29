/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:28:37 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:41 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert_str(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	if (bu->precision && bu->precision_width < 0)
		bu->precision_width = -bu->precision_width;
	if (!(str = va_arg(ap, char *)))
		str = ft_strdup_l("(null)", bu);
	else
		str = ft_strdup_l(str, bu);
	bu->len = ft_strlen(str);
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}

void	ft_convert_c(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	str = NULL;
	bu->len = 1;
	bu->converter == 'c' ? str = ft_c_to_str(va_arg(ap, int)) : 0;
	bu->converter == '%' ? str = ft_c_to_str('%') : 0;
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}

void	ft_convert_n(va_list ap, t_printf *bu)
{
	intmax_t	*n;

	if (bu->l_count >= 2)
		n = (intmax_t *)va_arg(ap, long long *);
	else if (bu->l_count == 1)
		n = (intmax_t *)va_arg(ap, long *);
	else if (bu->h_count && ((bu->h_count % 2) == 0))
		n = (intmax_t *)((char *)va_arg(ap, int *));
	else if (bu->h_count && ((bu->h_count % 2) != 0))
		n = (intmax_t *)((short *)va_arg(ap, int *));
	else
		n = (intmax_t *)va_arg(ap, int *);
	if (!n)
		return ;
	*n = bu->ret;
}

void	ft_convert_x(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	str = NULL;
	bu->is_int = 1;
	ft_size_u(ap, bu);
	bu->converter == 'x' ? str = ft_itoa_base(bu->u, "0123456789abcdef") : 0;
	bu->converter == 'X' ? str = ft_itoa_base(bu->u, "0123456789ABCDEF") : 0;
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
	bu->sharp && bu->u ? bu->len += 2 : 0;
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}

void	ft_convert_p(va_list ap, t_printf *bu)
{
	char	*str;
	char	*sp;

	bu->u = va_arg(ap, unsigned long);
	str = ft_itoa_base(bu->u, "0123456789abcdef");
	bu->precision ? bu->zero = 0 : 0;
	bu->len = ft_strlen(str);
	str = ft_num_precision(str, bu);
	bu->len = ft_strlen(str) + 2;
	if (bu->u == 0 && bu->precision && bu->precision_width == 0)
	{
		free(str);
		str = ft_strdup("");
		bu->len -= 1;
	}
	sp = ft_print_sp(bu);
	ft_join_all(str, sp, bu);
}
