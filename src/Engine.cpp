#include "Engine.hpp"

Engine::Engine(){
  TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
  map = new Map(ANCHO_MAPA,ALTO_MAPA);
  player = new Actor(25,25,'@',TCODColor::yellow);

  //Añadir NPC
  Actor* npc = new Actor(40,25,'O',TCODColor::orange);


  actors.push(player);
  actors.push(npc);

  createRoom(true,2,2,40,40);
}

Engine::~Engine(){
  delete map;
  actors.clearAndDelete();
}

void Engine::update(){
       TCOD_key_t key;
       TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
       switch(key.vk) {
           case TCODK_UP :
           if(!map->isWall(player->x,player->y-1)){
              player->y--;
           }
           break;
           case TCODK_DOWN :
           if(!map->isWall(player->x,player->y+1)){
              player->y++;
           }; break;
           case TCODK_LEFT :
           if(!map->isWall(player->x-1,player->y)){
              player->x--;
           }
           break;
           case TCODK_RIGHT :
            if(!map->isWall(player->x+1,player->y)){
              player->x++;
            }
            break;
           default:break;
       }
}

void Engine::render(){
    TCODConsole::root->clear();
    //Renderizamos el mapa:
    map->render();

    //Renderizamos Actores
    for(Actor* actorAux : actors){
      actorAux->render();
    }
    //re-renderizo el jugador:
    player->render();
    TCODConsole::flush();
}
void Engine::createRoom(bool first, int x1, int y1, int x2, int y2){

    if(first){
      map->dig(x1,y1,x2,y2);
    }
}

