/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:46:43 by yamzil            #+#    #+#             */
/*   Updated: 2022/07/24 16:26:52 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while ((s11[i] || s22[i]) && i < n)
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	i = 0;
	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;

	while (s11[i] || s22[i])
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}
