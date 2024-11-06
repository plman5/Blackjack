// main.cpp

#include "blackjack.cpp"
#include "simulator.cpp"
int main() {
    

    playerNames = loadPlayerNames();
    // Populate the deck with values for 4 suits (0-12, 13-25, 26-38, 39-51)
    initializeDeck(deck,52);
    std::cout << "Select player:\n1. Existing Player\n2. New Player \n";
    std::cin >> input;
    
    if(input == '1'){
        playerNumber = selectPlayerProfile();
        
        if (playerNumber != -1) {
            std::string playerName = std::get<1>(playerNames[playerNumber-1]);
            std::cout << "Welcome back, " << playerName << "!\n";
        } else {
            std::cout << "Invalid selection. Please try again.\n";
            return 1;  // Exit if no valid player is selected
        }
    } else if (input == '2'){
        addPlayer();
    }
    
    std::cout << "Welcome to Blackjack! Please select an option from the menu:\n";
    do {
        std::cout << "1. Print Deck\n";
        std::cout << "2. Shuffle Deck\n";
        std::cout << "3. Deal Initial Cards\n";
        std::cout << "4. Draw Card\n";
        std::cout << "5. Show Hands\n";
        std::cout << "6. End Game\n";
        std::cout << "7. Play Game\n";
        std::cout << "8. Show Win/Loss Record\n";
        std::cout << "9. Start Simulator\n";
        std::cout << "q. Quit\n";
        std::cin >> input;

        switch (input) {
            case '1':
                printDeck(deck);
                break;
            case '2':
                shuffleDeck(deck, sizeof(deck) / sizeof(deck[0]));
                std::cout << "Deck Shuffled!\n";
                break;
            case '3':
                dealInitialCards(deck, player, computer);
                checkHands(player,"Player");
                checkHands(computer,"Computer");
                break;
            case '4':
                drawCard(deck, player);
                checkHands(player,"Player");
                break;
            case '5':
                printHand(player, "Player");
                printHand(computer, "Computer");
                break;
            case '6':
                endGame(player,computer,playerNumber);
                break;
            case '7':
                playGame();
                break;
            case '8': {
                vector<tuple<int, std::string, int, int>> playerNames = loadPlayerNames();
                int playerTotalWins = 0;
                int playerTotalLosses = 0;
                bool playerFound = false;
                cout << "playernumber is " << playerNumber;
                for (const auto& entry : playerNames) {
                    int checkNum = std::get<0>(entry);
                    if (playerNumber == checkNum) {
                        playerWins = std::get<2>(entry);
                        computerWins = std::get<3>(entry);
                        playerTotalWins = playerWins;
                        playerTotalLosses = computerWins;
                        playerFound = true;
                        break;
                 }
             }
                if (!playerFound) {
                    std::cout << "Player number " << playerNumber << " not found.\n";
                } else {
                    std::cout << "Player Wins: " << playerTotalWins << "\n";
                    std::cout << "Player Losses: " << playerTotalLosses << "\n";
                }
                break;
            }
            case '9':
            runSimulation();

            case 'q':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (input != 'q');

    return 0;
}
