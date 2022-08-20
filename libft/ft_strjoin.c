/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:06:53 by yamzil            #+#    #+#             */
/*   Updated: 2022/08/13 00:01:28 by yamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		n;
	char	*temp;

	i = 0;
	n = 0;
	if (!s1 || !s2)
		return (NULL);
	temp = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (s1[i])
		temp[n++] = s1[i++];
	i = 0;
	while (s2[i])
		temp[n++] = s2[i++];
	temp[n] = '\0';
	return (temp);
}

char    *ft_strjoin_v2(char *s1, char *s2)
{
    int		i;
    int		l;
    char	*temp;
    int		j;

    if (!s2)
        return (NULL);
    if (!s1)
    {
        s1 = (char *)malloc(1);
        s1[0] = '\0';
    }
    temp = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!temp)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
        temp[j++] = s1[i++];
    l = 0;
    while (s2[l])
        temp[j++] = s2[l++];
    temp[j] = '\0';
    free(s1);
    return (temp);
}

char	**ft_join2darray(char **tmp, char **temp)
{
    char	**new;
    int		i;
    int		j;
    int		k;

	i = 0;
    while (tmp[i])
		i++;
	j = 0;
    while (temp[j])
		j++;
	new = malloc ((i + j + 1) * sizeof(char *));
    if (!new)
        return (NULL);
	i = 0;
	k = 0;
	while (tmp[i])
		new[k++] = ft_strdup (tmp[i++]);
	j = 0;
    while (temp[j])
		new[k++] = ft_strdup (temp[j++]);
	new [k] = NULL;
	ft_free(tmp);
    ft_free(temp);
	return (new);
}