#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void *read_image(const char *filepath);

int main( int argc, const char* argv[] ) {
	void *a = read_image(argv[1]);
    // ntohl(a);
	a += 18;
	printf("BMP image width: %d\n", *(uint32_t*)a);
	a += 4;
	printf("BMP image height: %d\n", *(uint32_t*)a);
	return 0;
}