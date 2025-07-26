/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:16:11 by tukaraca          #+#    #+#             */
/*   Updated: 2025/07/25 18:16:13 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
	{
		printf("Error: Argument is not correct!\n");
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (start_simulation(&data) != 0)
		return (1);
	end_simulation(&data);
	return (0);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;

	if (init_mutex(data) != 0)
		return (1);
	if (init_philosophers(data) != 0)
		return (1);
	data->start_time = get_time();
	if (init_threads(data) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, monitor_thread, data) != 0)
		return (1);
	pthread_join(monitor, NULL);
	return (0);
}
