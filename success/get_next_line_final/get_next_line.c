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
    dest = (char *)malloc(sizeof(char) * (i + 1));
    if (!dest)
        return (NULL);
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
    static char     buffer[BUFFER_SIZE];
    static int      buffer_read = 0;
    static int      buffer_pos = 0;
    char            line[70000];
    char            current;
    int             i = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        current = buffer[buffer_pos];
        if (current == '\n')
        {
            line[i++] = current;
            buffer_pos++;
            break;
        }
        line[i++] = current;
        buffer_pos++;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

int main(void)
{
    int     fd;
    char    *line;
    int     i = 0;

    fd = open("./test.txt", O_RDONLY);
    line = get_next_line(fd);
    while(line)
    {
        printf("%d -> %s", i, line);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    free(line);
}