#include "Map.hpp"
#include "libtcod.hpp"

Map::Map(int width, int height): width(width), height(height){
  //Habra que inicializar el tiles
  tiles = new Tile[width*height];

  //Hacer todo el borde como pared

  for (int i = 0; i < width; i++)
  {
    tiles[i+0*width].canWalk = false;
  }

  for (int i = 0; i < height; i++)
  {
    tiles[0+i*width].canWalk = false;
  }

    for (int i = 0; i < width; i++)
  {
    tiles[i+(height-1)*width].canWalk = false;
  }

  for (int i = 0; i < height; i++)
  {
    tiles[(width-1)+i*width].canWalk = false;
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
