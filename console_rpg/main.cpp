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
		printCharacter(1, 33);
		WINDOW * characterCreation = newwin(15, 50, 10, 32);
		refresh();
		wborder(characterCreation, '|', '|', '-', '-', '/', '\\', '\\', '/');
		wrefresh(characterCreation);
		mvwprintw(characterCreation, 2, 2, "Input your character name: ");
		curs_set(1);
		wmove(characterCreation, 3, 2);
	}
	endwin();
    return 0;
}