#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include "Menu.hpp" //page_menu 1=home, 2=level

/* Define */
#define num_rows 10
#define num_cols 10
#define RAD_OFFSET 1.33

using namespace std;
using namespace sf;

namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

class myCircle : public CircleShape
{
public:

    int x, y;
    int circle_type;

    /* Check neighbor */
    int check_neighbor(int xx, int yy)
    {
        int n[6][2] = {{x, y-1}, {x+1, y-1}, {x-1, y}, {x+1, y}, {x-1, y+1}, {x, y+1}}; // a set of relative neighbors

        /*  note : will return way 1-6, if node is not neighbor will return 99 */
        for(int i=0; i<6; i++)
        {
            if(n[i][0] == xx && n[i][1] == yy)
            {
                cout << "debug : check_neighbor >> matched nodes are " << i << endl;
                cout << xx << "," << yy << " and ";
                cout << n[i][0] << "," << n[i][1] << endl;
                return i;
            }/********************************************/
        }
        return 99;
    }
    /* Generate and set type to 0:walkable 1:non-walkable 3:cat */
    void generate(int xx, int yy)
    {
        x = xx;
        y = yy;
        set_type(0);
    }
    /* debug : showing x, y and type of node */
    void display()
    {
        cout << "debug : display >>  node : " << x << "," << y << " type :" << circle_type << endl;
    }
    /* set node type */
    void set_type(int t)
    {
        circle_type = t;
    }
};

void gotoHome();
void gotoLevel();
void gotoPlay(int levelSelect);
void gotoGuide();
void gotoStats();
bool isBtnClicked(sf::FloatRect sprite, sf::Vector2f mp);
int findPath(vector<myCircle> &circles);
int catWalk(vector<myCircle>& circles);
int gameLoop(RenderWindow &window, int levelSelect);

/* Global Variable */
int pNode=99; //for tracking previous node when find a way to walk

sf::RenderWindow window(sf::VideoMode(800, 600), "Border the Cat", Style::Close);

