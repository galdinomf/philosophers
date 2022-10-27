/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:51 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/27 14:55:29 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo_ind *philo_ind, int fork_ind)
{
	int *forks;
	int	timestamp;

	forks = philo_ind->data->forks;
	forks[fork_ind] = 1;
	timestamp = get_timestamp(philo_ind->data);
	printf("%d %d has taken a fork\n", timestamp, philo_ind->ind + 1);
}

void	lay_fork_down(t_philo_ind *philo_ind, int fork_ind)
{
	int *forks;

	forks = philo_ind->data->forks;
	forks[fork_ind] = 0;
}

void	eat(t_philo_ind *philo_ind)
{
	t_data	*data;
	int		ind;
	int		timestamp;

	data = philo_ind->data;
	ind = philo_ind->ind;
	timestamp = get_timestamp(data);
	printf("%d %d is eating\n", timestamp, ind + 1);
	usleep(data->time_to_eat * 1000);
}

int	try_to_eat(t_philo_ind *philo_ind)
{
	t_data	*data;
	int		ind;
	int		left_ind;
	int		has_not_eaten;

	data = philo_ind->data;
	ind = philo_ind->ind;
	has_not_eaten = 1;
	if (ind == 0)
		left_ind = data->number_of_philosophers - 1;
	else
		left_ind = ind - 1;
	pthread_mutex_lock(&data->mutex);
	if ((data->forks[ind] == 0) && (data->forks[left_ind] == 0))
	{
		take_fork(philo_ind, ind);
		take_fork(philo_ind, left_ind);
		eat(philo_ind);
		has_not_eaten = 0;
		lay_fork_down(philo_ind, ind);
		lay_fork_down(philo_ind, left_ind);
	}
	pthread_mutex_unlock(&data->mutex);
	return (has_not_eaten);
}