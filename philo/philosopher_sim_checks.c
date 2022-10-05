/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sim_checks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:05:04 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/02 17:50:41 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_close_to_death(t_philosopher *philosopher)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if ((current_time.tv_sec - philosopher->time_of_last_meal.tv_sec) * 1000
		+ (current_time.tv_usec - philosopher->time_of_last_meal.tv_usec) / 1000
		>= (philosopher->time_to_die / 3) * 2)
		return (1);
	else
		return (0);
}

int	calculate_usleep_time(t_philosopher *philosopher)
{
	if (philosopher->philo_id % 2 == 0)
		return (113);
	else
		return (613);
}

int	wait_for_tick(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	while (current_time.tv_usec % 1000 > 1)
	{
		gettimeofday(&current_time, NULL);
	}
	return (1);
}

int	no_one_dead(t_philosopher *philosopher)
{
	int				first_philosopher_id;
	t_philosopher	*current_philosopher;

	first_philosopher_id = philosopher->philo_id;
	current_philosopher = philosopher;
	while (current_philosopher->philo_id != -1)
	{
		if (current_philosopher->alive == 0)
			return (0);
		current_philosopher = current_philosopher + 1;
	}
	current_philosopher = philosopher - first_philosopher_id;
	while (current_philosopher != philosopher)
	{
		if (current_philosopher->alive == 0)
			return (0);
		current_philosopher = current_philosopher + 1;
	}
	return (1);
}

int	not_all_finished(t_philosopher *philosopher)
{
	int				first_philosopher_id;
	t_philosopher	*current_philosopher;

	if (philosopher->necessary_meals == 0)
		return (1);
	first_philosopher_id = philosopher->philo_id;
	current_philosopher = philosopher;
	while (current_philosopher->philo_id != -1)
	{
		if (current_philosopher->meals < current_philosopher->necessary_meals)
			return (1);
		current_philosopher = current_philosopher + 1;
	}
	current_philosopher = philosopher - first_philosopher_id;
	while (current_philosopher != philosopher)
	{
		if (current_philosopher->meals < current_philosopher->necessary_meals)
			return (1);
		current_philosopher = current_philosopher + 1;
	}
	return (0);
}
