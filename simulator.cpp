#include "blackjack.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <ctime>
#include <chrono>
using namespace std;
//Hand player;
//Hand computer;
char cardCountingStrategy(const Hand& player, const int deck[]);
int countCards(const int deck[]);
int runSimulation();
//int deck[52];
// Function to simulate a game
void simulateGame(int &playerWins, int &computerWins, int numSimulations) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= 13; ++j) {
            deck[i * 13 + (j - 1)] = j;
        }
    }
    playerNumber = 3;
    // Set up the game environment
    for(int i = 0; i < numSimulations; i++){
    shuffleDeck(deck, 52);
    dealInitialCards(deck, player, computer);
    bool end = false;
    while (!end) {
       // dealInitialCards(deck, player, computer);
        // Simulate player's actions
        char action = cardCountingStrategy(player, deck); // Randomly choose 'Hit' or 'Stand'
        if (action == '1' && player.cardCount < 5) {
            
            drawCard(deck, player);
            if (checkHands(player, "Player") > 21) {
                endGame(player, computer, playerNumber);
                end = true;
            }
        } else {
            endGame(player, computer, playerNumber);
            end = true;
        }
    }
    }
}
int countCards(const int deck[]) {
    int count = 0;
    for (int i = 0; i < 52; ++i) {
        if (deck[i] >= 10) count--;
        else if (deck[i] > 1 && deck[i] < 8) count++;
    }
    return count;
}
char cardCountingStrategy(const Hand& player, const int deck[]) {
    int playerValue = checkHands(player, "Player");
    int count = countCards(deck);
    if(playerValue < 17){
        return '1';
    }else{
        return '2';
    } // Hit if positive count and under 17, otherwise Stand
}

int runSimulation() {
    auto start = std::chrono::high_resolution_clock::now();
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation
    cout << "How many times should the game be run?";
    int numSimulations = 0;
    cin >> numSimulations;
      // Number of games to simulate
    playerWins = 0;
    computerWins = 0;
    
    simulateGame(playerWins, computerWins, numSimulations);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output results
    cout << "Total games simulated: " << numSimulations << endl;
    cout << "Player wins: " << playerWins << endl;
    cout << "Computer wins: " << computerWins << endl;
    cout << "Player win percentage: " << (static_cast<double>(playerWins) /( playerWins+computerWins) * 100) << "%" << endl;
    cout << "Computer win percentage: " << (static_cast<double>(computerWins) / (playerWins+computerWins) * 100) << "%" << endl;
    cout << "Blackjacks: " << blackjack << endl;
    cout << "duration was " << duration.count() << " milliseconds";
    return 0;
}
