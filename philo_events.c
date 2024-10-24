/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:43:23 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 09:52:11 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!check_stop(philo) && !check_num_meal(philo))
			print_action(philo, "has taken a fork left");
		pthread_mutex_lock(philo->right_fork);
		if (!check_stop(philo) && !check_num_meal(philo))
			print_action(philo, "has taken a fork right");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!check_stop(philo) && !check_num_meal(philo))
			print_action(philo, "has taken a fork right");
		pthread_mutex_lock(philo->left_fork);
		if (!check_stop(philo) && !check_num_meal(philo))
			print_action(philo, "has taken a fork left");
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philosopher *philo)
{
	if (!check_stop(philo) && !check_num_meal(philo))
	{
		pthread_mutex_lock(&philo->env->eat_mutex);
		if (!check_stop(philo))
			print_action(philo, "is eating");
		philo->last_meal_time = get_current_time();
		sleep_for(philo->env->time_to_eat, philo);
		pthread_mutex_unlock(&philo->env->eat_mutex);
		pthread_mutex_lock(&philo->env->num_meal_mutex);
		philo->meals_count += 1;
		pthread_mutex_unlock(&philo->env->num_meal_mutex);
	}
}

void	sleep_and_think(t_philosopher *philo)
{
	if (!check_stop(philo) && !check_num_meal(philo))
	{
		print_action(philo, "is sleeping");
		sleep_for(philo->env->time_to_eat, philo);
	}
	if (!check_stop(philo) && !check_num_meal(philo))
		print_action(philo, "is thinking");
}
