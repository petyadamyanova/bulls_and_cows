#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


void rules(){
    printf("You have to read this before you start to play!!!\n");
    printf("                      | | | \n");
    printf("                      V V V\n");
    printf("                      RULES: \n");
    printf("1: The number that you will entered must have 4 digits!\n");
    printf("2: You can only enter digits between 0-9!\n");
    printf("2: The number can't started with 0!\n");
    printf("3: The digits of number have to be different!");
    printf("\n\n");
}

bool size_of_num(int num){
    if(num >= 1000 && num <= 9999){
        return true;
    }else{
        return false;
    }
}

bool is_num(char str_num[100]){
        int num = atoi(str_num);
        if(strlen(str_num)!=4){
            return false;
        }
        int digit_1 = num / 1000;
        int digit_2 = (num % 1000) / 100;
        int digit_3 = (num % 100) / 10;
        int digit_4 = (num % 10);
        if((digit_1 > 0 && digit_1 <= 9) && (digit_2 >= 0 && digit_2 <= 9) && (digit_3 >= 0 && digit_3 <= 9)
           && (digit_4 >= 0 && digit_4 <= 9)){
            return true;
        }else{
            return false;
        }
}

bool dif_digits(char str_num[100]){
    int num = atoi(str_num);
    int digit_1 = num / 1000;
    int digit_2 = (num % 1000) / 100;
    int digit_3 = (num % 100) / 10;
    int digit_4 = (num % 10);
    if((digit_1 != digit_2) && (digit_1 != digit_3) && (digit_1 != digit_4) && (digit_2 != digit_3)
       && (digit_2 != digit_4)&& (digit_3 != digit_4)){
        return true;
    }else{
        return false;
    }
}

void timer(clock_t difference){
    int min = (difference/1000)/60;
    int sec = (difference/1000) - min*60;
    if(min < 10 && sec > 9){
        printf("Time: 0%d:%d\n", min, sec);
    }else if(min < 10 && sec < 10){
        printf("Time: 0%d:0%d\n", min, sec);
    }else if(min >= 10 && sec < 10){
        printf("Time: %d:0%d\n", min, sec);
    }else{
        printf("Time: %d:%d\n", min, sec);
    }
}


int main()
{
    char buffer[255];
    rules();
    srand(time(NULL));

    int n_1 = rand()%10;
    int n_2 = rand()%10;
    int n_3 = rand()%10;
    int n_4 = rand()%10;

    while(n_1 == 0){
        n_1 = rand()%10;
    }
    while(n_1 == n_2){
        n_2 = rand()%10;
    }
    while(n_3 == n_1 || n_3 == n_2){
        n_3 = rand()%10;
    }
    while(n_4 == n_1 || n_4 == n_2 || n_4 == n_3){
        n_4 = rand()%10;
    }

    //printf("%d %d %d %d\n", n_1, n_2, n_3, n_4);

    int n = n_1 * 1000 +  n_2 * 100 + n_3 * 10 +  n_4 * 1;
    char opit_str[100];
    int num_of_tries=0;

    printf("Try to guess the number: ");
    scanf("%s", &opit_str);
    clock_t start = clock();

    while(true){
        while(size_of_num(atoi(opit_str))==false || is_num(opit_str)==false || dif_digits(opit_str)==false){
            printf("You have to entered a valid number!\n");
            printf("Try to guess the number: ");
            scanf("%s", &opit_str);
        }
        num_of_tries++;
        int opit = atoi(opit_str);
        if(opit == n){
            clock_t end = clock();
            clock_t difference = end - start;
            printf("You win!");
            printf("\n\n");
            printf("\n");
            timer(difference);
            printf("\nScore: %d\n", num_of_tries);
            break;
        }
        int opit_1 = opit / 1000;
        int opit_2 = (opit % 1000) / 100;
        int opit_3 = (opit % 100) / 10;
        int opit_4 = (opit % 10);
        int bulls = 0;
        int cows = 0;
        if(n_1 == opit_1){
            bulls++;
        }
        if(n_2 == opit_2){
            bulls++;
        }
        if(n_3 == opit_3){
            bulls++;
        }
        if(n_4 == opit_4){
            bulls++;
        }
        if(n_1 == opit_2 || n_1 == opit_3 || n_1 == opit_4){
            cows++;
        }
        if(n_2 == opit_1 || n_2 == opit_3 || n_2 == opit_4){
            cows++;
        }
        if(n_3 == opit_1 || n_3 == opit_2 || n_3 == opit_4){
            cows++;
        }
        if(n_4 == opit_1 || n_4 == opit_2 || n_4 == opit_3){
            cows++;
        }
        if(n_1 != opit_1 && n_1 != opit_2 && n_1 != opit_3 && n_1 != opit_4
           && n_2 != opit_1 && n_2 != opit_2 && n_2 != opit_3 && n_2 != opit_4
           && n_3 != opit_1 && n_3 != opit_2 && n_3 != opit_3 && n_3 != opit_4
           && n_4 != opit_1 && n_4 != opit_2 && n_4 != opit_3 && n_4 != opit_4){
            printf("nothing \n");
        }
        else{
            printf("bulls: %d \n" , bulls);
            printf("cows: %d \n", cows);
        }
        printf("Try to guess the number: ");
        scanf("%s", &opit_str);
    }

    FILE *f = fopen("score.txt", "r+");
    int best_score = atoi(fgets(buffer, 255, f));
    fclose(f);
    if(num_of_tries <= best_score ){
        FILE *s = fopen("score.txt", "w+");
        best_score = num_of_tries;
        fprintf(s,"%d", best_score);
        fclose(s);
    }
    printf("Best score: %d\n", best_score);

    return 0;
}

