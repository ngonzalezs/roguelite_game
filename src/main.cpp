#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
int main() {
   int playerx=40,playery=25;

   Actor player (25,25,'@',TCODColor::yellow);
   //Declarar una instancia de mapa !!
   Map map (80,50);

   TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
   while ( !TCODConsole::isWindowClosed() ) {
       TCOD_key_t key;
       TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
       switch(key.vk) {
           case TCODK_UP :
           if(!map.isWall(player.x,player.y-1)){
              player.y--;
           }
           break;
           case TCODK_DOWN :
           if(!map.isWall(player.x,player.y-1)){
              player.y--;
           }/*player.y++*/; break;
           case TCODK_LEFT : player.x--; break;
           case TCODK_RIGHT : player.x++; break;
           default:break;
       }
       TCODConsole::root->clear();
       //Renderizamos el mapa:
       map.render();
       //TO-DO
       player.render();
       TCODConsole::flush();
   }
   return 0;
}
