/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:05:33 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/01 22:47:53 by aionescu         ###   ########.fr       */
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

void	lock_eat_unlock(t_philosopher *philo, sem_t *my_sem)
{
	sem_wait(my_sem);
	sem_wait(my_sem);
	philo->got_forks = 1;
	philo->is_eating = 1;
	philo->meals++;
	gettimeofday(&(philo->time_of_last_meal), NULL);
	usleep(philo->time_to_eat * 1000 - 2000);
	sem_post(my_sem);
	sem_post(my_sem);
	philo->dropped_forks = 1;
}

int	eat(t_philosopher *philosopher, sem_t *my_sem)
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
	lock_eat_unlock(philosopher, my_sem);
	return (1);
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

void	philosopher_actions(t_philosopher *philosopher, sem_t *my_sem)
{
	long long	thoughts;
	int			eating_successful;
	int			thinking_successful;
	struct timeval	start_time;
	struct timeval	finish_time;

	gettimeofday(&start_time, NULL);
	wait_for_tick();
	while (no_one_dead(philosopher)
		&& not_all_finished(philosopher))
	{
		wait_for_tick();
		thoughts = 0;
		thinking_successful = 1;
		eating_successful = 0;
		while (thinking_successful == 1 && eating_successful == 0)
		{
			wait_for_tick();
			thinking_successful = think(philosopher, thoughts);
			thoughts++;
			eating_successful = eat(philosopher, my_sem);
			printf("Philosopher %d alive = %d, meals = %d\n", philosopher->philo_id, philosopher->alive, philosopher->meals);
		}
		philosopher->is_sleeping = 1;
		usleep(philosopher->time_to_sleep * 1000 - 2000);
		check_philosopher_alive(philosopher);
		printf("Philosopher %d alive = %d, meals = %d\n", philosopher->philo_id, philosopher->alive, philosopher->meals);
		gettimeofday(&finish_time, NULL);
		if (finish_time.tv_sec - start_time.tv_sec > 10)
			exit(0);
	}
}
