/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:32:20 by jinspark          #+#    #+#             */
/*   Updated: 2021/03/23 22:32:21 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new;
	t_list	*begin;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new = ft_lstnew(f(lst->content))))
		return (NULL);
	tmp = lst;
	begin = new;
	while (tmp->next)
	{
		tmp = tmp->next;
		new->next = ft_lstnew(f(tmp->content));
		new = new->next;
	}
	return (begin);
}
