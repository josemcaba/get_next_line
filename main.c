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
	int	fd;
	int	i;

	atexit(ft_leaks);
	printf("%d : %s\n", argc, argv[argc - 1]);
	printf("BUFFER SIZE = %d\n", BUFFER_SIZE);
	fd = open ("lorem.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: open() failed\n");
		return (1);
	}
	i = 0;
	while (i++ < 20)
		get_next_line(fd);
	get_next_line(fd);
	if (close(fd) == -1)
	{
		printf("Error: close() failed\n");
		return (1);
	}
	return (0);
}
