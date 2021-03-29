/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:02 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:29:10 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_sign(t_printf *bu)
{
	if (bu->n < 0)
	{
		bu->len--;
		ft_add_to_buff(bu, "-", 1);
	}
	else if (bu->plus && (bu->n >= 0))
	{
		bu->len--;
		ft_add_to_buff(bu, "+", 1);
	}
	else if (bu->space && !bu->plus && (bu->n >= 0))
	{
		bu->len--;
		ft_add_to_buff(bu, " ", 1);
	}
}

void	ft_add_prefix(t_printf *bu)
{
	if (bu->converter == 'x')
	{
		ft_add_to_buff(bu, "0x", 2);
		bu->len -= 2;
	}
	if (bu->converter == 'X')
	{
		ft_add_to_buff(bu, "0X", 2);
		bu->len -= 2;
	}
}

void	ft_join_all(char *str, char *sp, t_printf *bu)
{
	(bu->is_int && bu->zero) ? ft_add_sign(bu) : 0;
	if (bu->zero && bu->converter == 'p')
	{
		ft_add_to_buff(bu, "0x", 2);
		bu->len -= 2;
	}
	if (bu->sharp && bu->u && bu->zero && bu->precision_width < bu->len)
		ft_add_prefix(bu);
	if (sp && !bu->minus)
		ft_add_to_buff(bu, sp, bu->sp_len);
	if (!bu->zero && bu->converter == 'p')
	{
		ft_add_to_buff(bu, "0x", 2);
		bu->len -= 2;
	}
	if (bu->sharp && bu->u && !bu->zero && bu->precision_width < bu->len)
		ft_add_prefix(bu);
	if (bu->is_int && !bu->zero)
		ft_add_sign(bu);
	ft_add_to_buff(bu, str, bu->len);
	if (sp && bu->minus)
		ft_add_to_buff(bu, sp, bu->sp_len);
	free(str);
	free(sp);
}

char	*ft_print_sp(t_printf *bu)
{
	char	*str;
	int		i;

	i = 0;
	if (bu->width < bu->len)
		return (NULL);
	if (!(str = ft_calloc((bu->width - bu->len + 1), sizeof(char))))
		return (NULL);
	if (bu->precision && bu->precision_width > bu->len)
		bu->zero = 0;
	while (i < bu->width - bu->len)
	{
		if (bu->zero)
			str[i] = '0';
		else
			str[i] = ' ';
		i++;
	}
	bu->sp_len = i;
	str[i] = '\0';
	return (str);
}

char	*ft_num_precision(char *str, t_printf *bu)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!bu->precision)
		return (str);
	if (bu->precision_width < bu->len)
		return (str);
	if (!(tmp = ft_calloc(bu->precision_width + bu->len + 1, sizeof(char))))
		return (NULL);
	while (i < bu->precision_width - bu->len)
	{
		tmp[i] = '0';
		i++;
	}
	while (str[j])
	{
		tmp[i + j] = str[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(str);
	return (tmp);
}
