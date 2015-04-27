#include <iostream>
#include <allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include <string>
#include "card.h"
#include "player.h"
#include <stdlib.h> // For random
#include <time.h>
#include "game1.h"
using namespace std;

int main() {
    al_init();
    ALLEGRO_DISPLAY *display ;

    display = al_create_display(900,500);
   Player newPlayer;
al_init_image_addon();

GamePlay* game = new GamePlay;
    ALLEGRO_BITMAP *first;
    ALLEGRO_BITMAP *second;

    game->display(first ,newPlayer.getCard1()->getImage() , 500 , 300 );
    game->display(second ,newPlayer.getCard2()->getImage() , 700 , 300 );

    al_flip_display();

    al_rest(2.0);
    al_destroy_display(display);
    game->destroy(first);
     game->destroy(second);
	return 0;
}
