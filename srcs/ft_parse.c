/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:14 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/28 20:34:07 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_flag(char *str, va_list ap, t_printf *backup)
{
	if (str[backup->i] == '*')
	{
		if (backup->precision_parsing)
			backup->precision_width = va_arg(ap, int);
		else
			backup->width = va_arg(ap, int);
	}
	if (str[backup->i] == '0' && !backup->minus && !backup->precision_parsing)
		backup->zero = 1;
	if (str[backup->i] > '0' && str[backup->i] <= '9' && !backup->precision_parsing)
		backup->width = ft_atoi_printf(str, &backup->i);
	if (str[backup->i] >= '0' && str[backup->i] <= '9' && backup->precision_parsing)
		backup->precision_width = ft_atoi_printf(str, &backup->i);
	backup->precision_parsing = 0;
	if (str[backup->i] == '-')
	{
		backup->zero = 0;
		backup->minus = 1;
	}
	str[backup->i] == '.' ? ft_set_precision(backup) : 0;
	str[backup->i] == ' ' ? backup->space = 1 : 0;
	str[backup->i] == '+' ? backup->plus = 1 : 0;
	str[backup->i] == '#' ? backup->sharp = 1 : 0;
	str[backup->i] == 'l' ? backup->l_count += 1 : 0;
	str[backup->i] == 'h' ? backup->h_count += 1 : 0;
}

int		ft_parse2(char *str, va_list ap, t_printf *backup)
{
	char	*sp;
	char	*c;

	while (!ft_is_flag(str[backup->i]))
	{
		ft_check_flag(str, ap, backup);
		if (str[backup->i + 1] == '\0')
			return (0);
		if (!ft_from_sub(str[backup->i + 1]))
		{
			c = ft_c_to_str(str[backup->i + 1]);
			backup->len = 1;
			backup->minus ? ft_add_to_buff(backup, c, 1) : 0;
			sp = ft_print_sp(backup);
			ft_add_to_buff(backup, sp, backup->sp_len);
			!backup->minus ? ft_add_to_buff(backup, c, 1) : 0;
			free(c);
			free(sp);
			backup->i++;
			return (0);
		}
		backup->i++;
	}
	return (1);
}

void	ft_parse(char *str, va_list ap, t_printf *backup)
{
	backup->i++;
	ft_reset_flags(backup);
	if (!ft_parse2(str, ap, backup))
		return ;
	if (backup->width < 0)
	{
		backup->minus = 1;
		backup->zero = 0;
		backup->width = -backup->width;
	}
	if (backup->precision_width < 0)
		backup->precision = 0;
	backup->precision && backup->precision_width >= 0 ? backup->zero = 0 : 0;
	backup->converter = str[backup->i];
	str[backup->i] == 'c' ? ft_convert_c(ap, backup) : 0;
	str[backup->i] == 's' ? ft_convert_str(ap, backup) : 0;
	str[backup->i] == 'p' ? ft_convert_p(ap, backup) : 0;
	str[backup->i] == 'd' || str[backup->i] == 'i' ? ft_convert_int(ap, backup) : 0;
	str[backup->i] == 'u' ? ft_convert_uint(ap, backup) : 0;
	str[backup->i] == 'x' ? ft_convert_x(ap, backup) : 0;
	str[backup->i] == 'X' ? ft_convert_x(ap, backup) : 0;
	str[backup->i] == '%' ? ft_convert_c(ap, backup) : 0;
	str[backup->i] == 'n' ? ft_convert_n(ap, backup) : 0;
}

size_t	ft_is_flag(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
	|| c == 'u' || c == 'x' || c == 'n' || c == 'X' || c == '%');
}

size_t	ft_from_sub(char c)
{
	return (ft_is_flag(c) || (c >= '0' && c <= '9')
	|| c == '-' || c == ' ' || c == '.' || c == '+' || c == '#' || c == '*'
	|| c == 'l' || c == 'h');
}
