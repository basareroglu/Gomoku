#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int file_read(char table[19][20], int b_counter, int w_counter);
int play_time(char table[19][20], int b_counter, int w_counter);
int winner(char table[19][20]);

int main() {
    char table[19][20];
    int b_counter = 0;
    int w_counter = 0;
    if (file_read(table,b_counter, w_counter) == -1) {
        return -1;
    }
    play_time(table, b_counter, w_counter);
    return 0;
}

int file_read(char table[19][20], int b_counter, int w_counter){
    FILE *fp;
    if ((fp = fopen("board.txt", "r"))==NULL){
        printf("Invalid file!");
        return -1;
    }
    for (int i=0; i<19; i++){
        for (int j=0; j<20; j++){
            fscanf(fp, "%c", &table[i][j]);
            if (table[i][j] == 'B') {
                b_counter++;
            }
            else if (table[i][j] == 'W'){
                w_counter++;
            }
        }

    }
    fclose(fp);
    return 0;
}

int play_time(char table[19][20], int b_counter, int w_counter){
    char move;
    int flag,row,column,game_result=1;
    if (b_counter == w_counter){
        flag=1;
    }
    else {
        flag=0;
    }
    while(game_result==1){
        printf("\nEnter row and column of your move:\n");
        scanf("%d %d", &row, &column);
        row--;
        column--;
        if (0<=row<=18 && 0<=column<=19 && table[row][column] == '.'){
            if (flag==0){
                move = 'W';
                //flag=1;
            }
            else{
                move = 'B';
                flag=0;
            }
            table[row][column] = move;
            for (int i=0;i<19;i++){
                for (int j=0;j<20;j++){
                    printf("%c",table[i][j]);
                }
            }
            if ((winner(table))==0){
                return 0;
            }

        }
        else{
            printf("Enter valid numbers!\n");
        }

    }

    return 0;

}

int winner(char table[19][20]){
    int count=1;
    char c='a';
    for (int i=0;i<19;i++){
        for (int j=0;j<20;j++){
            if (table[i][j]==c && (c=='B' || c=='W')){
                count++;
            }
            else{
                c = table[i][j];
                count=1;
            }
            if (count==5){
                printf("The winner is %c", table[i][j]);
                return 0;
            }
        }
    }
    count = 1;
    c = 'a';
    for (int j=0;j<20;j++){
        for (int i=0;i<19;i++){
            if (table[i][j] == c && (c=='B' || c=='W')){
                count++;

            }
            else{
                c = table[i][j];
                count = 1;
            }
            if (count == 5){
                printf("The winner is %c", table[i][j]);
                return 0;
            }
        }
    }
    count = 1;
    c = 'a';
    for (int i=0;i<19;i++){
        for (int j=0;j<20;j++){
            for (int f=0;f<5;f++){
                if (table[i+f][j+f]==c && (c=='B' || c=='W')){
                    count++;
                }
                else{
                    c = table[i+f][j+f];
                    count = 1;
                }
                if (count==5){
                    printf("The winner is %c", table[i+f][j+f]);
                    return 0;
                }
            }
        }
    }
    count = 1;
    c = 'a';
    for (int i=19;i>0;i--){
        for (int j=20;j>0;j--){
            for (int f=5;f>0;f--){
                if (table[i-f][j-f]==c && (c=='B' || c=='W')){
                    count++;
                }
                else{
                    c = table[i-f][j-f];
                    count = 1;
                }
                if (count==5){
                    printf("The winner is %c", table[i-f][j-f]);
                    return 0;
                }
            }
        }
    }
    return 1;
}