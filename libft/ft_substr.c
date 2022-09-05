/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:49:09 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 22:34:52 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*temp;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen (&s[start]) < len)
	{
		temp = malloc (ft_strlen(&s[start] + 1) * sizeof(char));
		ft_addbackthegarbe(&g_mode.trash, ft_newgarbage(temp));
	}
	else
		temp = malloc((len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_addbackthegarbe(&g_mode.trash, ft_newgarbage(temp));
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	while (len > i && s[i + start])
	{
		temp[i] = s[i + start];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
