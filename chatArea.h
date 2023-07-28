int xChat = 70, yChat = 19;
int widthChat = 80, heightChat = 21;

void writeNotify(int &yChat, vector<string> variables = {}) {
	textcolor(7);
	for(int i = 0; i < variables.size(); i++) {	
		gotoXY(72, yChat);
		cout << variables[i];	
	}
	yChat++;
	textcolor(39);
}
