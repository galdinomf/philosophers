/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:37:52 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/09 10:46:56 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks_mutex[i]);
	free(data->forks_mutex);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->eat_time_mutex[i]);
	free(data->eat_time_mutex);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->eat_counter_mutex[i]);
	free(data->eat_counter_mutex);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->counter_mutex);
	free(data->philos);
	free(data->forks);
	free(data->fork_used);
	free(data->counter);
	free(data->eat_time);
	free(data);
}
