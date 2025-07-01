/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:26:48 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/20 16:13:06 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_validate(int argc, char **argv, t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (0);
		if (argv[i][0] == '-' || argv[i][0] == '0')
			return (0);
		else if (ft_strlen(argv[i]) >= 10 && ft_strcmp("2147483647",
				argv[i]) < 0)
			return (0);
	}
	table->sim_stop = FALSE;
	table->optional_eat = 0;
	table->num_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->optional_eat = ft_atoi(argv[5]);
	return (1);
}
