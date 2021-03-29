/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:19 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/28 16:13:16 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dump_buffer(t_printf *backup)
{
	write(1, backup->buf, backup->buf_count);
	backup->buf_count = 0;
}

void	ft_add_to_buff(t_printf *backup, char *str, int len)
{
	int		i;

	i = 0;
	backup->ret += len;
	while (i < len)
	{
		backup->buf[backup->buf_count] = str[i];
		backup->buf_count++;
		if (backup->buf_count == BUFFER_SIZE)
			ft_dump_buffer(backup);
		i++;
	}
}

void	ft_print_normal(t_printf *backup, char *str)
{
	int		len;

	len = 0;
	while (str[backup->i] && str[backup->i] != '%')
	{
		backup->buf[backup->buf_count] = str[backup->i];
		backup->buf_count++;
		len++;
		if (backup->buf_count == BUFFER_SIZE)
			ft_dump_buffer(backup);
		backup->i++;
	}
	backup->ret += len;
	backup->i--;
}

void	ft_init_struct(t_printf *backup)
{
	backup->buf_count = 0;
	backup->ret = 0;
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
	backup->i = 0;
}

int		ft_printf(const char *str, ...)
{
	t_printf	backup;
	va_list		ap;

	ft_init_struct(&backup);
	va_start(ap, str);
	while (str[backup.i])
	{
		if (str[backup.i] == '%')
		{
			if (str[backup.i + 1] == '\0')
				break ;
			if (ft_from_sub(str[backup.i + 1]))
				ft_parse((char*)str, ap, &backup);
		}
		else
			ft_print_normal(&backup, (char*)str);
		backup.i++;
	}
	va_end(ap);
	ft_dump_buffer(&backup);
	return (backup.ret);
}
