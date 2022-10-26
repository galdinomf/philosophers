/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:59 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/25 21:26:44 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*initialize_data(int *parameters)
{
	t_data	*data;
	int		n_philos;
	struct timeval initial_time;

	n_philos = parameters[0];
	data = (t_data *) malloc(sizeof(t_data));
	data->time_to_die = parameters[1];
	data->time_to_eat = parameters[2];
	data->time_to_sleep = parameters[3];
	data->number_of_times_each_philosopher_must_eat = parameters[4];
	data->number_of_philosophers = n_philos;
	data->philos = (pthread_t *) malloc((n_philos) * sizeof(pthread_t));
	data->forks = (pthread_mutex_t *) malloc((n_philos) * \
										sizeof(pthread_mutex_t));
	gettimeofday(&initial_time, NULL);
	data->initial_time_ms = (initial_time.tv_sec * 1000) + \
								(initial_time.tv_usec / 1000);
	return (data);
}

t_philo_ind	**initialize_philo_ind(t_data *data)
{
	t_philo_ind	**philo_inds;
	int			i;
	int			n_philos;

	n_philos = data->number_of_philosophers;
	philo_inds = (t_philo_ind **) malloc((n_philos) * sizeof(t_philo_ind *));
	i = -1;
	while (++i < n_philos)
	{
		philo_inds[i] = (t_philo_ind *) malloc(sizeof(t_philo_ind));
		philo_inds[i]->ind = i;
		philo_inds[i]->data = data;
	}
	return (philo_inds);
}