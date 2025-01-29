
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *ft_str_dup(char *str)
{
	int		i = 0;
	int		len = 0;
	char	*dup;

	while (str[i])
		len += i++;
	i = 0;
	dup = (char *)malloc(sizeof(char)* len + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;

	}
	dup[i] = '\0';
	return (dup);


}
// char *get_next_line(int fd)
// {
//     static char buffer[BUFFER_SIZE + 1];
//     static int index = 0, bytes_in_buffer = 0;
//     char line[7000000];
//     int line_index = 0;

//     if (fd < 0 || BUFFER_SIZE <= 0)
//         return (NULL);

//     while (1)
//     {
//         if (index >= bytes_in_buffer)
//         {
//             bytes_in_buffer = read(fd, buffer, BUFFER_SIZE);
//             if (bytes_in_buffer <= 0)
//                 return (line_index > 0) ? ft_str_dup(line) : NULL;
//             index = 0;
//         }

//         line[line_index++] = buffer[index];
//         if (buffer[index++] == '\n')
//             break;
//     }
//     line[line_index] = '\0';
//     return ft_str_dup(line);
// }

char *get_next_line(int fd){

	int 	readed = 0;
	int 	index = 0;
	char	character;
	char	buffer[10000];

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = read(fd, &character, 1);
	while (readed > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		readed = read(fd, &character, 1);
	}
	if (readed <= 0 && index == 0)
		return (NULL);
	buffer[index] = '\0';
	return(ft_str_dup(buffer));
}

int main(int ac, char **av)
{
	int fd = 0;
	char *line;
    int n = 0;


	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		line = get_next_line(fd);

		while (n < 3)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
            n++;


		}
		free(line);
		
	}
	return 0;
}