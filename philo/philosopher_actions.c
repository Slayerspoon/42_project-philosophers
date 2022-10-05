/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:05:33 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/02 17:57:07 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	u_wait(int usec_to_wait, t_philosopher *philosopher)
{
	struct timeval	current_time;
	struct timeval	target_time;
	int				sec_to_wait;

	if (usec_to_wait < 1)
		return ;
	sec_to_wait = usec_to_wait / 1000000;
	if (usec_to_wait >= 1000000)
		usec_to_wait = usec_to_wait % 1000000;
	gettimeofday(&current_time, NULL);
	target_time.tv_sec = current_time.tv_sec + sec_to_wait;
	target_time.tv_usec = current_time.tv_usec + usec_to_wait;
	while (current_time.tv_sec < target_time.tv_sec)
	{
		if (no_one_dead(philosopher) == 0)
			return ;
		gettimeofday(&current_time, NULL);
	}
	while (current_time.tv_usec < target_time.tv_usec)
	{
		if (no_one_dead(philosopher) == 0)
			return ;
		gettimeofday(&current_time, NULL);
	}
}

void	lock_eat_unlock(t_philosopher *philo, t_philosopher *left_philo)
{
	if (philo->own_fork_free)
	{
		pthread_mutex_lock(&(philo->mutex));
		pthread_mutex_lock(&(left_philo->mutex));
	}
	else
	{
		pthread_mutex_lock(&(left_philo->mutex));
		pthread_mutex_lock(&(philo->mutex));
	}
	philo->own_fork_free = 0;
	left_philo->own_fork_free = 0;
	philo->got_forks = 1;
	philo->is_eating = 1;
	philo->meals++;
	gettimeofday(&(philo->time_of_last_meal), NULL);
	usleep(philo->time_to_eat * 1000 - 2000);
	pthread_mutex_unlock(&(left_philo->mutex));
	pthread_mutex_unlock(&(philo->mutex));
	philo->own_fork_free = 1;
	left_philo->own_fork_free = 1;
	philo->dropped_forks = 1;
}

int	eat(t_philosopher *philosopher)
{
	t_philosopher	*philosopher_to_the_left;
	t_philosopher	*last_philosopher;

	last_philosopher = philosopher;
	while (last_philosopher->philo_id != -1)
		last_philosopher = last_philosopher + 1;
	if (philosopher->philo_id == 0)
		philosopher_to_the_left = last_philosopher - 1;
	else
		philosopher_to_the_left = philosopher - 1;
	if (philosopher == philosopher_to_the_left)
		return (0);
	if ((philosopher->own_fork_free && philosopher_to_the_left->own_fork_free)
		|| is_close_to_death(philosopher))
	{
		lock_eat_unlock(philosopher, philosopher_to_the_left);
		return (1);
	}
	return (0);
}

int	think(t_philosopher *philosopher, int thoughts)
{
	struct timeval	current_time;

	if (thoughts == 0)
		philosopher->is_thinking = 1;
	gettimeofday(&current_time, NULL);
	if ((current_time.tv_sec - philosopher->time_of_last_meal.tv_sec) * 1000
		+ (current_time.tv_usec - philosopher->time_of_last_meal.tv_usec) / 1000
		>= philosopher->time_to_die)
	{
		philosopher->alive = 0;
		return (0);
	}
	usleep(calculate_usleep_time(philosopher));
	gettimeofday(&current_time, NULL);
	if ((current_time.tv_sec - philosopher->time_of_last_meal.tv_sec) * 1000
		+ (current_time.tv_usec - philosopher->time_of_last_meal.tv_usec) / 1000
		>= philosopher->time_to_die)
	{
		philosopher->alive = 0;
		return (0);
	}
	return (1);
}

void	*philosopher_actions(void *philosopher)
{
	long long	thoughts;
	int			eating_successful;
	int			thinking_successful;

	wait_for_first_tick();
	while (no_one_dead((t_philosopher *)philosopher)
		&& not_all_finished((t_philosopher *)philosopher))
	{
		wait_for_tick();
		thoughts = 0;
		thinking_successful = 1;
		eating_successful = 0;
		while (thinking_successful == 1 && eating_successful == 0)
		{
			wait_for_tick();
			thinking_successful = think((t_philosopher *)philosopher, thoughts);
			thoughts++;
			eating_successful = eat((t_philosopher *)philosopher);
		}
		((t_philosopher *)philosopher)->is_sleeping = 1;
		usleep(((t_philosopher *)philosopher)->time_to_sleep * 1000 - 2000);
		check_philosopher_alive((t_philosopher *)philosopher);
	}
	return (NULL);
}
