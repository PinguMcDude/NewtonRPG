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

	initscr();
	start_color();

	printTitle(2, 11);

	WINDOW * menuScreen = newwin(7, 70, 11, 22);
	keypad(menuScreen, true);
	refresh();
	box(menuScreen, 0, 0);
	wrefresh(menuScreen);

	std::string menuOptions[2] = { "Start Game", "   Exit   " };
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

		curs_set(1);
		char nameInput[20];

		int availablePoints = 9;
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
		mvwprintw(characterCreation, 7, 2, "STRENGTH:");
		mvwprintw(characterCreation, 8, 2, "INTELLIGENCE:");
		mvwprintw(characterCreation, 9, 2, "DEXTERITY:");
		mvwprintw(characterCreation, 12, 21, "Finish");

		printChar(characterCreation, strength, strengthToString, strengthChar, 7, 18);
		printChar(characterCreation, intelligence, intelligenceToString, intelligenceChar, 8, 18);
		printChar(characterCreation, dexterity, dexterityToString, dexterityChar, 9, 18);
		
		wmove(characterCreation, 3, 2);
		wgetstr(characterCreation, nameInput);
		player1.name = (std::string)nameInput;
		wborder(characterCreation, '|', '|', '-', '-', '/', '\\', '\\', '/');
		wrefresh(characterCreation);

		curs_set(0);
		noecho();

		std::string abilityOptions[4] = { std::to_string(strength), std::to_string(intelligence), std::to_string(dexterity), "Finish" };
		currentChoice = (int)Options::FIRST_OPTION;
		input;
		while (1) {
			for (int i = 0; i < 3; i++) {
				if (currentChoice == i) {
					wattron(characterCreation, A_REVERSE);
				}
				mvwprintw(characterCreation, i + 7, 18, abilityOptions[i].c_str());
				wattroff(characterCreation, A_REVERSE);
				if (currentChoice == 3) {
					wattron(characterCreation, A_REVERSE);
				}
				mvwprintw(characterCreation, 12, 21, abilityOptions[3].c_str());
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
				if (currentChoice == 4) {
					currentChoice = (int)Options::FOURTH_OPTION;
				}
				break;
			case KEY_RIGHT:
				if (availablePoints > 0 && currentChoice != 3) {
					availablePoints--;
					if (currentChoice == (int)Options::FIRST_OPTION) {
						strength++;
					}
					if (currentChoice == (int)Options::SECOND_OPTION) {
						intelligence++;
					}
					if (currentChoice == (int)Options::THIRD_OPTION) {
						dexterity++;
					}
				}

				pointsToString = std::to_string(availablePoints);
				pointsChar = pointsToString.c_str();
				mvwprintw(characterCreation, 5, 38, pointsChar);

				abilityOptions[0] = std::to_string(strength);
				abilityOptions[1] = std::to_string(intelligence);
				abilityOptions[2] = std::to_string(dexterity);
				break;
			case KEY_LEFT:
				if (availablePoints < 9 && currentChoice != 3 ) {
					if (currentChoice == (int)Options::FIRST_OPTION && strength > 0) {
						strength--;
						availablePoints++;
					}
					if (currentChoice == (int)Options::SECOND_OPTION && intelligence > 0) {
						intelligence--;
						availablePoints++;
					}
					if (currentChoice == (int)Options::THIRD_OPTION && dexterity > 0) {
						dexterity--;
						availablePoints++;
					}
				}

				pointsToString = std::to_string(availablePoints);
				pointsChar = pointsToString.c_str();
				mvwprintw(characterCreation, 5, 38, pointsChar);

				abilityOptions[0] = std::to_string(strength);
				abilityOptions[1] = std::to_string(intelligence);
				abilityOptions[2] = std::to_string(dexterity);
				break;
			default:
				break;
			}
			if (input == 10 && currentChoice == 3) {
				player1.strength = strength;
				player1.intelligence = intelligence;
				player1.dexterity = dexterity;
				break;
			}
		}
		clear();
		//Start actual game
		WINDOW * statusWindow = newwin(7, getmaxx(stdscr) - 20, getmaxy(stdscr) - 8, 10);
		box(statusWindow, 0, 0);
		refresh();
		wrefresh(statusWindow);
		WINDOW * mainWindow = newwin(getmaxy(stdscr) - 14, getmaxx(stdscr) - 20, 6 , 10);
		refresh();
		box(mainWindow, 0, 0);
		wrefresh(mainWindow);
		WINDOW * msgBox = newwin(6, getmaxx(stdscr) - 20, 0, 10);
		refresh();
		box(msgBox, 0, 0);
		wrefresh(statusWindow);

		WINDOW * menuItems[6] =
		{
			newwin(6, 12, 8, 13), //Inventory
			newwin(6, 12, 14, 13),
			newwin(6, 12, 8, 28),
			newwin(6, 12, 14, 28),
			newwin(6, 12, 8, 43),
			newwin(6, 12, 14, 43)
		};
		refresh();
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		init_pair(2, COLOR_WHITE, COLOR_BLACK);
		char * messages[4]{ "You've entered the game", "", "", "" };
		keypad(mainWindow, true);

		currentChoice = (int)Options::FIRST_OPTION;
		while (1) {
			box(menuItems[0], 0, 0); wrefresh(menuItems[0]);
			box(menuItems[1], 0, 0); wrefresh(menuItems[1]);
			box(menuItems[2], 0, 0); wrefresh(menuItems[2]);
			box(menuItems[3], 0, 0); wrefresh(menuItems[3]);
			box(menuItems[4], 0, 0); wrefresh(menuItems[4]);
			box(menuItems[5], 0, 0); wrefresh(menuItems[5]);
			mvwprintw(menuItems[0], 2, 1, "Moves"); wrefresh(menuItems[0]);
			mvwprintw(menuItems[1], 2, 1, "2"); wrefresh(menuItems[1]);
			mvwprintw(menuItems[2], 2, 1, "3"); wrefresh(menuItems[2]);
			mvwprintw(menuItems[3], 2, 1, "4"); wrefresh(menuItems[3]);
			mvwprintw(menuItems[4], 2, 1, "5"); wrefresh(menuItems[4]);
			mvwprintw(menuItems[5], 2, 1, "Inventory"); wrefresh(menuItems[5]);
			mvwprintw(msgBox, 1, 1, messages[0]);
			mvwprintw(msgBox, 2, 1, messages[1]);
			mvwprintw(msgBox, 3, 1, messages[2]);
			mvwprintw(msgBox, 4, 1, messages[3]);
			wrefresh(msgBox);
			for (int i = 0; i < 6; i++) {
				if (currentChoice == i) {
					wbkgd(menuItems[i], COLOR_PAIR(1));
					wrefresh(menuItems[i]);
				}
				wrefresh(menuItems[i]);
				wbkgd(menuItems[i], COLOR_PAIR(2));
			}
			input = wgetch(mainWindow);

			switch (input) {
			case KEY_UP:
				if (currentChoice == 1 || currentChoice == 3 || currentChoice == 5) {
					currentChoice--;
				}
				break;
			case KEY_DOWN:
				if (currentChoice == 0 || currentChoice == 2 || currentChoice == 4) {
					currentChoice++;
				}
				break;
			case KEY_RIGHT:
				if (currentChoice >= 0 && currentChoice < 4) {
					currentChoice += 2;
				}
				break;
			case KEY_LEFT:
				if (currentChoice <= 5 && currentChoice > 1) {
					currentChoice -= 2;
				}
				break;
			default:
				break;
			}
			if (input == 10) {
				for (int b = 0; b < 6; b++) {
					wclear(menuItems[b]);
					wrefresh(menuItems[b]);
				}
				getch();
				break;
			}
		}
	}
	endwin();
    return 0;
}