/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aionescu <aionescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:07:19 by aionescu          #+#    #+#             */
/*   Updated: 2022/02/27 20:24:27 by aionescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_positive_number(char *arg)
{
	int	index;

	index = 0;
	while (arg[index] != '\0')
	{
		if (index == 0 && arg[index + 1] != '\0'
			&& (arg[index] < '1' || '9' < arg[index]))
			return (-1);
		if (arg[index] < '0' || '9' < arg[index])
			return (-1);
		index++;
	}
	if (index == 0)
		return (-1);
	return (1);
}

int	handle_arg(char *arg)
{
	int	number;
	int	index;

	if (is_positive_number(arg) < 0 || arg == NULL)
		return (-1);
	number = 0;
	index = 0;
	while (arg[index] != '\0')
	{
		number = (number * 10) + (arg[index] - '0');
		index++;
	}
	return (number);
}

int	handle_input(int argc, char **argv, int *array_of_args)
{
	int		index;
	char	arg_no;

	if (argc < 5 || 6 < argc)
	{
		write(1, "Error: Invalid number of arguments. Exiting...\n", 48);
		return (1);
	}
	index = 1;
	while (index < argc)
	{
		array_of_args[index - 1] = handle_arg(argv[index]);
		if (array_of_args[index - 1] < 0 || array_of_args[0] == 0)
		{
			arg_no = index + '0';
			write(1, "Error: Argument ", 17);
			write(1, &arg_no, 1);
			write(1, " invalid. Exiting...\n", 22);
			return (2);
		}
		index++;
	}
	if (argc == 5)
		array_of_args[index - 1] = 0;
	return (0);
}
