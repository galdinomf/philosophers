/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:26:12 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/07 17:13:55 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(char *msg, t_philo_ind *philo_ind)
{
	t_data *data;
	int	ind;
	char	*s;
	char	*s2;
	int		time;

	data = 	((t_philo_ind *) philo_ind)->data;
	ind = ((t_philo_ind *) philo_ind)->ind;
	s = ft_strjoin("%d %d ", msg);
	s2 = ft_strjoin(s, "\n");
	time = get_timestamp(data);
	
	pthread_mutex_lock(&data->mutex);
	if (data->can_show_messages == 1)
		printf(s2, time, ind + 1);
	pthread_mutex_unlock(&data->mutex);
	free(s);
	free(s2);
}