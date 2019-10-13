#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <arpa/inet.h>

void *read_image(const char *filepath);

int main( int argc, const char* argv[] ) {
	void *res = read_image(argv[1]);
	char *ext = strrchr(argv[1], '.');
	FILE *read = fopen(argv[1],"r");
	if (res == NULL || read == NULL){
		perror("Unable to open file\n");
		exit(1);
	}
	if (strcmp(ext+1, "png") != 0){
		perror("Unable to parse file\n");
		exit(1);
	}
	res += 16;
	printf("PNG image width: %d\n", ntohl(*(uint32_t*)res));
	res += 4;
	printf("PNG image height: %d\n", ntohl(*(uint32_t*)res));
	fseek(read, 0, SEEK_END);
	printf("PNG file size: %d\n",(uint32_t)ftell(read));
	fclose(read);
	return 0;
}