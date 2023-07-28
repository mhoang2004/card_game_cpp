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
	
	player.score = reduceAce(player);
	checkMagicFive(player);
	if(player.isMagicFive) {
		textcolor(7);					
		gotoXY(72, yChat++);
		cout << "Friday: You got a Magic Five!";
	}
	
	textcolor(39);
}
