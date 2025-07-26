/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:15:47 by tukaraca          #+#    #+#             */
/*   Updated: 2025/07/25 18:15:49 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 2147483647)
			return (-1);
	}
	return (result);
}

int	is_digit_char(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_digit(char *str)
{
	while (*str)
	{
		if (!is_digit_char(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_arg_is_digit(int argc, char **argv)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	while (i < argc)
	{
		arg = argv[i];
		j = 0;
		while (arg[j])
		{
			if (!is_digit_char(arg[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: 5 or 6 arguments must be entered!\n");
		return (1);
	}
	if (check_arg_is_digit(argc, argv))
	{
		printf("Error: Arguments must be numeric!\n");
		return (1);
	}
	while (++i < argc)
	{
		j = ft_atoi(argv[i]);
		if (j <= 0)
			return (1);
	}
	return (0);
}
