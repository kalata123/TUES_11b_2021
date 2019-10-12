#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void *read_image(const char *filepath);

int main( int argc, const char* argv[] ) {
	void *a = read_image(argv[1]);
	a += 18;
	printf("BMP image width: %d\n", *(int*)a);
	a += 4;
	printf("BMP image height: %d\n", *(int*)a);
	return 0;
}