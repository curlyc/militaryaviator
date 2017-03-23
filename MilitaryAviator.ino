// early work in progress of a airplane fighting game shoot down the enemies before they get you, you will be shot down, but how many can you take out first?
#include "Arduboy2.h"
Arduboy2 ab;
int gamestate  = 0;
int locx = 0; //player location x
int locy = 0; //player location y
int bulx = 0; //player bullet location x
int buly = 0; // player bullet location y
int hp = 5; //current planes health
int life = 0; // extra lives (planes)
int elocx = 100; //enemy location x
int elocy = 30; // enemy location y
int enemyex = 1; //enemy exists (0 no 1 yes)
int ehp = 1; //enemy hit points 
int ebulx = 0; // enemy bullet x coord
int ebuly = 0; //enemy bulley y coord
unsigned long ebulm = 0; // when bulx changed last
unsigned long pbulm = 0; // when bulx changed last
unsigned long emove = 0; // when bulx changed last
unsigned long cMillis = 0; // currant miliseconds
const long interval = 10; // time between bullet movments
void setup() {
  // put your setup code here, to run once:
ab.begin();
  // massivley lowered framerate to test one of my theories
ab.setFrameRate(30);
ab.clear();
}

void loop() {
  ab.clear();
 if (!(ab.nextFrame()))
    return;
    hp += ab.everyXFrames(20);
unsigned long cMillis = millis();  //current miliseconds
    // move the player back one space
    if (ab.pressed(LEFT_BUTTON) && (gamestate == 0) && (locx > 1)){
    locx -= 1; //edited this to make the player move faster
  }

  // move player forward one space
  if (ab.pressed(RIGHT_BUTTON) && (gamestate == 0) && (locx < 100)){
    locx += 1; //dito edit
  }

  // move player up one space
    if (ab.pressed(UP_BUTTON) && (gamestate == 0) && (locy > 1)){
    locy -= 1;
  }

  //move player down one space
  if (ab.pressed(DOWN_BUTTON) && (gamestate == 0) && (locy < 44)){
    locy += 1;
  }
 // print  hp 
  ab.setCursor((0), (55)); 
      ab.print("HP");
  // print the players hp
  ab.setCursor((20), (55)); 
      ab.print(hp);

      ab.setCursor((50), (55)); 
      ab.print("EHP");
  // print the ehp
  ab.setCursor((80), (55)); 
      ab.print(ehp);

      ab.setCursor((locx ), (locy)); 
      ab.print("X");

 

  
      // if enemy exists, make it be
  if ((enemyex = 1) && (elocy < locy) && (cMillis - emove >= interval)) {
     elocx -= 1;
     elocy += 1;
    ab.setCursor((elocx), (elocy)); 
      ab.print("@");
  }
     // if enemy is higher than player go forward and down
  if ((enemyex = 1) && (elocy > locy) && (cMillis - emove >= interval)&& (elocx <= (locx + 21))) {
     elocx -= 1;
     elocy -= 1;
    ab.setCursor((elocx), (elocy)); 
      ab.print("@");
  }  
  // if enemy is at same height as player go forward and shoot
   if ((enemyex = 1) && (elocy == locy) && (elocx >= locx + 20) && (cMillis - emove >= interval)) {
      elocx -= 1;
    ab.setCursor((elocx), (elocy)); 
      ab.print("@");
  }
   // if enemy is at same height as player and within 20 px go up to avoid
   if ((enemyex = 1) && (elocy == locy) && (elocx <= (locx + 20)) && (cMillis - emove >= interval)) {
     elocx -= 1;
     elocy -= 10;
    ab.setCursor((elocx), (elocy)); 
      ab.print("@");
  }
    // enemy shoot if within 80 px or player
    if ((enemyex = 1 ) && (80 > (elocx-locx))&& (elocy-locy) && (ebulx == 0)) {
    
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
  // if bullet falls off the screen set it back to 0 
  if (bulx > 128) {
    bulx = 0;
    buly = 0;
  }

    // if enemy falls off the screen set it back  
  if (elocx < 0) {
    elocx = 128;
    bulx = 0;
    ebulx = 0;
    elocy = (random(0, 30));
    
  }
    // move the players bullet forward 1 px untill it falls off the screen if with a delay without a delay
    while ((gamestate == 0) && (bulx <= 128) && (bulx > 0) && (cMillis - pbulm >= interval)){
      bulx += 1;
      pbulm = cMillis; //previous bullet move = current miliseconds
    ab.setCursor((bulx), (buly)); 
      ab.print("-");
      
  }

  //eeeeeee
    // if enemy bullet falls off the screen set it back to 0 
  if (ebulx < 0) {
    ebulx = 0;
    ebuly = 0;
  }
       // move the enemy bullet backward 1 px untill it falls off the screen if with a delay without a delay
    while ((gamestate == 0) && (ebulx > 0) && (cMillis - ebulm >= interval)){
      ebulx -= 1;
      ebulm = cMillis; //previous bullet move = current miliseconds
    ab.setCursor((ebulx), (ebuly)); 
      ab.print("-");
      
  }
ab.display();
}
