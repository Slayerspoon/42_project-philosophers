/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:43:53 by aionescu          #+#    #+#             */
/*   Updated: 2022/02/27 20:58:00 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	comment_actions_set1(t_philosopher *philosopher, char *time_str)
{
	char	*philo_id_str;

	philo_id_str = ft_itoa(philosopher->philo_id);
	if (philosopher->is_thinking == 1)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " is thinking.\n", 15);
		philosopher->is_thinking = 0;
	}
	free(philo_id_str);
}

void	comment_actions_set2(t_philosopher *philosopher, char *time_str)
{
	char	*philo_id_str;

	philo_id_str = ft_itoa(philosopher->philo_id);
	if (philosopher->got_forks == 1)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " has taken a fork.\n", 20);
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " has taken a fork.\n", 20);
		philosopher->got_forks = 0;
	}
	if (philosopher->is_eating == 1)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " is eating.\n", 13);
		philosopher->is_eating = 0;
	}
	free(philo_id_str);
}

void	comment_actions_set3(t_philosopher *philosopher, char *time_str)
{
	char			*philo_id_str;

	philo_id_str = ft_itoa(philosopher->philo_id);
	if (philosopher->is_sleeping == 1)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " is sleeping.\n", 15);
		philosopher->is_sleeping = 0;
	}
	if (check_philosopher_alive(philosopher) == 0)
	{
		write(1, time_str, ft_strlen(time_str));
		write(1, " Philosopher ", 14);
		write(1, philo_id_str, ft_strlen(philo_id_str));
		write(1, " died.\n", 8);
	}
	free(philo_id_str);
}

int	necessary_meals_reached(t_philosopher *philosophers)
{
	int	index;
	int	necessary_meals;
	int	meals;

	index = 0;
	while (philosophers[index].philo_id != -1)
	{
		necessary_meals = philosophers[index].necessary_meals;
		meals = philosophers[index].meals;
		if (meals < necessary_meals)
			return (0);
		index++;
	}
	return (1);
}

int	monitor_philosophers(t_philosopher *philosophers)
{
	int				index;
	struct timeval	timestamp;

	timestamp.tv_sec = 0;
	timestamp.tv_usec = 0;
	index = 0;
	while (philosophers[index].philo_id != -1)
	{
		gettimeofday(&timestamp, NULL);
		comment_actions_set1(&philosophers[index], time_to_str(&timestamp));
		gettimeofday(&timestamp, NULL);
		comment_actions_set2(&philosophers[index], time_to_str(&timestamp));
		gettimeofday(&timestamp, NULL);
		comment_actions_set3(&philosophers[index], time_to_str(&timestamp));
		if (philosophers[index].necessary_meals > 0)
		{
			if (necessary_meals_reached(philosophers) == 1)
				return (2);
		}
		if (philosophers[index].alive == 0)
			return (1);
		index++;
	}
	return (0);
}
