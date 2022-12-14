/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:23:05 by mgaldino          #+#    #+#             */
/*   Updated: 2022/11/08 23:30:00 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		parameters[5];
	t_data	*data;

	if (check_input_and_initialize(argc, argv, parameters))
		return (1);
	data = initialize_data(parameters);
	initialize_simulation(data);
	free_data(data);
	return (0);
}
