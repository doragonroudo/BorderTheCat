#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

class myCircle : public CircleShape
{
private:
    int x, y;
    int circle_type;
public:
    /* Get Variable */
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    int get_type()
    {
        return circle_type;
    }

     /* Set Variable */
    void set_x(int xx)
    {
        x = xx;
    }
    void set_y(int yy)
    {
        y = yy;
    }
    void set_type(int t)
    {
        circle_type = t;
    }

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
};
