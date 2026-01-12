/*
 * bsq.c
 *
 * Find the largest square containing only 'empty' characters in a 2D map.
 * The input format (first line) is: <lines> <empty> <obstacle> <full>
 * The following lines contain the map rows.
 *
 * Algorithm overview:
 * - Read and validate the map and header.
 * - Use dynamic allocation for the map and a flat DP array `array` of size
 *   `lines * width` where `array[i * width + j]` holds the size of the
 *   largest square whose bottom-right corner is cell (i,j).
 * - DP recurrence (row-major traversal):
 *     if cell is obstacle -> 0
 *     else if i==0 or j==0  -> 1
 *     else -> 1 + min(top, left, top-left)
 *   This only needs the three neighbors: (i-1,j), (i,j-1), (i-1,j-1).
 * - Track the maximum square size and its bottom-right coordinates, then
 *   overwrite the corresponding cells with the 'full' character and print.
 *
 * Notes:
 * - Uses getline/fscanf and dynamic memory; prints "map error" to stderr on
 *   invalid input and cleans up.
 */

#include <stdio.h>      // File I/O
#include <stdlib.h>     // malloc, calloc, free
#include <string.h>     // strlen
#include <unistd.h>     // For compatibility (getline on some systems)

/* Return the minimum of three integers. Small helper for the DP step. */
int min(int a, int b, int c) { return a < b ? (a < c ? a : c) : (b < c ? b : c); }

/* Print a map error, free the map buffer, and close the file if needed. */
void clean_map(char **map, int lines, FILE *file) {
    fprintf(stderr, "map error\n");
    for (int k = 0; k < lines; k++) 
        if (map && map[k]) free(map[k]);
    free(map);
    if (file != stdin) 
        fclose(file);
}

/* We use direct index arithmetic (i * width + j) instead of an IDX macro
 * to access the flat DP buffer `array`. This keeps the code explicit and
 * avoids a macro indirection. */

void process_file(char *filename) {
    int lines = 0, width = 0, max = 0, maxi = 0, maxj = 0, *buffer;
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
    map = calloc((size_t)lines, sizeof(char*));
    for (int i = 0; i < lines; i++) {
        // Read each line dynamically
        read = getline(&map[i], &len, file);
        if (read == -1) { clean_map(map, lines, file); return;}
        // Remove newline character
        if (map[i][read-1] == '\n') map[i][read-1] = 0;
        // Set width from first line
        if (i == 0) width = strlen(map[i]);
        // Check all lines have the same width
        if ((int)strlen(map[i]) != width) { clean_map(map, lines, file); return;}
        // Validate allowed characters
        for (int j = 0; j < width; j++) {
            if (map[i][j] != empty && map[i][j] != obstacle) { clean_map(map, lines, file); return;}
        }
    }
    // Check for unique map characters
    if (empty == obstacle || empty == full || obstacle == full) { clean_map(map, lines, file); return;}
    // Create DP table for largest square calculation (flat buffer)
    buffer = calloc((size_t)lines * width, sizeof(int));
    if (!buffer) { clean_map(map, lines, file); return; }
    // Fill DP table and track largest square
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == obstacle) buffer[i * width + j] = 0;
            else if (i == 0 || j == 0) buffer[i * width + j] = 1;
            else buffer[i * width + j] = min(buffer[(i-1) * width + j], buffer[i * width + (j-1)], buffer[(i-1) * width + (j-1)]) + 1;
            if (buffer[i * width + j] > max) { max = buffer[i * width + j]; maxi = i; maxj = j; }
        }
    }
    // Mark the largest square with the 'full' character
    for (int i = maxi-max+1; i <= maxi; i++)
        for (int j = maxj-max+1; j <= maxj; j++)
            map[i][j] = full;
    // Print the resulting map
    for (int i = 0; i < lines; i++) puts(map[i]);
    // Free all allocated memory
    for (int i = 0; i < lines; i++) { free(map[i]); }
    free(map); free(buffer);
    if (file != stdin) fclose(file);
    return;
}
int main(int argc, char **argv) {
    if (argc == 1) process_file(NULL);
    else for (int i = 1; i < argc; i++) process_file(argv[i]);
    return 0;
}
