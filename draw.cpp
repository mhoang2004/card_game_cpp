#include <bits/stdc++.h>
#include "mylib.h"
using namespace std;
int x = 15, y = 28;

void active(int x, int y, int w, int h, int bg_color) {
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

void card(int x, int y, int w, int h, int rank, int suit) {
	active(x, y, w, h, 112);
	
	if(suit == 5 || suit == 6) {
		textcolor(112);
	} else {
		textcolor(116);
	}

	gotoXY(x+2, y+1);
	cout << rank << endl;
	gotoXY(x+2, y+2);
	cout << (char) suit << endl;
	
	textcolor(39);
	
	onlyBox(x, y, w, h);
}

void bai_up(int x, int y, int w, int h, int num) {
	active(x, y, w, h, 199);
	
	textcolor(199);
	gotoXY(x+6, y+4);
	cout << num;
	
	textcolor(39);
	
	onlyBox(x, y, w, h);
}

int main() {
	int h = 13;
	
	//random card
	for(int i = 0; i < 2; i++) {
		card(x + i*h, y, 12, 8, 4+i, 6);
	}

	//bot card
	bai_up(x, y - 20, 12, 8, 2);
	
	//control
	while(1) {
		if(kbhit()) {
			char c = getch();
			if(c == 13) { //Enter
				//system("cls");
				//card(40, 5, 12, 8, 6, 4);	
			}
			if(c == 27) { //Esc
				system("cls");
				cout << "Thanks for playing game... \nSee you next time!!";
				exit(0);
			}
		}	
	}
	

	for(int i = 0; i < 200; i++) {
		textcolor(i);
		cout << "Hello " << i << endl;
	}
	getch();
	return 0;
}
