#include "Enemie.h"


Enemie::Enemie(SpriteSheet *sheet, int width, int height):Sprite(sheet,width,height){
    frameSkip=5;
    poeni=0;
    speed=2;
}
void Enemie::draw(SDL_Renderer *renderer) {
    if(state&LEFT) {
        sheet->drawFrame("walk_left", currentFrame, spriteRect, renderer);
    } else if(state&RIGHT) {
        sheet->drawFrame("walk_right", currentFrame, spriteRect, renderer);
    } else if(state&UP) {
        sheet->drawFrame("walk_up", currentFrame, spriteRect, renderer);
    } else if(state&DOWN) {
        sheet->drawFrame("walk_down", currentFrame, spriteRect, renderer);
    } else if(state == STOP) {
        sheet->drawFrame("walk_down", 0, spriteRect, renderer);
    }
    frameCounter++;
    if(frameCounter%frameSkip == 0) {
        currentFrame++;
        if(currentFrame >= 3) {
            currentFrame = 0;
        }
        frameCounter = 0;
    }
}
void Enemie::move(){
    if(state != 0) {
        if(state & 1) {
            move(-1, 0);
        }
        if(state & 2) {
            move(1, 0);
        }
        if(state & 4) {
            move(0, -1);
        }
        if(state & 8) {
            move(0, 1);
        }
    }
}
void Enemie::move(int dx,int dy){
    spriteRect->x += dx*speed;
    spriteRect->y += dy*speed;
}

void Enemie::trazi_point(){
    state=Sprite::STOP;
    int x=spriteRect->x,y=spriteRect->y;
    int xp[3],yp[3];

    for(int i=0;i<3;i++){
        xp[i]=p1[i]->spriteRect->x;
        yp[i]=p1[i]->spriteRect->y;
    }
    float rast[3];
    for(int i=0;i<3;i++){
        rast[i]=sqrt((xp[i]-x)*(xp[i]-x)+(yp[i]-y)*(yp[i]-y));
    }
    int najmanji=0;
    float min=rast[0];
    for(int i=0;i<3;i++){
        if(rast[i]<min){
            min=rast[i];
            najmanji=i;
        }
    }
    if(spriteRect->x<xp[najmanji]){
     //  (spriteRect->x)++;
        state=state|Sprite::RIGHT;
    }
     if(spriteRect->x > xp[najmanji]){
     //   (spriteRect->x)--;

        state=state|Sprite::LEFT;
    }
    if(y<yp[najmanji]){
       // (spriteRect->y)++;
      state=state|Sprite::DOWN;
    }
     if(y>yp[najmanji]){
        //(spriteRect->y)--;
        state=state|Sprite::UP;
    }
}
void Enemie::pokupio_protivnik(){
    int x=spriteRect->x;
    int y=spriteRect->y;
    for(int i=0;i<3;i++){
        int xi=p1[i]->spriteRect->x;
        int yi=p1[i]->spriteRect->y;
        if(abs(x-xi)<32 && abs(y-yi)<32){
            int x_r=p1[i]->random_od_0_do_n(10)*32;
            int y_r=p1[i]->random_od_0_do_n(20)*32;
            int x_bi=p1[i]->spriteRect->x;
            int y_bi=p1[i]->spriteRect->y;
            p1[i]->spriteRect->x=x_r;
            p1[i]->spriteRect->y=y_r;
            if(x_bi==p1[i]->spriteRect->x && y_bi==p1[i]->spriteRect->y){
                continue ;
            }
            poeni++;
        }
    }

}
void Enemie::drawScore( SDL_Renderer* renderer){
    TTF_Font* font = TTF_OpenFont("font/comicbd.ttf", 24);
    SDL_Color white = {0, 255, 255};
    stringstream ss;
    ss << "Poeni Slepog misa: " << poeni<<"/50" ;
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,ss.str().c_str(), white);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = 32*10;
    text_rect.y = 5*32;
    text_rect.w =text_surface->w;
    text_rect.h =text_surface->h;
    SDL_RenderCopy(renderer, text, NULL, &text_rect);
}
