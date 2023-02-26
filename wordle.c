#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
    /*
     Requirements:
        1. Find out who is playing the game
        2. Open a text file with words to use (maybe in /usr/share/dict ?)
            * Make a word list from those words (only 5 letters, no special chars)
        3. Pick one word randomly
        4. Read guesses on standard input (stdin) -- but only give them 6 chances
            * Check if it's actually a valid word, no uppercase, punctuation
            * Check if the letter is in the right spot, or at least in the word
        5. Let user know which letters have already been used
            * Track which letters were wrong
        6. Have some way of showing what was right/wrong, how many times guessed, how many left
        7. Either print that they win or lose (with personalization, e.g., "You are terrible Matthew")
        8. Ask them if they want to play again

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

        /* find out who is playing*/
        char name[100];
        printf("Please enter your name: ");
        scanf("%s", name);
        printf("Welcome to my wordle game, %s.\n", name);

        for (int i = 0; i < NUM_OF_CHANCE; i++)  {
            char guess[100];
            printf("Enter your Guess: ");
            scanf("%s", guess);

            if (strlen(guess) != 5) {
                printf("that is not 5 character, please do it again.\n");
                continue;
            }

            for (int j = 0; j < 5; j++) { /* iterate each char in the word*/
                if (ispunct(guess[j]) > 0 || isupper(guess[j]) > 0 || isdigit(guess[j])) {
                        printf("Please enter a valid word, No Punctuation, UpperCase or LowerCase!");
                        break;
                    }
                if (secret_word[j] == guess[j]) { /* check the letter if in the right spot*/
                    printf("o");
                    /* search first occurence of letter if existed in target str */
                } else if (strchr(secret_word, guess[j]) != NULL) {
                    printf("a");
                } else {
                    printf("x");
                }
            }
            time_guessed++;
            printf("\n");
            strcpy(used_words[i], guess);
            printf("Used words: ");
            int k = i + 1;
            while (k > 0) {
                printf("%s ", used_words[k - 1]);
                k--;
            }
            printf("\n");
            printf("You have guessed %d times, you still have %d times left", time_guessed, NUM_OF_CHANCE - time_guessed);
            printf("\n");
            if (strncmp(secret_word, guess, 5) == 0) {
                printf("Nice job, you win!!!\n");
                break;
            }
        }
        printf("Sorry you lose, you have used all you chances :(\nThe correct word is %s", secret_word);
        printf("\nWould you like to play again(Y/N)? ");
        scanf(" %c", userInput);
    } while (*userInput == 'Y' || *userInput == 'y');
}