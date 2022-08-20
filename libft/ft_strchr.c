/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:10:08 by yamzil            #+#    #+#             */
/*   Updated: 2022/06/15 18:27:04 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*ss;

	i = 0;
	ss = (char *) s;
	cc = (char) c;
	while (ss[i] != cc && ss[i])
		i++;
	if (ss[i] == cc)
		return (&ss[i]);
	else
		return (NULL);
}
