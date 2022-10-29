/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:47:11 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/21 15:48:23 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	char			*p;
	unsigned int	i;

	total_size = nmemb * size;
	if ((nmemb != 0) && ((total_size / nmemb) != size))
		return (NULL);
	if ((size != 0) && (total_size / size != nmemb))
		return (NULL);
	p = (char *) malloc(total_size);
	i = 0;
	while ((i < total_size) && (p != NULL))
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
