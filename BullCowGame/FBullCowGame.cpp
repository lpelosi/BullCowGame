//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by lanzone on 5/11/17.
//  Copyright © 2017 gpk. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <string>


using int32 = int;
using FString = std::string;

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
int32 FBullCowGame::GetMaxTries() const {return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

FBullCowGame::FBullCowGame() {
    Reset();
}

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    
    if(!IsIsogram(Guess)) { // TODO write isogram check
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(Guess)) { // TODO write lower case check
        return EGuessStatus::Not_Lowercase;
    } else if(Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    } else {
        return EGuessStatus::OK;
    }
}

// Receives a valid guess, increments and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    
    MyCurrentTry++;
    
    FBullCowCount BullCowCount;
    
    for(int32 MHWChar = 0; MHWChar < MyHiddenWord.length(); MHWChar++) {
        for(int32 GChar = 0; GChar < MyHiddenWord.length(); GChar++) {
            if(Guess[GChar] == MyHiddenWord[MHWChar]) {
                if(MHWChar == GChar) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if(BullCowCount.Bulls == MyHiddenWord.length()) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    
    if(Word.length() <= 1) {
        return true;
    }
    
    TMap<char, bool> LetterSeen;
    for(auto Letter: Word) { // for all letters of the word
        Letter = tolower(Letter); // handle mixed case words
        if(LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    for(auto Letter: Word){
        if(!islower(Letter)){
            return false;
        }
    }
    return true;
}


