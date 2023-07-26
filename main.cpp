#include <bits/stdc++.h>
#include <conio.h> 
#include <cstdlib>
#include <ctime>
using namespace std;

int numberOfComputer = 6;
vector<int> computersSum(numberOfComputer, 0); //array of computers score
vector<int> computersAceCount(numberOfComputer, 0); //vector with size numberOfComputer and all elements initialized to 0

int playerSum = 0;
int playerAceCount = 0;

class Card {
	private:
	    string ranks = ""; // 2->A
	    string suits = ""; // clubs, diamonds, hearts, spades
	    int value;
	public:
	    string getRanks() {
	        return ranks;
	    }
	    void setRanks(string ranks) {
	        this->ranks = ranks;
	    }
	    string getSuits() {
	        return suits;
	    }
	    void setSuits(string suits) {
	        this->suits = suits;
	    }
	    void setValue(string rank) {
	    	if(rank == "A") {
	    		this->value = 11;
	    	} else if(rank == "K" || rank == "Q" || rank == "J") {
	    		this->value = 10;
			} else {
				this->value = stoi(ranks);
			}
		}
	    int getValue() {
	    	return value;
		}
};
	
class PlayingCards {
	private:
	    static const string ranks[13];
	    static const string suits[4];
	    vector<Card> playingCards;
	public:
	    // Constructor
	    PlayingCards() {
	        this->createPlayingCards();
	    }
	    vector<Card> getPlayingCards() {
	        return playingCards;
	    }
	    void setPlayingCards(vector<Card> playingCards) {
	        this->playingCards = playingCards;
	    }
	    // Helper function to generate playingcards
	    void createPlayingCards() {
		    for (int j = 0; j < 13; j++) {
		        for (int k = 0; k < 4; k++) {
		            Card card;  // declare a new Card object inside the loop
		            card.setRanks(ranks[j]);
		            card.setSuits(suits[k]);
		            card.setValue(ranks[j]);
		            playingCards.push_back(card);
		        }
		    }
		}
	    void shufflePlayingCards() {
		    for(int i = 0; i < playingCards.size(); i++) {
		        int j = rand() % 52; // generate a random number between 0 - 51
		        Card temp = playingCards[i];
		        playingCards[i] = playingCards[j];
		        playingCards[j] = temp;
		    }
		}
		Card get1Card() {
		    Card lastCard = playingCards.back();
		    cout << lastCard.getRanks() << " " << lastCard.getSuits() << endl;
		    playingCards.pop_back();
		    return lastCard;
		}
};

class User {
	private:
		int score;
		bool isSpecial; //when init 2 cards
		bool isMagicFive;
		bool isBust;
		 
};

