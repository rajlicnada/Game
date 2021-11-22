#include "Point.h"

int Point::poeni=0;

Point::Point(SpriteSheet *sheet, int width, int height):Sprite(sheet,width,height){
    pojeo=false;
    spriteRect->x=random_od_0_do_n(10)*32;
    spriteRect->y=random_od_0_do_n(20)*32;
}

void Point::draw(SDL_Renderer * renderer){
    sheet->drawFrame("walk_down",0,spriteRect,renderer);
}

void Point::move(){}
void Point::move(int dx,int dy){}

int Point::pokupio(Player *plajer){
    int x1=plajer->sprite->spriteRect->x;
    int x2=spriteRect->x-32;

    int y1=plajer->sprite->spriteRect->y;
    int y2=spriteRect->y-32;

   // cout <<"\tpoeni="<<poeni<< "\tx1=" << x1 <<"\tx1=" << y1 << "\tx2="<< x2 << "\t y2=" << y2 <<endl;

    if(abs(x1-x2)<32 && abs(y1-y2)<32){
      //  cout << "BBBBBBBBBBB"<<endl;
        int x_r=random_od_0_do_n(10)*32;
        int y_r=random_od_0_do_n(20)*32;
        int x_b= spriteRect->x;
        int y_b=spriteRect->y;
        spriteRect->x=x_r;
        spriteRect->y=y_r;

        if(x_b==spriteRect->x && y_b==spriteRect->y){
            return poeni;
        }
            poeni++;
    }
    return poeni;

}

void Point::razmesti(Point *p2){
    int i=0;        //da ne napravi besk petlju
   while(abs(spriteRect->x-p2->spriteRect->x)<64 && abs(spriteRect->y - p2->spriteRect->y)<64 ){//ako su u precniku blizem od 64 piksela da ih razmesti

        spriteRect->x=p2->spriteRect->x+random_od_0_do_n(10)*32;
        spriteRect->y=p2->spriteRect->y+random_od_0_do_n(20)*32;
        if (spriteRect->x < 0){
            spriteRect->x = 0;
        }else if (spriteRect->x > 32*9){
            spriteRect->x = 32*9;
        }
        if ( spriteRect->y < 0){
            spriteRect->y =0;
        }else if (spriteRect->y >32*19){
            spriteRect->y = 32*19;
        }
        i++;
        if(i==500){
            break;
        }
    }
}
int Point::random_od_0_do_n(int n){
    srand(time(0));
    return rand()%n;
}

