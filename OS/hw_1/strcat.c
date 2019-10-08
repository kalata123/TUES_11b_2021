void strcat(char* dest, char* src){
    int i = 0, k = 0;
    while(dest[i] != '\0') ++i;
    for (; src[k] != '\0'; ++k) {
        dest[i+k] = src[k];
    }
    dest[i+k] = '\0';
}
