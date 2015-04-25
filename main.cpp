#include <iostream>
#include <allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include <string>
#include "card.h"
#include "player.h"
#include <stdlib.h> // For random
#include <time.h>
using namespace std;

int main() {
    al_init();
    ALLEGRO_DISPLAY *display ;
    display = al_create_display(900,500);

    al_init_image_addon();
    Player newPlayer;
    ALLEGRO_BITMAP *first=al_load_bitmap((newPlayer.getCard1()->getImage()).c_str());
    ALLEGRO_BITMAP *second=al_load_bitmap((newPlayer.getCard2()->getImage()).c_str());

    al_draw_bitmap(first,350,150,NULL);

    al_draw_bitmap(second,450,150,NULL);

    al_flip_display();

    al_rest(2.0);
    al_destroy_display(display);
    al_destroy_bitmap(first);
    al_destroy_bitmap(second);
	return 0;
}
