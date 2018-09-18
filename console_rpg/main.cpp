#include "stdafx.h"
#include <iostream>
#include <curses.h>
#include <string>
#include "constants.h"
#include "item_types.h"
#include "characters.h"
#include "functions.h"

int main()
{
	Player player1;
	player1.level = 0;
	player1.requiredxp = defaultRequiredXP;
	player1.currentxp = 0;

	initscr();
	start_color();

	printTitle(2, 4);

	WINDOW * menuScreen = newwin(7, 70, 11, 22);
	keypad(menuScreen, true);
	refresh();
	box(menuScreen, 0, 0);
	wrefresh(menuScreen);

	std::string menuOptions[2] = { "Start Game", "Exit" };
	int currentChoice = (int)Options::FIRST_OPTION;
	int input;

	curs_set(0);
	noecho();
	while (1) {
		for (int i = 0; i < 2; i++) {
			if (currentChoice == i) {
				wattron(menuScreen, A_REVERSE);
			}
			mvwprintw(menuScreen, i + 2, 30, menuOptions[i].c_str());
			wattroff(menuScreen, A_REVERSE);
		}
		input = wgetch(menuScreen);

		switch (input) {
		case KEY_UP:
			currentChoice--;
			if (currentChoice == -1) {
				currentChoice = (int)Options::FIRST_OPTION;
			}
			break;
		case KEY_DOWN:
			currentChoice++;
			if (currentChoice == 2) {
				currentChoice = (int)Options::SECOND_OPTION;
			}
			break;
		default:
			break;
		}
		if (input == 10) {
			break;
		}
	}

	if (currentChoice == 1) {
		endwin();
		return 0;
	}
	else if (currentChoice == 0) {
		clear();
		echo();
		printCharacter(1, 33);
		WINDOW * characterCreation = newwin(15, 50, 10, 32);
		keypad(characterCreation, true);
		refresh();
		wborder(characterCreation, '|', '|', '-', '-', '/', '\\', '\\', '/');
		wrefresh(characterCreation);
		mvwprintw(characterCreation, 2, 2, "Input your character name: ");
		mvwprintw(characterCreation, 5, 2, "Choose your stats|");
		mvwprintw(characterCreation, 5, 20, "Available points: ");
		int availablePoints = 5;
		int strength = 0;
		int intelligence = 0;
		int dexterity = 0;
		std::string pointsToString = std::to_string(availablePoints);
		std::string strengthToString = std::to_string(strength);
		std::string dexterityToString = std::to_string(dexterity);
		std::string intelligenceToString = std::to_string(intelligence);
		const char *pointsChar = pointsToString.c_str();
		const char *strengthChar = strengthToString.c_str();
		const char *dexterityChar = dexterityToString.c_str();
		const char *intelligenceChar = intelligenceToString.c_str();
		mvwprintw(characterCreation, 5, 38, pointsChar);
		mvwprintw(characterCreation, 7, 2, "STRENGTH: ");
		mvwprintw(characterCreation, 8, 2, "INTELLIGENCE: ");
		mvwprintw(characterCreation, 9, 2, "DEXTERITY: ");

		printChar(characterCreation, strength, strengthToString, strengthChar, 7, 18);
		printChar(characterCreation, intelligence, intelligenceToString, intelligenceChar, 8, 18);
		printChar(characterCreation, dexterity, dexterityToString, dexterityChar, 9, 18);

		curs_set(1);
		char nameInput[20];
		wmove(characterCreation, 3, 2);
		wgetstr(characterCreation, nameInput);
		player1.name = (std::string)nameInput;
		wborder(characterCreation, '|', '|', '-', '-', '/', '\\', '\\', '/');
		wrefresh(characterCreation);

		curs_set(0);
		noecho();

		std::string menuOptions[3] = { std::to_string(strength), std::to_string(strength), std::to_string(strength) };
		currentChoice = (int)Options::FIRST_OPTION;
		input;
		while (1) {
			for (int i = 0; i < 3; i++) {
				if (currentChoice == i) {
					wattron(characterCreation, A_REVERSE);
				}
				mvwprintw(characterCreation, i + 7, 18, menuOptions[i].c_str());
				wattroff(characterCreation, A_REVERSE);
			}
			input = wgetch(characterCreation);

			switch (input) {
			case KEY_UP:
				currentChoice--;
				if (currentChoice == -1) {
					currentChoice = (int)Options::FIRST_OPTION;
				}
				break;
			case KEY_DOWN:
				currentChoice++;
				if (currentChoice == 3) {
					currentChoice = (int)Options::THIRD_OPTION;
				}
				break;
			default:
				break;
			}
			if (input == 10) {
				break;
			}
		}
	}
	endwin();
    return 0;
}