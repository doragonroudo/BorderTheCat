#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <cstdlib>
#include <time.h>

#define num_rows 10
#define num_cols 10
#define RAD_OFFSET 1.15

using namespace std;
using namespace sf;

int pNode = 40;

class myCircle : public CircleShape
{
public:

    int x, y;
    int circle_type;

    int check_neighbor(int xx, int yy)
    {
        int n[6][2] = {{x, y-1}, {x+1, y-1}, {x-1, y}, {x+1, y}, {x-1, y+1}, {x, y+1}};

//        /* If next circle is destination */
//
//        int destination[32][2] = {
//            {-2,-4}, {-1,-4}, {0,-4}, {1,-4}, {2,-4}, {3,-4}, {4,-4}, {5,-4}, {6,-4},
//            {-2,-3}, {-3,-2}, {-3,-1}, {-4,0}, {-4,1}, {-5,2}, {-5,3}, {-6,4,},
//            {-5,4}, {-4,4}, {-3,4}, {-2,4} ,{-1,4}, {0,4}, {1,4}, {2,4},
//            {6,3}, {5,2}, {5,1}, {4,0}, {4,1}, {3,2}, {3,3}
//        };
//
//        for(int i=0; i<32; i++)
//        {
//            for(int j=0; j<6; j++)
//            {
//                if (n[j][0] == xx && n[j][1] == yy && xx == destination[i][0] && yy == destination[i][1])
//                    return j+1;
//            }
//        }
//
//        /* If almost destination */
//
//        int almost_destination[24][2] = {
//            {-1,-3},{0,-3},{1,-3},{2,-3},{3,-3},{4,-3},{5,-3},
//            {-2,-2},{-2,-2},{-3,0},{-3,1},{-4,2},{-4,3},
//            {3,3},{-2,3},{-1,3},{0,3},{1,3},{2,3},
//            {4,-2},{4,-1},{3,0},{3,1},{2,2}
//        };
//
//        for(int i=0; i<32; i++)
//        {
//            for(int j=0; j<6; j++)
//            {
//                if (n[j][0] == xx && n[j][1] == yy && xx == almost_destination[i][0] && yy == almost_destination[i][1])
//                    return j+1;
//            }
//        }
//
//        /* if 2 almost destination */
//
//        int almost2_destination[16][2] = {
//            {-1,-2},{0,-2},{1,-2},{2,-2},{3,-2},{3,-1},{2,0},{2,1},{1,2},
//            {0,2},{-1,2},{-2,2},{-2,2},{-2,1},{-2,0},{-1,1}
//        };
//
//        for(int i=0; i<32; i++)
//        {
//            for(int j=0; j<6; j++)
//            {
//                if (n[j][0] == xx && n[j][1] == yy && xx == almost2_destination[i][0] && yy == almost2_destination[i][1])
//                    return j+1;
//            }
//        }
//
////          if 3 almost destination
//
//        int almost3_destination[5][2] = {
//            {0,-1},{1,-1},{-1,0},{-1,1},{0,1}
//        };
//
//        for(int i=0; i<32; i++)
//        {
//            for(int j=0; j<6; j++)
//            {
//                if (n[j][0] == xx && n[j][1] == yy && xx == almost3_destination[i][0] && yy == almost3_destination[i][1])
//                    return j+1;
//            }
//        }
//
////         if 4 almost destination
//
//        int almost4_destination[3][2] = {
//            {2,-1},{1,0},{1.1}
//        };
//
//        for(int i=0; i<32; i++)
//        {
//            for(int j=0; j<6; j++)
//            {
//                if (n[j][0] == xx && n[j][1] == yy && xx == almost4_destination[i][0] && yy == almost4_destination[i][1])
//                    return j+1;
//            }
//        }


        /* If Not then random */
        for(int i=0; i<6; i++)
        {
            if(n[i][0] == xx && n[i][1] == yy)
            {
                cout << "i = " << i << endl;
                cout << xx << "," << yy << " and ";

                cout << n[i][0] << "," << n[i][1] << endl;
                return i;
            }
        }
        return 99;
    }
    void generate(int xx, int yy)
    {
        x = xx;
        y = yy;
        set_type(0);
    }
    void display()
    {
        cout << x << "," << y << " Type : " << circle_type << endl;
    }
    void set_type(int t)
    {
        circle_type = t;
    }
};


