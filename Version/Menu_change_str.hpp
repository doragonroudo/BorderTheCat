#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(int max_menu, int page_index); // 1 homepage
	~Menu();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int GetPressedItem() { return selectedItemIndex; }
    void setHover(int);
protected:
	int selectedItemIndex;
	int mx, pg;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS],brackets;

};

Menu::Menu(int max_menu, int page_index)
{
    int i;
    mx = max_menu;
    pg = page_index;

	font.loadFromFile("fonts/Rickles.ttf");

	for(i=0; i<3; i++)
    {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::Black);
        menu[i].setCharacterSize(32);
        if(pg == 1)
        {
            if(i == 0)
            {
                menu[0].setFillColor(sf::Color::White);
                menu[0].setString("Play");
                menu[0].setPosition(430, 200);
            }
            if(i == 1)
            {
                menu[1].setString("Guide");
                menu[1].setPosition(430, 330);
            }
            if(i == 2)
            {
                menu[2].setString("Stats");
                menu[2].setPosition(430, 460);
            }
        }
        if(pg == 2)
        {
            if(i == 0)
            {
                menu[0].setFillColor(sf::Color::White);
                menu[0].setString("easy");
                menu[0].setPosition(430, 200);
            }
            if(i == 1)
            {
                menu[1].setString("hard");
                menu[1].setPosition(430, 330);
            }
            if(i == 2)
            {
                menu[2].setFillColor(sf::Color::Black);
                menu[2].setString("back");
                menu[2].setPosition(680, 520);
            }
        }
    }

	brackets.setFont(font);
	brackets.setFillColor(sf::Color::White);
	brackets.setString("<          >");
	brackets.setPosition(415, 205);
	brackets.setCharacterSize(32);

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(menu[i]);
	}
	window.draw(brackets);
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
	    menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		if (selectedItemIndex == 0) brackets.setPosition(415, 205);
		if (selectedItemIndex == 1) brackets.setPosition(415, 335);
		if (selectedItemIndex == 2) brackets.setPosition(415, 465);
		menu[selectedItemIndex].setFillColor(sf::Color::White);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < mx)
	{
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		if (selectedItemIndex == 0) brackets.setPosition(415, 205);
		if (selectedItemIndex == 1) brackets.setPosition(415, 335);
		if (selectedItemIndex == 2) brackets.setPosition(415, 465);
        menu[selectedItemIndex].setFillColor(sf::Color::White);
	}
}

void Menu::MoveLeft()
{
	if (selectedItemIndex == 2 && mx == 2)
	{
	    menu[2].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[1].setFillColor(sf::Color::White);
		brackets.setPosition(415, 335);
	}
}

void Menu::MoveRight()
{
	if (selectedItemIndex == 1 && mx == 2)
	{
        menu[2].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[1].setFillColor(sf::Color::Black);
		brackets.setPosition(1000, 1000);
	}
}

void Menu::setHover(int index)
{
    int i;
    for(i=0; i<3; i++) menu[i].setFillColor(sf::Color::Black);
    switch (index)
    {
    case 1:
        menu[0].setFillColor(sf::Color::White);
        brackets.setPosition(415, 205);
        selectedItemIndex = 0;
        break;
    case 2:
        menu[1].setFillColor(sf::Color::White);
        brackets.setPosition(415, 335);
        selectedItemIndex = 1;
        break;
    case 3:
        menu[2].setFillColor(sf::Color::White);
        selectedItemIndex = 2;
        if (pg == 1)
            brackets.setPosition(415, 465);
        else if (pg == 2)
            brackets.setPosition(1000, 1000);
        break;
    default:
        ;
    }
}

#endif // MENU_HPP_INCLUDED
