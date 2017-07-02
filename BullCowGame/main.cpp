//
//  main.cpp
//  BullCowGame
//
//  Created by lanzone on 5/7/17.
//  Copyright © 2017 gpk. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
FBullCowGame BCGame;

int32 main(int32 argc, const char * argv[]) {
    
    PrintIntro();
    do
    {
        PlayGame();
    }
    while(AskToPlayAgain() == true);
    
    return 0;
}

void PlayGame() {
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows;
        
        std::cout << std::endl;
    }
    return;
}

void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows!\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << "Please enter all guesses in lowercase with no letters repeating.\n";
    return;
}

bool AskToPlayAgain() {
    if(BCGame.IsGameWon() == true) {
        std::cout << "\nCongratulations, you win!\n";
    } else {
        std::cout << "\nBetter luck next time!\n";
    }
    std::cout << "\nDo you want to play again? (y/n)";
    FText Response = "";
    getline(std::cin, Response);
    
    return (Response[0] == 'y' || Response[0] == 'Y');
}

// loop continually until a valid guess is entered
FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do {
        std::cout << "\nTry " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter a guess: ";
        getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a guess in all lower case characters.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating characters.\n";
                break;
            default:
                return Guess;
        }
    } while(Status != EGuessStatus::OK); // Keep looping until we get no errors.
    return Guess;
}
