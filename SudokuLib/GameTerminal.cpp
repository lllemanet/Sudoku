#pragma once
#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>	//cin >> string
#include <iterator>
#include <vector>
#include "GameTerminal.h"
#include "SudokuBoard.h"
using namespace Sudoku;



/*Useful utility from "C++ Programmin Language book"*/
template<typename Target = std::string, typename Source = std::string>
Target to(Source arg) // convert Source to Target
{
	std::stringstream interpreter;
	Target result;
	if (!(interpreter << arg) // write arg into stream
		|| !(interpreter >> result) // read result from stream
		|| !(interpreter >> std::ws).eof()) // stuff left in stream?
		throw std::runtime_error{ "to<>() failed" };
	return result;
}

GameTerminal::GameTerminal(Game& game) : game{ game } {}

void GameTerminal::Start() {
	while (1) {
		PrintBoard(game.GetCurBoard());
		std::cout << "Choose your option: \n" <<
			"1. Move\n" <<
			"2. Undo\n" <<
			"3. Redo\n" <<
			"4. Exit\n";

		int choose = GetMenuItem();

		switch (choose) {
		case 1:
			try {
				game.MakeMove(GetMove());
			}
			catch (...) {
				break;
			}
			break;
		case 2:
			game.Undo();
			break;
		case 3:
			game.Redo();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}

		system("CLS");
	}
	
}

void GameTerminal::PrintBoard(const Board& board) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			std::string value = IsChangeable(board(r, c)) ? 
				to<std::string>(board(r, c) + 1) : 
				to<std::string>((board(r, c) % 9) + 1) + "L";
			std::cout << "\t" << value;	//not zero-based
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int GameTerminal::GetMenuItem() {
	int res;
	std::cin >> res;
	std::getchar(); //get riod of \n

	return res;
}

Move GameTerminal::GetMove() {
	using namespace std;

	cout << "Pls input your move in one of four possible formats (all values should be integers). 0 for empty:\n" <<
		"\'value index\'\n" <<
		"\'value row col\'\n" <<
		"\'value sqrrow sqrcol sqrind\'\n";
	
	//split string
	string str;
	std::getline(cin, str);
	istringstream iss{ str };
	vector<string> tokens{ istream_iterator<string>(iss),
					  istream_iterator<string>{} };

	if (tokens.size() < 2 || tokens.size() > 4)
		throw invalid_argument("There should be 1-3 ints");

	//get index
	int index;
	switch (tokens.size()) {
	case 2:
		index = to<int>(tokens[1]);
		break;
	case 3:
		index = Board::GetIndex(to<int>(tokens[1]), to<int>(tokens[2]));
		break;
	case 4:
		index = Board::GetIndex(to<int>(tokens[1]), to<int>(tokens[2]), to<int>(tokens[2]));
		break;
	default:
		break;
	}

	Point newValue = static_cast<Point>(to<int>(tokens[0]) - 1); //zero-based
	Point oldValue = static_cast<Point>(game.GetCurBoard()(index));

	return Move{index, newValue, oldValue};
}