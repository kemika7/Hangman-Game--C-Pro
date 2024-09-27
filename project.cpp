#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Hangman {
private:
    vector<string> easyPersonalities = {"elonMusk", "marieCurie", "oprahWinfrey", "albertEinstein", "steveJobs"};
    vector<string> mediumPersonalities = {"markZuckerberg", "stephenHawking", "janeGoodall", "malalaYousafzai", "nelsonMandela"};
    vector<string> hardPersonalities = {"katherineJohnson", "fridaKahlo", "georgeOrwell", "adaLovelace", "ralphWaldoEmerson"};

    vector<string> easyCities = {"newYork", "losAngeles", "chicago", "miami", "sanFrancisco"};
    vector<string> mediumCities = {"vancouver", "toronto", "sydney", "dublin", "tokyo"};
    vector<string> hardCities = {"barcelona", "capeTown", "moscow", "bangkok", "amsterdam"};

    vector<string> easySports = {"basketball", "soccer", "baseball", "tennis", "football"};
    vector<string> mediumSports = {"hockey", "cricket", "rugby", "volleyball", "swimming"};
    vector<string> hardSports = {"fencing", "gymnastics", "curling", "squash", "archery"};

    vector<string> easyMovies = {"inception", "titanic", "avatar", "joker", "gladiator"};
    vector<string> mediumMovies = {"interstellar", "matrix", "godfather", "forrestGump", "pulpFiction"};
    vector<string> hardMovies = {"fightClub", "theShawshankRedemption", "theDarkKnight", "goodfellas", "se7en"};

    vector<string> easyBooks = {"harryPotter", "greatGatsby", "mobyDick", "1984", "toKillAMockingbird"};
    vector<string> mediumBooks = {"prideAndPrejudice", "catcherInTheRye", "warAndPeace", "theHobbit", "braveNewWorld"};
    vector<string> hardBooks = {"crimeAndPunishment", "theBrothersKaramazov", "wutheringHeights", "theCountOfMonteCristo", "theGreatExpectations"};

    string secretWord;
    string guessedLetters;
    int remainingAttempts;
    int score;

//This method selects a random word based on the chosen category and difficulty level using rand(). The word is chosen from one of the pre-defined vectors of strings.
    string selectWord(int category, int difficulty) {
        if (category == 1) { // Personalities
            switch (difficulty) {
                case 1: return easyPersonalities[rand() % easyPersonalities.size()];
                case 2: return mediumPersonalities[rand() % mediumPersonalities.size()];
                case 3: return hardPersonalities[rand() % hardPersonalities.size()];
            }
        } else if (category == 2) { // Cities
            switch (difficulty) {
                case 1: return easyCities[rand() % easyCities.size()];
                case 2: return mediumCities[rand() % mediumCities.size()];
                case 3: return hardCities[rand() % hardCities.size()];
            }
        } else if (category == 3) { // Sports
            switch (difficulty) {
                case 1: return easySports[rand() % easySports.size()];
                case 2: return mediumSports[rand() % mediumSports.size()];
                case 3: return hardSports[rand() % hardSports.size()];
            }
        } else if (category == 4) { // Movies
            switch (difficulty) {
                case 1: return easyMovies[rand() % easyMovies.size()];
                case 2: return mediumMovies[rand() % mediumMovies.size()];
                case 3: return hardMovies[rand() % hardMovies.size()];
            }
        } else if (category == 5) { // Books
            switch (difficulty) {
                case 1: return easyBooks[rand() % easyBooks.size()];
                case 2: return mediumBooks[rand() % mediumBooks.size()];
                case 3: return hardBooks[rand() % hardBooks.size()];
            }
        }
        return ""; // Default return
    }

    void displayWord() const {
        for (char letter : secretWord) {
            if (guessedLetters.find(letter) != string::npos) {
                cout << letter << " ";
            } else {
                cout << "_ ";
            }
        }
        cout << endl;
    }

    void displayHangman() const {
        cout << "  ----\n";
        cout << "  |  |\n";
        cout << "  |  " << (remainingAttempts <= 5 ? "O" : " ") << "\n";
        cout << "  | " << (remainingAttempts <= 3 ? "/" : " ") 
             << (remainingAttempts <= 4 ? "|" : " ") 
             << (remainingAttempts <= 2 ? "\\" : " ") << "\n";
        cout << "  | " << (remainingAttempts <= 1 ? "/" : " ") 
             << " " << (remainingAttempts <= 0 ? "\\" : " ") << "\n";
        cout << "  |\n";
        cout << "=========\n";
    }

    bool hasGuessedWord() const {
        for (char letter : secretWord) {
            if (guessedLetters.find(letter) == string::npos) {
                return false;
            }
        }
        return true;
    }

