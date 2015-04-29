#ifndef GAME1_H
#define GAME1_H
#include <iostream>
#include <allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include <string>
#include<cstring>
class GamePlay {
private:

public:
    void display(ALLEGRO_BITMAP*,string, int , int);
    void destroy(ALLEGRO_BITMAP*);
    };
void GamePlay::display(ALLEGRO_BITMAP *img, string name ,int x , int y){
img = al_load_bitmap(name.c_str());
al_draw_bitmap(img,x,y,NULL);
}
void GamePlay::destroy(ALLEGRO_BITMAP* allPtr){
  al_destroy_bitmap(allPtr);
}
#endif

