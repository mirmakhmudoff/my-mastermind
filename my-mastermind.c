#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *my_rand(){
    srand(time(NULL));
    char *secret_code = calloc(5, sizeof(char));
    int used[9] = {0};
    for(int i = 0; i < 4; i++){
        int rand_num = rand() % 9;
        if(!used[rand_num]){
            secret_code[i] = '0' + rand_num;
            used[rand_num] = 1;
        }else{
            i--;
        }
    }
    return secret_code;
}

int my_strlen(char *len){
    int i = 0;
    while(len[i] != '\0'){
        i++;
    }
    return i;
}

int check_code(char *insert_code){
    int length = my_strlen(insert_code);
    if(length != 4){
        return 0;
    }
    for(int i = 0; i < 4; i++){
        if(insert_code[i] < '0' || insert_code[i] > '8'){
            return 0;
        }
        for(int j = i + 1; j < 4; j++){
            if(insert_code[i] == insert_code[j]){
                return 0;
            }
        }
    }
    return 1;
}

void read_input(char *insert_code){
    char c;
    int i = 0, result;
    while((result = read(0, &c, 1)) > 0 && c != '\n'){
        insert_code[i++] = c;
    }
    insert_code[i] = '\0';
    if(result == 0){
        insert_code[0] = '\0';
    }
}

void check_input(char *insert_code){
    while(!check_code(insert_code)){
        if(insert_code[0] == '\0'){
            char eot = 4;
            write(0, &eot, 1);
            return;
        } else {
            printf("Wrong input!\n");
            write(1, ">", 1);
            read_input(insert_code);
        }
    }
}

void user_prompt(char *insert_code){
    write(1, ">", 1);
    read_input(insert_code);
    if(insert_code[0] == '\0'){
        char eot = 4;
        write(0, &eot, 1);
    }else{
        check_input(insert_code);
    }
}

void check_guess(char *code, char *insert_code, int *well_placed, int *misplaced){
    *well_placed = 0;
    *misplaced = 0;
    if(!check_code(insert_code)){
        return;
    }
    for(int i = 0; i < 4; i++){
        if(code[i] == insert_code[i]){
            *well_placed += 1;
        }else{
            for(int j = 0; j < 4; j++){
                if(i != j && code[j] == insert_code[i]){
                    *misplaced += 1;
                    break;
                }
            }
        }
    }
}

int print_guess(char *code, char *insert_code){
    int well_placed = 0;
    int misplaced = 0;
    check_guess(code, insert_code, &well_placed, &misplaced);
    if(well_placed == 4){
        printf("Congratz! You did it!\n");
        return 1;
    }else{
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        return 0;
    }
}

void start_game(char *code, int attempts){
    char *insert_code = calloc(5, sizeof(char));
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int i = 0; i < attempts; i++){
        printf("---\nRound %d\n", i);
        user_prompt(insert_code);
        if(insert_code[0] == '\0'){
            free(code);
            free(insert_code);
            return;
        }
        if(print_guess(code, insert_code)){
            free(insert_code);
            free(code);
            return;
        }
    }
    free(insert_code);
    free(code);
}

void read_arguments(int argc, char *argv[], char **code, int *attempts){
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            char *code_input = calloc(5, sizeof(char));
            for(int j = 0; j < 4; j++){
                code_input[j] = argv[i + 1][j];
            }
            code_input[4] = '\0';
            *code = code_input;
        }else if(strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            *attempts = atoi(argv[i + 1]);
        }
    }
}

int main(int argc, char *argv[]){
    char *code = NULL;
    int attempts = 10;
    read_arguments(argc, argv, &code, &attempts);
    if(code == NULL){
        code = my_rand();
    }
    start_game(code, attempts);
    return 0;
}
