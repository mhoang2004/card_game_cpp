const int numberOfComputer = 3;

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
