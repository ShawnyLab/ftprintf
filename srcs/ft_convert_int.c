/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:28:32 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/28 23:19:52 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_size_int(va_list ap, t_printf *backup)
{
	if (backup->l_count >= 2)
		backup->n = (intmax_t)va_arg(ap, long long);
	else if (backup->l_count == 1)
		backup->n = (intmax_t)va_arg(ap, long);
	else if (backup->h_count && ((backup->h_count % 2) == 0))
		backup->n = (intmax_t)((char)va_arg(ap, int));
	else if (backup->h_count && ((backup->h_count % 2) != 0))
		backup->n = (intmax_t)((short)va_arg(ap, int));
	else
		backup->n = (intmax_t)va_arg(ap, int);
}

void	ft_size_u(va_list ap, t_printf *backup)
{
	if (backup->l_count >= 2)
		backup->u = (uintmax_t)va_arg(ap, unsigned long long);
	else if (backup->l_count == 1)
		backup->u = (uintmax_t)va_arg(ap, unsigned long);
	else if (backup->h_count && ((backup->h_count % 2) == 0))
		backup->u = (uintmax_t)((unsigned char)va_arg(ap, int));
	else if (backup->h_count && ((backup->h_count % 2) != 0))
		backup->u = (uintmax_t)((unsigned short)va_arg(ap, int));
	else
		backup->u = (uintmax_t)va_arg(ap, unsigned int);
}

void	ft_convert_int(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	backup->is_int = 1;
	ft_size_int(ap, backup);
	str = itoa_printf(backup->n);
	backup->len = ft_intlen(backup->n);
	str = ft_num_precision(str, backup);
	backup->len = ft_strlen(str);
	(backup->n < 0) ? backup->len++ : 0;
	(backup->n >= 0) && (backup->plus || backup->space) ? backup->len++ : 0;
	if (backup->n == 0 && backup->precision && backup->precision_width == 0
		&& !backup->width)
	{
		free(str);
		return ;
	}
	if (backup->n == 0 && backup->precision && backup->precision_width == 0)
	{
		free(str);
		str = ft_strdup(" ");
	}
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}

void	ft_convert_uint(va_list ap, t_printf *backup)
{
	char	*str;
	char	*sp;

	backup->is_int = 1;
	ft_size_u(ap, backup);
	str = ft_uitoa(backup->u);
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
	sp = ft_print_sp(backup);
	ft_join_all(str, sp, backup);
}
