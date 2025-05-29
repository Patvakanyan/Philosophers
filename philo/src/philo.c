/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/28 11:45:42 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str, int exit_code)
{
	printf("%s", str);
	return (exit_code);
}

int	create_philo(t_descrip *descrip_philo)
{
	int	i;

	i = -1;
	while (++i < (descrip_philo->num_of_init_philo + 1))
	{
		if (pthread_mutex_init(&(descrip_philo->philo->fork_mutex[i]),
				NULL) != 0)
			return (0);
	}
	return (1);
}

int	intput_descrip(t_descrip *descrip_philo)
{
	descrip_philo->philo = malloc(sizeof(t_philo));
	descrip_philo->philo->thread_ids = malloc(sizeof(pthread_t)
			* (descrip_philo->num_of_init_philo + 1));
	descrip_philo->philo->fork_mutex = malloc(sizeof(pthread_mutex_t)
			* descrip_philo->num_of_init_philo);
	if (!descrip_philo->philo->thread_ids || descrip_philo->philo->fork_mutex
		|| !descrip_philo->philo)
		return (print_error("Error: Memory allocation failed!\n", 0), 0);
	if (!create_philo(descrip_philo))
		return (0);
	return (1);
}

void	end_of_program(t_descrip *descrip_philo)
{
	free(descrip_philo->philo->thread_ids);
	free(descrip_philo->philo->fork_mutex);
	free(descrip_philo->philo);
	free(descrip_philo);
}

int	main(int argc, char **argv)
{
	t_descrip	*descrip_philo;

	descrip_philo = malloc(sizeof(t_descrip));
	if (!descrip_philo)
		return (print_error("Error: Memory allocation failed!\n", 0));
	if (!((argc == 5 || argc == 6) && is_validate(argc, argv, descrip_philo)))
		return (free(descrip_philo), print_error("Wrong arguments!\n", 0));
	if (!intput_descrip(descrip_philo))
		return (end_of_program(descrip_philo), 0);
	end_of_program(descrip_philo);
	return (1);
}
