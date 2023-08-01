#include <bits/stdc++.h>
#include "mylib.h"

using namespace std;
enum Suits{HEARTS = 3, DIAMONDS, CLUBS, SPADES};
int main() {
//	for(int i = 0; i < 200; i++) {
//		textcolor(i);
//		cout << i << endl;
//	}
	vector<int> a = {1, 2, 3, 1};
//	while(1) {
//		if(kbhit()) {
//			char c = getch();
//			if(c == 49 || c == 50) {
//				cout << c - 49;
//			}
//		}
//	}	
	a.clear();
	if(a.size()) {
		for(int i = 0; i < 4; i++) {
		cout << a[i] << endl;
	}
	}

	return 0;
}
