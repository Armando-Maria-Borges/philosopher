/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:38:59 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 08:47:00 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_for(long long milliseconds, t_philosopher *philo)
{
	long long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < milliseconds)
	{
		if (time_to_die_exceeded(philo))
			break ;
		usleep(100);
	}
}

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time);
}

int	time_to_die_exceeded(t_philosopher *philo)
{
	long long	current_time;

	current_time = get_current_time();
	if (check_stop(philo))
		return (0);
	pthread_mutex_lock(&philo->env->stop_mutex);
	if (current_time - philo->last_meal_time >= philo->env->time_to_die)
	{
		if (!check_num_meal(philo))
			print_action(philo, "died");
		philo->env->stop_flag = 1;
		pthread_mutex_unlock(&philo->env->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->stop_mutex);
	return (0);
}
