#include <bits/stdc++.h>
#include <conio.h> 
#include <cstdlib>
#include <ctime>

using namespace std;

#include "card.h"
#include "user.h"
#include "draw.h"
#include "logicGame.h"
#include "computer.h"

/*
	todo
		player and computer inherit...
		fix bugs: magicFivePlayer
		separate file
		
	properties
		width: 150
		height: 40
		bg_color: green
*/

//Function Prototype
bool initTwoCards(PlayingCards &plCards, int &playerSum, int &playerAceCount);
void pickOneCard(PlayingCards &plCards, int &playerSum, int &playerAceCount, int &cardsNum, bool isDrawing = true);
void printBust(int score);

//money
int money = 0;

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

void pickOneCard(PlayingCards &plCards, User &player) {
	Card lastCard = plCards.get1Card();
	player.score += lastCard.getValue();
	player.aceCount += checkAce(lastCard);
	
	string my_suits = convertSuits(lastCard.getSuits());
	
	//write notification
 	gotoXY(72, yChat++);
	textcolor(7);
	cout << "Friday: You got " << lastCard.getRanks() << " of " << my_suits << endl;
	
	//draw the card picked
	drawCard(x + player.cardCount*5, y, h, w, lastCard.getRanks(), lastCard.getSuits());
	(player.cardCount)++;
	
	checkMagicFive(player);
	if(player.isMagicFive) {					
		gotoXY(72, yChat++);
		cout << "Friday: You got a Magic Five!";
	}
	
	textcolor(39);
}

bool initTwoCards(PlayingCards &plCards, User &player) {
	Card firstCard = plCards.get1Card();
	player.score += firstCard.getValue();
	player.aceCount += checkAce(firstCard);
		
	Card secondCard = plCards.get1Card();
	player.score += secondCard.getValue();
	player.aceCount += checkAce(secondCard);
	
	player.setUserCards(firstCard);
	player.setUserCards(secondCard);

	gotoXY(x, y - 1); //set x,y if it special

	return checkSpecial(player, firstCard, secondCard);
}

void printBust(int score) {
	if(score > 21)
		cout << "(BUST) :((\n\n";
	else
		cout << "\n\n";  
}

void playAgain() {
//	yChat = 19;
//	playerSum = 0;
//	playerCardsNum = 2; //init is 2
//	playerAceCount = 0;
}

void openCard(User user, int xPos, int yPos) {
	vector<Card> userCards = user.getUserCards();
	
	//print cards
	for(int j = 0; j < userCards.size(); j++) {
		drawCard(xPos, xPos, h, w, userCards[j].getRanks(), userCards[j].getSuits());
	}
}

