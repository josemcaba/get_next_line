#include <stdio.h>
#include "get_next_line.h"
#ifndef O_RDONLY
# define O_RDONLY 0000
#endif

void	ft_leaks(void)
{
	system("leaks -q a.exe");
}

int main(int argc, char *argv[])
{
    int fd;
//    char *line;

	atexit(ft_leaks);
    printf("%d : %s\n", argc, argv[argc - 1]);
    printf("%d\n", BUFFER_SIZE);
    fd = open (argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error: open() failed\n");
        return (1);
    }
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
//    line = get_next_line(fd);    
//    free (line);
    //printf(line);
    //free(line);
    if (close(fd) == -1)
    {
        printf("Error: close() failed\n");
        return (1);
    }
    return (0);
}
