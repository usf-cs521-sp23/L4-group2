#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* Adding color to output */
void green () {
    printf("\033[0;32m");
}

void yellow () {
    printf("\033[0;33m");
}

void red () {
    printf("\033[1;31m");
}

void reset () {
    printf("\033[0m");
}

int main(void) {
    /*
        Potential Special Features
        1. Stats (wins, losses, how many guesses, streaks) / previous results
            * Print to text file for bragging rights
        2. Let user choose the size of the word
        3. Use colors to indicate right, wrong, and "out of place"
        4. Cowsay integration
        5. Time limit
        6. Do everything in C (no pre-generated list)
    */
    
    #define NUM_WORDS 20 
    #define WORD_SIZE 50
    #define NUM_OF_CHANCE 6
    #define MAX_LETTER 26

    char userInput[50];
    FILE *user_File;
    int win_time = 0;
    int lose_time = 0;
    char name[100];

    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Welcome to my wordle game, %s.\n", name);
    strcat(name, " game record");
    user_File = fopen(name, "w");

    do {
        /* open word file */
        FILE *file = fopen("/home/zshuai/eighth-day/L4-group2/word-dict.txt", "r");
        if (file == NULL) {
            perror("Unable to find the word list");
            exit(EXIT_FAILURE);
        }
        /* adding word to wordList array */
        char word[WORD_SIZE];
        char wordList[NUM_WORDS][WORD_SIZE];
        int i = 0;
        char secret_word[WORD_SIZE];
        while (fgets(word, sizeof(word), file) != NULL) {
            strcpy(wordList[i], word);
            i++;
        }
        fclose(file);
        /* pick one word randomly */
        int num = (rand() % (NUM_WORDS + 1));
        strcpy(secret_word, wordList[num]);

        char used_words[NUM_OF_CHANCE][WORD_SIZE];
        int time_guessed = 0;
        bool has_winner = false;

        /* find out who is playing */
        for (int i = 0; i < NUM_OF_CHANCE; i++)  {
            char guess[100];
            printf("Enter your Guess: ");
            scanf("%s", guess);

            if (strlen(guess) != 5) {
                printf("that is not 5 character, please do it again.\n");
                continue;
            }

            for (int j = 0; j < 5; j++) { /* iterate each char in the word */
                if (ispunct(guess[j]) > 0 || isupper(guess[j]) > 0 || isdigit(guess[j])) {
                        printf("Please enter a valid word, No Punctuation, UpperCase or LowerCase!");
                        break;
                    }
                if (secret_word[j] == guess[j]) { /* check the letter if in the right spot */
                    green();
                    printf("o");
                    /* search first occurence of letter if existed in target str */
                } else if (strchr(secret_word, guess[j]) != NULL) {
                    yellow();
                    printf("a");
                } else {
                    red();
                    printf("x");
                }
                reset();
            }
            time_guessed++;
            printf("\n");
            strcpy(used_words[i], guess);
            printf("Used words: ");
            int k = i + 1;
            int w = 0;
            while (k > 0) {
                printf("%s ", used_words[w]);
                w++;
                k--;
            }
            printf("\n");
            printf("You have guessed %d times, you still have %d times left", time_guessed, NUM_OF_CHANCE - time_guessed);
            printf("\n");
            if (strncmp(secret_word, guess, 5) == 0) {
                printf("Nice job, you win!!!\n");
                win_time += 1;
                has_winner = true;
                fprintf(user_File, "win/lose: %d / %d", win_time, lose_time);
                break;
            }
        }
        if ((NUM_OF_CHANCE == 6) && (has_winner == false)) {
            printf("Sorry you lose, you have used all you chances :(\nThe correct word is %s", secret_word);
        }
        lose_time += 1;
        fprintf(user_File, "\nwin/lose: %d / %d", win_time, lose_time);
        printf("Would you like to play again(Y/N)? ");
        scanf(" %c", userInput);
        fclose(user_File);
    } while (*userInput == 'Y' || *userInput == 'y');
}
