//string name[4];
int money = 0;

void printMoney() {
	gotoXY(x+1, y+9);
	textcolor(38);
	cout << "Money: " << money;
	textcolor(39);
}

void caculateMoney(int &money, User player, User computer) {
	textcolor(7);		
	
	/////////////begin special cases/////////////

	//doubleAces -> blackJack -> magicFive

	if(player.isDoubleAces) {
		money += 2;
		return;
	}
	
	if(computer.isDoubleAces) {
		money -= 2;		
		return;
	}
	
	if(player.blackJack) {
		money++;
		return;
	}
	
	if(computer.blackJack) {
		money--;	
		return;
	}
	
	if(player.isMagicFive) {
		money++;
		return;
	}

	if(computer.isMagicFive) {
		money--;
		return;		
	}

	/////////////end special cases/////////////
	
	if(player.score <= 21) {
		if(player.score > computer.score || computer.score > 21) {
			money++;
		} else if(player.score < computer.score) {
			money--;
		} 
	} else {
		if(computer.score <= 21) {
			money--;
		}	
	}
}
