/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:38:34 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 10:24:48 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_philosopher *philosophers, t_env *env, int ac)
{
	int	i;

	i = 0;
	while (i < env->num_philosophers)
	{
		philosophers[i].env = env;
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &env->forks[i];
		philosophers[i].right_fork = &env->forks[(i + 1)
			% env->num_philosophers];
		philosophers[i].last_meal_time = env->start_time;
		if (ac == 6)
			philosophers[i].meals_count = 0;
		i++;
	}
}

int	initialize_env(t_env *env, int argc, char **argv)
{
	if (!check_arg(argv))
	{
		printf("error!");
		printf("\nUse: ./philo (number of philosophers) ");
		printf("(time to die) (time to eat) (time to sleep)\n");
		return (0);
	}
	env->num_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->start_time = get_current_time();
	env->stop_flag = 0;
	if (argc == 6)
		env->num_max_meal = ft_atoi(argv[5]);
	else
		env->num_max_meal = -1;
	return (0);
}

int	allocate_resources(t_env *env, t_philosopher **philosophers)
{
	*philosophers = malloc(sizeof(t_philosopher) * env->num_philosophers);
	if (!*philosophers)
	{
		printf("Failed to allocate memory for philosophers");
		return (1);
	}
	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_philosophers);
	if (!env->forks)
	{
		printf("Failed to allocate memory for forks");
		free(*philosophers);
		return (1);
	}
	return (0);
}

int	validate_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Use: ./philo (number of philosophers) ");
		printf("(time to die) (time to eat)");
		printf(" (time to sleep) (max number meal)\n");
		return (1);
	}
	return (0);
}
