/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:03:46 by aionescu          #+#    #+#             */
/*   Updated: 2022/03/01 22:46:20 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philosopher
{
	pid_t							process_id;
	int								philo_id;
	useconds_t						time_to_die;
	useconds_t						time_to_sleep;
	useconds_t						time_to_eat;
	int								necessary_meals;
	int								meals;
	struct timeval					time_of_last_meal;
	int								alive;
	int								is_eating;
	int								is_sleeping;
	int								is_thinking;
	int								got_forks;
	int								dropped_forks;
}	t_philosopher;
int		handle_input(int argc, char **argv, int *array_of_args);
int		handle_arg(char *arg);
int		is_positive_number(char *arg);
void	philosopher_actions(t_philosopher *philosopher, sem_t *my_sem);
int		monitor_philosophers(t_philosopher *philosophers);
int		check_philosopher_alive(t_philosopher *philosopher);
void	custom_wait(int ms);
int		is_close_to_death(t_philosopher *philosopher);
int		calculate_usleep_time(t_philosopher *philosopher);
int		wait_for_tick(void);
int		no_one_dead(t_philosopher *philosopher);
int		not_all_finished(t_philosopher *philosopher);
char	*time_to_str(struct timeval *timestamp);
size_t	ft_strlen(const char *s);
char	*ft_itoa(long n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

#endif