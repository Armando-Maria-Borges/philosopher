/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:38:45 by aborges           #+#    #+#             */
/*   Updated: 2024/09/11 10:16:16 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philosopher_threads(t_env *env, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < env->num_philosophers)
	{
		pthread_create(&philosophers[i].thread, NULL,
			philosopher_routine, (void *)&philosophers[i]);
		i++;
	}
}

void	init_mutexes(t_env *env)
{
	int	i;

	pthread_mutex_init(&env->print_mutex, NULL);
	pthread_mutex_init(&env->stop_mutex, NULL);
	pthread_mutex_init(&env->eat_mutex, NULL);
	pthread_mutex_init(&env->meals_mutex, NULL);
	pthread_mutex_init(&env->num_meal_mutex, NULL);
	i = 0;
	while (i < env->num_philosophers)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
}

void	join_philosopher_threads(t_env *env, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < env->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

void	destroy_mutexes_and_free(t_env *env, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < env->num_philosophers)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->print_mutex);
	pthread_mutex_destroy(&env->stop_mutex);
	pthread_mutex_destroy(&env->eat_mutex);
	pthread_mutex_destroy(&env->meals_mutex);
	pthread_mutex_destroy(&env->num_meal_mutex);
	free(philosophers);
	free(env->forks);
}