int findPath(vector<myCircle> &circles);
int catWalk(vector<myCircle>& circles);


int main()
{
    srand(time(NULL));
    /* Windows Initial */
    RenderWindow window(VideoMode(800, 600), "SFML", Style::Default); // Style Default means it is Windows Mode **Can be change to FullScreen, ETC
    window.setFramerateLimit(60); // Set Frame rate

    /* Shapes */
    myCircle circle;
    circle.setRadius(20.f);
    circle.setFillColor(Color::Blue);
    circle.setPosition(0+circle.getRadius(), 0+circle.getRadius()); // first position

    vector<myCircle> circles;

    /* Var */
    bool isClick = false;

    /* Set All Circles Position For Drawing*/
    for(size_t i=0; i<1; i++)
    {
        float x = circle.getPosition().x;
        float y = circle.getPosition().y;
        float z = 0.f;

        for (int k=0; k<9; k++)
        {
            if(k!=0)
            {
                y = circle.getPosition().y+circle.getRadius()*2;
                if (k%2!=0)
                    z = circle.getRadius()*RAD_OFFSET;
                else
                    z = 0.f;
                circle.setPosition(z+x, y); // first position

            }
            circles.push_back(myCircle(circle));

//        circle.setPosition(x-(circle.getRadius()*RAD_OFFSET), y-circle.getRadius()*2);
//        circle.setPosition(x-(circle.getRadius()*2*RAD_OFFSET), y);

            for(int j=0; j<8; j++)
            {
                circle.setPosition(circle.getPosition().x+circle.getRadius()*2*RAD_OFFSET, y);
                circles.push_back(myCircle(circle));
            }
        }


    }

    /* Set All Circles X, Y Position */
    {
        int i=0;
        int gX, gY;

        /* ROW 1 | gY = -4 | gX = -2 -> +6 */
        gY = -4;
        for (gX=-2; gX<=6; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 2 | gY = -3 | gX = -2 -> +6 */
        gY = -3;
        for (gX=-2; gX<=6; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 3 | gY = -2 | gX = -3 -> +5 */
        gY = -2;
        for (gX=-3; gX<=5; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 4 | gY = -1 | gX = -3 -> +5 */
        gY = -1;
        for (gX=-3; gX<=5; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 5 | gY = 0 | gX = -4 -> +4 */
        gY = 0;
        for (gX=-4; gX<=4; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 6 | gY = 1 | gX = -4 -> +4 */
        gY = 1;
        for (gX=-4; gX<=4; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 7 | gY = 2 | gX = -5 -> +3 */
        gY = 2;
        for (gX=-5; gX<=3; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 8 | gY = 3 | gX = -5 -> +3 */
        gY = 3;
        for (gX=-5; gX<=3; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }

        /* ROW 9 | gY = 4 | gX = -6 -> +2 */
        gY = 4;
        for (gX=-6; gX<=2; gX++, i++)
        {
            circles[i].generate(gX, gY);
            circles[i].display();
        }
    }
    cout << "circle 40" << endl;
    circles[40].set_type(3);
    int r, temp=40;
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
            cout << r << " r:temp " << temp;
        } while (r == 40 || temp == r);
        temp = r;
        cout << endl;
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
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                isClick = true;
            }
        }
        /* Update */

        if (isClick)
        {

            isClick = false;

            /* Click to Select */
            for(size_t i=0; i<circles.size(); i++)
            {
                if(circles[i].circle_type == 0)
                {
                    if(Mouse::getPosition(window).x > circles[i].getPosition().x && Mouse::getPosition(window).x < (circles[i].getPosition().x+(circles[i].getRadius()*2)) && Mouse::getPosition(window).y > circles[i].getPosition().y && Mouse::getPosition(window).y < (circles[i].getPosition().y+(circles[i].getRadius()*2)))
                    {
                        cout << "Clicked" << endl;
                        circles[i].set_type(1);
                        int win = catWalk(circles);
                        if(win == 1)
                        {
                            cout << "Lose" << endl;
                        }
                        if(win == 2)
                        {
                            cout << "Win" << endl;
                            /* Reset */
//                            for(int k=0; k<circles.size(); k++)
//                            {
//                                circles[k].set_type(0);
//                            }
                        }
                    }
                }

            }

        }



        /* Draw */

        window.clear(Color::White); //Clear Screen Before Actually Draw

        for(size_t i = 0; i < circles.size() ; i++)
        {
            if(circles[i].circle_type == 3)
                circles[i].setFillColor(Color::Red);
            else if (circles[i].circle_type == 0)
                circles[i].setFillColor(Color::Blue);
            else if (circles[i].circle_type == 1)
                circles[i].setFillColor(Color::Green);
            window.draw(circles[i]);
        }

        window.display();
    }
    return 0;
}

int findPath(vector<myCircle> &circles)
{
    bool really = false, really2 = false;
    bool _1 = false, _2 = false, _3 = false, _4 = false, _5 = false;
    int tempPos=99;
    int tempLine=99;
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
        {
            cout << "Cat is now at : " << i << endl;
            for(size_t j = 0; j < circles.size() ; j++)
            {
//                cout << "Get in new func" << endl;
                int xx = circles[j].x, yy = circles[j].y;
                if (circles[j].circle_type == 0)
                {

                    int isNeighbor = circles[i].check_neighbor(xx, yy);
                    //                    cout << "isNeighbor " << isNeighbor << endl;
                    if (isNeighbor != 99)
                    {
                        cout << "compare j and pNode " << j << "," << pNode << endl;
                        if(j == pNode && really == false)
                        {
                            really = true;
                            cout << "really" << endl;
                        }
                        else
                        {
                            int firstLine[32] =
                            {
                                0,1,2,3,4,5,6,7,8,9,18,27,36,45,54,63,72,
                                73,74,75,76,77,78,79,80,71,62,53,44,35,26,17
                            };
                            int secondLine[24] = {10,11,12,13,14,15,16,19,28,37,46,55,64,65,66,
                                                  67,68,69,70,61,52,43,34,25
                                                 };
                            int thirdLine[16] = {20,21,22,23,24,33,42,51,60,59,58,57,56,47,38,29};
                            int forthLine[8] = {30,31,39,48,49,50,41,32};
                            int fifthLine[1] = {32};

                            for(int k=0; k<1; k++)
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
                            for(int k=0; k<8; k++)
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
                            for(int k=0; k<16; k++)
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
                            for(int k=0; k<24; k++)
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
                            for(int k=0; k<32; k++)
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
                    cout << "J before end "<< j << endl;
                    if ( j == 80 && tempPos == 99 && really == true && really2 == false)
                    {
                        j=0;
                        really2 = true;
                        cout << "really2" << endl;
                    }

                    if(j == 80 && tempPos != 99)
                    {
                        cout << "final tempPos " << tempPos << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    }
                    else if ((j == 80 && tempPos == 99))
                    {
                        return 99;
                    }



                    /*switch(circles[i].check_neighbor(xx, yy))
                    {
                    case 1:
                        cout << tempPos << endl;
                        cout << "TOP LEFT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    case 2:
                        cout << tempPos << endl;
                        cout << "TOP RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    case 3:
                        cout << tempPos << endl;
                        cout << "LEFT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    case 4:
                        cout << tempPos << endl;
                        cout << "RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    case 5:
                        cout << tempPos << endl;
                        cout << "BTM LEFT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;
                    case 6:
                        cout << tempPos << endl;
                        cout << "BTM RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[tempPos].set_type(3);
                        pNode = i;
                        return tempPos;*/
                }
            }
        }
    }
return 99;

}

int catWalk(vector<myCircle> &circles)
{
    int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                            9, 18, 27, 39, 45, 54, 63, 72, //left
                            73, 74, 75, 76, 77, 78, 79, 80, //bottom
                            17, 26, 35, 44, 53, 62, 71 //right
                          };
    int hop_path;

    hop_path = findPath(circles);
    if (hop_path == 99)
        return 2;
    cout << "hop to : " << hop_path << endl;
    for(int i=0; i<32; i++)
    {
        if(hop_path == destination[i])
        {
            return 1;
        }
    }
    return 0;
}

//void catWalk(vector<myCircle> &circles, )
