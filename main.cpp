#include <bits/stdc++.h>
#include <conio.h> 
#include <cstdlib>
#include <ctime>
#include "draw.h"

using namespace std;

int h = 12, w = 8;

/*
properties
	width: 150
	height: 40
	bg_color: green
*/

//chat area
int xChat = 70, yChat = 19;
void writeNotify(int &yChat, vector<string> variables = {}) {
	textcolor(7);
	for(int i = 0; i < variables.size(); i++) {	
		gotoXY(72, yChat);
		cout << variables[i];	
	}
	yChat++;
	textcolor(39);
}

//====player==========
int playerSum = 0;
int playerCardsNum = 2; //init is 2
int playerAceCount = 0;

//====computers=======
const int numberOfComputer = 3;

//class Player {
//	int playerSum = 0;
//	int playerCardsNum = 2; //init is 2
//	int playerAceCount = 0;			
//};

class Card {
	private:
	    string ranks = ""; // 2->A
	    int suits; // clubs, diamonds, hearts, spades
	    int value;
	public:
		void setRanks(string ranks) {
	        this->ranks = ranks;
	    }
	    string getRanks() {
	        return ranks;
	    }
	    void setSuits(int suits) {
	        this->suits = suits;
	    }
	    int getSuits() {
	        return suits;
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

//create n computers
class Computer {
	private:	
		vector<Card> computerCards;
	public:
		int score = 0;
		int	aceCount = 0;
		int cardCount = 2;
		bool special = false;
		bool blackJack = false;

		void setComputerCards(Card card) {
			this->computerCards.push_back(card);
		}
		vector<Card> getComputerCards() {
			return computerCards;
		}
};
	
class PlayingCards {
	private:
	    static const string ranks[13];
	    static const int suits[4];
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
		    for(int j = 0; j < 13; j++) {
		        for(int k = 0; k < 4; k++) {
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
		    playingCards.pop_back();
		    return lastCard;
		}
};

const string PlayingCards::ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const int PlayingCards::suits[4] = {CLUBS, DIAMONDS, HEARTS, SPADES};

//Function Prototype
int checkAce(Card card);
int reduceAce(int &userSum, int &userAceCount);
bool checkSpecial(Card firstCard, Card secondCard);
bool initTwoCards(PlayingCards &plCards, int &playerSum, int &playerAceCount);
void pickOneCard(PlayingCards &plCards, int &playerSum, int &playerAceCount, int &cardsNum, bool isDrawing = true);
void printBust(int score);
void computerPlay(PlayingCards &plCards, int &score, int &numCard, int &numAce);

void pickOneCard(PlayingCards &plCards, int &playerSum, int &playerAceCount, int &cardsNum, bool isDrawing) {
	Card lastCard = plCards.get1Card();
	playerSum += lastCard.getValue();
	playerAceCount += checkAce(lastCard);
	
	if(isDrawing) {
		string my_suits;
		if(lastCard.getSuits() == 6) {
			my_suits = "Spade";
		} else if(lastCard.getSuits() == 5) {
			my_suits = "Club";
		} else if(lastCard.getSuits() == 4) {
			my_suits = "Diamond";
		} else {
			my_suits = "Heart";
		}
		
		//write notification
	 	gotoXY(72, yChat++);
		textcolor(7);
		cout << "Friday: You got " << lastCard.getRanks() << " of " << my_suits << endl;
		
		drawCard(x + cardsNum*5, y, h, w, lastCard.getRanks(), lastCard.getSuits());
		cardsNum++;
		
		textcolor(39);
	}
}

void computerPickOneCard(PlayingCards &plCards, Computer &computer) {
	Card lastCard = plCards.get1Card();
	computer.score += lastCard.getValue();
	computer.aceCount += checkAce(lastCard);
	computer.setComputerCards(lastCard);
}

//player
bool initTwoCards(PlayingCards &plCards, int &userSum, int &userAceCount) {
	Card firstCard = plCards.get1Card();
	userSum += firstCard.getValue();
	userAceCount += checkAce(firstCard);
		
	Card secondCard = plCards.get1Card();
	userSum += secondCard.getValue();
	userAceCount += checkAce(secondCard);
	

	drawCard(x, y, h, w, firstCard.getRanks(), firstCard.getSuits());
	drawCard(x + 5, y, h, w, secondCard.getRanks(), secondCard.getSuits()); //5 is left paddding
	gotoXY(x, y - 1); //set x,y if it special

	return checkSpecial(firstCard, secondCard);
}

//computer
bool initComputerTwoCards(PlayingCards &plCards, Computer &computer) {
	Card firstCard = plCards.get1Card();
	computer.score += firstCard.getValue();
	computer.aceCount += checkAce(firstCard);
		
	Card secondCard = plCards.get1Card();
	computer.score += secondCard.getValue();
	computer.aceCount += checkAce(secondCard);
	
	computer.setComputerCards(firstCard);
	computer.setComputerCards(secondCard);

	return checkSpecial(firstCard, secondCard);
}

bool checkSpecial(Card firstCard, Card secondCard) {
	textcolor(39);
	if(firstCard.getRanks() == "A" && secondCard.getRanks() == "A") {
		cout << "Double Aces!!";
		return true;
	} else if(firstCard.getRanks() == "A") {
		if(secondCard.getRanks() == "K" || secondCard.getRanks() == "Q" || 
		secondCard.getRanks() == "J" || secondCard.getRanks() == "10") {
			cout << "Blackjack!!";
			return true;
		}
	} else if(secondCard.getRanks() == "A") {
		if(firstCard.getRanks() == "K" || firstCard.getRanks() == "Q" || 
		firstCard.getRanks() == "J" || firstCard.getRanks() == "10") {
			cout << "Blackjack!!";
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
 
void computerPlay(PlayingCards &plCards, Computer &computer) {
	while(reduceAce(computer.score, computer.aceCount) < 17 && computer.cardCount < 5) {
		computer.cardCount++;
		computerPickOneCard(plCards, computer);	
	}
} 

void playAgain() {
	yChat = 19;
	playerSum = 0;
	playerCardsNum = 2; //init is 2
	playerAceCount = 0;
}

int main() {
	ShowCur(0);
	
	srand(time(0)); //set a seed
	
	//init deck
	PlayingCards plCards;
	
	//shuffle the deck
	plCards.shufflePlayingCards();
	
	//init computers
	class Computer computers[numberOfComputer];
	
	//player init 2 card
	bool playerSpecial = initTwoCards(plCards, playerSum, playerAceCount);
	
	//computers init 2 card
	for(int i = 0; i < numberOfComputer; i++) 
		faceDownCard(x + i*40, y - 20, h, w, 2);	
	
	//before playing...
	setBackground(xChat, 18, 80, 21, 7);
	textcolor(7);
	gotoXY(xChat+2, yChat++);
	cout << "Friday: Press any key to start playing game..." << endl;
	getch();
	
	//start playing game...
	for(int i = 0; i < numberOfComputer; i++) {
		//int computerCardsNum = 2;

		//computer init 2 cards value
		gotoXY(x + i*40, y - 21); //set x,y if it special
		bool computerSpecial = initComputerTwoCards(plCards, computers[i]);
		
		gotoXY(72, yChat);
		textcolor(7);
		cout << "Friday: Computer " << i+1 << " playing...";
		
		//how the computer play
		if(!computerSpecial) {
			computerPlay(plCards, computers[i]);
			faceDownCard(x + i*40, y - 20, h, w, computers[i].cardCount);
			textcolor(7);
			gotoXY(102, yChat);
			if(computers[i].cardCount - 2 == 0) {
				cout << " [do not hit]";
			} else if(computers[i].cardCount - 2 == 1) {
				cout << " [hit 1 card]";
			} else {
				cout << " [hit " << computers[i].cardCount - 2 << " cards]";
			}
		} else {
			gotoXY(72, yChat);
			textcolor(7);
			cout << "Friday: Computer " << i+1 << " got a special case!!";
			
			//open 2 cards when special
			vector<Card> computerCards = computers[i].getComputerCards();
			for(int j = 0; j < computers[i].cardCount; j++) {
				drawCard(x + i*40 + j*5, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
			}
		}
		
		yChat++;
		
		Sleep(1500);
	}
	
	gotoXY(72, yChat++);
	textcolor(7);
	cout << "Friday: Your turn, press 'Space' to Hit or 'Enter' to Stand..." << endl;
	
	textcolor(39);
	
	//control
	bool canHit = true;
	while(1) {
		if(kbhit()) {
			char c = getch();
			if(c == 13) { //Enter		
				bool isMagicFive = false, isComputerMagicFive = false;
				playerSum = reduceAce(playerSum, playerAceCount);
				if(playerSum > 15 || playerCardsNum == 5) {
					//==open cards==
					for(int i = 0; i < numberOfComputer; i++) {	
						canHit = false;
						
						//choose computer
						vector<Card> computerCards = computers[i].getComputerCards();
						
						//print cards
						for(int j = 0; j < computerCards.size(); j++) {
							drawCard(x + i*40 + j*5, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
						}
					}
					textcolor(7);
					
					bool isMagicFive = false;
					if(playerCardsNum == 5 && playerSum <= 21) {					
						gotoXY(72, yChat++);
						cout << "Friday: You got a Magic Five!";
						isMagicFive = true;
												
						break;
					} else {
						gotoXY(72, yChat++);
						cout <<"Friday: Your score is: " << playerSum;  
					}
					
					for(int i = 0; i < numberOfComputer; i++) {
						computers[i].score = reduceAce(computers[i].score, computers[i].aceCount);
						
						if(computers[i].cardCount == 5 && computers[i].score <= 21) {
							gotoXY(72, yChat++);
							cout << "Friday: Computer " << i << " got a Magic Five!";
							
							if(!isMagicFive) {
								cout << "Friday: Computer " << i << " win!!";
							}
							
							isComputerMagicFive = true;
						}
					}
					
					if(isMagicFive) {
						if(isComputerMagicFive) {
							gotoXY(72, yChat++);
							cout << "Friday: Tie";
						} else {
							gotoXY(72, yChat++);
							cout << "Friday: You win!! Congratulations!!";
						}		 
					} 
					
					if(isComputerMagicFive)
						break;
							
					//take valid scores
					vector<int> validScores;
					for(int i = 0; i < numberOfComputer; i++) {
						if(computers[i].score <= 21)
							validScores.push_back(computers[i].score);
					}
					
					if(validScores.size() == 0) {
						if(playerSum <= 21) {
							gotoXY(72, yChat++);
							cout << "Friday: You win!! Congratulations!!";							
						}
						 else {
						 	gotoXY(72, yChat++);
							cout << "Friday: Tie!!";
						}						 	
						break;
					}
				
					int maxScore = *max_element(validScores.begin(), validScores.end());
					
					if(playerSum > maxScore && playerSum <= 21) {
						gotoXY(72, yChat++);
						cout << "Friday: You win!! Congratulations!!";
					} else if(playerSum < maxScore || playerSum > 21) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computers[i].score == maxScore) {
								gotoXY(72, yChat++);
								cout << "Friday: Computer " << i+1 << " win!!";
							}
						}
					} else {
						gotoXY(72, yChat++);
						cout << "Friday: Tie!!";
					}
					
					break;
				}
			}
			
			if(c == 32) { //Space
				if(canHit and !playerSpecial) {	
					pickOneCard(plCards, playerSum, playerAceCount, playerCardsNum);				
					if(reduceAce(playerSum, playerAceCount) > 21) { //check if Aces
	        			canHit = false;
					}
				} else {
					gotoXY(72, yChat++);
					textcolor(7);
					cout << "Friday: You can't hit anymore, hit 'Enter' to end the game..." << endl;
				}
			}
			
			if(c == 27) { //Esc
				system("cls");
				cout << "Thanks for playing game... \nSee you next time!!";
				exit(0);
			}
		}	
	}
	
	gotoXY(72, yChat++);
	textcolor(7);
	cout << "Friday: Press 'Enter' to play again, 'Esc' to exit..." << endl;
	
	textcolor(39);
	
	while(1) {
		if(kbhit()) {
		char c = getch();
			if(c == 13) { //Enter
				system("cls");
				playAgain();
				return main();
			}
		}
	}
	getch();
	return 0;
}
