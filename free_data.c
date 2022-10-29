/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:37:52 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/28 21:34:25 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks_mutex[i]);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->eat_time_mutex[i]);
	free(data->forks_mutex);
	free(data->eat_time_mutex);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->counter_mutex);
	free(data->philos);
	free(data->forks);
	free(data->counter);
	free(data->eat_time);
	free(data);
}