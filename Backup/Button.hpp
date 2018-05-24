#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
int mx, pg;

class Button
{
public:
	Button(int, int);
	~Button();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS],brackets;

};
