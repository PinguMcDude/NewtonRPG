#include "stdafx.h"
#include <curses.h>
#include <string>

void printTitle(int y, int x) {
	mvprintw(y, x, "$$\\   $$\\ $$$$$$$$\\ $$\\      $$\\ $$$$$$$$\\  $$$$$$\\  $$\\   $$\\       $$$$$$$\\  $$$$$$$\\   $$$$$$\\  ");
	mvprintw(y + 1, x, "$$$\\  $$ |$$  _____|$$ | $\\  $$ |\\__$$  __|$$  __$$\\ $$$\\  $$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\ ");
	mvprintw(y + 2, x, "$$$$\\ $$ |$$ |      $$ |$$$\\ $$ |   $$ |   $$ /  $$ |$$$$\\ $$ |      $$ |  $$ |$$ |  $$ |$$ /  \\__|");
	mvprintw(y + 3, x, "$$ $$\\$$ |$$$$$\\    $$ $$ $$\\$$ |   $$ |   $$ |  $$ |$$ $$\\$$ |      $$$$$$$  |$$$$$$$  |$$ |$$$$\\ ");
	mvprintw(y + 4, x, "$$ \\$$$$ |$$  __|   $$$$  _$$$$ |   $$ |   $$ |  $$ |$$ \\$$$$ |      $$  __$$< $$  ____/ $$ |\\_$$ |");
	mvprintw(y + 5, x, "$$ |\\$$$ |$$ |      $$$  / \\$$$ |   $$ |   $$ |  $$ |$$ |\\$$$ |      $$ |  $$ |$$ |      $$ |  $$ |");
	mvprintw(y + 6, x, "$$ | \\$$ |$$$$$$$$\\ $$  /   \\$$ |   $$ |    $$$$$$  |$$ | \\$$ |      $$ |  $$ |$$ |      \\$$$$$$  |");
	mvprintw(y + 7, x, "\\__|  \\__|\\________|\\__/     \\__|   \\__|    \\______/ \\__|  \\__|      \\__|  \\__|\\__|       \\______/");
}

void printCharacter(int y, int x) {
	mvprintw(y, x,		"   ___ _  _   _   ___    _   ___ _____ ___ ___ ");
	mvprintw(y + 1, x,	"  / __| || | /_\\ | _ \\  /_\\ / __|_   _| __| _ \\ ");
	mvprintw(y + 2, x,	" | (__| __ |/ _ \\|   / / _ \\ (__  | | | _||   /");
	mvprintw(y + 3, x,	"  \\___|_||_/_/ \\_\\_|_\\/_/_\\_\\___|_|_| |___|_|_\\	");
	mvprintw(y + 4, x,	"      / __| _ \\ __| /_\\_   _|_ _/ _ \\| \\| |  ");
	mvprintw(y + 5, x,	"     | (__|   / _| / _ \\| |  | | (_) | .` | ");
	mvprintw(y + 6, x,	"      \\___|_|_\\___/_/ \\_\\_| |___\\___/|_|\\_|  ");
}                                         

void printChar(WINDOW * window, int availablePoints, std::string stringConverter, const char * charArray, int y, int x ) {
	stringConverter = std::to_string(availablePoints);
	charArray = stringConverter.c_str();
	mvwprintw(window, y, x, charArray);
}