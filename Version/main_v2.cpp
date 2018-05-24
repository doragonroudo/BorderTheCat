#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <cstdlib>

#define num_rows 10
#define num_cols 10
#define RAD_OFFSET 1.15

using namespace std;
using namespace sf;

class myCircle : public CircleShape
{
public:

    int x, y;
    int circle_type;

    int check_neighbor(int xx, int yy)
    {
        int n[6][2] = {{x, y-1}, {x+1, y-1}, {x-1, y}, {x+1, y}, {x-1, y+1}, {x, y+1}};
        for(int i=0; i<6; i++)
        {
            if(n[i][0] == xx && n[i][1] == yy)
            {
                cout << xx << "," << yy << " and ";

                cout << n[i][0] << "," << n[i][1] << endl;
                return i+1;
            }
        }
        return 0;
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


int FindPath(vector<myCircle> &circles);
void isBorder(vector<myCircle> &circles);


int main()
{
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
    circles[21].set_type(1);
    circles[20].set_type(1);
    circles[22].set_type(1);


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

            /* Find Path to walk */

            int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                                    9, 18, 27, 39, 45, 54, 63, 72, //left
                                    73, 74, 75, 76, 77, 78, 79, 80, //bottom
                                    17, 26, 35, 44, 53, 62, 71 //right
                                    };
            int hop_path;
            for(int i=0; i<2; i++)
            {
                int dist = 0;
                do
                {
                    hop_path = FindPath(circles);
                    dist++;
                    cout << "hop to : " << hop_path << endl;
                } while(hop_path != destination[i]);
                circles[hop_path].set_type(0);
                circles[40].set_type(3);
                cout << "to : " << destination[i] << " distance : " << dist << endl;
            }


            isBorder(circles);

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

int FindPath(vector<myCircle> &circles)
{
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
        {
            cout << "Cat is now at : " << i << endl;
            for(size_t j = 0; j < circles.size() ; j++)
            {
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
                        return j;
                    case 2:
                        cout << j << endl;
                        cout << "TOP RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        return j;
                    case 3:
                        cout << j << endl;
                        cout << "LEFT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        return j;
                    case 4:
                        cout << j << endl;
                        cout << "RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        return j;
                    case 5:
                        cout << j << endl;
                        cout << "BTM LEFT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
                        return j;
                    case 6:
                        cout << j << endl;
                        cout << "BTM RIGHT" << endl;
                        circles[i].set_type(0);
                        circles[j].set_type(3);
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

void isBorder(vector<myCircle> &circles)
{
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
        {
            if(i == 0) {
                cout << "Win";
            }
        }
    }
}
