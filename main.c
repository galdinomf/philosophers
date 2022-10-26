/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:23:05 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/25 21:29:09 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int	parameters[5];
	int	i;
	t_data	*data;


	if (check_input_and_initialize(argc, argv, parameters))
		return (1);
	data = initialize_data(parameters);
	usleep(1000000);
	i = get_time_stamp(data);
	printf("timestamp = %d\n", i);
	initialize_simulation(data);
	/*
	printf("data->number_of_philosophers = %d\n", data->number_of_philosophers);
	printf("data->time_to_die = %d\n", data->time_to_die);
	printf("data->time_to_eat = %d\n", data->time_to_eat);
	printf("data->time_to_sleep = %d\n", data->time_to_sleep);
	printf("data->number_of_times_each_philosopher_must_eat = %d\n", data->number_of_times_each_philosopher_must_eat);
	*/
	free_data(data);
	return (0);
}