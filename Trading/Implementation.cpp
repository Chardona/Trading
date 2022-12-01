#include "Header.h"

Aggressor::Aggressor(std::string newTrader, char newSide, int newQuantity, int newPrice):
	trader(newTrader), side(newSide), quantity(newQuantity), price(newPrice) {}
void Aggressor::generateInputData(std::string fileRoute) {
	std::ofstream fout(fileRoute);
	for (int i = 1; i <= 10; i++) {
		std::string trader = "T" + std::to_string(rand() % 9 + 1);
		char side = ' ';
		(rand() % 2 == 0) ? side = 'B' : side = 'S';
		int quantity = rand() % 101;
		int price = rand() % 101;
		
		fout << trader << " " << side << " " << quantity << " " << price << "\n";
	}
	fout.close();
}
std::vector<Aggressor> Aggressor::extractData(std::string fileRoute) {
	std::ifstream fin(fileRoute);
	std::string line{};
	
	std::vector<Aggressor> data;
	while (!fin.eof()) {
		std::string trader{};
		char side{};
		std::string quantity{};
		std::string price{};
		int index{};
		getline(fin, line);
		if (line.length() > 0) {
			//getting trader
			for (int i = index; i < line.length(); i++) {
				index++;
				if (!isspace(line[i])) {
					trader += line[i];
				}
				else {
					break;
				}
			}
			//getting side
			for (int i = index; i < line.length(); i++) {
				index++;
				if (!isspace(line[i])) {
					side += line[i];
				}
				else {
					break;
				}
			}
			//getting quantity
			for (int i = index; i < line.length(); i++) {
				index++;
				if (!isspace(line[i])) {
					quantity += line[i];
				}
				else {
					break;
				}
			}
			//getting price
			for (int i = index; i < line.length(); i++) {
				index++;
				if (!isspace(line[i])) {
					price += line[i];
				}
				else {
					break;
				}
			}
			data.push_back(Aggressor(trader, side, std::stoi(quantity), std::stoi(price)));
		}
	}
	fin.close();
	return data;
}
void Aggressor::proccessOutputData(std::vector<Aggressor>& fileData, std::string fileRoute) {
	//wanted to use it instead of +- sign, but it's redundant
	/*std::map<char, char> sign;
	sign['B'] = '+';
	sign['S'] = '-';*/
	std::deque<Aggressor> oneLineChecker;
	//crutch to solve the problem with blank line
	int crutch = 0;
	std::ofstream fout(fileRoute, std::ios::app);
	for (auto& traderOne : fileData) {
		for (auto& traderTwo : fileData) {
			oneLineChecker.push_back(traderOne);
				//  50/50 chance to make a deal
				if (rand() % 100 < 50 && traderOne.side == 'B' && traderTwo.side == 'S' && traderOne.trader != traderTwo.trader &&
					traderOne.quantity != 0 && traderTwo.quantity != 0) {
					sendBuyerOutput(traderOne, traderTwo, fout);
				}
				if (rand() % 100 < 50 && traderOne.side == 'S' && traderTwo.side == 'B' && traderOne.trader != traderTwo.trader &&
					traderOne.quantity != 0 && traderTwo.quantity != 0) {
					sendSellerOutput(traderOne, traderTwo, fout);
				}
				//checks, when it's time to make a new line
				if (oneLineChecker[0].trader != traderOne.trader && !oneLineChecker.empty()) {
					oneLineChecker.clear();
					if (crutch > 0) {
						fout << "\n";
					}
					crutch++;
				}
			}
		}
	fout.close();
	}
//the difference between 2 functions below is in their sign order and price checker:
//seller wants higher price, buyer lower
void Aggressor::sendBuyerOutput(Aggressor& traderOne, Aggressor& traderTwo, std::ofstream& fout)
{
	//randomizing size of the purchase
	int dealQuantity = rand() % traderOne.quantity;
	//do not buy nothing
	if (dealQuantity == 0) { dealQuantity++; };
	//do not buy/sell more, than you can
	if (dealQuantity > traderTwo.quantity) {
		dealQuantity = traderTwo.quantity;
	}

	//check better price to buy
	if (traderOne.price <= traderTwo.price) {
		fout << traderOne.trader << "+" << dealQuantity << "@" << traderOne.price << " " <<
			traderTwo.trader << "-" << dealQuantity << "@" << traderOne.price << " ";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}
	else {
		fout<< traderOne.trader << "+" << dealQuantity << "@" << traderTwo.price << " " <<
			traderTwo.trader << "-" << dealQuantity << "@" << traderTwo.price << " ";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}
}
void Aggressor::sendSellerOutput(Aggressor& traderOne, Aggressor& traderTwo, std::ofstream& fout)
{	
	//randomising size of the sale
	int dealQuantity = rand() % traderOne.quantity;
	//do not buy nothing
	if (dealQuantity == 0) { dealQuantity++; };
	//do not buy/sell more, than you can
	if (dealQuantity > traderTwo.quantity) {
		dealQuantity = traderTwo.quantity;
	}
	//check better price to sell
	if (traderOne.price >= traderTwo.price) {
		fout << traderOne.trader << "-" << dealQuantity << "@" << traderOne.price << " " <<
			traderTwo.trader << "+" << dealQuantity << "@" << traderOne.price << " ";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}
	else {
		fout << traderOne.trader << "-" << dealQuantity << "@" << traderTwo.price << " " <<
			traderTwo.trader << "+" << dealQuantity << "@" << traderTwo.price << " ";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}
}

