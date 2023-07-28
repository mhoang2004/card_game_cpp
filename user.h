class User {
	private:	
		vector<Card> userCards;
	public:		
		int score = 0;
		int	aceCount = 0;
		int cardCount = 2;
		bool isSpecial = false;
		bool isDoubleAces = false;
		bool blackJack = false;
		bool isMagicFive = false;
		void setUserCards(Card card) {
			this->userCards.push_back(card);
		}
		
		vector<Card> getUserCards() {
			return userCards;
		}
};

string convertSuits(int suit) {
	string my_suits;
	
	if(suit == 6) {
		my_suits = "Spade";
	} else if(suit == 5) {
		my_suits = "Club";
	} else if(suit == 4) {
		my_suits = "Diamond";
	} else {
		my_suits = "Heart";
	}
	
	return my_suits;
}

void checkMagicFive(User &user) {
	if(user.cardCount == 5 && user.score <= 21) {
		user.isMagicFive = true;		
	}	
}
