/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:38:08 by aborges           #+#    #+#             */
/*   Updated: 2024/09/14 10:19:22 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philosofo(t_philosopher *philo)
{
	if (philo->env->num_philosophers == 1)
	{
		print_action(philo, "has taken a fork");
		sleep_for(philo->env->time_to_die, philo);
		pthread_mutex_lock(&philo->env->stop_mutex);
		print_action(philo, "died");
		philo->env->stop_flag = 1;
		pthread_mutex_unlock(&philo->env->stop_mutex);
		return (1);
	}
	return (0);
}

int	check_stop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->env->stop_mutex);
	if (philo->env->stop_flag)
	{
		pthread_mutex_unlock(&philo->env->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->stop_mutex);
	return (0);
}

int	check_num_meal(t_philosopher *philo)
{
	int	i;

	if (philo->env->num_max_meal == -1)
		return (0);
	i = 0;
	while (i < philo->env->num_philosophers)
	{
		pthread_mutex_lock(&philo->env->num_meal_mutex);
		if (philo[i].meals_count <= philo->env->num_max_meal)
		{
			pthread_mutex_unlock(&philo->env->num_meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->env->num_meal_mutex);
		i++;
	}
	return (1);
}
