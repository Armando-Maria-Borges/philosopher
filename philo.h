/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:29:02 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 08:46:19 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_env
{
	int				stop_flag;
	int				num_philosophers;
	int				num_max_meal;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;

	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	num_meal_mutex;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
}	t_env;

typedef struct s_philosopher
{
	int				id;
	int				meals_count;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_env			*env;
}	t_philosopher;

int			check_stop(t_philosopher *philo);
int			check_num_meal(t_philosopher *philo);
int			one_philosofo(t_philosopher *philo);
int			time_to_die_exceeded(t_philosopher *philo);
long long	get_current_time(void);

void		*philosopher_routine(void *arg);
void		take_forks(t_philosopher *philo);
void		release_forks(t_philosopher *philo);
void		eat(t_philosopher *philo);
void		sleep_and_think(t_philosopher *philo);
void		init_philosophers(t_philosopher *philosophers, t_env *env, int ac);
void		print_action(t_philosopher *philo, const char *action);
int			validate_args(int argc);
int			initialize_env(t_env *env, int argc, char **argv);
int			allocate_resources(t_env *env, t_philosopher **philosophers);

void		init_mutexes(t_env *env);
void		sleep_for(long long milliseconds, t_philosopher *philo);
void		create_philosopher_threads(t_env *env, t_philosopher *philosophers);
void		join_philosopher_threads(t_env *env, t_philosopher *philosophers);
void		destroy_mutexes_and_free(t_env *env, t_philosopher *philosophers);

int			check_arg(char **argv);
int			ft_atoi(char *str);

#endif
