# Description

Mastermind is a classic code breaking game where the player tries to find a secret code consisting of four separate pieces from nine possible colors. The player has a limited number of attempts to unlock the code. After each guess, the game provides feedback showing the number of correctly placed pieces and the number of incorrectly placed pieces.

# Task

I wrote Mastermind game in C programming language. The program allows the player to enter their guesses, provide feedback on each guess, and end the game when the code is guessed correctly or the maximum number of attempts is reached.

The my_rand() function will randomize itself if the user does not enter a number, and the randomized numbers will be between 0 and 8 and the numbers will not be repeated.

The my_strlen() function returns the length of the given string of words or numbers.

The check_code() function checks the number entered by the user according to the rules.

The read_input() function reads the number entered by the user and checks whether the CTRL + D command was issued.

The check_input() function checks numbers if they don't match the rules Wrong input! returns his word. If CTRL + D is given, it will exit the game.

The remaining functions continue in this manner.

# Usage

./my_mastermind or ./my_mastermind -c 0123 -t 10

# Installation

Just download the code and type mingw32-make or make in the terminal
