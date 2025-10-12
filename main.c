#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc - 1 == 0){
        puts("\033[0;31mError:\033[0m No input file");
        return 1;
    }
    FILE* fsrc = fopen(argv[1], "r");
    if (!fsrc) {
        printf("\033[0;31mError:\033[0m File \033[4m%s\033[0m does not exist\n", argv[1]);
        return 1;
    }

    fseek(fsrc, 0, SEEK_END);
    long size = ftell(fsrc);
    rewind(fsrc);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, fsrc);
    buffer[size] = '\0';
    fclose(fsrc);

    unsigned char arr[30000] = {0};
    size_t ptr = 0;

    for (size_t i = 0; i < strlen(buffer); i++) {
        switch (buffer[i]) {
        case '>':
            ptr++;
            break;
        case '<':
            ptr--;
            break;
        case '+':
            arr[ptr]++;
            break;
        case '-':
            arr[ptr]--;
            break;
        case '.':
            putchar(arr[ptr]);
            break;
        case ',':
            arr[ptr] = getchar();
            break;
        case '[':
            if (arr[ptr] == 0) {
                int loop = 1;
                while (loop > 0) {
                    i++;
                    if (buffer[i] == '[') loop++;
                    else if (buffer[i] == ']') loop--;
                }
            }
            break;
        case ']':
            if (arr[ptr] != 0) {
                int loop = 1;
                while (loop > 0) {
                    i--;
                    if (buffer[i] == ']') loop++;
                    else if (buffer[i] == '[') loop--;
                }
            }
            break;
        }
    }

    free(buffer);
    return 0;
}
