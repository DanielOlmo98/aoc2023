#include <stddef.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int check_game_possible(char* line, ssize_t line_len){

    printf("%s", line);
    while (line[0] != ':') {
        if (--line_len == 0) {
            return 0;
        }
        line++;
    }
    line++;


    int parsed_int = 0;
    for (size_t i = 0; i < line_len; ++i) {
        if (line[i] > 47 && line[i] < 58) {
            parsed_int = atoi(line + i);
            if (parsed_int > 14) {
                printf("OVER");
                return 0;
            } else if (parsed_int > 12) {

                switch (parsed_int) {
                    case 13:
                        if (line[i+3] == 'r') {
                            printf("RED");
                            return 0;
                        }
                        break;
                    case 14:
                        if (line[i+3] == 'g') {
                            printf("GREEN");
                            return 0;
                        }
                        break;
                    case 15:
                        if (line[i+3] == 'b') {
                            printf("BLUE");
                            return 0;
                        }
                        break;
                    default:
                        break;
                }
            }

        }
    }
    printf("WIN");
    return 1;
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
    size_t line_count = 1;
    while((read = getline(&line, &len, input)) != -1) {

        sum += line_count*check_game_possible(line, read);

        printf(" | GAME %zu, SCORE %d \n\n", line_count, sum);

        line_count++;
    }

    printf("\ntotal %d\n", sum);
    free(line);
    fclose(input);
    return EXIT_SUCCESS;
}
