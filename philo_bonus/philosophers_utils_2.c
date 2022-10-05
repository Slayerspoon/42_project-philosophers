/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:45:55 by aionescu          #+#    #+#             */
/*   Updated: 2022/02/28 19:41:09 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	length;

	length = ft_strlen(src);
	index = 0;
	if (!dest || !src)
		return (0);
	if (size > 0)
	{
		while (index < size - 1 && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (length);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	start;
	size_t	result;

	start = ft_strlen(dest);
	index = 0;
	if (ft_strlen(dest) < size)
	{
		result = ft_strlen(dest) + ft_strlen(src);
		while (((start + index) < (size - 1)) && (src[index] != '\0'))
		{
			dest[start + index] = src[index];
			index++;
		}
		dest[start + index] = '\0';
	}
	else
		result = ft_strlen(src) + size;
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 != NULL && s2 != NULL)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		str_new = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
		if (str_new != NULL)
		{
			ft_strlcpy(str_new, s1, len_s1 + 1);
			ft_strlcat(str_new, s2, len_s1 + len_s2 + 1);
		}
	}
	else
		str_new = NULL;
	return (str_new);
}

int	check_philosopher_alive(t_philosopher *philosopher)
{
	struct timeval	current_time;

	current_time.tv_sec = 0;
	current_time.tv_usec = 0;
	gettimeofday(&current_time, NULL);
	if ((current_time.tv_sec - philosopher->time_of_last_meal.tv_sec) * 1000
		+ (current_time.tv_usec - philosopher->time_of_last_meal.tv_usec) / 1000
		>= philosopher->time_to_die)
	{
		philosopher->alive = 0;
		return (0);
	}
	else
		return (1);
}

void	custom_wait(int ms)
{
	while (ms > 0)
	{
		usleep(10);
		ms--;
	}
}
