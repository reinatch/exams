#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line = NULL;
	char		*temp = NULL;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read, i = 0, j = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, NULL, 0) < 0)) // Invalid fd check
		return (NULL);

	// Read and append to storage until a newline or EOF is encountered
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0) // Handle read errors
			return (free(storage), storage = NULL, NULL);
		buffer[bytes_read] = '\0';

		// Append buffer to storage
		if (!storage)
		{
			storage = malloc(bytes_read + 1);
			if (!storage)
				return (NULL);
			while (buffer[i])
				storage[i] = buffer[i++];
			storage[i] = '\0';
		}
		else
		{
			i = 0;
			while (storage[i])
				i++;
			temp = malloc(i + bytes_read + 1);
			if (!temp)
				return (free(storage), storage = NULL, NULL);
			for (j = 0; storage[j]; j++)
				temp[j] = storage[j];
			for (i = 0; i < bytes_read; i++)
				temp[j + i] = buffer[i];
			temp[j + i] = '\0';
			free(storage);
			storage = temp;
		}

		// Check if a newline exists in storage
		i = 0;
		while (storage[i] && storage[i] != '\n')
			i++;
		if (storage[i] == '\n' || bytes_read == 0) // Found newline or EOF
			break;
	}

	// Allocate the line to return
	line = malloc(i + 2); // Include space for '\n' and '\0'
	if (!line)
		return (free(storage), storage = NULL, NULL);
	for (j = 0; j <= i && storage[j]; j++)
		line[j] = storage[j];
	line[j] = '\0';

	// Remove extracted line from storage
	if (storage[j] == '\n')
		line[j++] = '\n';
	i = 0;
	while (storage[j])
		storage[i++] = storage[j++];
	storage[i] = '\0';

	if (i == 0) // If storage is empty after processing, free it
		return (free(storage), storage = NULL, line);
	return (line);
}























// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <fcntl.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif


// // Utility function to calculate string length
// static size_t	ft_strlen(const char *str)
// {
// 	size_t	i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

// // Utility function to find the first occurrence of a character in a string
// static char *ft_strchr(const char *s, int c)
// {
//     while (*s)
//     {
//         if (*s == (char)c)
//             return ((char *)s);
//         s++;
//     }
//     return (c == '\0' ? (char *)s : NULL);
// }


// // Utility function to join two strings
// static char	*ft_strjoin(char *s1, const char *s2)
// {
// 	size_t	len1 = ft_strlen(s1);
// 	size_t	len2 = ft_strlen(s2);
// 	char	*new_str = malloc(len1 + len2 + 1);

// 	if (!new_str)
// 		return (NULL);
// 	for (size_t i = 0; i < len1; i++)
// 		new_str[i] = s1[i];
// 	for (size_t j = 0; j < len2; j++)
// 		new_str[len1 + j] = s2[j];
// 	new_str[len1 + len2] = '\0';
// 	free(s1); // Free the old string to prevent leaks
// 	return (new_str);
// }

// // Extract the line up to the first newline, or the entire string
// static char	*extract_line(char *storage)
// {
// 	size_t	i = 0;
// 	char	*line;

// 	while (storage[i] && storage[i] != '\n')
// 		i++;
// 	line = malloc(i + 2); // Include space for '\n' and '\0'
// 	if (!line)
// 		return (NULL);
// 	for (size_t j = 0; j <= i; j++)
// 		line[j] = storage[j];
// 	line[i + 1] = '\0';
// 	return (line);
// }

// // Remove the extracted line from storage
// static char	*trim_storage(char *storage)
// {
// 	size_t	i = 0, j = 0;
// 	char	*new_storage;

// 	while (storage[i] && storage[i] != '\n')
// 		i++;
// 	if (!storage[i]) // No newline, free storage
// 		return (free(storage), NULL);
// 	new_storage = malloc(ft_strlen(storage) - i);
// 	if (!new_storage)
// 		return (free(storage), NULL);
// 	i++; // Skip the '\n'
// 	while (storage[i])
// 		new_storage[j++] = storage[i++];
// 	new_storage[j] = '\0';
// 	free(storage);
// 	return (new_storage);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*storage = NULL;
// 	char		buffer[BUFFER_SIZE + 1];
// 	int			bytes_read;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (1)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0) // Handle read errors
// 			return (free(storage), storage = NULL, NULL);
// 		buffer[bytes_read] = '\0';
// 		storage = ft_strjoin(storage, buffer); // Append buffer to storage
// 		if (!storage)
// 			return (NULL);
// 		if (ft_strchr(storage, '\n') || bytes_read == 0) // Found a line or EOF
// 			break;
// 	}
// 	if (!storage || !*storage) // If storage is empty, return NULL
// 		return (free(storage), storage = NULL, NULL);
// 	char *line = extract_line(storage); // Extract the next line
// 	storage = trim_storage(storage);    // Update storage
// 	return (line);
// }





































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
