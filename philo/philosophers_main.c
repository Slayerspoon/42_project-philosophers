/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:03:18 by aionescu          #+#    #+#             */
/*   Updated: 2022/02/27 20:26:48 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher_values(t_philosopher *philo, int *args, int index)
{
	philo->philo_id = index;
	pthread_mutex_init(&(philo->mutex), NULL);
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_to_sleep = args[3];
	philo->necessary_meals = args[4];
	philo->meals = 0;
	gettimeofday(&(philo->time_of_last_meal), NULL);
	philo->alive = 1;
	philo->is_eating = 0;
	philo->is_sleeping = 0;
	philo->is_thinking = 0;
	philo->own_fork_free = 1;
	philo->got_forks = 0;
	philo->dropped_forks = 0;
}

t_philosopher	*create_philosophers(int *array_of_args)
{
	t_philosopher	*philosophers;
	int				index;

	philosophers = malloc(sizeof(t_philosopher) * (array_of_args[0] + 1));
	philosophers[array_of_args[0]].philo_id = -1;
	philosophers[array_of_args[0]].own_fork_free = 0;
	if (philosophers == NULL)
	{
		printf("Error: Could not allocate philosophers!\n");
		return (NULL);
	}
	index = 0;
	while (index < array_of_args[0])
	{
		init_philosopher_values(philosophers + index, array_of_args, index);
		if (pthread_create(&((philosophers + index)->thread), NULL,
				philosopher_actions, &philosophers[index]) != 0)
		{
			printf("Error: Could not create thread %d!\n", index);
			free(philosophers);
			return (NULL);
		}
		index++;
	}
	return (philosophers);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosophers;
	int				array_of_args[5];
	int				status;
	int				index;

	if (handle_input(argc, argv, array_of_args) != 0)
		return (1);
	philosophers = create_philosophers(array_of_args);
	if (philosophers == NULL)
		return (2);
	status = 0;
	while (status == 0)
		status = monitor_philosophers(philosophers);
	index = 0;
	while (philosophers[index].philo_id != -1)
	{
		pthread_join(philosophers[index].thread, NULL);
		index++;
	}
	free(philosophers);
	return (0);
}
