#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *ft_strdup(char *src)
{
    int i = 0;
    char *dest;

    while (src[i])
        i++;
    dest = (char *)malloc(sizeof(char)  * (i + 1));
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    char line[70000];
    static char buffer_read;
    static char buffer_pos;
    int i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break ;
        }
        if (buffer[buffer_pos] == '\n')
            break ;
        line[i] = buffer[buffer_pos++];
        i++;
    }
    line[i] = '\0';
    if (i == 0)
        return NULL;
    return (ft_strdup(line));

}

// int main()
// {
//     int fd = open("test.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     return 0;
// }

// int main(int argc, char **argv)
// {
//     char *line;
//     int fd[FOPEN_MAX];
//     int n_fds;
//     int n;
//     int i;

//     if (argc < 2)
// 	{
// 		printf("Usage: %s <file1> <file2>\n", argv[0]);
//         return 1;
// 	}
// 	// open fds
//     n_fds = (argc - 1);
// 	for (i = 0; i < n_fds; ++i) 
// 	{
// 		if ((fd[i] = open(argv[(i + 1)], O_RDONLY)) == -1)
// 		{
// 			printf("Error opening file: %s\n", argv[i + 1]);
// 			return 1;
// 		}
// 	}
// 	// test get_next_line
//     printf("Testing get_next_line w BUFFER_SIZE = %d\n\n", BUFFER_SIZE);
// 	n = 1;
// 	line = NULL;
//     for (i = 0; i < n_fds; ++i)
// 	{
//         while ((line = get_next_line(fd[i])) != NULL)
// 		{
//             printf("%d:\t%s", n, line);
//             free(line);
//             ++n;
//             if (++i >= n_fds)
//                 i = 0; // Wrap around to the first file descriptor
//         }
//     }
// 	// close fds
// 	for (i = 0; i < n_fds; ++i)
// 		close(fd[i]);
//     return 0;
// }
