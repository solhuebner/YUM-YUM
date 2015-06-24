#include "Arduboy.h"
#include <ArduboyExtra.h>
#include <sprites.h>
#include <simple_buttons.h>
#include "assets.h"
#include "game.h"

extern Arduboy AB;
extern SimpleButtons buttons;
extern GameState app_state;

uint8_t menu_selection = 0;

void gameMenu()
{
  while(true) {
    if (!AB.nextFrame())
      continue;
    buttons.poll();

    AB.clearDisplay();
    AB.paintScreen(intro_screen);

    // AB.setCursor(0,0);
    // AB.println("menu");

    if (buttons.up())
    {
      menu_selection-=1;
    } else if (buttons.down())
    {
      menu_selection+=1;
    }
    // limit us to options 0 - 3
    menu_selection = menu_selection % 4;

    // render menu


    // choosing a selection
    if (buttons.a())
    {
      // AB.println("A button");
      // AB.println(buttons.currentButtonState);
      // AB.println(buttons.previousButtonState);
      // AB.display();
      app_state = NEW_GAME;
      return;
    }
    // AB.display();


    // case to choose item
    // case CREDITS:
    //  credits();
    //  break;

    // AB.display();
  }

}
