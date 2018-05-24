/********************************************/
/* Project : BorderTheCat -new-             */
/* Version : 17.1                           */
/********************************************/

/* Include SFML library */
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>

/* Include CPP library */
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <windows.h>

#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <exception>

/* Include Headers */
#include "Menu.hpp" //page_menu 1=home, 2=level
#include "Player.hpp"
#include "TextBTC.hpp"
#include "ButtonBTC.hpp"
#include "MyCircle.hpp"

/* Define */
#define num_rows 10
#define num_cols 10
#define RAD_OFFSET 1.33

/* PQ */
template<typename T, typename priority_t>
struct PriorityQueue
{
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
        std::greater<PQElement>> elements;

    inline bool empty() const
    {
        return elements.empty();
    }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

/* Namespace */
using namespace std;
using namespace sf;

/* Prototype */
void gotoHome();
void gotoLevel();
void gotoPlay(int levelSelect);
void gotoGuide();
void gotoStat(int );
void gotoWin(Player);
bool isBtnClicked(FloatRect sprite, Vector2f mp);
int gameLoop(int);
int findPath(vector<myCircle>&, int);
int dijkstra(vector<myCircle>&, int, int, map<int, int>&, map<int, int>&);
set<int> isNeighbor(vector<myCircle>&, int);

/* Global Variable */
int pages;

RenderWindow window(VideoMode(800, 600), "Border the Cat", Style::Close);

int main()
{
    /* Set Game Icon */
    Image icon;
    icon.loadFromFile("pics/CATICON.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    pages = 0;
    while (window.isOpen())
    {
        switch (pages)
        {
        case 0:
            gotoHome();
            break;
        case 1:
            gotoLevel();
            break;
        case 11:
            gotoPlay(1);
            break;
        case 12:
            gotoPlay(2);
            break;
        case 2:
            gotoGuide();
            break;
        case 31:
            gotoStat(1);
            break;
        case 32:
            gotoStat(2);
            break;
        default:
            cout << "ERROR 1" << endl;
        }
    }
    gotoHome();

    system("PAUSE");
    return 0;
}

void gotoHome()
{
    std::cout << "i'm Home\n";

    //mouse position
    Vector2f mp, posM;
    mp.x = Mouse::getPosition(window).x;
    mp.y = Mouse::getPosition(window).y;

    //btn
    ButtonBTC btn1("pics/iconcat.png", 160, 160);
    ButtonBTC btn2("pics/iconcat.png", 160, 290);
    ButtonBTC btn3("pics/iconcat.png", 160, 420);

    //create text object
    TextBTC textHeader("photoshoot", Color::Black, 52, "[Border the Cat]", 165, 80);

    Menu menu(3,1);

    //loop
    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                if(isBtnClicked(btn1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    pages = 1;
                    goto endloop;
                }
                if(isBtnClicked(btn2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    pages = 2;
                    goto endloop;
                }
                if(isBtnClicked(btn3.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    pages = 31;
                    goto endloop;
                }
            }

            if(event.type == sf::Event::MouseMoved)
            {
                posM.x = (float)event.mouseMove.x;
                posM.y = (float)event.mouseMove.y;
                if(btn1.isMouseHover(posM)) menu.setHover(1);
                else if(btn2.isMouseHover(posM)) menu.setHover(2);
                else if(btn3.isMouseHover(posM)) menu.setHover(3);
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        pages = 1;
                        goto endloop;
                        break;
                    case 1:
                        pages = 2;
                        goto endloop;
                        break;
                    case 2:
                        pages = 31;
                        goto endloop;
                        break;
                    }
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.drawText(window);
        btn1.drawButton(window);
        btn2.drawButton(window);
        btn3.drawButton(window);
        menu.draw(window);
        window.display();
    }

endloop:
    ;
}

void gotoLevel()
{
    std::cout << "i'm level\n";

    //mouse position
    sf::Vector2f mp, posM;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    ButtonBTC btn1("pics/iconcat.png", 160, 160);
    ButtonBTC btn2("pics/iconcat.png", 160, 290);
    ButtonBTC btnb("pics/button.png", 662, 450);

    //create text object
    TextBTC textHeader("photoshoot", Color::Black, 52, "Level", 370, 80);

    Menu menu(2,2);

    //loop
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                if(isBtnClicked(btn1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 11;
                    goto endloop;
                    //gotoWin(player);
                }
                if(isBtnClicked(btn2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 12;
                    goto endloop;
                }
                if(isBtnClicked(btnb.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 0;
                    goto endloop;
                }
            }

            if(event.type == sf::Event::MouseMoved)
            {
                posM.x = (float)event.mouseMove.x;
                posM.y = (float)event.mouseMove.y;
                if(btn1.isMouseHover(posM)) menu.setHover(1);
                else if(btn2.isMouseHover(posM)) menu.setHover(2);
                else if(btnb.isMouseHover(posM)) menu.setHover(3);
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Left:
                    menu.MoveLeft();
                    break;

                case sf::Keyboard::Right:
                    menu.MoveRight();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        pages = 11;
                        goto endloop;
                        break;
                    case 1:
                        pages = 12;
                        goto endloop;
                        break;
                    case 2:
                        pages = 0;
                        goto endloop;
                        break;
                    }
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.drawText(window);
        btn1.drawButton(window);
        btn2.drawButton(window);
        btnb.drawButton(window);
        menu.draw(window);
        window.display();
    }
endloop:
    ;
}

void gotoPlay(int levelSelect)
{
    int gameWin=0;
    do
    {
        gameWin = 0;
        gameWin = gameLoop(levelSelect);
        if(gameWin == 0)
        {
            cout << "===================GAME LOSE==================" << endl;
        }
        if(gameWin == 1)
        {
            cout << "===================GAME WIN==================" << endl;
        }
    }
    while (gameWin != 1);
}

void gotoGuide()
{
    std::cout << "i'm guide\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    ButtonBTC btnb("pics/button.png", 662, 450);

    //view
    sf::Texture viewt;
    sf::Sprite views;
    if (!viewt.loadFromFile("pics/borderguide.png"))
    {
        std::cout << "viewt fail\n";
    }
    views.setTexture(viewt);
    viewt.setSmooth(true);

    //create text object
    TextBTC textHeader("photoshoot", Color::Black, 52, "Guide", 330, 80);
    TextBTC textButton("rickles", Color::White, 32, "back", 680, 520);
    TextBTC textDetail("sweet", Color::White, 28, "Let's border the naughty cat!\nOnce you clicked, once cat moved.\nDon't let cat out of hexagon board!",100, 200);

    //loop
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                if(isBtnClicked(btnb.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 0;
                    goto endloop;
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    pages = 0;
                    goto endloop;
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.drawText(window);
        views.setPosition(60, 160);
        window.draw(views);
        textDetail.drawText(window);
        btnb.drawButton(window);
        textButton.drawText(window);
        window.display();
    }
endloop:
    ;
}

void gotoStat(int page)
{
    std::cout << "i'm stats\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    ButtonBTC btnb("pics/button.png", 662, 450);
    ButtonBTC btnnext("pics/nextpastel.png");
    ButtonBTC btnback("pics/backpastel.png");

    //view
    sf::Texture viewt;
    sf::Sprite views;
    if (!viewt.loadFromFile("pics/borderguide.png"))
    {
        std::cout << "viewt fail\n";
    }
    views.setTexture(viewt);
    viewt.setSmooth(true);

    //create text object
    TextBTC textHeader("photoshoot", Color::Black, 52, "Stat", 330, 80);
    TextBTC textButton("rickles", Color::White, 32, "back", 680, 520);
    TextBTC textsub("photoshoot", Color::Black, 18, " ", 500, 80);

    //open file
    string ranks[9];
    string name[9];
    string point[9];
    fstream myfile;
    ranks[0] = "Rank";
    name[0] = "Name";
    point[0] = "Move";
    if (page == 1)
    {
        myfile.open ("stat1.txt", std::ios::in);
        if (myfile.is_open())
        {
            cout << "fopen " << page << '\n';
        }
    }
    else if (page == 2)
    {
        myfile.open ("stat2.txt", std::ios::in);
        if (myfile.is_open())
        {
            cout << "fopen " << page << '\n';
        }
    }

    //get data
    int i=1,countloop=0;
    while ( !myfile.eof() && i<9 )
    {
        myfile >> point[i] >> name[i];
        ranks[i] = patch::to_string(i)+".";
        i++;
        countloop++;
    }
    cout<<i<<' '<<countloop<<endl;
    for(i=0; i<countloop+1; i++)
    {
        cout << ranks[i] << point[i] << name[i] << " " << countloop <<'\n';
    }
    myfile.close();

    //set text object from file
    TextBTC txtrank[8],txtname[8],txtpoint[8];
    for(i=0; i<countloop; i++)
    {
        txtrank[i].setProperty("sweet", Color::White, 28, ranks[i]);
        txtname[i].setProperty("sweet", Color::White, 28, name[i]);
        txtpoint[i].setProperty("sweet", Color::White, 28, point[i]);
    }

    //loop
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                if(isBtnClicked(btnb.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    cout << "button worked\n";
                    pages = 0;
                    goto endloop;
                }
                if(isBtnClicked(btnnext.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    cout << "button worked\n";
                    pages = 32;
                    goto endloop;
                }
                if(isBtnClicked(btnback.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 31;
                    goto endloop;
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case Keyboard::Return:
                    pages = 0;
                    goto endloop;
                    break;
                case Keyboard::Right:
                    pages = 32;
                    goto endloop;
                    break;
                case Keyboard::Left:
                    pages = 31;
                    goto endloop;
                    break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.drawText(window);
        views.setPosition(60, 160);
        window.draw(views);
        for (i=0; i<countloop; i++)
        {
            txtrank[i].setPosition(100,200+(40*i));
            txtrank[i].drawText(window);
            txtname[i].setPosition(200,200+(40*i));
            txtname[i].drawText(window);
            txtpoint[i].setPosition(640,200+(40*i));
            txtpoint[i].drawText(window);
        }
        if(page == 1)
        {
            textsub.setString("(easy)");
            btnnext.setPosition(675, 70);
            btnnext.drawButton(window);
        }
        else if(page == 2)
        {
            textsub.setString("(hard)");
            btnback.setPosition(75, 70);
            btnback.drawButton(window);
        }
        textsub.drawText(window);
        btnb.drawButton(window);
        textButton.drawText(window);
        window.display();
    }
endloop:
    ;
}

void gotoWin(Player p, int level)
{
    std::cout << "i'm win\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    ButtonBTC btnb("pics/button.png", 662, 450);

    //view
    sf::Texture viewt;
    sf::Sprite views;
    if (!viewt.loadFromFile("pics/borderguide.png"))
    {
        std::cout << "viewt fail\n";
    }
    views.setTexture(viewt);
    viewt.setSmooth(true);

    //create text object
    TextBTC textHeader("photoshoot", Color::Black, 52, "!!! You Win !!!", 180, 80);
    TextBTC textButton("rickles", Color::White, 32, "OK", 690, 520);
    TextBTC textDetail("sweet", Color::White, 28, "player name :", 100, 200);
    TextBTC txtinput("sweet", Color::White, 28);

    string str,strtemp;

    //loop
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                if(isBtnClicked(btnb.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    p.setName(str);
                    cout << "button worked\n";
                    cout<< "!!!RESULT!!! " << p.getMoveCount() << ' ' << p.getName() << endl;
                    p.saveToFile(level);
                    pages = 0;
                    goto endloop;
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    p.setName(str);
                    cout<< "!!!RESULT!!! " << p.getMoveCount() << ' ' << p.getName() << endl;
                    p.saveToFile(level);
                    pages = 0;
                    goto endloop;
                    break;
                }
            }

            if(event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)))
                {
                    str += static_cast<char>(event.text.unicode);
                    cout << str << endl;
                    txtinput.setString(str);
                }
                if (event.text.unicode < 128 && (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)))
                {
                    if(str.size()>=1)
                    {
                        str.pop_back();
                        txtinput.setString(str);
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.drawText(window);
        views.setPosition(60, 160);
        window.draw(views);
        textDetail.drawText(window);
        txtinput.setPosition(250,200);
        txtinput.drawText(window);
        btnb.drawButton(window);
        textButton.drawText(window);
        window.display();
    }
endloop:
    ;
}

bool isBtnClicked(FloatRect sprite, Vector2f mp)
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}

/* Game Function */
int gameLoop(int levelSelect)
{
    /* Variable */
    int isWin = 2;
    srand(time(NULL)); //set random seed

    /* Shape Properties*/

    /* Hexagon */
    myCircle hexagon;
    hexagon.setPointCount(6);
    hexagon.setRadius(25.f);
    hexagon.setFillColor(Color(244, 195, 95));
    hexagon.setOutlineThickness(5);
    hexagon.setOutlineColor(Color(255, 221, 153));
    hexagon.setPosition(20.f, 20.f);

    /* Hex */
    vector<myCircle> hex;

    /* Cat Sprite */
    Texture catTex;
    Sprite cat;
    if(!catTex.loadFromFile("pics/cat.png"))
    {
        cout << "cant load cat" << endl;
        return 99;
    }
    cat.setTexture(catTex);

    /* Cone Sprite*/
    Texture coneTex;
    Sprite cone;
    if(!coneTex.loadFromFile("pics/cone.png"))
    {
        cout << "cant load cone" << endl;
        return 99;
    }
    cone.setTexture(coneTex);
    vector<Sprite> cones;

    /* Set All Circles 'Actual Position' on screen*/
    for(size_t i=0; i<1; i++)
    {
        /* get x, y position of first hexagon */
        float x = hexagon.getPosition().x;
        float y = hexagon.getPosition().y;
        float z = 0.f; // is OFF-SET handler 'not a coordinate'

        for (int k=0; k<11; k++) // draw 9 from left to right
        {
            if(k!=0) // if NOT first row
            {
                y = hexagon.getPosition().y+hexagon.getRadius()*2-RAD_OFFSET;
                if (k%2!=0) // if is odd rows
                    z = hexagon.getRadius(); // set off-set
                else
                    z = 0.f; // set off-set to 0
                hexagon.setPosition(z+x, y); // set position

            }
            /* put those hexagon into vector hexagons */
            hex.push_back(myCircle(hexagon));
            for(int j=0; j<10; j++)
            {
                hexagon.setPosition(hexagon.getPosition().x+hexagon.getRadius()*2, y);
                hex.push_back(myCircle(hexagon));
            }
        }
    }

    /* Set ALl Hex X, Y Coordinates */
    {
        int i=0;
        for(int r=0; r<11; r++)
        {
            for(int q=0; q<11; q++, i++)
            {
                hex[i].set_x(q);
                hex[i].set_y(r);
                hex[i].set_type(0);
//                cout << hex[i].get_x() << "," << hex[i].get_y() << endl;
            }
        }
    }

    /* Set Start Hex Type */
    hex[60].set_type(3);

    /* Set Destination Hex Type */
    int goal[40] = {0,1,2,3,4,5,6,7,8,9,10,11,21,22,32,33,43,44,54,55,65,66,76,77,87,88,98,99,109,110,111,112,113,114,115,116,117,118,119,120};
    for(int i=0; i<40; i++)
    {
        hex[goal[i]].set_type(2);
        hex[goal[i]].setOutlineColor(Color::White);
        hex[goal[i]].setFillColor(Color::White);
        hex[goal[i]].setOutlineThickness(0);
    }

    /* Set Obstacle */
    int r, temp=40;
    if(levelSelect == 1)
    {
        for(int i=0; i<4; i++)
        {
            do
            {
                r = rand() % 120;
                for(int j=0; j<40; j++)
                {
                    if (r==goal[j])
                        temp = r;
                }
//            cout << "debug : random type 1 >> r,temp = "<< r << "," << temp << endl;
            }
            while (r == 60 || temp == r);
            temp = r;
            hex[r].set_type(1);
        }
    }

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    ButtonBTC btnb("pics/button.png", 662, 450);

    //create text object
    TextBTC textButton("rickles", Color::White, 32, "back", 680, 520);
    TextBTC textDetail("sweet", Color::Black, 20, "if you press back, your score won't be kept.", 335, 545);

    // create player object
    Player player;
    player.setMoveCount(0);

    /* Game Loop */
    bool isClick = false;
    while (window.isOpen()) //return a boolean
    {
        Event event;
        while(window.pollEvent(event)) //pollEvent is when we press a button ETC
        {
            if (event.type == Event::Closed) // Exit button right-top X
                window.close();
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) //if mouse click
            {
                for(int i=0; i<hex.size(); i++)
                {
                    if(hex[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && hex[i].get_type()==0)
                    {
                        hex[i].set_type(1);
                        isClick = true; // to prevent repeated input, maybe?
                        break;
                    }
                }
                if(isBtnClicked(btnb.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    pages = 0;
                    goto endloop;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
                    pages = 0;
                    goto endloop;
                    break;
                }
            }
            /* Debug Propose */
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right) //if mouse click
            {
                for(int i=0; i<hex.size(); i++)
                {
                    if(hex[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && hex[i].get_type()==0)
                    {
                        hex[i].set_type(1);
                        break;
                    }
                }
            }
        }

        /* Update */
        if (isClick)
        {
            isClick = false;
            for(int i=0; i<hex.size(); i++)
            {
                if(hex[i].get_type()==3)
                {
                    isWin = findPath(hex, i);
                    player.setMoveCount(player.getMoveCount()+1);
                    break;
                }
            }
            switch(isWin)
            {
            case 0:
                cout << "B Lose" << endl;
                break;
            case 1:
                cout << "B Win" << endl;
                break;
            case 2:
                cout << "B Go on" << endl;
                break;
            }
        }

        /* Draw */
        window.clear(Color::White); //Clear Screen Before Actually Draw

        /* Set Color By Type */
        for(int i=0; i<hex.size(); i++)
        {
            if(hex[i].get_type() == 1)
            {
                cones.push_back(Sprite(cone));
                cones.back().setPosition(Vector2f(hex[i].getPosition().x-3, hex[i].getPosition().y-10));
            }
//            else if(hex[i].get_type() == 2)
//            {
//                hex[i].setOutlineColor(Color::White);
//                hex[i].setFillColor(Color::White);
//                hex[i].setOutlineThickness(0);
//            }
            else if(hex[i].get_type() == 3)
            {
                cat.setPosition(Vector2f(hex[i].getPosition().x, hex[i].getPosition().y-10));
            }

        }
        for(int i=0; i<hex.size(); i++)
        {
            window.draw(hex[i]);
        }

        window.draw(cat);
        for (size_t i=0; i<cones.size(); i++)
            window.draw(cones[i]);
        btnb.drawButton(window);
        textButton.drawText(window);
        textDetail.drawText(window);
        window.display(); // display on screen

        /* if win or lose */
//        cout << "isWin" << isWin << endl;
        if(isWin == 0)
        {
            Sleep(1000);
            cout << "Lose" << endl;
            cout << player.getMoveCount() << "last" << endl;
            return 0;
        }
        else if(isWin == 1)
        {
            Sleep(1000);
            cout << "Win" << endl;
            cout << player.getMoveCount() << "last" << endl;
            gotoWin(player, levelSelect);
            return 1;
        }
    }
endloop:
    ;
    return 1; //end game loop
}

int findPath(vector<myCircle>&hex, int start)
{
    int cost = 0, t_cost = 999, c_path = -1, c_i;
    int goal[40] = {0,1,2,3,4,5,6,7,8,9,10,11,21,22,32,33,43,44,54,55,65,66,76,77,87,88,98,99,109,110,111,112,113,114,115,116,117,118,119,120};
    for(int i=0; i<40; i++)
    {
        vector<int> path;
        map<int, int> came_from;
        map<int, int> cost_so_far;

        cost = dijkstra(hex, start, goal[i], came_from, cost_so_far);

        if (cost <= t_cost)
        {
             t_cost = cost;
             c_i = goal[i];
        }

    }

    vector<int> path;
    map<int, int> came_from;
    map<int, int> cost_so_far;

    cost = dijkstra(hex, start, c_i, came_from, cost_so_far);
    int current = c_i;
    if(cost == 999)
    {
        return 1;
    }
    else
    {
        while(current!=start)
        {
            path.push_back(current);
            current = came_from[current];
        }
        reverse(path.begin(), path.end());
        c_path = path[0];
    }
    cout << "path : " << c_path << endl;

    if(hex[c_path].get_type() == 0 || hex[c_path].get_type() == 2)
    {
        hex[c_path].set_type(3);
        hex[start].set_type(0);

        for(int i=0; i<40; i++)
        {
            if(c_path == goal[i])
            {
                return 0; // Lose
            }
        }
        return 2; // Game Still Go On
    }
}
int dijkstra(vector<myCircle> &hex, int start, int goal, map<int, int>& came_from, map<int, int>& cost_so_far)
{
    int current;

    PriorityQueue<int, int> frontier;

    frontier.put(start, 0);
    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        current = frontier.get();

        if(current == goal)
        {
            break;
        }
        for(int next : isNeighbor(hex, current))
        {
//            cout << "next:new_cost " << next/* << ":" << new_cost*/ << endl;
            if(hex[current].get_type()!=1)
            {
                int new_cost = cost_so_far[current] + 1;
                if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
                {
                    cost_so_far[next] = new_cost;
                    came_from[next] = current;
                    frontier.put(next, new_cost);
                }
            }
        }
    }
    if(hex[frontier.get()].get_type() == 1)
    {
        cout << "NOT WALKABLE" << endl;
        return 999;
    }

    cout << "frontier : " << frontier.get();
    cout << " cost_so_far : " << cost_so_far[frontier.get()] << endl;
    return cost_so_far[current];
}

set<int> isNeighbor(vector<myCircle> &hex, int current)
{
    set<int> NBs;
    for(size_t i=0; i<hex.size()/* && (hex[i].get_type() == 0 || hex[i].get_type() == 2)*/; i++)
    {
        int xx = hex[i].get_x();
        int yy = hex[i].get_y();
        int isNB = hex[current].find_neighbor(xx, yy);
        if(isNB == 1)
        {
//            cout << "NB : " << i << endl;
            NBs.insert(i);
        }
    }
    return NBs;
}

int isWalkable(vector<myCircle> &hex, int path)
{
    if(hex[path].get_type() == 0)
    {
        return 1;
    }
    return 0;
}
