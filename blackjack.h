// blackjack.h
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;
// Class Declarations
class Hand {
public:
    int cards[5] = {0};
    int cardCount = 0;
};
// Global Variables
extern int deck[52];
extern int playerNumber;
extern char input;
extern int playerWins;
extern int computerWins;
extern std::vector<std::tuple<int, std::string, int, int>> playerNames;
extern Hand player;
extern Hand computer;


// Function Declarations
void shuffleDeck(int arr[], int n);
void dealInitialCards(int deck[], Hand &player, Hand &computer);
void drawCard(int deck[], Hand &hand);
void printDeck(int deck[]);
void printHand(const Hand &hand, const std::string &owner);
void printCard(const Hand &hand, const string &owner, int cardPos);
int checkHands(const Hand &hand, const std::string &owner);
void endGame(const Hand &player, Hand &computers, int playerNumber);
std::vector<std::tuple<int, std::string, int, int>> readWinLossRecord();
void updateWinLossRecord(const std::vector<std::tuple<int, std::string, int, int>> &playerNames);
std::vector<std::tuple<int, std::string, int, int>> loadPlayerNames();
void writePlayerNames(const std::vector<std::tuple<int, std::string, int, int>> &playerNames);
void updatePlayerRecord(int playerNumber, bool isWin);
void addPlayer();
int selectPlayerProfile();
void playGame();

#endif
