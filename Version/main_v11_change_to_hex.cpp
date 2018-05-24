/********************************************/
/* Project : BorderTheCat                   */
/* Version : 11                             */
/********************************************/


/* Include SFML library */
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/* Include CPP library */
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>

/* Define */
#define num_rows 10
#define num_cols 10
#define RAD_OFFSET 1.33

/* namespace */
using namespace std;
using namespace sf;

/* Global Variable */
int pNode=99; //for tracking previous node when find a way to walk

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

/* Function Prototype */
int findPath(vector<myCircle> &circles);
int catWalk(vector<myCircle>& circles);
int gameLoop(RenderWindow &window);

/* Main Function */
int main()
{
    /* Windows Initial */
    RenderWindow window(VideoMode(800, 600), "Border the Cat ~Catch Me If You Can~", Style::Close); // Style Default means it is Windows Mode
    window.setFramerateLimit(60); // Set Frame rate

    /* Set Game Icon */
    Image icon;
    icon.loadFromFile("CATICON.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int gameWin=0;
    do
    {
        gameWin = 0;
        pNode = 99;
        gameWin = gameLoop(window);
        if(gameWin == 0)
        {
            cout << "===================GAME LOSE==================" << endl;
        }
        if(gameWin == 1)
        {
            cout << "===================GAME WIN==================" << endl;
        }
    } while (gameWin != 99);
    return 0;
}

/* Game Function */
int gameLoop(RenderWindow &window)
{
    srand(time(NULL)); //set random seed

    /* Shapes */
    myCircle circle;
    circle.setPointCount(6);
    circle.setRadius(25.f); // set radius
    circle.setFillColor(Color::Yellow); //set color : unused
    circle.setOutlineThickness(5);
    circle.setOutlineColor(Color(255, 206, 117));
    circle.setPosition(130+circle.getRadius(), 40+circle.getRadius()); // set first position

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

    /* Random Non-walkable Nodes */
    int r, temp=40;
    /* destination here because do not want to random on those border */
    int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                            9, 18, 27, 39, 45, 54, 63, 72, //left
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
        } while (r == 40 || temp == r);
        temp = r;
        circles[r].set_type(1);
    }




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
                circles[i].setFillColor(Color(255, 28, 39));
            else if (circles[i].circle_type == 0)
                circles[i].setFillColor(Color(255, 179, 28));
            else if (circles[i].circle_type == 1)
                circles[i].setFillColor(Color(205, 28, 255));
            window.draw(circles[i]);
        }

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

    if (pNode == 99 && circles[40].circle_type ==3)
    {
        do
        {
            int r = rand()%6-1;
            switch(r)
            {
            case 1:
                if(circles[31].circle_type ==0)
                    tempPos = 31;
            case 2:
                if(circles[32].circle_type ==0)
                    tempPos = 32;
            case 3:
                if(circles[39].circle_type ==0)
                    tempPos = 39;
            case 4:
                if(circles[48].circle_type ==0)
                    tempPos = 48;
            case 5:
                if(circles[49].circle_type ==0)
                    tempPos = 49;
            case 6:
                if(circles[41].circle_type ==0)
                    tempPos = 41;
            }
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

                    int isNeighbor = circles[i].check_neighbor(xx, yy);
                    if (isNeighbor != 99)
                    {
                        cout << "debug : findPath >> compare j and pNode " << j << "," << pNode << endl;
                        if(j == pNode && really == false)
                        {
                            really = true;
                            cout << "debug : findPath >> j == pNode, skip this j" << endl;
                        }
                        else
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
                                if(j == fifthLine[k] && _7 == false)
                                {
                                    if(tempLine > 5)
                                    {
                                        tempPos = j;
                                        tempLine = 5;
                                    }
                                    _5 = true;
                                }
                            }

                            for(int k=0; k<6; k++)
                            {
                                if(j == fifthLine[k] && _6 == false)
                                {
                                    if(tempLine > 5)
                                    {
                                        tempPos = j;
                                        tempLine = 5;
                                    }
                                    _5 = true;
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
                                    }
                                    _1 = true;
                                }
                            }
                        }
                    }

                    if ( j == 80 && tempPos == 99 && really == true && really2 == false)
                    {
                        j=0;
                        really2 = true;
                        cout << "debug : findPath >> could not find other node, so pNode is okay" << endl;
                    }

                    if(j == 80 && tempPos != 99)
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
    }
    return 99; // return if could not find any walkable node
}

/* Check if Win, Lose or Continue Function */
int catWalk(vector<myCircle> &circles)
{
    /* destination to check if we win */
    int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                            9, 18, 27, 39, 45, 54, 63, 72, //left
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
