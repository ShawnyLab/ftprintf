/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:28:37 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 17:03:34 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert_str(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	if (backup->precision && backup->precision_width < 0)
		backup->precision_width = -backup->precision_width;
	if (!(str = va_arg(ap, char *)))
		str = ft_strdup_l("(null)", backup);
	else
		str = ft_strdup_l(str, backup);
	backup->len = ft_strlen(str);
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}

void	ft_convert_c(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	str = NULL;
	backup->len = 1;
	backup->converter == 'c' ? str = ft_c_to_str(va_arg(ap, int)) : 0;
	backup->converter == '%' ? str = ft_c_to_str('%') : 0;
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}

void	ft_convert_n(va_list ap, t_printf *backup)
{
	intmax_t	*n;

	if (backup->l_count >= 2)
		n = (intmax_t *)va_arg(ap, long long *);
	else if (backup->l_count == 1)
		n = (intmax_t *)va_arg(ap, long *);
	else if (backup->h_count && ((backup->h_count % 2) == 0))
		n = (intmax_t *)((char *)va_arg(ap, int *));
	else if (backup->h_count && ((backup->h_count % 2) != 0))
		n = (intmax_t *)((short *)va_arg(ap, int *));
	else
		n = (intmax_t *)va_arg(ap, int *);
	if (!n)
		return ;
	*n = backup->ret;
}

void	ft_convert_x(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	str = NULL;
	backup->is_int = 1;
	ft_size_u(ap, backup);
	backup->converter == 'x' ? str = ft_itoa_base(backup->u, "0123456789abcdef") : 0;
	backup->converter == 'X' ? str = ft_itoa_base(backup->u, "0123456789ABCDEF") : 0;
	backup->len = ft_strlen(str);
	str = ft_num_precision(str, backup);
	backup->len = ft_strlen(str);
	if (backup->u == 0 && backup->precision && backup->precision_width == 0
		&& !backup->width)
	{
		free(str);
		return ;
	}
	if (backup->u == 0 && backup->precision && backup->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	backup->sharp && backup->u ? backup->len += 2 : 0;
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}

void	ft_convert_p(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	backup->u = va_arg(ap, unsigned long);
	str = ft_itoa_base(backup->u, "0123456789abcdef");
	backup->precision ? backup->zero = 0 : 0;
	backup->len = ft_strlen(str);
	str = ft_num_precision(str, backup);
	backup->len = ft_strlen(str) + 2;
	if (backup->u == 0 && backup->precision && backup->precision_width == 0)
	{
		free(str);
		str = ft_strdup("");
		backup->len -= 1;
	}
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}
