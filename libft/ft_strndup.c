/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 04:33:54 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 06:56:17 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int len)
{
	int		i;
	char	*ss;

	i = -1;
	if ((ss = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (s[++i] && i < len)
		ss[i] = s[i];
	ss[i] = '\0';
	return (ss);
}
