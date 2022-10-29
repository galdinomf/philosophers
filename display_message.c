/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:26:12 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/28 19:41:32 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(char *msg, t_philo_ind *philo_ind)
{
	t_data *data;
	int	ind;
	char	*s;
	char	*s2;

	data = 	((t_philo_ind *) philo_ind)->data;
	ind = ((t_philo_ind *) philo_ind)->ind;
	s = ft_strjoin("%d %d ", msg);
	s2 = ft_strjoin(s, "\n");
	if (data->all_alive)
		printf(s2, get_timestamp(data), ind + 1);
	free(s);
	free(s2);
}