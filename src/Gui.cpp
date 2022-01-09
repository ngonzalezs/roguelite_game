#include "main.hpp"
static const int PANEL_HEIGHT=7;
static const int BAR_WIDTH=20;
static const int MSG_X=BAR_WIDTH+2;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui() {
   con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui() {
   delete con;
   log.clearAndDelete();
}

void Gui::render() {
   // Limpiamos la consola
   con->setDefaultBackground(TCODColor::black);
   con->clear();

   renderBar(1,1,BAR_WIDTH,"HP",engine.player->destructible->hp,
   engine.player->destructible->maxHp,
   TCODColor::lightRed,TCODColor::darkerRed);

   // Escribimos el mensaje en el log
	 int y=1;
	 float colorCoef=0.4f;
	 for (Message **it=log.begin(); it != log.end(); it++) {
		  Message *message=*it;
		  con->setDefaultForeground(message->col * colorCoef);
		  con->print(MSG_X,y,message->text);
		  y++;
		  if ( colorCoef < 1.0f ) {
			  colorCoef+=0.3f;
		  }
	  }

    // renderizamos la interfaz del raton
    renderMouseLook();

   // Partimos el GUI en la consola raiz
   TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,
   TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT);
}

void Gui::renderBar(int x, int y, int width, const char *name,
    float value, float maxValue, const TCODColor &barColor,
    const TCODColor &backColor) {

    // Rellenamos el fondo
    con->setDefaultBackground(backColor);
    con->rect(x,y,width,1,false,TCOD_BKGND_SET);

    int barWidth = (int)(value / maxValue * width);
    if ( barWidth > 0 ) {
      // Pintamos la barra
      con->setDefaultBackground(barColor);
      con->rect(x,y,barWidth,1,false,TCOD_BKGND_SET);
    }

     // Escribimos por encima de la barra
      con->setDefaultForeground(TCODColor::white);
      con->printEx(x+width/2,y,TCOD_BKGND_NONE,TCOD_CENTER,
      "%s : %g/%g", name, value, maxValue);
}

Gui::Message::Message(const char *text, const TCODColor &col) :
	text(strdup(text)),col(col) {
}

Gui::Message::~Message() {
	free(text);
}

void Gui::message(const TCODColor &col, const char *text, ...) {
	va_list ap;
	char buf[128];
	va_start(ap,text);
	vsprintf(buf,text,ap);
	va_end(ap);

	char *lineBegin=buf;
	char *lineEnd;
	do {
		// Hacemos un espacio para el texto
		if ( log.size() == MSG_HEIGHT ) {
			Message *toRemove=log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}

		// Checkeamos si estamos en la linea final
		lineEnd=strchr(lineBegin,'\n');
		if ( lineEnd ) {
			*lineEnd='\0';
		}

		// Añadimos un mensaje nuevo al log
		Message *msg=new Message(lineBegin, col);
		log.push(msg);

		// Vamos a la siguiente linea
		lineBegin=lineEnd+1;
	} while ( lineEnd );
}

void Gui::renderMouseLook() {
  if (! engine.map->isInFov(engine.mouse.cx, engine.mouse.cy)) {
      // Si el raton esta fuera del fov no se renderiza
      return;
	}

	char buf[128]="";
	bool first=true;
	for (Actor **it=engine.actors.begin(); it != engine.actors.end(); it++) {
		Actor *actor=*it;
		// Buscamos los actores
		if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy ) {
			if (! first) {
				strcat(buf,", ");
			} else {
				first=false;
			}
			strcat(buf,actor->name.c_str());
		}
	}
	  // Pintamos la lista de la lista debajo del cursor
	  con->setDefaultForeground(TCODColor::lighterPurple);
	  con->print(1,0,buf);
}