int main() {
	ShowCur(0);
	
	//set a seed
	srand(time(0)); 
	
	//init deck
	PlayingCards plCards;
	
	//shuffle the deck
	plCards.shufflePlayingCards();
	
	//print money
	gotoXY(x+1, y+9);
	textcolor(38);
	cout << "Money: " << money;
	textcolor(39);
	
	//init computers
	class User computers[numberOfComputer];
	for(int i = 0; i < numberOfComputer; i++) 
		faceDownCard(x + i*40, y - 20, h, w, 2);
	
	//init player
	class User player;
	//draw 2 player's card (only draw card)
	faceDownCard(x, y, h, w, 0);
	faceDownCard(x + 5, y, h, w, 0);
	
	//before playing...
	setBackground(xChat, 18, 80, 21, 7);
	textcolor(7);
	gotoXY(xChat+2, yChat++);
	cout << "Friday: Press any key to start playing game...";
	getch();
	
	player.isSpecial = initTwoCards(plCards, player);
	
	if(player.isSpecial) {
		gotoXY(72, yChat++);
		textcolor(7);
		cout << "Friday: You got a special case!!";
	}
	
	//open 2 cards init of player 
	drawCard(x, y, h, w, player.getUserCards()[0].getRanks(), player.getUserCards()[0].getSuits());
	drawCard(x + 5, y, h, w, player.getUserCards()[1].getRanks(), player.getUserCards()[1].getSuits()); //5 is left-paddding
	
	//start computers playing game...
	for(int i = 0; i < numberOfComputer; i++) {
		//computer init 2 cards value
		gotoXY(x + i*40, y - 21); //set x,y if it special
		computers[i].isSpecial = computerInitTwoCards(plCards, computers[i]);
		
		gotoXY(72, yChat);
		textcolor(7);
		cout << "Friday: Computer " << i+1 << " playing...";
		
		//how the computer play
		if(computers[i].isSpecial) {
			gotoXY(72, yChat);
			textcolor(7);
			cout << "Friday: Computer " << i+1 << " got a special case!!";
			
			//open 2 cards when special
			vector<Card> computerCards = computers[i].getUserCards();
			for(int j = 0; j < computers[i].cardCount; j++) {
				int xPos = x + i*40 + j*5;
				drawCard(xPos, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
			}
		} else {
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
		}
		yChat++;
		
		Sleep(1500);
	}

	gotoXY(72, yChat++);
	textcolor(7);
	if(player.isSpecial) {
		cout << "Friday: Press 'Enter' to end the game...";	
	} else {
		cout << "Friday: Your turn, press 'Space' to Hit, 'Enter' to Stand...";	
	}
	
	textcolor(39);
	
	//====control=========
	bool canHit = true;
	while(1) {
		if(kbhit()) {
			char c = getch();
			if(c == 13) { //Enter		
				player.score = reduceAce(player);
				if(player.score > 15 || player.cardCount == 5) {
					canHit = false;
					//==open cards==
					for(int i = 0; i < numberOfComputer; i++) {	
						vector<Card> computerCards = computers[i].getUserCards();
						
						//print cards
						for(int j = 0; j < computerCards.size(); j++) {
							drawCard(x + i*40 + j*5, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
						}
					}
					
					textcolor(7);
					
					//caculate computers' score and specials
					bool computerMagicFive = false; //does any computer have magic five? 
					bool computerBlackJack = false;
					bool computerDoubleAces = false;
					
					for(int i = 0; i < numberOfComputer; i++) {
						computers[i].score = reduceAce(computers[i]);
						
						checkMagicFive(computers[i]);
						
						if(computers[i].isMagicFive) {
							gotoXY(72, yChat++);
							cout << "Friday: Computer " << i + 1 << " got a Magic Five!";
							computerMagicFive = true;
						}
						
						if(computers[i].blackJack) {
							computerBlackJack = true;
						}
						
						if(computers[i].isDoubleAces) {
							computerDoubleAces = true;
						}
					}		
					
					/////////////begin special cases/////////////
					
					if(computerMagicFive && player.isMagicFive || 
					computerBlackJack && player.blackJack ||
					computerDoubleAces && player.isDoubleAces) {
						gotoXY(72, yChat++);
						cout << "Friday: Tie!!";
						break;
					}
					
					//doubleAces -> blackJack -> magicFive
				
					if(player.isDoubleAces) {
						gotoXY(72, yChat++);
						cout << "Friday: You win!! Congratulations!!";
						money++;
						break;
					}
					
					if(computerDoubleAces) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computers[i].isDoubleAces) {
								gotoXY(72, yChat++);
								cout << "Friday: Computer " << i + 1 << " win!!";
								money--;		
							}	
						}
						break;
					}
					
					if(player.blackJack) {
						gotoXY(72, yChat++);
						cout << "Friday: You win!! Congratulations!!";
						money++;
						break;
					}
					
					if(computerBlackJack) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computers[i].blackJack) {
								gotoXY(72, yChat++);
								cout << "Friday: Computer " << i + 1 << " win!!";	
								money--;	
							}	
						}
						break;
					}
					
					if(player.isMagicFive) {
						gotoXY(72, yChat++);
						cout << "Friday: You win!! Congratulations!!";
						money++;
						break;
					}
					
					if(computerMagicFive) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computers[i].isMagicFive) {
								gotoXY(72, yChat++);
								cout << "Friday: Computer " << i + 1 << " win!!";
								money--;		
							}	
						}
						break;
					}
					
					/////////////end special cases/////////////
					
					gotoXY(72, yChat++);
					cout << "Friday: Your score is " << player.score;
						
					//take valid scores
					vector<int> validScores;
					for(int i = 0; i < numberOfComputer; i++) {
						if(computers[i].score <= 21)
							validScores.push_back(computers[i].score);
					}
					
					if(validScores.size() == 0) {
						if(player.score <= 21) {
							gotoXY(72, yChat++);
							cout << "Friday: You win!! Congratulations!!";	
							money++;						
						}
						 else {
						 	gotoXY(72, yChat++);
							cout << "Friday: Tie!!";
						}						 	
						break;
					}
				
					int maxScore = *max_element(validScores.begin(), validScores.end());
					
					if(player.score > maxScore && player.score <= 21) {
						gotoXY(72, yChat++);
						cout << "Friday: You win!! Congratulations!!";
						money++;
					} else if(player.score < maxScore || player.score > 21) {
						for(int i = 0; i < numberOfComputer; i++) {
							if(computers[i].score == maxScore) {
								gotoXY(72, yChat++);
								cout << "Friday: Computer " << i+1 << " win!!";
								money--;
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
				if(canHit && !player.isSpecial && player.cardCount < 5) {	
					pickOneCard(plCards, player);				
					if(reduceAce(player) > 21) { //check if Aces
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
				yChat = 19;
				system("cls");
				playAgain();
				return main();
			}
			if(c == 27) { //Esc
				system("cls");
				cout << "Thanks for playing game... \nSee you next time!!";
				exit(0);
			}
		}
	}
	
	getch();
	return 0;
}
