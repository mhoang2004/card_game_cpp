bool checkSpecial(User &user, Card firstCard, Card secondCard) {
	textcolor(39);
	if(firstCard.getRanks() == "A" && secondCard.getRanks() == "A") {
		cout << "Double Aces!!";
		user.isDoubleAces = true;
		return true;
	} else if(firstCard.getRanks() == "A") {
		if(secondCard.getRanks() == "K" || secondCard.getRanks() == "Q" || 
		secondCard.getRanks() == "J" || secondCard.getRanks() == "10") {
			cout << "Blackjack!!";
			user.blackJack = true;
			return true;
		}
	} else if(secondCard.getRanks() == "A") {
		if(firstCard.getRanks() == "K" || firstCard.getRanks() == "Q" || 
		firstCard.getRanks() == "J" || firstCard.getRanks() == "10") {
			cout << "Blackjack!!";
			user.blackJack = true;
			return true;
		}
	}
	return false;
}

int checkAce(Card card) {
	if(card.getRanks() == "A") 
		return 1;
	return 0;
}

int reduceAce(User &user) {
    while(user.score > 21 && user.aceCount > 0) {
        user.score -= 10;
        user.aceCount -= 1;
    }
    return user.score;
}
