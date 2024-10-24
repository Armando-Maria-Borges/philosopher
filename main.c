/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:15:59 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 09:06:37 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		one_philosofo(philo);
		pthread_mutex_lock(&philo->env->stop_mutex);
		if (philo->env->stop_flag)
		{
			pthread_mutex_unlock(&philo->env->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->env->stop_mutex);
		if (time_to_die_exceeded(philo))
			break ;
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env				env;
	t_philosopher		*philosophers;

	if (validate_args(argc))
		return (1);
	initialize_env(&env, argc, argv);
	if (allocate_resources(&env, &philosophers))
		return (1);
	init_mutexes(&env);
	init_philosophers(philosophers, &env, argc);
	create_philosopher_threads(&env, philosophers);
	join_philosopher_threads(&env, philosophers);
	destroy_mutexes_and_free(&env, philosophers);
	return (0);
}
