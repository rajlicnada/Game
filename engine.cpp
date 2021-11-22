#include "engine.h"

ostream& operator<<(ostream& out, const Level& l) {
    int rows = l.getLevelMatrix().size();
    int cols = 0;
    if(rows > 0) {
        cols = l.getLevelMatrix()[0].size();
    }
    out << rows << " " << cols << endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            out << l.getLevelMatrix()[i][j] << " ";
        }
        out << endl;
    }

    return out;
}

Engine::Engine(string title) {
    nivo=1;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Engine::addTileset(Tileset *tileset, const string &name) {
    tilesets[name] = tileset;
}

void Engine::addTileset(istream &inputStream, const string &name) {
    addTileset(new Tileset(inputStream, renderer), name);
}

void Engine::addTileset(const string &path, const string &name) {
    ifstream tilesetStream(path);
    addTileset(tilesetStream, name);
}

Tileset* Engine::getTileset(const string &name) {
    return tilesets[name];
}

void Engine::addDrawable(Drawable *drawable) {
    drawables.push_back(drawable);
}

void Engine::run() {
    int maxDelay = 1000/frameCap;
    int frameStart = 0;
    int frameEnd = 0;

    bool running = true;
    SDL_Event event;

    cout << (*dynamic_cast<Level*>(drawables[0])) << endl;

    ifstream spriteSheetStream1("resources/creatures/plants_sprite_sheet.txt");
    SpriteSheet *sheet1 = new SpriteSheet(spriteSheetStream1, renderer);


    Point *pt=new Point(sheet1);
    drawables.push_back(pt);
    Point *pt1=new Point(sheet1);

    Point *pt2=new Point(sheet1);

   // movables.push_back(pt);

    srand(time(0));

    pt->spriteRect->x=32*(rand()%10);
    pt->spriteRect->y=32*(rand()%20);

    ifstream spriteSheetStream("resources/creatures/sprite_sheet.txt");
    SpriteSheet *sheet = new SpriteSheet(spriteSheetStream, renderer);


    Sprite *sp = new Sprite(sheet);
    sp->setFrameSkip(4);

    Player *player = new Player(sp);

    drawables.push_back(player);
    movables.push_back(player);
    eventListeners.push_back(player);




    while(running) {
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else {
                for(size_t i = 0; i < eventListeners.size(); i++) {
                    eventListeners[i]->listen(event);
                }
            }
        }

        for(size_t i = 0; i < movables.size(); i++) {
            movables[i]->move();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Enemie *ene;
        for(size_t i = 0; i < drawables.size(); i++) {
            drawables[i]->draw(renderer);
        }
        if(nivo==1){
            if(drawScore(pt->pokupio(player),renderer,1)==1 ){
              //  cout << "AAAAAAAAAAAAAAAA"<<endl;
               nivo++;
               ene=preso_prvi_nivo(player,pt);
               drawables.push_back(pt1);
               drawables.push_back(pt2);
               ene->looking_for_point(pt,pt1,pt2);


            }

        }
        if(nivo==2){
           // cout << "CCCCCCCCCCCC"<<endl;
            ene->drawScore(renderer);
            if(drawScore(pt->pokupio(player),renderer,50)==50){
                running=false;
                cout << "\n\n\n\tCESTITAM POBEDILI STE!!!" << endl;
            }
            if(ene->poeni==50){
                running=false;
                cout << "\n\n\n\tNAZALOST IZGUBILI STE!!!POKUSAJTE PONOVO!!!" << endl;
            }
            pt->razmesti(pt1);
            pt->razmesti(pt2);
            pt1->razmesti(pt2);
            pt->pokupio(player);
            pt1->pokupio(player);
            pt2->pokupio(player);
            ene->trazi_point();
            ene->pokupio_protivnik();

         }

        SDL_RenderPresent(renderer);

        frameEnd = SDL_GetTicks();
        if(frameEnd - frameStart < maxDelay) {
            SDL_Delay(maxDelay - (frameEnd - frameStart));
        }
    }
}
Enemie* Engine::preso_prvi_nivo(Player *player,Point *pt){
    drawables.clear();
    addTileset("resources/tilesets/sand_tileset.txt","lvl2");
    ifstream level2stream("resources/levels/level2.txt");
    addDrawable(new Level(level2stream,getTileset("lvl2")));
    drawables.push_back(player);
    drawables.push_back(pt);
    player->sprite->set_speed(2);



    ifstream spriteSheetBat("resources/creatures/bat_sprite_sheet.txt");
    SpriteSheet *sheetbat = new SpriteSheet(spriteSheetBat, renderer);


    Enemie *ene=new Enemie(sheetbat);
    drawables.push_back(ene);
    movables.push_back(ene);

    ene->spriteRect->x=32;
    ene->spriteRect->y=32;


    return ene;

}
int Engine::drawScore(int rezultat, SDL_Renderer* renderer,int max){
    TTF_Font* font = TTF_OpenFont("font/comicbd.ttf", 24);
    SDL_Color white = {0, 0, 255};
    stringstream ss;
    ss << "Poeni: " << rezultat <<"/"<<max;
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,ss.str().c_str(), white);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = 32*10;
    text_rect.y = 0;
    text_rect.w =text_surface->w;
    text_rect.h =text_surface->h;
    SDL_RenderCopy(renderer, text, NULL, &text_rect);

    return rezultat;
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
