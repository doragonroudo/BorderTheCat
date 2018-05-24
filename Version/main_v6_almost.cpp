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

        /* If next circle is destination */

        int destination[32][2] = {
            {-2,-4}, {-1,-4}, {0,-4}, {1,-4}, {2,-4}, {3,-4}, {4,-4}, {5,-4}, {6,-4},
            {-2,-3}, {-3,-2}, {-3,-1}, {-4,0}, {-4,1}, {-5,2}, {-5,3}, {-6,4,},
            {-5,4}, {-4,4}, {-3,4}, {-2,4} ,{-1,4}, {0,4}, {1,4}, {2,4},
            {6,3}, {5,2}, {5,1}, {4,0}, {4,1}, {3,2}, {3,3}
        };

        for(int i=0; i<32; i++)
        {
            for(int j=0; j<6; j++)
            {
                if (n[j][0] == xx && n[j][1] == yy && xx == destination[i][0] && yy == destination[i][1])
                    return j+1;
            }
        }

        /* If almost destination */

        int almost_destination[24][2] = {
            {-1,-3},{0,-3},{1,-3},{2,-3},{3,-3},{4,-3},{5,-3},
            {-2,-2},{-2,-2},{-3,0},{-3,1},{-4,2},{-4,3},
            {3,3},{-2,3},{-1,3},{0,3},{1,3},{2,3},
            {4,-2},{4,-1},{3,0},{3,1},{2,2}
        };

        for(int i=0; i<32; i++)
        {
            for(int j=0; j<6; j++)
            {
                if (n[j][0] == xx && n[j][1] == yy && xx == almost_destination[i][0] && yy == almost_destination[i][1])
                    return j+1;
            }
        }

        /* if 2 almost destination */

        int almost2_destination[16][2] = {
            {-1,-2},{0,-2},{1,-2},{2,-2},{3,-2},{3,-1},{2,0},{2,1},{1,2},
            {0,2},{-1,2},{-2,2},{-2,2},{-2,1},{-2,0},{-1,1}
        };

        for(int i=0; i<32; i++)
        {
            for(int j=0; j<6; j++)
            {
                if (n[j][0] == xx && n[j][1] == yy && xx == almost2_destination[i][0] && yy == almost2_destination[i][1])
                    return j+1;
            }
        }

//          if 3 almost destination

        int almost3_destination[5][2] = {
            {0,-1},{1,-1},{-1,0},{-1,1},{0,1}
        };

        for(int i=0; i<32; i++)
        {
            for(int j=0; j<6; j++)
            {
                if (n[j][0] == xx && n[j][1] == yy && xx == almost3_destination[i][0] && yy == almost3_destination[i][1])
                    return j+1;
            }
        }

//         if 4 almost destination

        int almost4_destination[3][2] = {
            {2,-1},{1,0},{1.1}
        };

        for(int i=0; i<32; i++)
        {
            for(int j=0; j<6; j++)
            {
                if (n[j][0] == xx && n[j][1] == yy && xx == almost4_destination[i][0] && yy == almost4_destination[i][1])
                    return j+1;
            }
        }


        /* If Not then random */
//        cout << "random" << endl;
//        int r = rand() % 6;
//        cout << "out r = " << r << endl;
//        for(int i=0; i<6; i++)
//        {
//            if(n[r][0] == xx && n[r][1] == yy)
//            {
//                cout << "r = " << r << endl;
//                cout << xx << "," << yy << " and ";
//
//                cout << n[r][0] << "," << n[r][1] << endl;
//                return r;
//            }
//        }
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
                        cout << "clicked" << endl;
                        circles[i].set_type(1);
                        int win = catWalk(circles);
                        if(win == 1)
                        {
                            cout << "Lose" << endl;
                        }
                        if(win == 2)
                        {
                            cout << "Win" << endl;
                        }
                    }
                }

            }

            /* Find Path to walk */


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
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
        {
            cout << "Cat is now at : " << i << endl;
            for(size_t j = 0; j < circles.size() ; j++)
            {
                cout << "J and Node " << j << "," << pNode << endl;
                if(j == pNode && really == false)
                {
                    j++;
                    really = true;
                    cout << "Really? " << j << "," << pNode << endl;
                }
                if(j == 80 && really == true && really2 == false)
                    {
                        j=0;
                        really2 = true;
                    cout << "Really2? " << j << "," << pNode << endl;
                    }
                int xx = circles[j].x, yy = circles[j].y;
                if (circles[j].circle_type == 0)
                {
                    switch(circles[i].check_neighbor(xx, yy))
                    {
                    case 1:
                        cout << j << endl;
                        cout << "TOP LEFT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    case 2:
                        cout << j << endl;
                        cout << "TOP RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    case 3:
                        cout << j << endl;
                        cout << "LEFT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    case 4:
                        cout << j << endl;
                        cout << "RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    case 5:
                        cout << j << endl;
                        cout << "BTM LEFT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    case 6:
                        cout << j << endl;
                        cout << "BTM RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        pNode = i;
                        return j;
                    //default:
                        //cout << "Not Match " << xx << "," << yy << endl;
                    }
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
