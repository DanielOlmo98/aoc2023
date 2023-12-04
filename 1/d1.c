#include <stddef.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int char_window_to_int(char* window, size_t* i){
    window[5] = '\0';
    /* printf("%s ", window); */
    if(strncmp(window, "three", 5) == 0){
        *i+= 4;
        return 3;
    }
    if(strncmp(window, "seven", 5) == 0){
        *i+= 4;
        return 7;
    }
    if(strncmp(window, "eight", 5) == 0){
        *i+= 4;
        return 8;
    }
    if(strncmp(window, "four", 4) == 0){
        *i+= 3;
        return 4;
    }
    if(strncmp(window, "five", 4) == 0){
        *i+= 3;
        return 5;
    }
    if(strncmp(window, "nine", 4) == 0){
        *i+= 3;
        return 9;
    }
    if(strncmp(window, "one", 3) == 0){
        *i += 2;
        return 1;
    }
    if(strncmp(window, "two", 3) == 0){
        *i += 2;
        return 2;
    }
    if(strncmp(window, "six", 3) == 0){
        *i += 2;
        return 6;
    }

    return 0;
}

int read_int_digits(char* line, ssize_t line_len){
    printf("\n%s", line);
    int digitFront = 0;
    int digitBack = 0;
    size_t i = 0;
    for (i = 0; i < line_len; ++i) {
        if (line[i] > 48 && line[i] < 58) {
            digitFront = line[i] - '0';
            break;
        } else {
            char window[line_len];
            memcpy(window, line+i, sizeof(char)*5);
            digitFront = char_window_to_int(window, &i);
            if (digitFront!= 0){
                break;
            }
        }
    }

    if (digitFront == 0){
        return 0;
    }

    i += 1;
    for (size_t j = line_len-1; j-- > i;) {

        if (line[j] > 48 && line[j] < 58) {
            digitBack = line[j] - '0';
            break;

        } else {
            size_t window_size = 5;

            char window[line_len];
            if (line_len - i < window_size) {
                window_size = line_len - i;
            }
            memcpy(window, line + (j - 2), sizeof(char)*window_size);
            size_t dummy = 0;
            printf("window %s\n", window);
            printf("i%zu j%zu w%zu l%zu\n", i, j, window_size, line_len);
            digitBack = char_window_to_int(window, &dummy);
            if (digitBack != 0){
                break;
            }
        }
    }

    printf(" front: %d \n", digitFront);
    printf("  back: %d \n", digitBack);


    if (digitBack == 0){
        return 0;
    }

    int s =(digitFront * 10) + digitBack;
    return s;
}

int main(int argc, char* argv[argc+1]) {

    FILE* input = fopen("input.txt", "r");
    if (input == NULL){
        exit(EXIT_FAILURE);
    }

    uint sum = 0;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, input)) != -1) {
        sum += read_int_digits(line, read);
    }

    printf("\ntotal %d\n", sum);
    fclose(input);
}
