/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:16:30 by tukaraca          #+#    #+#             */
/*   Updated: 2025/07/26 19:27:44 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_action(philo, "is thinking");
}

int	special_one(t_philo *philo)
{
	if (get_sim_end(philo->data))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	smart_sleep(philo->data->time_to_die, philo->data);
	print_action(philo, "died");
	set_sim_end(philo->data, 1);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		special_one(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->id * 50);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	while (!get_sim_end(philo->data))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
