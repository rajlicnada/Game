#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "sprite.h"
#include "player.h"

#include <math.h>
#include <time.h>
using namespace std;

class Point:public Sprite{
private:
    static int poeni;
    bool pojeo;
public:
    Point(SpriteSheet *sheet,int w=32,int h=32);
    void draw(SDL_Renderer * renderer);
    void move();
    void move(int dx,int dy);
    int pokupio(Player *plajer);
    int random_od_0_do_n(int n);
    void razmesti(Point *p1);
    //int pokupio_protivnik(Enemie *enemie);

};


#endif // POINT_H_INCLUDED
