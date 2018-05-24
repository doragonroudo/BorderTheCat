#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <cstdlib>
#include <math.h>

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
//                cout << xx << "," << yy << " and ";

//                cout << n[i][0] << "," << n[i][1] << endl;
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


int FindPath(vector<myCircle> &circles, vector<int> &cVisited, int Pos);
void findBestPath(vector<myCircle>& circles);
int findCurrentCatPos(vector<myCircle> &circles);


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

            int catPos = findCurrentCatPos(circles);

            cout << "Cat Pos " << catPos << endl;

            int startX = circles[catPos].x;
            int startY = circles[catPos].y;

//            for (int i=0; i<32 ;)
            int destX = circles[42].x;
            int destY = circles[42].y;

            cout << "Start " << startX << "," << startY << endl;
            cout << "Dest " << destX << "," << destY << endl;

            if(startX == destX)
                cout << abs(destY - startY);
            else if (startY == destY)
                cout << abs(destX - startX);
            else
            {
                int dx = abs(destX = startX);
                int dy = abs(destY - startY);
                if (startY < destY)
                    cout << dx + dy - (int) ceil(dx / 2.0);
                else
                    cout << dx + dy - (int) floor(dx / 2.0);

            }

//            findBestPath(circles);

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

int FindPath(vector<myCircle> &circles, vector<int> &cVisited, int Pos)
{
    bool noMatch = true;
    int n;
    cout << "Cat is now at : " << Pos << endl;


    for(size_t j=0; j<circles.size(); j++)
    {
        for (int i=0; i < cVisited.size(); i++)
        if(j == cVisited[i])
            j++;
            int xx = circles[j].x, yy = circles[j].y;
            //cout << "j : " << j << endl;
            switch(circles[Pos].check_neighbor(xx, yy))
            {
            case 1:
                cout << j;
                cout << ":TOP LEFT" << endl;
                cout << "j : " << j << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            case 2:
                cout << j;
                cout << ":TOP RIGHT" << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            case 3:
                cout << j;
                cout << ":LEFT" << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            case 4:
                cout << j;
                cout << ":RIGHT" << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            case 5:
                cout << j;
                cout << ":BTM LEFT" << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            case 6:
                cout << j;
                cout << ":BTM RIGHT" << endl;
                n=j;
                noMatch = false;
                j=99;
                break;
            }
    }
    cout << "n is" << n << endl;
    cout << "momatch is " << noMatch << endl;

        if(!noMatch)
            return n;
        else
            return 99;

}

void findBestPath(vector<myCircle> &circles)
{
    int startNode = findCurrentCatPos(circles);

    vector<int> totalCost;
    vector<int> prevNode;

    vector<int> minPQ;
    vector<int> Visited;
/*
    int nb
    int altPath, distance;

    totalCost[startNode] = 0;
    minPQ.push_back(startNode);

    while(!minPQ)
    {
        int newSmallest = deleteMin(minPQ); //add func later
        while((nb = FindPath(circles, minPQ.back())) != 99)
        {
            minPQ.push_back(nb);
            for(int i=0; i<Visited.size(); i++)
            {
                if(Visited[i] != minPQ.back())
                {
                    int altPath = totalCost[newSmallest] +

                }
            }
        }
    }
*/
}

int findCurrentCatPos(vector<myCircle> &circles)
{
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
            return i;
    }
}



/*


temp

Cost[80]
PrevMode[80]

visited<>
minPQ<>

cost[0] = 0
prevNode[0] = 1
minPQ.back = 1

loop
{
    temp = minPQ.back
    visited.push_back(minPQ)
    minPq.pop_back

    if same as visiteds
    {

    }

    loop
    {
        find nebor of visited.back
        add all to minPQ

    }
    cost[] = all in minPQ
    prev = all prev.back
}
*/









