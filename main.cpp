 #include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>

using namespace std;

#include "colors.h"
#include "card.h"
#include "draw.h"
#include "chatArea.h"
#include "user.h"
#include "logicGame.h"
#include "computer.h"
#include "player.h"
#include "money.h"
#include "fileManip.h"

/*		
	properties
		width: 150
		height: 40
		bg_color: green
*/

int main() {
	ShowCur(0);
	
	//set a seed
	srand(time(0)); 

	//init deck
	PlayingCards plCards;
	
	//shuffle the deck
	plCards.shufflePlayingCards();
	
	//money
	readFile(money);
	printMoney();
	
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
	setBackground(xChat, yChat-1, widthChat, heightChat, 7);
	textcolor(7);
	gotoXY(xChat+2, yChat++);
	cout << "Friday: Press any key to start playing game...";
	getch();
	
	gotoXY(x, y - 1); //set x,y if it special
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
		gotoXY(72, yChat);
		textcolor(7);
		cout << "Friday: Computer " << i+1 << " playing...";
		
		Sleep(1500);
		
		//computer init 2 cards value
		gotoXY(x + i*40, y - 21); //set x,y if it special
		computers[i].isSpecial = initTwoCards(plCards, computers[i]);
		
		//how the computer play
		if(computers[i].isSpecial) {
			//open 2 cards when special
			vector<Card> computerCards = computers[i].getUserCards();
			for(int j = 0; j < computers[i].cardCount; j++) {
				int xPos = x + i*40 + j*5;
				drawCard(xPos, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
			}
			
			gotoXY(72, yChat);
			textcolor(7);
			cout << "Friday: Computer " << i+1 << " got a special case!!";
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
	clearInputBuffer(); //clear all buffer
	
	int checkedCards = 0;	
	bool canHit = true; //if player score > 21
	while(1) {
		if(kbhit()) {
			char c = getch();
			if(c == 13) { //Enter		
				if(player.score > 15 || player.cardCount == 5) {
					int oldMoney = money;
					
					textcolor(7);
					
					//print user scores
					if(!player.isSpecial) {
						gotoXY(72, yChat++);
						if(player.score > 21) {
							cout << "Friday: You bust!";
						} else {
							cout << "Friday: Your score is " << player.score;
						}
					}
						
					//open computer's cards
					for(int i = 0; i < numberOfComputer; i++) {	
						if(computers[i].getUserCards().size()) {
							vector<Card> computerCards = computers[i].getUserCards();
							
							//print cards
							for(int j = 0; j < computerCards.size(); j++) {
								drawCard(x + i*40 + j*5, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
							}
						}
					}

					//caculate money
					for(int i = 0; i < numberOfComputer; i++) {
						//caculate computer's scores
						if(computers[i].getUserCards().size()) {
							computers[i].score = reduceAce(computers[i]);
							
							checkMagicFive(computers[i]);
							if(computers[i].isMagicFive) {
								gotoXY(72, yChat++);
								textcolor(7);
								cout << "Friday: Computer " << i + 1 << " got a Magic Five!";
							}
							
							caculateMoney(money, player, computers[i]);
						}
					}
					
					if(checkedCards != 3) {
						int profit = money - oldMoney;
						if(profit < 0) {
							gotoXY(72, yChat++);
							cout << "Friday: You lost, money " << profit;
						} else if(profit > 0) {
							gotoXY(72, yChat++);
							cout << "Friday: You win, money +" << profit;
						} else {
							gotoXY(72, yChat++);
							cout << "Friday: Tie!!";						
						}
						
						printMoney();
						
						//write file money
						writeFile(money);
					}
					
					break;						
				} else {
					gotoXY(72, yChat++);
					textcolor(7);
					cout << "Friday: Press 'Space' to Hit...";
				}
			}
			if(c == 32) { //Space
				if(canHit && !player.isSpecial && player.cardCount < 5 && checkedCards != 3) {	
					pickOneCard(plCards, player);
									
					if(reduceAce(player) > 21) { //check if Aces
	        			canHit = false;
					}
				} else {
					gotoXY(72, yChat++);
					textcolor(7);
					cout << "Friday: You can't hit anymore, press 'Enter' to end the game...";
				}
			}
			if(c == 27) { //Esc
				system("cls");
				cout << "Thanks for playing game... \nSee you next time!!";
				exit(0);
			}
			if(c == 49 || c == 50 || c == 51) { //1, 2, 3 key to solo with one computer	
				if((player.score > 14 || player.cardCount == 5) && !player.isSpecial) {
					int computerIndex = c - 49;
	
					//check if size != 0
					if(computers[computerIndex].getUserCards().size()) {
						checkedCards++;
						//open computer's cards
						for(int i = 0; i < numberOfComputer; i++) {	
							if(i == computerIndex) {
								vector<Card> computerCards = computers[i].getUserCards();
								
								//print cards
								for(int j = 0; j < computerCards.size(); j++) {
									drawCard(x + i*40 + j*5, y-20, h, w, computerCards[j].getRanks(), computerCards[j].getSuits());
								}						
								computers[i].clearUserCards();
							}		
						}
						
						int oldMoney = money;
						textcolor(7);
						
						//caculate computer's scores
						computers[computerIndex].score = reduceAce(computers[computerIndex]);
						
						checkMagicFive(computers[computerIndex]);
						if(computers[computerIndex].isMagicFive) {
							gotoXY(72, yChat++);
							textcolor(7);
							cout << "Friday: Computer " << computerIndex + 1 << " got a Magic Five!";
						}
						
						caculateMoney(money, player, computers[computerIndex]);

						//write notify
						int profit = money - oldMoney;
						gotoXY(72, yChat);
						cout << "Friday: You check computer " << computerIndex + 1;
						if(profit < 0) {
							gotoXY(100, yChat);
							cout << ": You lost, money " << profit;
						} else if(profit > 0) {
							gotoXY(100, yChat);
							cout << ": You win, money +" << profit;
						} else {
							gotoXY(100, yChat);
							cout << ": Tie!!";						
						}
						yChat++;
						
						printMoney();
					}							
				} else {
					gotoXY(72, yChat++);
					textcolor(7);
					if(player.isSpecial) {
						cout << "Friday: Press 'Enter' to end the game...";
					} else {
						cout << "Friday: Press 'Space' to Hit...";
					}	
				}
			}
		}	
	}
	
	gotoXY(72, yChat++);
	textcolor(7);
	cout << "Friday: Press any key to play again, 'Esc' to exit...";
	
	textcolor(39);
	

	char c = getch();
	if(c == 27) { //Esc
		system("cls");
		cout << "Thanks for playing game... \nSee you next time!!";
		exit(0);
	}
	
	yChat = 19;
	system("cls");
	
	return main();
} 
