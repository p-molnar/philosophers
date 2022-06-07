/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/07 18:07:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_data	data;
	gettimeofday(&data.start_time, NULL);
	usleep(10000);
	gettimeofday(&data.curr_time, NULL);
	printf("diff: %ld\n", (data.curr_time.tv_sec * 1000 + data.curr_time.tv_usec / 1000) - (data.start_time.tv_sec * 1000 + data.start_time.tv_usec/ 1000 ));
	if (parse_input(argc, argv, &data))
		return (1);

	return (0);
}
