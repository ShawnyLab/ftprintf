/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:02 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/28 23:14:26 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_sign(t_printf *backup)
{
	if (backup->n < 0)
	{
		backup->len--;
		ft_add_to_buff(backup, "-", 1);
	}
	else if (backup->plus && (backup->n >= 0))
	{
		backup->len--;
		ft_add_to_buff(backup, "+", 1);
	}
	else if (backup->space && !backup->plus && (backup->n >= 0))
	{
		backup->len--;
		ft_add_to_buff(backup, " ", 1);
	}
}

void	ft_add_prefix(t_printf *backup)
{
	if (backup->converter == 'x')
	{
		ft_add_to_buff(backup, "0x", 2);
		backup->len -= 2;
	}
	if (backup->converter == 'X')
	{
		ft_add_to_buff(backup, "0X", 2);
		backup->len -= 2;
	}
}

void	ft_join_all(char *str, char *sp, t_printf *backup)
{
	(backup->is_int && backup->zero) ? ft_add_sign(backup) : 0;
	if (backup->zero && backup->converter == 'p')
	{
		ft_add_to_buff(backup, "0x", 2);
		backup->len -= 2;
	}
	if (backup->sharp && backup->u && backup->zero && backup->precision_width < backup->len)
		ft_add_prefix(backup);
	if (sp && !backup->minus)
		ft_add_to_buff(backup, sp, backup->sp_len);
	if (!backup->zero && backup->converter == 'p')
	{
		ft_add_to_buff(backup, "0x", 2);
		backup->len -= 2;
	}
	if (backup->sharp && backup->u && !backup->zero && backup->precision_width < backup->len)
		ft_add_prefix(backup);
	if (backup->is_int && !backup->zero)
		ft_add_sign(backup);
	ft_add_to_buff(backup, str, backup->len);
	if (sp && backup->minus)
		ft_add_to_buff(backup, sp, backup->sp_len);
	free(str);
	free(sp);
}

char	*ft_print_sp(t_printf *backup)
{
	char	*str;
	int		i;

	i = 0;
	if (backup->width < backup->len)
		return (NULL);
	if (!(str = ft_calloc((backup->width - backup->len + 1), sizeof(char))))
		return (NULL);
	if (backup->precision && backup->precision_width > backup->len)
		backup->zero = 0;
	while (i < backup->width - backup->len)
	{
		if (backup->zero)
			str[i] = '0';
		else
			str[i] = ' ';
		i++;
	}
	backup->sp_len = i;
	str[i] = '\0';
	return (str);
}

char	*ft_num_precision(char *str, t_printf *backup)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!backup->precision)
		return (str);
	if (backup->precision_width < backup->len)
		return (str);
	if (!(tmp = ft_calloc(backup->precision_width + backup->len + 1, sizeof(char))))
		return (NULL);
	while (i < backup->precision_width - backup->len)
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