public: //Constructor (Hangman()): Initializes the score to 0 and seeds the random number generator using the current time (srand(time(0))).
    Hangman() {
        srand(static_cast<unsigned int>(time(0))); // Seed random number generator
        score = 0; // Initialize score
    }

    void startGame() {
        int category, difficulty;

        // Select Category
        while (true) {
            cout << "Select Category:\n1. Personalities\n2. Cities\n3. Sports\n4. Movies\n5. Books\n";
            cin >> category;
            if (cin.fail() || category < 1 || category > 5) {
                cin.clear(); // Clear error flag
                cin.ignore(10000, '\n'); // Ignore invalid input
                cout << "Invalid input. Please select a number between 1 and 5.\n";
                continue;
            }
            break;
        }

        // Select Difficulty Level
        while (true) {
            cout << "Select Difficulty Level:\n1. Easy\n2. Medium\n3. Hard\n";
            cin >> difficulty;
            if (cin.fail() || difficulty < 1 || difficulty > 3) {
                cin.clear(); // Clear error flag
                cin.ignore(10000, '\n'); // Ignore invalid input
                cout << "Invalid input. Please select a number between 1 and 3.\n";
                continue;
            }
            break;
        }

        secretWord = selectWord(category, difficulty);

        // Set number of attempts based on difficulty
        if (difficulty == 1) {
            remainingAttempts = 8; // Easy level
        } else if (difficulty == 2) {
            remainingAttempts = 6; // Medium level
        } else {
            remainingAttempts = 3; // Hard level
        }

        guessedLetters = "";

        // Set time limit based on difficulty
        int timeLimit = (difficulty == 1) ? 60 : (difficulty == 2) ? 45 : 30;
        time_t startTime = time(0); // Get current time

        cout << "Welcome to Hangman! You have " << remainingAttempts << " attempts and " << timeLimit << " seconds.\n";

        while (remainingAttempts > 0) {
            time_t currentTime = time(0);
            if (difftime(currentTime, startTime) > timeLimit) {
                cout << "Time's up! The word was: " << secretWord << ". Better luck next time!\n";
                cout << "Your score: " << score << endl; // Display score at the end
                return; // Exit the game after time runs out
            }

            displayHangman();
            displayWord();
            cout << "Remaining attempts: " << remainingAttempts << endl;

            char guess;
            cout << "Enter your guess: ";
            cin >> guess;

            if (guessedLetters.find(guess) != string::npos) {
                cout << "You already guessed that letter. Try again." << endl;
                continue; // Go back to the beginning of the loop
            }

            guessedLetters += guess;

            if (secretWord.find(guess) != string::npos) {
                cout << "Good guess!" << endl;
                score += 10; // Award points for a correct guess
                if (hasGuessedWord()) {
                    cout << "Congratulations! You've guessed the word: " << secretWord << endl;
                    cout << "Your score: " << score << endl; // Display score
                    return; // Exit the game after winning
                }
            } else {
                cout << "Incorrect guess." << endl;
                score -= 5; // Deduct points for an incorrect guess
                remainingAttempts--;
            }
        }

        cout << "Out of attempts! The word was: " << secretWord << ". Better luck next time!\n";
        cout << "Your score: " << score << endl; // Display score at the end
    }
};

int main() {
    Hangman game;
    string playAgain;

    do {
        game.startGame();

        // Ask the user if they want to play again
        cout << "Do you want to play again? (yes/no): ";
        cin >> playAgain;
    } while (playAgain == "yes");

    return 0;
}