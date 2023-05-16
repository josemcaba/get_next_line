/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:54:52 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/16 22:32:05 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void	ft_leaks(void)
{
	system("leaks -q a.exe");
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	printf("%d\n", getdtablesize());

	atexit(ft_leaks);
	printf("%d : %s\n", argc, argv[argc - 1]);
	printf("BUFFER SIZE = %d\n", BUFFER_SIZE);
	fd = open ("lorem.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (1);
	}
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	if (close(fd) == -1)
	{
		printf("Error: close() failed\n");
		return (1);
	}
	return (0);
}
