/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:14 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:35 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_flag(char *str, va_list ap, t_printf *bu)
{
	if (str[bu->i] == '*')
	{
		if (bu->precision_parsing)
			bu->precision_width = va_arg(ap, int);
		else
			bu->width = va_arg(ap, int);
	}
	if (str[bu->i] == '0' && !bu->minus && !bu->precision_parsing)
		bu->zero = 1;
	if (str[bu->i] > '0' && str[bu->i] <= '9' && !bu->precision_parsing)
		bu->width = ft_atoi_printf(str, &bu->i);
	if (str[bu->i] >= '0' && str[bu->i] <= '9' && bu->precision_parsing)
		bu->precision_width = ft_atoi_printf(str, &bu->i);
	bu->precision_parsing = 0;
	if (str[bu->i] == '-')
	{
		bu->zero = 0;
		bu->minus = 1;
	}
	str[bu->i] == '.' ? ft_set_precision(bu) : 0;
	str[bu->i] == ' ' ? bu->space = 1 : 0;
	str[bu->i] == '+' ? bu->plus = 1 : 0;
	str[bu->i] == '#' ? bu->sharp = 1 : 0;
	str[bu->i] == 'l' ? bu->l_count += 1 : 0;
	str[bu->i] == 'h' ? bu->h_count += 1 : 0;
}

int		ft_parse2(char *str, va_list ap, t_printf *bu)
{
	char	*sp;
	char	*c;

	while (!ft_is_flag(str[bu->i]))
	{
		ft_check_flag(str, ap, bu);
		if (str[bu->i + 1] == '\0')
			return (0);
		if (!ft_from_sub(str[bu->i + 1]))
		{
			c = ft_c_to_str(str[bu->i + 1]);
			bu->len = 1;
			bu->minus ? ft_add_to_buff(bu, c, 1) : 0;
			sp = ft_print_sp(bu);
			ft_add_to_buff(bu, sp, bu->sp_len);
			!bu->minus ? ft_add_to_buff(bu, c, 1) : 0;
			free(c);
			free(sp);
			bu->i++;
			return (0);
		}
		bu->i++;
	}
	return (1);
}

void	ft_parse(char *str, va_list ap, t_printf *bu)
{
	bu->i++;
	ft_reset_flags(bu);
	if (!ft_parse2(str, ap, bu))
		return ;
	if (bu->width < 0)
	{
		bu->minus = 1;
		bu->zero = 0;
		bu->width = -bu->width;
	}
	if (bu->precision_width < 0)
		bu->precision = 0;
	bu->precision && bu->precision_width >= 0 ? bu->zero = 0 : 0;
	bu->converter = str[bu->i];
	str[bu->i] == 'c' ? ft_convert_c(ap, bu) : 0;
	str[bu->i] == 's' ? ft_convert_str(ap, bu) : 0;
	str[bu->i] == 'p' ? ft_convert_p(ap, bu) : 0;
	str[bu->i] == 'd' || str[bu->i] == 'i' ? ft_convert_int(ap, bu) : 0;
	str[bu->i] == 'u' ? ft_convert_uint(ap, bu) : 0;
	str[bu->i] == 'x' ? ft_convert_x(ap, bu) : 0;
	str[bu->i] == 'X' ? ft_convert_x(ap, bu) : 0;
	str[bu->i] == '%' ? ft_convert_c(ap, bu) : 0;
	str[bu->i] == 'n' ? ft_convert_n(ap, bu) : 0;
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
