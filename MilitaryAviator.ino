// early work in progress of a airplane fighting game shoot down the enemies before they get you, you will be shot down, but how many can you take out first?
#include "Arduboy.h"
Arduboy ab;
int gamestate  = 0;
int locx = 0; //player location x
int locy = 0; //player location y
int bulx = 0; //player bullet location x
int buly = 0; // player bullet location y
int hp = 0; //current planes health
int life = 0; // extra lives (planes)
int elocx = 100; //enemy location x
int elocy = 30; // enemy location y
int enemyex = 1; //enemy exists (0 no 1 yes)
int ehp = 0; //enemy hit points 
int ebulx = 0; // enemy bullet x coord
int ebuly = 0; //enemy bulley y coord
void setup() {
  // put your setup code here, to run once:
ab.begin();
ab.setFrameRate(1);
ab.clear();
}

void loop() {
  ab.clear();
 if (!(ab.nextFrame()))
    return;

    // move the player back one space
    if (ab.pressed(LEFT_BUTTON) && (gamestate == 0) && (locx > 1)){
    locx -= 1;
  }

  // move player forward one space
  if (ab.pressed(RIGHT_BUTTON) && (gamestate == 0) && (locx < 100)){
    locx += 1;
  }

  // move player up one space
    if (ab.pressed(UP_BUTTON) && (gamestate == 0) && (locy > 1)){
    locy -= 1;
  }

  //move player down one space
  if (ab.pressed(DOWN_BUTTON) && (gamestate == 0) && (locy < 44)){
    locy += 1;
  }

  // print the players location
  ab.setCursor((locx), (locy)); 
      ab.print("x");
      // if enemy exists, make it be
  if (enemyex = 1) {
    
    ab.setCursor((elocx), (elocy)); 
      ab.print("@");
  }
    // enemy shoot if within 80 px or player
    if ((enemyex = 1 ) && (80 > (elocx-locx)) && (ebulx == 0)) {
    
    ab.setCursor((elocx - 5), (elocy)); 
      ab.print("-");
      ebulx = (elocx - 10);
      ebuly = (elocy);
  }
    //if a bullet is not on the screen and player presses a shoot
  if (ab.pressed(A_BUTTON) && (gamestate == 0) && (bulx == 0)){
      bulx = (locx + 10);
      buly = (locy);
    ab.setCursor((bulx), (buly)); 
      ab.print("-");
      
  }

  
ab.display();
}
