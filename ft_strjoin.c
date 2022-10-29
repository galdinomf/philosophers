/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:34:50 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/21 16:35:19 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint_str;
	int		i;
	int		len_s1;
	int		len_s2;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	joint_str = (char *) malloc(len_s1 + len_s2 + 1);
	if (joint_str == NULL)
		return (NULL);
	i = -1;
	while (i++ < len_s1)
		joint_str[i] = s1[i];
	i = -1;
	while (i++ < len_s2)
		joint_str[len_s1 + i] = s2[i];
	joint_str[len_s1 + len_s2] = '\0';
	return (joint_str);
}

static size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