const string PlayingCards::ranks[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
const string PlayingCards::suits[4] = { "clubs", "diamonds", "hearts", "spades" };

//(Function Prototype
int checkAce(Card card);
int reduceAce(int &userSum, int &userAceCount);
int hit(PlayingCards &plCards);
bool checkSpecial(Card firstCard, Card secondCard);
bool initTwoCards(PlayingCards &plCards, int &userSum, int &userAceCount);
void pickOneCard(PlayingCards &plCards, int &userSum, int &userAceCount);
void printBust(int score);

void pickOneCard(PlayingCards &plCards, int &userSum, int &userAceCount) {
	Card lastCard = plCards.get1Card();
	userSum += lastCard.getValue();
	userAceCount += checkAce(lastCard);
}

bool initTwoCards(PlayingCards &plCards, int &userSum, int &userAceCount) {
	Card firstCard = plCards.get1Card();
	userSum += firstCard.getValue();
	userAceCount += checkAce(firstCard);
		
	Card secondCard = plCards.get1Card();
	userSum += secondCard.getValue();
	userAceCount += checkAce(secondCard);
	
	return checkSpecial(firstCard, secondCard);
}

bool checkSpecial(Card firstCard, Card secondCard) {
	if(firstCard.getRanks() == "A" && secondCard.getRanks() == "A") {
		cout << "Double Aces!! Unbelievable!\n\n";
		return true;
	} else if(firstCard.getRanks() == "A") {
		if(secondCard.getRanks() == "K" || secondCard.getRanks() == "Q" || 
		secondCard.getRanks() == "J" || secondCard.getRanks() == "10") {
			cout << "Blackjack!!\n\n";
			return true;
		}
	} else if(secondCard.getRanks() == "A") {
		if(firstCard.getRanks() == "K" || firstCard.getRanks() == "Q" || 
		firstCard.getRanks() == "J" || firstCard.getRanks() == "10") {
			cout << "Blackjack!!\n\n";
			return true;
		}
	}
	return false;
}

void printBust(int score) {
	if(score > 21)
		cout << "(BUST) :((\n\n";
	else
		cout << "\n\n";  
}

void printRes(PlayingCards &plCards, int numberOfComputer) {
	//======Computer============
	for(int i = 0; i < numberOfComputer; i++) {
		cout <<"Computer " << i + 1 << " playing...\n";  	

		//init for player 2 cards
		bool isSpecial = initTwoCards(plCards, computersSum[i], computersAceCount[i]);
		
		int currentCardsNum = 2;
		if(!isSpecial) {
			while(computersSum[i] < 17) {
				currentCardsNum++;
				pickOneCard(plCards, computersSum[i], computersAceCount[i]);
			}
			if(currentCardsNum == 5 && computersSum[i] <= 21) {
				cout << "Magic Five! So lucky!!!\n\n";
			} else {
				cout << "Computer " << i + 1 << " score is " << computersSum[i] << " ";
				printBust(computersSum[i]);
			}
		}
	}
	//=====Player======
	cout <<"Player playing...\n";  	
	//init for player 2 cards
	bool isSpecial = initTwoCards(plCards, playerSum, playerAceCount);
	
	if(!isSpecial)
		hit(plCards);
}

int checkAce(Card card) {
	if(card.getRanks() == "A") 
		return 1;
	return 0;
}

int reduceAce(int &userSum, int &userAceCount) {
    while(userSum > 21 && userAceCount > 0) {
        userSum -= 10;
        userAceCount -= 1;
    }
    return userSum;
}

int hit(PlayingCards &plCards) {
	bool canHit = true;
	int currentCardsNum = 2;
	while(true) {
		if(kbhit()) {
			char c = getch();
			if(c == 13) { //Enter
				if(canHit) {
					Card lastCard = plCards.get1Card();
					playerSum += lastCard.getValue();
					playerAceCount += checkAce(lastCard);
					
					currentCardsNum++;
					
					if (reduceAce(playerSum, playerAceCount) > 21)  //check if Aces
	        			canHit = false;
				}
			}
			if(c == 32) { //Space
				playerSum = reduceAce(playerSum, playerAceCount);
				if(playerSum > 15 || currentCardsNum == 5) {
					for(int i = 0; i < numberOfComputer; i++) {
						computersSum[i] = reduceAce(computersSum[i], computersAceCount[i]);
					}
					
					canHit = false;
					if(currentCardsNum == 5 && playerSum <= 21) {
						cout << "Magic Five! So lucky!!!\n\n";
						cout << "You win!! Congratulations!!\n";
						break; 
					} else {
						cout <<"Player score is " << playerSum << " ";  
						printBust(currentCardsNum);
					}
				
					//take valid scores
					vector<int> validScores;
					for(int i = 0; i < numberOfComputer; i++) {
						if(computersSum[i] <= 21)
							validScores.push_back(computersSum[i]);
					}
					
					if(validScores.size() == 0) {
						if(playerSum <= 21) 
							cout << "You win!! Congratulations!!\n";	
						 else 
							cout << "Tie!!\n";
						break;
					}
						
					int maxScore = validScores[0];
					for(int i = 1; i < validScores.size(); i++) {
						if(maxScore < computersSum[i]) 
							maxScore = computersSum[i];
					}
					
					if(playerSum > maxScore && playerSum <= 21) 
						cout << "You win!! Congratulations!!\n";
					else if(playerSum < maxScore || playerSum > 21) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computersSum[i] == maxScore)
								cout << "Computer " << i+1 << " win!!\n";
						}
					} else {
						cout << "Tie!!\n";
					}
					
					break;
				}
			}
		}
	}
}

int main() {
	srand(time(0)); //set a seed
	PlayingCards plCards;
	
	plCards.shufflePlayingCards();
	//plCards.createPlayingCards();
	
	printRes(plCards, numberOfComputer);

	return 0;
}
