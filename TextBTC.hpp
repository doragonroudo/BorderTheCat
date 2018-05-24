#ifndef TEXTBTC_HPP_INCLUDED
#define TEXTBTC_HPP_INCLUDED

#include <iostream>

using namespace std;
using namespace sf;

class TextBTC : public Font, public Text {
public:
    TextBTC() { ; }
    TextBTC(string textLabel, float posX, float posY);
    TextBTC(string textFont, const Color& textColor, int textSize, string textLabel, float posX, float posY);
    void setProperty(string textFont, const Color& textColor, int textSize, string textLabel, float posX, float posY);
    void setString(const String& string);
    void setPosition(float, float);
    void drawText(RenderWindow& Window);
protected:
    void initInstances();
    Text t;
    Font font_photoshoot, font_rickles, font_sweet;
};

TextBTC::TextBTC(string textLabel, float posX, float posY) {
    initInstances();
    t.setFont(font_rickles);
    t.setFillColor(Color::Black);
    t.setCharacterSize(32);
    t.setString(textLabel);
    t.setPosition(posX, posY);
}

TextBTC::TextBTC(string textFont, const Color& textColor, int textSize, string textLabel="", float posX=0, float posY=0) {
    initInstances();
    if(textFont == "photoshoot") t.setFont(font_photoshoot);
    else if(textFont == "rickles") t.setFont(font_rickles);
    else if(textFont == "sweet") t.setFont(font_sweet);
    t.setFillColor(textColor);
    t.setCharacterSize(textSize);
    t.setString(textLabel);
    t.setPosition(posX, posY);
}

void TextBTC::setProperty(string textFont, const Color& textColor, int textSize, string textLabel, float posX=0, float posY=0) {
    initInstances();
    if(textFont == "photoshoot") t.setFont(font_photoshoot);
    else if(textFont == "rickles") t.setFont(font_rickles);
    else if(textFont == "sweet") t.setFont(font_sweet);
    t.setFillColor(textColor);
    t.setCharacterSize(textSize);
    t.setString(textLabel);
    t.setPosition(posX, posY);
}

void TextBTC::setString(const String& s) {
    t.setString(s);
}

void TextBTC::setPosition(float posX, float posY) {
    t.setPosition(posX, posY);
}

void TextBTC::drawText(RenderWindow& Window) {
    Window.draw(t);
}

void TextBTC::initInstances() {
    font_photoshoot.loadFromFile("fonts/photoshoot.ttf");
    font_rickles.loadFromFile("fonts/Rickles.ttf");
    font_sweet.loadFromFile("fonts/Cutie Patootie.ttf");
}

#endif // TEXTBTC_HPP_INCLUDED

