/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:37:52 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/27 14:49:13 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data->philos);
	free(data->forks);
	free(data);
}