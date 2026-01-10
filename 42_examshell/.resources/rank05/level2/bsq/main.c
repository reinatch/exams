

#include <stdio.h>

int main(int argc, char **argv) {
	extern void process_file(char *filename); // Declare your main logic function
	if (argc == 1) {
		process_file(NULL); // Read from stdin
	} else {
		for (int i = 1; i < argc; i++) {
			process_file(argv[i]);
		}
	}
	return 0;
}






// #include "bsq.h"

// int main(int argc, char* argv[])
// {
// 	if(argc == 1)
// 	{
// 		if(execute_bsq(stdin) == -1)
// 			fprintf(stderr, "map error\n");
// 	}
// 	else if(argc == 2)
// 	{
// 		if(convert_file_pointer(argv[1]) == -1)
// 			fprintf(stderr, "map error\n");
// 	}
// 	else
// 	{
// 		int i = 1;
// 		while(i < argc)
// 		{
// 			if(convert_file_pointer(argv[i]) == -1)
// 				fprintf(stderr, "map error\n");
// 			i++;
// 			if(i < argc - 1)
// 				fprintf(stdout, "\n");

// 		}
// 	}
// 	return(0);
// }

