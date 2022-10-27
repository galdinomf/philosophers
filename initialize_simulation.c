/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:19:42 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/26 11:20:06 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ind_i)
{
	t_data	*data;
	int	c;
	int	ind;

	printf("data->time_to_die = %d\n", ((t_philo_ind *) philo_ind_i)->data->time_to_die);
	data = 	((t_philo_ind *) philo_ind_i)->data;
	ind = ((t_philo_ind *) philo_ind_i)->ind;
	c = 0;
	while (c <= data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&data->forks[ind]);
		printf("started eating\n");
		if (ind == 0)
			pthread_mutex_lock(&data->forks[data->number_of_philosophers]);
		else
			pthread_mutex_lock(&data->forks[ind - 1]);
		usleep(data->time_to_eat * 1000);
		printf("finished eating\n");
		pthread_mutex_unlock(&data->forks[ind]);
		c++;
		if (ind == 0)
			pthread_mutex_unlock(&data->forks[data->number_of_philosophers]);
		else
			pthread_mutex_unlock(&data->forks[ind - 1]);
		printf("started sleeping\n");
		usleep(data->time_to_sleep * 1000);
		printf("finished sleeping\n");
	}
	
	return (NULL);
}

int	initialize_simulation(t_data *data)
{
	int	i;
	t_philo_ind	**philo_ind;

	philo_ind = initialize_philo_ind(data);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		
		if (pthread_create(&data->philos[i], NULL, &routine, philo_ind[i]))
			return (1);
		printf("Thread #%d started\n", i);
	}

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(data->philos[i], NULL))
			return (2);
		printf("Thread #%d finished\n", i);
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		free(philo_ind[i]);
	free(philo_ind);
	return (0);
}
