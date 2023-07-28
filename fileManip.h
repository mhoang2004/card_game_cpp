void readFile(int &money) {
	//read file money
	ifstream fileInput("moneyFile.txt");
	
	while (!fileInput.eof()) {	
		fileInput >> money;
	}	
}

void writeFile(int money) {
	ofstream outfile; 
    outfile.open("moneyFile.txt");
    outfile << money;
}

