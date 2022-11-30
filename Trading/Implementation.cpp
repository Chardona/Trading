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
	for (auto& traderOne : fileData) {
		for (auto& traderTwo : fileData) {
			//  50/50 chance to make a deal
			if (rand() % 100 < 50 && traderOne.side == 'B' && traderTwo.side == 'S' && traderOne.trader != traderTwo.trader && 
				traderOne.quantity != 0 && traderTwo.quantity != 0) {
				int dealQuantity = rand() % traderOne.quantity;
				if (dealQuantity == 0) { dealQuantity++; };
				//do not buy/sell more, than you can
				if (dealQuantity < traderTwo.quantity) {
					{
						sendOuputData(traderOne, traderTwo, dealQuantity, fileRoute);
					}
				}
				else {
					dealQuantity = traderTwo.quantity;
					sendOuputData(traderOne, traderTwo, dealQuantity, fileRoute);
				}
			}
			if (rand() % 100 < 50 && traderOne.side == 'S' && traderTwo.side == 'B' && traderOne.trader != traderTwo.trader && 
				traderOne.quantity != 0 && traderTwo.quantity != 0) {
				int dealQuantity = rand() % traderOne.quantity;
				if (dealQuantity == 0) { dealQuantity++; };
				//do not buy/sell more, than you can
				if (dealQuantity < traderTwo.quantity) {
					{
						sendOuputData(traderOne, traderTwo, dealQuantity, fileRoute);
					}

				}
				else {
					dealQuantity = traderTwo.quantity;
					sendOuputData(traderOne, traderTwo, dealQuantity, fileRoute);
				}
			}
		}
	}
}
void Aggressor::sendOuputData(Aggressor& traderOne, Aggressor& traderTwo, int dealQuantity, std::string fileRoute) {
	std::map<char, char> sign;
	sign['B'] = '+';
	sign['S'] = '-';

	std::ofstream fout(fileRoute, std::ios::app);

	//check better price
	if (traderOne.price <= traderTwo.price) {
		fout << traderOne.trader << sign[traderOne.side] << dealQuantity << "@" << traderOne.price << " " <<
			traderTwo.trader << sign[traderTwo.side] << dealQuantity << "@" << traderOne.price << "\n";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}
	else {
		fout << traderOne.trader << sign[traderOne.side] << dealQuantity << "@" << traderTwo.price << " " <<
			traderTwo.trader << sign[traderTwo.side] << dealQuantity << "@" << traderTwo.price << "\n";
		traderOne.quantity -= dealQuantity;
		traderTwo.quantity -= dealQuantity;
	}

}