#ifndef BUTTONBTC_HPP_INCLUDED
#define BUTTONBTC_HPP_INCLUDED

#include <iostream>

using namespace std;
using namespace sf;

class ButtonBTC : public Texture, public Sprite {
public:
    ButtonBTC() { ; }
    ButtonBTC(string , float , float );
    FloatRect getGlobalBounds();
    bool isMouseHover(Vector2f mp);
    void setPosition(float, float);
    void drawButton(RenderWindow& Window);
protected:
    Texture texture;
    Sprite sprite;
};

ButtonBTC::ButtonBTC(string imgDir, float posX=0, float posY=0) {
    texture.loadFromFile(imgDir);
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

FloatRect ButtonBTC::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

bool ButtonBTC::isMouseHover(Vector2f mp) {
    FloatRect fr;
    fr = sprite.getGlobalBounds();
    //std::cout << "in function isMouseHover " << fr.contains(mp) << " " << mp.x << ' ' << mp.y << " fr " << fr.left << ' ' << fr.top << "\n";
    if(fr.contains(mp)) { return true; }
    return false;
}

void ButtonBTC::setPosition(float posX, float posY) {
    sprite.setPosition(posX, posY);
}

void ButtonBTC::drawButton(RenderWindow& Window) {
    Window.draw(sprite);
}

#endif // BUTTONBTC_HPP_INCLUDED