int main()
{
    while (window.isOpen())
    {
        gotoHome();
        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}

void gotoHome()
{
    std::cout << "i'm Home\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    sf::Texture btnt1,btnt2,btnt3;
    sf::Sprite btns1, btns2, btns3;
    if (!btnt1.loadFromFile("pics/iconcat.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns1.setTexture(btnt1);
    if (!btnt2.loadFromFile("pics/iconcat.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns2.setTexture(btnt2);
    if (!btnt3.loadFromFile("pics/iconcat.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns3.setTexture(btnt3);

    //set font
    sf::Font font_photoshoot;
    if (!font_photoshoot.loadFromFile("fonts/photoshoot.ttf"))
    {
        std::cout << "font photoshoot fail\n";
    }
    sf::Font font_rickles;
    if (!font_rickles.loadFromFile("fonts/Rickles.ttf"))
    {
        std::cout << "font rickles fail\n";
    }
    sf::Font font_sweet;
    if (!font_sweet.loadFromFile("fonts/Cutie Patootie.ttf"))
    {
        std::cout << "font sweet fail\n";
    }

    //create text object
    sf::Text textHeader;

    textHeader.setFont(font_photoshoot);
    textHeader.setString("[Border the Cat]");
    textHeader.setCharacterSize(52);
    textHeader.setFillColor(sf::Color::Black);

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
                if(isBtnClicked(btns1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    gotoLevel();
                }
                if(isBtnClicked(btns2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    gotoGuide();
                }
                if(isBtnClicked(btns3.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    gotoStats();
                }
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
						gotoLevel();
					case 1:
						gotoGuide();
					case 2:
						gotoStats();
					}

					break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.setPosition(165, 80);
        window.draw(textHeader);
        btns1.setPosition(160, 160);
        window.draw(btns1);
        btns2.setPosition(160, 290);
        window.draw(btns2);
        btns3.setPosition(160, 420);
        window.draw(btns3);
        menu.draw(window);
        window.display();
    }
}

void gotoLevel()
{
    std::cout << "i'm level\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    sf::Texture btnt1,btnt2;
    sf::Sprite btns1, btns2;
    if (!btnt1.loadFromFile("pics/iconcat.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns1.setTexture(btnt1);
    if (!btnt2.loadFromFile("pics/iconcat.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns2.setTexture(btnt2);
    //btn back
    sf::Texture btnt;
    sf::Sprite btns;
    if (!btnt.loadFromFile("pics/button.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns.setTexture(btnt);

    //setfont
    sf::Font font_photoshoot;
    if (!font_photoshoot.loadFromFile("fonts/photoshoot.ttf"))
    {
        std::cout << "font photoshoot fail\n";
    }
    sf::Font font_rickles;
    if (!font_rickles.loadFromFile("fonts/Rickles.ttf"))
    {
        std::cout << "font rickles fail\n";
    }
    sf::Font font_sweet;
    if (!font_sweet.loadFromFile("fonts/Cutie Patootie.ttf"))
    {
        std::cout << "font sweet fail\n";
    }

    //create text object
    sf::Text textHeader;

    textHeader.setFont(font_photoshoot);
    textHeader.setString("Level");
    textHeader.setCharacterSize(52);
    textHeader.setFillColor(sf::Color::Black);

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
                if(isBtnClicked(btns1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoPlay(1);
                }
                if(isBtnClicked(btns2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoPlay(2);
                }
                if(isBtnClicked(btns.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoHome();
                }
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
						gotoPlay(1);
						break;
					case 1:
						gotoPlay(2);
						break;
                    case 2:
                        gotoHome();
					}
					break;
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.setPosition(370, 80);
        window.draw(textHeader);
        btns1.setPosition(160, 160);
        window.draw(btns1);
        btns2.setPosition(160, 290);
        window.draw(btns2);
        btns.setPosition(662, 450);
        window.draw(btns);
        menu.draw(window);
        window.display();
    }
}

void gotoPlay(int levelSelect)
{
    /* Set Game Icon */
    Image icon;
    icon.loadFromFile("pics/CATICON.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int gameWin=0;
    do
    {
        gameWin = 0;
        pNode = 99;
        gameWin = gameLoop(window, levelSelect);
        if(gameWin == 0)
        {
            cout << "===================GAME LOSE==================" << endl;
        }
        if(gameWin == 1)
        {
            cout << "===================GAME WIN==================" << endl;
        }
    } while (gameWin != 99);
}

void gotoGuide()
{
    std::cout << "i'm guide\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    sf::Texture btnt;
    sf::Sprite btns;
    if (!btnt.loadFromFile("pics/button.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns.setTexture(btnt);
    btnt.setSmooth(true);

    //view
    sf::Texture viewt;
    sf::Sprite views;
    if (!viewt.loadFromFile("pics/borderguide.png"))
    {
        std::cout << "viewt fail\n";
    }
    views.setTexture(viewt);
    viewt.setSmooth(true);

    //set font
    sf::Font font_photoshoot;
    if (!font_photoshoot.loadFromFile("fonts/photoshoot.ttf"))
    {
        std::cout << "font photoshoot fail\n";
    }
    sf::Font font_rickles;
    if (!font_rickles.loadFromFile("fonts/Rickles.ttf"))
    {
        std::cout << "font rickles fail\n";
    }
    sf::Font font_sweet;
    if (!font_sweet.loadFromFile("fonts/Cutie Patootie.ttf"))
    {
        std::cout << "font sweet fail\n";
    }

    //create text object
    sf::Text textHeader,textButton,textDetail;

    textHeader.setFont(font_photoshoot);
    textHeader.setString("Guide");
    textHeader.setCharacterSize(52);
    textHeader.setFillColor(sf::Color::Black);

    textButton.setFont(font_rickles);
    textButton.setString("back");
    textButton.setCharacterSize(32);
    textButton.setFillColor(sf::Color::White);

    textDetail.setFont(font_sweet);
    textDetail.setString("Let's border the naughty cat!\nOnce you clicked, once cat moved.\nDon't let cat out of hexagon board!");
    textDetail.setCharacterSize(28);
    textDetail.setFillColor(sf::Color::White);

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
                if(isBtnClicked(btns.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoHome();
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
					gotoHome();
                }
            }
        }

        window.clear(sf::Color::White);
        textHeader.setPosition(330, 80);
        window.draw(textHeader);
        views.setPosition(60, 160);
        window.draw(views);
        textDetail.setPosition(100, 200);
        window.draw(textDetail);
        btns.setPosition(662, 450);
        window.draw(btns);
        textButton.setPosition(680, 520);
        window.draw(textButton);
        window.display();
    }
}

void gotoStats()
{
    std::cout << "i'm stats\n";

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    sf::Texture btnt;
    sf::Sprite btns;
    if (!btnt.loadFromFile("pics/button.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns.setTexture(btnt);
    btnt.setSmooth(true);

    //view
    sf::Texture viewt;
    sf::Sprite views;
    if (!viewt.loadFromFile("pics/borderguide.png"))
    {
        std::cout << "viewt fail\n";
    }
    views.setTexture(viewt);
    viewt.setSmooth(true);

    //set font
    sf::Font font_photoshoot;
    if (!font_photoshoot.loadFromFile("fonts/photoshoot.ttf"))
    {
        std::cout << "font photoshoot fail\n";
    }
    sf::Font font_rickles;
    if (!font_rickles.loadFromFile("fonts/Rickles.ttf"))
    {
        std::cout << "font rickles fail\n";
    }
    sf::Font font_sweet;
    if (!font_sweet.loadFromFile("fonts/Cutie Patootie.ttf"))
    {
        std::cout << "font sweet fail\n";
    }

    //create text object
    sf::Text textHeader,textButton;

    textHeader.setFont(font_photoshoot);
    textHeader.setString("Stats");
    textHeader.setCharacterSize(52);
    textHeader.setFillColor(sf::Color::Black);

    textButton.setFont(font_rickles);
    textButton.setString("back");
    textButton.setCharacterSize(32);
    textButton.setFillColor(sf::Color::White);

    //read file
    int i,countloop=0;
    std::string ranks[8];
    std::string name[8];
    std::string point[8];
    std::fstream myfile;
    ranks[0] = "Rank";
    name[0] = "Name";
    point[0] = "Move";
    myfile.open ("stat.txt", std::ios::in);
    if (myfile.is_open())
    {
        i=1;
        std::cout << "fopen" << '\n';
        while ( !myfile.eof() )
        {
            myfile >> point[i] >> name[i];
            ranks[i] = patch::to_string(i)+".";
            i++;
            countloop++;
        }
        for(i=0; i<countloop+1; i++)
        {
            std::cout << ranks[i] << point[i] << name[i] <<'\n';
        }
    }

    //set text object from file
    sf::Text txtrank[8],txtname[8],txtpoint[8];
    for(i=0; i<countloop; i++)
    {
        txtrank[i].setFont(font_sweet);
        txtrank[i].setString(ranks[i]);
        txtrank[i].setCharacterSize(28);
        txtrank[i].setFillColor(sf::Color::White);

        txtname[i].setFont(font_sweet);
        txtname[i].setString(name[i]);
        txtname[i].setCharacterSize(28);
        txtname[i].setFillColor(sf::Color::White);

        txtpoint[i].setFont(font_sweet);
        txtpoint[i].setString(point[i]);
        txtpoint[i].setCharacterSize(28);
        txtpoint[i].setFillColor(sf::Color::White);
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
                if(isBtnClicked(btns.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoHome();
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
					gotoHome();
                }
            }
        }

        myfile.close();
        window.clear(sf::Color::White);
        textHeader.setPosition(330, 80);
        window.draw(textHeader);
        views.setPosition(60, 160);
        window.draw(views);
        for (i=0; i<countloop+1; i++)
        {
            txtrank[i].setPosition(100,200+(40*i));
            window.draw(txtrank[i]);
            txtname[i].setPosition(200,200+(40*i));
            window.draw(txtname[i]);
            txtpoint[i].setPosition(640,200+(40*i));
            window.draw(txtpoint[i]);
        }
        btns.setPosition(662, 450);
        window.draw(btns);
        textButton.setPosition(680, 520);
        window.draw(textButton);
        window.display();
    }
}

bool isBtnClicked(sf::FloatRect sprite, sf::Vector2f mp)
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}

/* Game Function */
int gameLoop(RenderWindow &window, int levelSelect)
{
    srand(time(NULL)); //set random seed

    /* Shapes */
    myCircle circle;
    circle.setPointCount(6);
    circle.setRadius(25.f); // set radius
    circle.setFillColor(Color::Yellow); //set color : unused
    circle.setOutlineThickness(5);
    circle.setOutlineColor(Color(255, 221, 153));
    circle.setPosition(130+circle.getRadius(), 40+circle.getRadius()); // set first position
    Color floorColor(244, 195, 95);
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

    /* Vector */
    vector<myCircle> circles;

    /* Variable */
    bool isClick = false;
    int win = 0;

    /* Set All Circles 'Actual Position' on screen*/
    for(size_t i=0; i<1; i++)
    {
        /* get x, y position of first circle */
        float x = circle.getPosition().x;
        float y = circle.getPosition().y;
        float z = 0.f; // is OFF-SET handler 'not a coordinate'

        for (int k=0; k<9; k++) // draw 9 from left to right
        {
            if(k!=0) // if NOT first row
            {
                y = circle.getPosition().y+circle.getRadius()*2-RAD_OFFSET;
                if (k%2!=0) // if is odd rows
                    z = circle.getRadius(); // set off-set
                else
                    z = 0.f; // set off-set to 0
                circle.setPosition(z+x, y); // set position

            }
            /* put those circle into vector circles */
            circles.push_back(myCircle(circle));
            for(int j=0; j<8; j++)
            {
                circle.setPosition(circle.getPosition().x+circle.getRadius()*2, y);
                circles.push_back(myCircle(circle));
            }
        }
    }

    /* Set All Circles X, Y Coordinate */
    {
        /* Variable */
        int i=0;
        int gX, gY;

        /* ROW 1 | gY = -4 | gX = -2 -> +6 */
        gY = -4;
        for (gX=-2; gX<=6; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 2 | gY = -3 | gX = -2 -> +6 */
        gY = -3;
        for (gX=-2; gX<=6; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 3 | gY = -2 | gX = -3 -> +5 */
        gY = -2;
        for (gX=-3; gX<=5; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 4 | gY = -1 | gX = -3 -> +5 */
        gY = -1;
        for (gX=-3; gX<=5; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 5 | gY = 0 | gX = -4 -> +4 */
        gY = 0;
        for (gX=-4; gX<=4; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 6 | gY = 1 | gX = -4 -> +4 */
        gY = 1;
        for (gX=-4; gX<=4; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 7 | gY = 2 | gX = -5 -> +3 */
        gY = 2;
        for (gX=-5; gX<=3; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 8 | gY = 3 | gX = -5 -> +3 */
        gY = 3;
        for (gX=-5; gX<=3; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }

        /* ROW 9 | gY = 4 | gX = -6 -> +2 */
        gY = 4;
        for (gX=-6; gX<=2; gX++, i++)
        {
            circles[i].generate(gX, gY);
//            circles[i].display();
        }
    }

    /* set cat position to center node : 40 */
    circles[40].set_type(3); // set to cat type

    /* If Level = 1 */
    if(levelSelect == 1)
    {
        int r, temp=40;
        /* destination here because do not want to random on those border */
        int destination[32] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, //top
            9, 18, 27, 36, 45, 54, 63, 72, //left
            73, 74, 75, 76, 77, 78, 79, 80, //bottom
            17, 26, 35, 44, 53, 62, 71 //right
        };
        for(int i=0; i<4; i++)
        {
            do
            {
                r = rand() % 80;
                for(int j=0; j<32; j++)
                {
                    if (r==destination[j])
                        temp = r;
                }
//            cout << "debug : random type 1 >> r,temp = "<< r << "," << temp << endl;
            }
            while (r == 40 || temp == r);
            temp = r;
            circles[r].set_type(1);
        }
    }

    //mouse position
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //btn
    sf::Texture btnt;
    sf::Sprite btns;
    if (!btnt.loadFromFile("pics/button.png"))
    {
        std::cout << "btnt fail\n";
    }
    btns.setTexture(btnt);
    btnt.setSmooth(true);

    //set font
    sf::Font font_photoshoot;
    if (!font_photoshoot.loadFromFile("fonts/photoshoot.ttf"))
    {
        std::cout << "font photoshoot fail\n";
    }
    sf::Font font_rickles;
    if (!font_rickles.loadFromFile("fonts/Rickles.ttf"))
    {
        std::cout << "font rickles fail\n";
    }
    sf::Font font_sweet;
    if (!font_sweet.loadFromFile("fonts/Cutie Patootie.ttf"))
    {
        std::cout << "font sweet fail\n";
    }

    //create text object
    sf::Text textButton;

    textButton.setFont(font_rickles);
    textButton.setString("back");
    textButton.setCharacterSize(32);
    textButton.setFillColor(sf::Color::White);

    /* Game Loop */
    while (window.isOpen()) //return a boolean
    {
        Event event;
        while(window.pollEvent(event)) //pollEvent is when we press a button ETC
        {
            if (event.type == Event::Closed) // Exit button right-top X
                window.close();
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) //if mouse click
            {
                isClick = true; // to prevent repeated input, maybe?

                if(isBtnClicked(btns.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    std::cout << "button worked\n";
                    gotoHome();
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Return:
					gotoHome();
                }
            }
        }

        /* Update */
        if (isClick)
        {
            isClick = false;

            /* Mouse click on Circle */
            for(size_t i=0; i<circles.size(); i++)
            {
                if(circles[i].circle_type == 0) /* if click on walkable type */
                {
                    /* if mouse position is in circle range : pos.x < mouse.x < pos.x+radius and pos.y < mouse.y < pos.y+radius */
                    if(Mouse::getPosition(window).x > circles[i].getPosition().x && Mouse::getPosition(window).x < (circles[i].getPosition().x+(circles[i].getRadius()*2)) && Mouse::getPosition(window).y > circles[i].getPosition().y && Mouse::getPosition(window).y < (circles[i].getPosition().y+(circles[i].getRadius()*2)))
                    {
                        circles[i].set_type(1); // set to non-walkable
                        cout << "click circle :" << i << endl;
                        /* do the cat move stuff*/
                        win = catWalk(circles);
                    }
                }
            }
        }

        /* Draw */
        window.clear(Color::White); //Clear Screen Before Actually Draw

        /* Draw by type */
        for(size_t i = 0; i < circles.size() ; i++)
        {
            if(circles[i].circle_type == 3)
            {
                cat.setPosition(Vector2f(circles[i].getPosition().x, circles[i].getPosition().y-10));
                circles[i].setFillColor(floorColor);
            }
            else if (circles[i].circle_type == 0)
            {
                circles[i].setFillColor(floorColor);
            }
            else if (circles[i].circle_type == 1)
            {
                cones.push_back(Sprite(cone));
                cones.back().setPosition(Vector2f(circles[i].getPosition().x-3, circles[i].getPosition().y-10));
                circles[i].setFillColor(floorColor);
            }

            window.draw(circles[i]);
        }
        window.draw(cat);
        for (size_t i=0; i<cones.size(); i++)
            window.draw(cones[i]);
        btns.setPosition(662, 450);
        window.draw(btns);
        textButton.setPosition(680, 520);
        window.draw(textButton);
        window.display(); // display on screen

        /* if win or lose */
        if(win == 1)
        {
            Sleep(1000);
            pNode = 99; // reset pNode
            cout << "Lose" << endl;
            return 0;
        }
        if(win == 2)
        {
            Sleep(1000);
            pNode = 99; // reset pNode
            cout << "Win" << endl;
            return 1;
        }
    }

    return 99; //end game loop
}

/* Find Path Function */
int findPath(vector<myCircle> &circles)
{
    bool really = false, really2 = false;
    bool _1 = false, _2 = false, _3 = false, _4 = false, _5 = false, _6 = false, _7 = false;
    int tempPos=99;
    int tempLine=99;
    int sameNode=99;

    if (pNode == 99 && circles[40].circle_type ==3)
    {
        do
        {
            int r = rand()%6-1;
            switch(r)
            {
            case 1:
                if(circles[30].circle_type ==0)
                    tempPos = 30;
                    break;
            case 2:
                if(circles[31].circle_type ==0)
                    tempPos = 31;
                    break;
            case 3:
                if(circles[39].circle_type ==0)
                    tempPos = 39;
                    break;
            case 4:
                if(circles[48].circle_type ==0)
                    tempPos = 48;
                    break;
            case 5:
                if(circles[49].circle_type ==0)
                    tempPos = 49;
                    break;
            case 6:
                if(circles[41].circle_type ==0)
                    tempPos = 41;
                    break;
            }
            cout << "random :" << r << endl;
        } while(tempPos == 99);
        cout << "debug : findPath >> final tempPos before return :" << tempPos << endl;
        circles[40].set_type(0);
        circles[tempPos].set_type(3);
        pNode = 40;
        cout << "set pNode = i " << 40 <<endl;
        return tempPos;
    }


    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
        {
            cout << "debug : findPath >> cat is now at : " << i << endl;
            for(size_t j = 0; j < circles.size() ; j++)
            {
                int xx = circles[j].x, yy = circles[j].y;
                if (circles[j].circle_type == 0)
                {
                    if(j == pNode && really == false)
                    {
                        cout << "debug : findPath >> compare j and pNode " << j << "," << pNode << endl;
                        really = true;
                        sameNode = j;
                        xx = circles[j+1].x, yy = circles[j+1].y;
                        cout << "debug : findPath >> j == pNode, better not using this j" << endl;
                    }
                    int isNeighbor = circles[i].check_neighbor(xx, yy);
                    if (isNeighbor != 99)
                    {
                        int firstLine[6] = {0,8,17,72,71,80};
                        int secondLine[14] = {1,7,9,16,18,26,35,53,62,70,79,73,63,54};
                        int thirdLine[24] = {2,3,4,5,6,10,15,19,25,27,34,36,44,45,52,61,55,64,74,75,76,77,78};
                        int forthLine[18] = {11,12,13,14,20,24,28,33,37,43,46,51,56,60,65,66,67,68};
                        int fifthLine[12] = {21,22,23,29,32,38,42,47,50,57,58,59};
                        int sixthLine[6] = {30,31,39,41,48,49};
                        int seventhLine[1] = {40};

                        for(int k=0; k<1; k++)
                        {
                            if(j == seventhLine[k] && _7 == false)
                            {
                                if(tempLine > 7)
                                {
                                    tempPos = j;
                                    tempLine = 7;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _7 = true;
                            }
                        }

                        for(int k=0; k<6; k++)
                        {
                            if(j == sixthLine[k] && _6 == false)
                            {
                                if(tempLine > 6)
                                {
                                    tempPos = j;
                                    tempLine = 6;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _6 = true;
                            }
                        }

                        for(int k=0; k<12; k++)
                        {
                            if(j == fifthLine[k] && _5 == false)
                            {
                                if(tempLine > 5)
                                {
                                    tempPos = j;
                                    tempLine = 5;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _5 = true;
                            }
                        }
                        for(int k=0; k<18; k++)
                        {
                            if(j == forthLine[k] && _4 == false)
                            {
                                if(tempLine > 4)
                                {
                                    tempPos = j;
                                    tempLine = 4;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _4 = true;
                            }
                        }
                        for(int k=0; k<24; k++)
                        {
                            if(j == thirdLine[k] && _3 == false)
                            {
                                if(tempLine > 3)
                                {
                                    tempPos = j;
                                    tempLine = 3;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _3 = true;
                            }
                        }
                        for(int k=0; k<14; k++)
                        {
                            if(j == secondLine[k] && _2 == false)
                            {
                                if(tempLine > 2)
                                {
                                    tempPos = j;
                                    tempLine = 2;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _2 = true;
                            }
                        }
                        for(int k=0; k<6; k++)
                        {
                            if(j == firstLine[k] && _1 == false)
                            {
                                if(tempLine > 1)
                                {
                                    tempPos = j;
                                    tempLine = 1;
                                    cout << "match:priority = " << tempPos << "," << tempLine << endl;
                                }
                                _1 = true;
                            }
                        }
                    }
                }
                if (j == 80 && tempPos == 99 && really == true && really2 == false)
                {
                    tempPos = sameNode;
                    really2 = true;
                    cout << "debug : findPath >> could not find other node, so pNode is okay" << endl;
                }
                if (j == 80 && tempPos != 99)
                {
                    cout << "debug : findPath >> final tempPos before return :" << tempPos << endl;
                    circles[i].set_type(0);
                    circles[tempPos].set_type(3);
                    pNode = i;
                    cout << "set pNode = i " << i <<endl;
                    return tempPos;
                }
                else if ((j == 80 && tempPos == 99))
                {
                    return 99;
                }
            }
        }
    }
    return 99; // return if could not find any walkable node
}

/* Check if Win, Lose or Continue Function */
int catWalk(vector<myCircle> &circles)
{
    /* destination to check if we win */
    int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                            9, 18, 27, 36, 45, 54, 63, 72, //left
                            73, 74, 75, 76, 77, 78, 79, 80, //bottom
                            17, 26, 35, 44, 53, 62, 71 //right
                          };
    int hop_path;

    hop_path = findPath(circles);

    cout << "debug : catWalk >> cat hop to : " << hop_path << endl;

    if (hop_path == 99)
    {
        return 2; // win
    }

    for(int i=0; i<32; i++)
    {
        if(hop_path == destination[i])
        {
            return 1; //lose
        }
    }

    return 0; // going on
}


