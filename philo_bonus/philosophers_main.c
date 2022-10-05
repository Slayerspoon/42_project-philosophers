/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:03:18 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/01 22:41:49 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher_values(t_philosopher *philo, int *args, int index)
{
	philo->process_id = -666;
	philo->philo_id = index;
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
	philo->got_forks = 0;
	philo->dropped_forks = 0;
}

t_philosopher	*create_philosophers(int *array_of_args)
{
	t_philosopher	*philosophers;
	int				index;

	philosophers = malloc(sizeof(t_philosopher) * (array_of_args[0] + 1));
	philosophers[array_of_args[0]].philo_id = -1;
	if (philosophers == NULL)
	{
		printf("Error: Could not allocate philosophers!\n");
		return (NULL);
	}
	index = 0;
	while (index < array_of_args[0])
	{
		init_philosopher_values(philosophers + index, array_of_args, index);
		index++;
	}
	return (philosophers);
}

pid_t	fork_processes(t_philosopher *philosophers, int total, sem_t *my_sem)
{
	pid_t	new_process_id;
	int		index;
	// int		index_b;

	index = 0;
	new_process_id = fork();
	philosophers[index].process_id = new_process_id;
	if (new_process_id == 0)
		philosopher_actions(philosophers, my_sem);
	else
	{
		index++;
		while (index < total)
		{
			if (new_process_id > 0)
				new_process_id = fork();
			philosophers[index].process_id = new_process_id;
			if (new_process_id == 0)
			{
				// index_b = 0;
				// while (index_b < total)
				// {
				// 	printf("From child %d... Child %d id: %d\n", index, index_b, philosophers[index_b].process_id);
				// 	index_b++;
				// }
				philosopher_actions(philosophers + index, my_sem);
				break ;
			}
			index++;
		}
	}
	return (new_process_id);
}

void	wait_for_all(t_philosopher *philosophers, int total)
{
	int	index;

	index = 0;
	while (index < total)
	{
		printf("Waiting for %d\n", philosophers[index].process_id);
		waitpid(philosophers[index].process_id, NULL, 0);
		index++;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosophers;
	int				array_of_args[5];
	sem_t			*my_sem;
	pid_t			process_id;
	int				status;
	// int				index;

	if (handle_input(argc, argv, array_of_args) != 0)
		return (1);
	philosophers = create_philosophers(array_of_args);
	if (philosophers == NULL)
		return (2);
	my_sem = sem_open("forks", O_CREAT, 0644, 5);
	process_id = fork_processes(philosophers, array_of_args[0], my_sem);
	if (process_id > 0)
	{
		// index = 0;
		// while (index < array_of_args[0])
		// {
		// 	printf("Child %d id: %d\n", index, philosophers[index].process_id);
		// 	index++;
		// }
		usleep(3000000);
		printf("id 0 Meals: %d\n", philosophers[0].meals);
		status = 0;
		while (status == 0)
			status = monitor_philosophers(philosophers);
		wait_for_all(philosophers, array_of_args[0]);
	}
	sem_close(my_sem);
	sem_unlink("forks");
	free(philosophers);
	return (0);
}
