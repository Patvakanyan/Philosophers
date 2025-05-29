/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:46:10 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/28 11:46:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct philo
{
	pthread_t		*thread_ids;
	pthread_mutex_t	*fork_mutex;
}					t_philo;

typedef struct s_descrip_philo
{
	int				num_of_init_philo;
	int				time_to_die;
	int				time_eat;
	int				time_to_sleep;
	int				optional_eat;
	int				init_philo_die;
	t_philo			*philo;
}					t_descrip;

// validate
int					is_validate(int argc, char **argv,
						t_descrip *descrip_philo);
int					ft_atoi(const char *str);
int					ft_atoi(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(char *str);
int					ft_isdigit(int c);

#endif
