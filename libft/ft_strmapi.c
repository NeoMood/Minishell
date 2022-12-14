/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:26:07 by yamzil            #+#    #+#             */
/*   Updated: 2022/09/05 21:58:30 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	int		j;
	char	*temp;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	temp = malloc ((j + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (s[i])
	{
		temp[i] = f (i, s[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
