#include <Arduboy2.h>
Arduboy2 arduboy;
Sprites sprites;
#include "Map.h"
#include "Gameloop.h"

void setup() {
  arduboy.begin();
  arduboy.initRandomSeed();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame()))
    return;
  updateGame();
}
