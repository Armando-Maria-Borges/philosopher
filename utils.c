/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:05:18 by aborges           #+#    #+#             */
/*   Updated: 2024/09/13 08:46:47 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philosopher *philo,
		const char *action)
{
	pthread_mutex_lock(&philo->env->print_mutex);
	printf("%lld %d %s\n",
		get_current_time() - philo->env->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->env->print_mutex);
}

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	result = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (result);
	else
		return (0);
}
