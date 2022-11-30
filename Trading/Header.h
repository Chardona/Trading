#ifndef TRADING_H
#define TRADING_H
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <map>


class Aggressor {
public:
	Aggressor() = default;
	Aggressor(std::string newTrader, char newSide, int newQuantity, int newPrice);
	void generateInputData(std::string fileRoute);
	std::vector<Aggressor> extractData(std::string fileRoute);
	void proccessOutputData(std::vector<Aggressor>& fileData, std::string fileRoute);
	void sendOuputData(Aggressor& traderOne, Aggressor& traderTwo, int dealQ, std::string fileRoute);
	std::string trader;
	char side{};
	int quantity{};
	int price{};
};



#endif // !TRADING_H
