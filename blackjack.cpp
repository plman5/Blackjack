#include "blackjack.h"
#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
using namespace std;
int deck[52];
int playerNumber;
int blackjack = 0;
char input;
int playerWins = 0;
int computerWins = 0;
std::vector<std::tuple<int, std::string, int, int>> playerNames;
Hand player;
Hand computer;
void initializeDeck(int deck[], int size);
void dealInitialCards(int deck[], Hand &player, Hand &computer) {
    if(deck[51] == 0){
        initializeDeck(deck,52);
    }
    player.cardCount = 0;
    computer.cardCount = 0;

    for (int i = 0; i < 52 && player.cardCount < 2; ++i) {
        if (deck[i] != 0) {
            player.cards[player.cardCount++] = deck[i];
            deck[i] = 0;
        }
    }

    for (int i = 0; i < 52 && computer.cardCount < 2; ++i) {
        if (deck[i] != 0) {
            computer.cards[computer.cardCount++] = deck[i];
            deck[i] = 0;
        }
    }
    if(deck[51] == 0){
        initializeDeck(deck,52);
        dealInitialCards(deck,player,computer);
    }
   // cout << "Initial cards dealt to Player and Computer.\n";
}
int currentCardIndex = 0;

void drawCard(int deck[], Hand &hand) {
    if (currentCardIndex >= 52) {
        initializeDeck(deck, 52);
        currentCardIndex = 0;
    }
    hand.cards[hand.cardCount++] = deck[currentCardIndex++];
}


void shuffleDeck(int arr[], int n) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(arr, arr + n, default_random_engine(seed)); 
}
void initializeDeck(int deck[], int size) {
    for (int i = 1; i < size; ++i) {
        deck[i] = (i % 13) + 1;
    } 
    shuffleDeck(deck, size);
}
void printDeck(int deck[]) {
    int count = 0;
    for (int i = 0; i < 52; i++) {
        if (deck[i] != 0) {
            count++;
        }
    }
    cout << "There are " << count << " cards in the deck:\n";
    for (int i = 0; i < 52; ++i) {
        if (deck[i] == 11) {
            cout << "Jack" << endl;
        } else if (deck[i] == 12) {
            cout << "Queen" << endl;
        } else if (deck[i] == 13) {
            cout << "King" << endl;
        } else if (deck[i] == 1) {
            cout << "Ace" << endl;
        } else if (deck[i] != 0) {
            cout << deck[i] << endl;
        }
    }
}
void printCard(const Hand &hand, const string &owner, int cardPos){
    if(hand.cards[cardPos] == 1){
        cout << owner << " has an Ace\n";
    }else if (hand.cards[cardPos] == 11){
        cout << owner << " has a Jack\n";
    }else if(hand.cards[cardPos] == 12){
        cout << owner << " has a Queen\n";
    }else if(hand.cards[cardPos] == 12){
       cout << owner << " has a King\n"; 
    }else{
    cout << owner << " has " << hand.cards[cardPos] << "\n";
    }
}
int checkHands(const Hand &hand, const string &owner){
        int playVal = 0;
        for(int i = 0; i < hand.cardCount; i++){
                if(hand.cards[i] >= 10){
                        playVal+= 10;
                }else{
                    // Handle case for when Ace could be worth one or eleven based on the hand 
                    if(playVal <=10 && hand.cards[i] == 1){
                        playVal+=11;
                    }else{
                         playVal+=hand.cards[i];
                    }
                }
        }
     //  cout << owner << "'s Hand is Worth " << playVal << "\n";
        
        return playVal;
}
void printHand(const Hand &hand, const string &owner) {
    cout << owner << "'s hand: ";
    for (int i = 0; i < hand.cardCount; ++i) {
        int card = hand.cards[i];
        if (card == 11) {
            cout << "Jack ";
        } else if (card == 12) {
            cout << "Queen ";
        } else if (card == 13) {
            cout << "King ";
        } else if (card == 1) {
            cout << "Ace ";
        } else {
            cout << card << " ";
        }
    }
    cout << endl;
}
void playGame(){
    bool end = false;
    cout << "Thank you for playing Blackjack\n";
    dealInitialCards(deck,player,computer);
    printHand(player,"Player");
    printCard(computer,"Computer",0);
    while(!end){
        bool stop = false;
        printHand(player,"Player");
        printCard(computer,"Computer",0);
        cout << "What would you like to do?\n";
        cout<< "1. Hit\n";
        cout << "2. Stand\n";
        for(int i = 0; i < 5; i++){
            for(int j = 0; j <5; j++){
                if(player.cards[i] == player.cards[j] && player.cards[i] != 0){
                    cout << "3. Double\n";
                    stop = 1;
                    break;
                }
            }
            if(stop){
                break;
            }
        }
        cin >> input;
        switch(input){
            case '1':{
                drawCard(deck,player);
                int check = checkHands(player,"Player");
                if(check > 21){            
                cout << "Player" << " busted. :(\n";
                    endGame(player,computer,playerNumber);
                    end = true;
                }
            }
                break;
            case '2':
                endGame(player,computer,playerNumber);
                cout << "Play again? y/n\n";
                cin >> input;
                if(input == 'y' || input == 'Y'){
                    end = false;
                    dealInitialCards(deck,player,computer);
                }else{
                end = true;
                }
                break;
        }
    }

}
void endGame(const Hand &player,  Hand &computer,int playerNumber){
    
        int playVal = 0;
        int compVal = 0;
        playVal = checkHands(player, "Player");
        compVal = checkHands(computer,"Computer");
        if(compVal < 21 && computer.cardCount < 5){
                while(compVal < 17){
                    drawCard(deck,computer);
                    compVal+= computer.cards[computer.cardCount-1];
                }
        }
        if(compVal > 21){
         //   cout << "Computer busted! >:)\n";
        }
        if(compVal == 21 && computer.cardCount == 2){
            blackjack++;
        }else if (playVal == 21 && player.cardCount == 2){
            blackjack++;
        }
       // cout << "Player had " << playVal << " and Computer had " << compVal << "\n";
        if((playVal > compVal && playVal <= 21) || (playVal <=21 && compVal > 21)){
              //  cout << "Player wins with " << playVal << "\n";
                playerWins++;
                updatePlayerRecord(playerNumber,true);
        }else if ((compVal > playVal && compVal <= 21) || (compVal <=21 && playVal > 21)){
               // cout << "Computer wins with " << compVal << "\n";
                computerWins++;
                updatePlayerRecord(playerNumber,false);
        }else{
               // cout << "Draw at " << playVal << " "<< compVal << "\n";
        }
        updateWinLossRecord(loadPlayerNames());
}

