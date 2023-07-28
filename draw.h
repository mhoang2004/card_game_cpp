#include <bits/stdc++.h>
#include "mylib.h"
using namespace std;
int x = 15, y = 28;
int h = 12, w = 8;

void setBackground(int x, int y, int w, int h, int bg_color) {
	textcolor(bg_color);	
	for(int iy = y + 1; iy <= y + h-1; iy++) {
		for(int ix = x + 1; ix <= x + w-1; ix++) {
			gotoXY(ix, iy);
			printf(" ");
		}
	}
	textcolor(39);
}

void onlyBox(int x, int y, int w, int h) {
	for(int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		printf("%c", 196); //char(196) is ascii
		gotoXY(ix, y + h);
		printf("%c",196);
	}
	
	for(int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		printf("%c", 179);
		gotoXY(x + w, iy);
		printf("%c", 179);
	}
	
	//border-radius 4 corner;
	gotoXY(x, y); printf("%c", 218);
	gotoXY(x + w, y); printf("%c", 191);
	gotoXY(x + w, y + h); printf("%c", 217);
	gotoXY(x, y + h); printf("%c", 192);
}

void drawCard(int x, int y, int w, int h, string rank, int suit) {
	setBackground(x, y, w, h, 112);
	
	if(suit == CLUBS || suit == SPADES) {
		textcolor(112);
	} else {
		textcolor(116);
	}

	gotoXY(x+2, y+1);
	cout << rank;
	
	//"CLUBS", "DIAMONDS", "HEARTS", "SPADES"
	gotoXY(x+2, y+2);
	cout << (char) suit;

	textcolor(39);
	
	onlyBox(x, y, w, h);
}

void faceDownCard(int x, int y, int w, int h, int num) {
	setBackground(x, y, w, h, 199);
	
	textcolor(199);
	if(num != 0) {
		gotoXY(x+6, y+4);
		cout << num;
	}

	textcolor(39);
	
	onlyBox(x, y, w, h);
}
