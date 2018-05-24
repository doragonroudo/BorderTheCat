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

            findBestPath(circles);

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
    int currentCatPos = findCurrentCatPos(circles);

    vector<int> cBefore;
    vector<int> cVisited;
    vector<int> cMinPQ;
    vector<int> cCost;


    int destination[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, //top
                            9, 18, 27, 39, 45, 54, 63, 72, //left
                            73, 74, 75, 76, 77, 78, 79, 80, //bottom
                            17, 26, 35, 44, 53, 62, 71 //right
                          };

    int walkable_path = currentCatPos;
    int currentPos = currentCatPos;
    int dist = 0;

    /* 1st Circle */
    cBefore.push_back(currentCatPos);
    cVisited.push_back(currentCatPos);
    cMinPQ.push_back(currentCatPos);
    cCost.push_back(0);

    cout << "cBefore : " <<cBefore.back() << endl;
    cout << "cVisited : " <<cVisited.back() << endl;
    cout << "cCost : " <<cCost.back() << endl;
    cout << "cMinPQ : " <<cMinPQ.back() << endl;

    for(int j=0; j<1; j++)
    {
        do
        {
            cVisited.back() = cBefore.back();
            walkable_path = FindPath(circles, cVisited, cMinPQ.back());
            if (walkable_path != 99)
            {
                cout << "hop to : " << walkable_path << endl;
                circles[walkable_path].set_type(3);
                cMinPQ.push_back(walkable_path);
                cBefore.push_back(currentPos);
                dist++;
            }
            else
            {
                cVisited.push_back(cMinPQ.back());
                cMinPQ.pop_back();
                cout << "walkable_path is " << walkable_path << endl;
//                cVisited.pop_back();
            }
        }
        while(cVisited.size() == 80);

        for(int i = 0; i < dist; i++)
        {
            cCost.push_back(j+1);
        }
    }


    for(size_t i = 0; i < cVisited.size() ; i++)
    {
        cout << "Visited : " <<cVisited[i] << endl;
    }

    for(size_t i = 0; i < cBefore.size() ; i++)
    {
        cout << "Before : " <<cBefore[i] << endl;
    }

    for(size_t i = 0; i < cCost.size() ; i++)
    {
        cout << "Cost : " <<cCost[i] << endl;
    }

}

int findCurrentCatPos(vector<myCircle> &circles)
{
    for(size_t i = 0; i < circles.size() ; i++)
    {
        if(circles[i].circle_type == 3)
            return i;
    }
}






temp

Cost<>
PrevMode<>

visited<>
minPQ<>

cost.back = 0
prevNode.back = 1
minPQ.back = 1

temp = minPQ.back
visited.push_back(minPQ)
minPq.pop_back

loop
{
    find nebor of temp
    add all to minPQ
    cost
}










