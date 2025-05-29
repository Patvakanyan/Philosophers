/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:26:48 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/28 11:44:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_validate(int argc, char **argv, t_descrip *descrip_philo)
{
	int	i;
	int	j;

	j = 0;
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
	descrip_philo->optional_eat = 0;
	descrip_philo->num_of_init_philo = ft_atoi(argv[1]);
	descrip_philo->time_to_die = ft_atoi(argv[2]);
	descrip_philo->time_eat = ft_atoi(argv[3]);
	descrip_philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		descrip_philo->optional_eat = ft_atoi(argv[5]);
	return (1);
}