void updateWinLossRecord(const vector<tuple<int, string, int, int>> &playerNames) {
    ofstream outFile("player_names.txt");
    if (outFile.is_open()) {
        for (const auto &entry : playerNames) {
            int number = std::get<0>(entry);
            string name = std::get<1>(entry);
            int wins = std::get<2>(entry);
            int losses = std::get<3>(entry);
            outFile << number << " " << name << " " << wins << " " << losses << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }
}
vector<tuple<int, string, int, int> > readWinLossRecord() {
    vector<tuple<int, string, int, int>> playerNames;
    ifstream inFile("player_names.txt");
    if (inFile.is_open()) {
        int number, wins, losses;
        string name;
        while (inFile >> number >> name >> wins >> losses) {
            playerNames.emplace_back(number, name, wins, losses);
        }
        inFile.close();
    } else {
        cout << "No existing record found. Starting fresh.\n";
        // Initialize with empty records or default values if needed
    }
    return playerNames;
}

int selectPlayerProfile() {
    vector<tuple<int, string,int,int> > playerNames = loadPlayerNames();
    int choice;
    
    cout << "Select your profile:\n";
    for (const auto& player : playerNames) {
        cout << get<0>(player) << ": " << get<1>(player) 
             << " Wins: " << get<2>(player) << " Losses: " << get<3>(player) << "\n";
    }
    cout << "Enter the number of your choice: ";
    cin >> choice;
    // Check if the choice is valid
    auto it = find_if(playerNames.begin(), playerNames.end(), [choice](const tuple<int, string, int, int>& player) {
        return get<0>(player) == choice;
    });

    if (it != playerNames.end()) {
      //  cout << "You selected: " << get<1>(*it) << "\n";
        return choice;
    } else {
        cout << "Invalid choice. Please try again.\n";
        return -1; // Indicate invalid choice
    }
}
vector<tuple<int, string, int, int>> loadPlayerNames() {
    vector<tuple<int, string, int, int>> playerNames;
    ifstream inFile("player_names.txt");
    if (inFile.is_open()) {
        string playerName;
        int playerNum;
        while (inFile >> playerNum >> playerName >> playerWins >> computerWins) {
            playerNames.emplace_back(playerNum, playerName, playerWins, computerWins);
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }
    return playerNames;
}
void addPlayer() {
    auto playerNames = loadPlayerNames();

    int newPlayerNumber = playerNames.size() + 1;
    string newPlayerName;

    cout << "Enter name for new player " << newPlayerNumber << ": ";
    cin.ignore(); // Clear input buffer
    getline(cin, newPlayerName);

    int initialWins = 0;
    int initialLosses = 0;
    playerNames.emplace_back(newPlayerNumber, newPlayerName, initialWins, initialLosses);
    for(const auto &entry : playerNames){
        cout << get<0>(entry);
        cout << get<1>(entry);
        cout << get<2>(entry);
    }
    writePlayerNames(playerNames);

    cout << "Player " << newPlayerNumber << " added with initial win/loss ratio of 0/0.\n";
}
void writePlayerNames(const vector<tuple<int, string, int, int>> &playerNames) {
    ofstream outFile("player_names.txt"); // Open file in write mode, not append

    if (outFile.is_open()) {
        for (const auto &entry : playerNames) {
            int number = std::get<0>(entry);
            string name = std::get<1>(entry);
            int wins = std::get<2>(entry);
            
            int losses = std::get<3>(entry);
            
            outFile << number << " " << name << " " << wins << " " << losses << "\n";
            //break;
            
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }
}
void updatePlayerRecord(int playerNumber, bool isWin) {
    vector<tuple<int, string, int, int>> playerNames = loadPlayerNames(); // Load existing records

    bool playerFound = false;

    for (auto &entry : playerNames) {
        int number = get<0>(entry);
        string name;
        int &wins = std::get<2>(entry);
        int &losses = std::get<3>(entry);

        if (number == playerNumber) {
            if (isWin) {
                wins++;
            } else {
                losses++;
            }
            playerFound = true;
            break;
        }
    }
    if (!playerFound) {
        cout << "Player number " << playerNumber << " not found.\n";
        return;
    }

    writePlayerNames(playerNames); // Save the updated records
}
