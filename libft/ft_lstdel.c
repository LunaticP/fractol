/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 02:23:38 by aviau             #+#    #+#             */
/*   Updated: 2015/12/28 06:28:22 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (del)(void *, size_t))
{
	if ((*alst)->next)
	{
		ft_lstdel(&(*alst)->next, (*del));
	}
	ft_lstdelone(&(*alst), (*del));
}
