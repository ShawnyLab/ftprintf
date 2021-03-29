/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:19 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:28 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dump_buffer(t_printf *bu)
{
	write(1, bu->buf, bu->buf_count);
	bu->buf_count = 0;
}

void	ft_add_to_buff(t_printf *bu, char *str, int len)
{
	int		i;

	i = 0;
	bu->ret += len;
	while (i < len)
	{
		bu->buf[bu->buf_count] = str[i];
		bu->buf_count++;
		if (bu->buf_count == BUFFER_SIZE)
			ft_dump_buffer(bu);
		i++;
	}
}

void	ft_print_normal(t_printf *bu, char *str)
{
	int		len;

	len = 0;
	while (str[bu->i] && str[bu->i] != '%')
	{
		bu->buf[bu->buf_count] = str[bu->i];
		bu->buf_count++;
		len++;
		if (bu->buf_count == BUFFER_SIZE)
			ft_dump_buffer(bu);
		bu->i++;
	}
	bu->ret += len;
	bu->i--;
}

void	ft_init_struct(t_printf *bu)
{
	bu->buf_count = 0;
	bu->ret = 0;
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
	bu->i = 0;
}

int		ft_printf(const char *str, ...)
{
	t_printf	bu;
	va_list		ap;

	ft_init_struct(&bu);
	va_start(ap, str);
	while (str[bu.i])
	{
		if (str[bu.i] == '%')
		{
			if (str[bu.i + 1] == '\0')
				break ;
			if (ft_from_sub(str[bu.i + 1]))
				ft_parse((char*)str, ap, &bu);
		}
		else
			ft_print_normal(&bu, (char*)str);
		bu.i++;
	}
	va_end(ap);
	ft_dump_buffer(&bu);
	return (bu.ret);
}
