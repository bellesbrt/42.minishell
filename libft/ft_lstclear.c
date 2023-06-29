/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:00:25 by inicole-          #+#    #+#             */
/*   Updated: 2023/05/26 18:46:40 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*next_cursor;

	if (!lst)
		return ;
	cursor = *lst;
	while (cursor)
	{
		next_cursor = cursor->next;
		ft_lstdelone(cursor, del);
		cursor = next_cursor;
	}
	*lst = NULL;
}
