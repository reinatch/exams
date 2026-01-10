#include <stdio.h>      // For file I/O and standard functions
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For strlen, strdup
#include <unistd.h>     // For POSIX getline (if available)
// Return the minimum of three integers
int min(int a, int b, int c) { return a < b ? (a < c ? a : c) : (b < c ? b : c); }
// Print error and free all allocated memory for the map, then close the file if needed
void free_map(char **map, int lines, FILE *file) {
    fprintf(stderr, "map error\n");
    for (int k = 0; k < lines; k++) 
        if (map && map[k]) free(map[k]);
    free(map);
    if (file != stdin) 
        fclose(file);
}
// Main function to process a map file or stdin
void process_file(char *filename) {
    int lines = 0, width = 0, max = 0, maxi = 0, maxj = 0, **array;
    char empty, obstacle, full, **map;
    size_t len = 0;
    ssize_t read;

    // Open file or use stdin
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if (!file) { fprintf(stderr, "map error\n"); return; }
    // Read map header (number of lines and map characters)
    if (fscanf(file, "%d %c %c %c\n", &lines, &empty, &obstacle, &full) != 4 || lines <= 0) {
        fprintf(stderr, "map error\n"); 
        if (file != stdin) fclose(file);
        return;
    }
    // Allocate memory for map lines
    map = malloc(lines * sizeof(char*));
    for (int i = 0; i < lines; i++) {
        map[i] = NULL;
        // Read each line dynamically
        read = getline(&map[i], &len, file);
        if (read == -1) { free_map(map, lines, file); return;}
        // Remove newline character
        if (map[i][read-1] == '\n') map[i][read-1] = 0;
        // Set width from first line
        if (i == 0) width = strlen(map[i]);
        // Check all lines have the same width
        if ((int)strlen(map[i]) != width) { free_map(map, lines, file); return;}
        // Validate allowed characters
        for (int j = 0; j < width; j++) {
            if (map[i][j] != empty && map[i][j] != obstacle) { free_map(map, lines, file); return;}
        }
    }
    // Check for unique map characters
    if (empty == obstacle || empty == full || obstacle == full) { free_map(map, lines, file); return;}
    // Create DP table for largest square calculation
    array = malloc(lines * sizeof(int*));
    for (int i = 0; i < lines; i++) array[i] = calloc(width, sizeof(int));
    // Fill DP table and track largest square
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == obstacle) array[i][j] = 0;
            else if (i == 0 || j == 0) array[i][j] = 1;
            else array[i][j] = min(array[i-1][j], array[i][j-1], array[i-1][j-1]) + 1;
            if (array[i][j] > max) { max = array[i][j]; maxi = i; maxj = j; }
        }
    }
    // Mark the largest square with the 'full' character
    for (int i = maxi-max+1; i <= maxi; i++)
        for (int j = maxj-max+1; j <= maxj; j++)
            map[i][j] = full;
    // Print the resulting map
    for (int i = 0; i < lines; i++) puts(map[i]);
    // Free all allocated memory
    for (int i = 0; i < lines; i++) { free(map[i]); free(array[i]);}
    free(map); free(array);
    if (file != stdin) fclose(file);
    return;
}
// int main(int argc, char **argv) {
//     if (argc == 1) process_file(NULL);
//     else for (int i = 1; i < argc; i++) process_file(argv[i]);
//     return 0;
// }
