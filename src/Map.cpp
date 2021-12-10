#include "Map.hpp"
#include "libtcod.hpp"

Map::Map(int width, int height): width(width), height(height){
  //Habra que inicializar el tiles
  tiles = new Tile[width*height];

  //Hacer todo el borde como pared

  for (int x = 0; x < width; x++)
  {
    setWall(x,0);
    setWall(x,height-1);
  }

  for (int y = 0; y < height; y++)
  {
    setWall(0,y);
    setWall(width-1,y);
  }
}

Map::~Map(){
  delete [] tiles;
}

bool Map::isWall(int x, int y) const{
  //Ir a la posicion y marcar que es pared
  return  !tiles[x+y*width].canWalk;
}
void Map::render() const{
  //Tengo que ir por cada tile (en ancho y en alto)
  static const TCODColor darkGround(50,50,150);
  //Si es pared lo renderizo de este otro:
  static const TCODColor darkWall(0,0,100);
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      if(isWall(i,j)){
         TCODConsole::root->setCharBackground(i,j,darkWall);

      }else{
         TCODConsole::root->setCharBackground(i,j,darkGround);
      }
    }
  }
}
void Map::setWall(int x, int y){
  //Ir a ese tile y ponerlo como no walkable
  tiles[x+y*width].canWalk  = false;
};

void Map::dig(int x_inicial, int y_inicial, int x_final, int y_final){
   for (int i = x_inicial; i < x_final; i++)
    {
    for (int j = y_inicial; j < y_final; j++)
    {
      tiles[i+j*width].canWalk  = true;
    }
   }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2){

}


