/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:05:42 by aionescu          #+#    #+#             */
/*   Updated: 2022/02/27 16:31:03 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

static size_t	get_number_length(int num)
{
	size_t		length;
	long long	llint;

	llint = num;
	length = 0;
	if (llint == 0)
		length = 1;
	if (llint < 0)
	{
		llint = llint * (-1);
		length++;
	}
	while (llint > 0)
	{
		llint = llint / 10;
		length++;
	}
	return (length);
}

char	*handle_number(char *number, long long llint, size_t index)
{
	if (llint < 0)
	{
		number[0] = '-';
		llint = llint * (-1);
	}
	while (llint > 0)
	{
		number[index] = '0' + llint % 10;
		llint = llint / 10;
		index--;
	}
	return (number);
}

char	*ft_itoa(long n)
{
	char		*number;
	size_t		number_length;
	size_t		index;
	long long	llint;

	llint = n;
	number_length = get_number_length(llint);
	number = malloc(number_length + 1);
	if (number != NULL)
	{
		number[number_length] = '\0';
		if (llint == 0)
			number[0] = '0';
		else
		{
			index = number_length - 1;
			number = handle_number(number, llint, index);
		}
	}
	return (number);
}

char	*time_to_str(struct timeval *timestamp)
{
	char	*time_str;
	char	*sec_str;
	char	*usec_str;

	sec_str = ft_itoa(timestamp->tv_sec);
	usec_str = ft_itoa(timestamp->tv_usec);
	usec_str[3] = '\0';
	usec_str[4] = '\0';
	usec_str[5] = '\0';
	time_str = ft_strjoin(sec_str, usec_str);
	free(sec_str);
	free(usec_str);
	return (time_str);
}
