/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:29:32 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/29 18:30:03 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct	s_printf
{
	char			buf[BUFFER_SIZE + 1];
	int				buf_count;
	int				ret;
	int				width;
	int				precision;
	int				precision_width;
	int				precision_parsing;
	int				converter;
	int				minus;
	int				zero;
	int				plus;
	int				space;
	int				sharp;
	int				len;
	int				sp_len;
	int				is_int;
	int				h_count;
	int				l_count;
	intmax_t		n;
	uintmax_t		u;
	int				i;
}				t_printf;

int				ft_printf(const char *str, ...);
void			ft_init_struct(t_printf *bu);
void			ft_str_it(va_list ap, t_printf *bu, char *str);
void			ft_parse(char *str, va_list ap, t_printf *bu);
void			ft_check_flag(char *str, va_list ap, t_printf *bu);
void			ft_add_to_buff(t_printf *bu, char *str, int len);
void			ft_dump_buffer(t_printf *bu);
void			ft_convert_str(va_list ap, t_printf *bu);
void			ft_convert_int(va_list ap, t_printf *bu);
void			ft_convert_uint(va_list ap, t_printf *bu);
void			ft_convert_x(va_list ap, t_printf *bu);
void			ft_convert_p(va_list ap, t_printf *bu);
void			ft_convert_c(va_list ap, t_printf *bu);
void			ft_convert_n(va_list ap, t_printf *bu);
void			ft_convert_o(va_list ap, t_printf *bu);
void			ft_size_u(va_list ap, t_printf *bu);
char			*ft_strdup_l(char *s, t_printf *bu);
char			*ft_print_sp(t_printf *bu);
char			*ft_num_precision(char *str, t_printf *bu);
void			ft_join_all(char *str, char *sp, t_printf *bu);
char			*ft_c_to_str(char c);
void			ft_add_sign(t_printf *bu);
int				ft_atoi_printf(char *str, int *i);
char			*itoa_printf(intmax_t n);
char			*uitoa_printf(uintmax_t n);
char			*itoa_base_pf(uintmax_t num, char *base);
size_t			intlen_printf(intmax_t n);
size_t			uintlen_printf(uintmax_t n);
size_t			intlen_base_pf(uintmax_t n, char *base);
void			ft_set_precision(t_printf *bu);
void			ft_reset_flags(t_printf *bu);
size_t			ft_is_flag(char c);
size_t			ft_from_sub(char c);

#endif
