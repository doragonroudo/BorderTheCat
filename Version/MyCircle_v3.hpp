/* Include SFML library */
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
/* C Library */
#include <iostream>

/* namespace */
using namespace sf;
using namespace std;

/* myCircle Class */
class myCircle : public CircleShape
{
private:
    int x, y;
    int hex_type;
public:
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
        return hex_type;
    }
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
        hex_type = t;
    }
    int find_neighbor(int xx, int yy)
    {
        int nb [2][6][2] = {{{x+1, y},{x, y-1},{x-1, y-1},
                    {x-1, y},{x-1, y+1},{x, y+1}}, //0-2-4-6
                    {{x+1, y},{x+1, y-1},{x, y-1},
                    {x-1, y},{x, y+1},{x+1, y+1}}}; // 1-3-5-7
        int even_odd = 99;
        if(y%2==0) //if even
            even_odd = 0;
        else
            even_odd = 1;
//        cout << "even_odd : " << even_odd <<endl;
//        cout << "x,y : " << x << "," << y << endl;
        for(int i=0; i<6; i++)
        {
//            cout << xx << "," << yy << " : " << nb[even_odd][i][0] << "," << nb[even_odd][i][1] << endl;
            if(xx == nb[even_odd][i][0] && yy == nb[even_odd][i][1])
            {
//                cout << "MATCHES!" << endl;
                return i;
            }
        }
        return 99;
    }
};
