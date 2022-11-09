/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_should_end.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:22:09 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/08 23:22:21 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_should_end(t_data *data)
{
	pthread_mutex_lock(&data->counter_mutex);
	if (data->end_simulation)
	{
		pthread_mutex_unlock(&data->counter_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->counter_mutex);
	return (0);
}
