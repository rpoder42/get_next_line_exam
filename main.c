/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:06:33 by rpoder            #+#    #+#             */
/*   Updated: 2022/10/16 14:45:48 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 3

char	*get_next_line(int fd);


int	main(int argc, char **argv)
{
	int				fd;
	char			*ret;
	size_t			count_line;
	(void)			argc;

	fd = open(argv [1], O_RDONLY);
	//fd = 0;
	count_line = 1;
	while ((ret = get_next_line(fd)) > 0)
	{
		printf("%s", ret);
		free(ret);
		count_line++;
	}
	printf("----------------------------\n");
	printf("Nombre de lignes lues : %zu \n\n", count_line - 1);
	return (0);
}
