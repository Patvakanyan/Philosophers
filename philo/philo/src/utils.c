/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:31:52 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/05 16:23:49 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str, int exit_code)
{
	printf("%s", str);
	return (exit_code);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	is_negativ;
	int	num;

	num = 0;
	i = 0;
	is_negativ = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '-')
	{
		is_negativ *= -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		++i;
	}
	return (is_negativ * num);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(char *str)
{
	char	*start;

	start = str;
	while (*str)
		++str;
	return (str - start);
}

int	ft_isdigit(int c)
{
	if (c == '+')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
