/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:43:29 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/27 12:39:17 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(t_data *data)
{
	struct timeval current_time;
	int		time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	//printf("time_ms - data->initial_time_ms = %d\n", time_ms - data->initial_time_ms);
	return (time_ms - data->initial_time_ms);
}