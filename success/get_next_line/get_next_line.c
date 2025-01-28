#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// Function prototypes
static char	*read_to_buffer(int fd, char *storage);
static char	*append_to_storage(char *storage, char *buffer, int bytes_read);
static int	find_newline(char *storage);
static char	*extract_line(char *storage);
static char	*trim_storage(char *storage);
static size_t ft_strlen(char *str);

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_to_buffer(fd, storage);
	if (!storage) // Error or EOF with no data left
		return (NULL);
	line = extract_line(storage);
	storage = trim_storage(storage);
	return (line);
}
static size_t ft_strlen(char *str)
{
	size_t i = 0;
	while(str[i])
		i++;
	return i;
}
// Read data from the file descriptor and store it in storage
static char	*read_to_buffer(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!find_newline(storage) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0) // Read error
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = append_to_storage(storage, buffer, bytes_read);
		if (!storage)
			break;
	}
	free(buffer);
	return (storage);
}

// Append the content of buffer to storage
static char	*append_to_storage(char *storage, char *buffer, int bytes_read)
{
	char	*new_storage;
	int		i = 0, j = 0;

	if (!storage)
	{
		new_storage = malloc(bytes_read + 1);
		if (!new_storage)
			return (NULL);
		while (buffer[i])
		{
			new_storage[i] = buffer[i];
			i++;

		}
		new_storage[i] = '\0';
	}
	else
	{
		while (storage[i])
			i++;
		new_storage = malloc(i + bytes_read + 1);
		if (!new_storage)
			return (NULL);
		for (j = 0; storage[j]; j++)
			new_storage[j] = storage[j];
		for (i = 0; buffer[i]; i++)
			new_storage[j + i] = buffer[i];
		new_storage[j + i] = '\0';
		free(storage);
	}
	return (new_storage);
}

// Check if a newline character exists in storage
static int	find_newline(char *storage)
{
	if (!storage)
		return (0);
	while (*storage)
	{
		if (*storage == '\n')
			return (1);
		storage++;
	}
	return (0);
}

// Extract the line up to and including the first newline, or to the end of storage
static char	*extract_line(char *storage)
{
	char	*line;
	int		i = 0;

	if (!storage || !*storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(i + (storage[i] == '\n') + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = storage[j];
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// Trim storage to remove the extracted line and keep only the remaining data
static char	*trim_storage(char *storage)
{
	char	*new_storage;
	int		i = 0, j = 0;

	if (!storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i]) // No newline found, free storage
	{
		free(storage);
		return (NULL);
	}
	i++; // Move past the newline
	new_storage = malloc(ft_strlen(storage) - i + 1);
	if (!new_storage)
		return (NULL);
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}







// #include <unistd.h>
// #include <stdlib.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif

// char	*get_next_line(int fd)
// {
// 	static char	*storage = NULL;
// 	char		*line = NULL, *buffer, *temp;
// 	int			bytes_read, i, j, k;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = malloc(BUFFER_SIZE + 1)))
// 		return (NULL);
// 	bytes_read = 1;
// 	while (bytes_read > 0)
// 	{
// 		// Read data into buffer
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read < 0) // Handle read error
// 			return (free(buffer), free(storage), NULL);
// 		buffer[bytes_read] = '\0';
// 		// Append buffer to storage
// 		if (!storage)
// 		{
// 			storage = malloc(bytes_read + 1);
// 			if (!storage)
// 				return (free(buffer), NULL);
// 			for (i = 0; i < bytes_read; i++)
// 				storage[i] = buffer[i];
// 			storage[i] = '\0';
// 		}
// 		else
// 		{
// 			for (i = 0; storage[i]; i++)
// 				;
// 			temp = malloc(i + bytes_read + 1);
// 			if (!temp)
// 				return (free(buffer), free(storage), NULL);
// 			for (j = 0; storage[j]; j++)
// 				temp[j] = storage[j];
// 			for (k = 0; k < bytes_read; k++)
// 				temp[j + k] = buffer[k];
// 			temp[j + k] = '\0';
// 			free(storage);
// 			storage = temp;
// 		}
// 		// Check if there's a newline in storage
// 		for (i = 0; storage[i]; i++)
// 			if (storage[i] == '\n')
// 				break;
// 		if (storage[i] == '\n') // Found a full line
// 			break;
// 	}
// 	free(buffer);
// 	if (bytes_read <= 0 && (!storage || !*storage)) // No more data
// 		return (free(storage), storage = NULL, NULL);
// 	// Extract the line from storage
// 	for (i = 0; storage[i] && storage[i] != '\n'; i++)
// 		;
// 	line = malloc(i + 2);
// 	if (!line)
// 		return (free(storage), NULL);
// 	for (j = 0; j <= i && storage[j]; j++)
// 		line[j] = storage[j];
// 	line[j] = '\0';
// 	if (storage[j] == '\n')
// 		line[j++] = '\n';
// 	line[j] = '\0';
// 	// Remove the extracted line from storage
// 	for (k = 0; storage[j + k]; k++)
// 		;
// 	temp = malloc(k + 1);
// 	if (temp)
// 	{
// 		for (k = 0; storage[j + k]; k++)
// 			temp[k] = storage[j + k];
// 		temp[k] = '\0';
// 	}
// 	free(storage);
// 	storage = temp;
// 	return (line);
// }


