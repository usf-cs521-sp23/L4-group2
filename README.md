# Wordle!
===========================================
* Below is the simple usage of Wordle game
===========================================

* Build and Run
run `cc wordle.c` then `./a.out`

* How to play with wordle
    * you will be asked to input your name to enter game.
    * then program will display a simple time clock to count down 5 sec.
    * It's best if you can fomulate your answer within 5 sec, but nothing will happen after the count down is complete. this is simply reminds you 5 sec has passed and please enter you answer.
    * right after you entered your guess, it will indicate the correct/wrong/out of place letter with green/yellow/red color to make the game easier
    * then each time you entered your guess, the used word will be displayed so that you can see which word is already used.
    * also will display how many times you have guess and how many more change have left.
    * if you fomulate the correct answer within 6 guesses. you win and will prompt you if you want to play again. you will see cowsay :)
    * otherwise if you cannot come up with the correct word within 6 guesses, you lose. you will see cowsay as well and ask you if want to play again.
    * last, once you start play the game you should see a text file created with the name format `{$user} game record` under the root directory. It will display how many time you have guessed and whats the word you have guessed. within the created text file, you should also see a score board indicating win/lose every time. Noted that in each game if you chose to play again, the text file will not be overwritten, it will be appended at the end with the newest game score. However when the game is ended and a new game started with even same user, the text file will be re-created with empty content, the previous score board will be erased.

===========================================
 - Happy playing!!!

