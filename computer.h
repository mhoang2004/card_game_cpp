const int numberOfComputer = 3;

bool computerInitTwoCards(PlayingCards &plCards, User &computer) {
	Card firstCard = plCards.get1Card();
	computer.score += firstCard.getValue();
	computer.aceCount += checkAce(firstCard);
		
	Card secondCard = plCards.get1Card();
	computer.score += secondCard.getValue();
	computer.aceCount += checkAce(secondCard);
	
	computer.setUserCards(firstCard);
	computer.setUserCards(secondCard);

	return checkSpecial(computer, firstCard, secondCard);
}

void computerPickOneCard(PlayingCards &plCards, User &computer) {
	Card lastCard = plCards.get1Card();
	computer.score += lastCard.getValue();
	computer.aceCount += checkAce(lastCard);
	computer.setUserCards(lastCard);
}

void computerPlay(PlayingCards &plCards, User &computer) {
	while(reduceAce(computer) < 17 && computer.cardCount < 5) {
		computer.cardCount++;
		computerPickOneCard(plCards, computer);	
	}
} 
