/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:16:55 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/03 18:21:53 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	temp = ft_malloc((j + 1) * sizeof (char));
	if (!temp)
		return (0);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp [i] = '\0';
	return (temp);
}
