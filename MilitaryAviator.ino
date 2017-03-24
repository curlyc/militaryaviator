// early work in progress of a airplane fighting game shoot down the enemies before they get you, you will be shot down, but how many can you take out first?
#include "Arduboy2.h"
Arduboy2 ab;
const unsigned char player[] PROGMEM  = {
    0xff, 0xfe, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x70, 0x70, 0x20, 0x20, 
};
const unsigned char enemy[] PROGMEM  = {
0x20, 0x20, 0x70, 0x70, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfe, 0xff, 
};
int gamestate  = 0;
int locx = 0; //player location x
int locy = 0; //player location y
int locyt = (locy + 7); //
int bulx = 0; //player bullet location x
int buly = 0; // player bullet location y
int buls = 0; // bullet starting x
int hp = 5; //current planes health
int life = 10; // extra lives (planes)
int killz = 0; // player kill count
int elocx = 100; //enemy location x
int elocy = 30; // enemy location y
int elocyt = (elocy + 8);
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
ab.setFrameRate(60);
ab.clear();
}

void loop() {

 if (!(ab.nextFrame()))
    return;
    ab.clear();
unsigned long cMillis = millis();  //current miliseconds
    // gs 1
    // move the player back one space
    if (ab.pressed(LEFT_BUTTON) && (gamestate == 1) && (locx > 1)){
    locx -= 1; //edited this to make the player move faster
  }

  // move player forward one space
  if (ab.pressed(RIGHT_BUTTON) && (gamestate == 1) && (locx < 100)){
    locx += 1; //dito edit
  }

  // move player up one space
    if (ab.pressed(UP_BUTTON) && (gamestate == 1) && (locy > 1)){
    locy -= 1;
  }

  //move player down one space
  if (ab.pressed(DOWN_BUTTON) && (gamestate == 1) && (locy < 44)){
    locy += 1;
  }
if (gamestate == 0) {
 // print  TITLE 
  ab.setCursor((13), (0)); 
  ab.print("Military Aviator");
  // print DIRECTIONS
  ab.setCursor((30), (10)); 
  ab.print("A TO PLAY");
    // print HOW TO PAUSE
  ab.setCursor((25), (20)); 
  ab.print("B to PAUSE");
  // print or unpause
  ab.setCursor((20), (30)); 
  ab.print("A to UNPAUSE ");  
// print VERSION
  ab.setCursor((30), (40)); 
  ab.print("VERSION 0.1 "); 
// print "HIGH SCORE" , WICH IS REALY JUST KILL COUNT untill i figure out eeprom
  ab.setCursor(14, 50); 
  ab.print("HIGH SCORE "); 
  // print kill count
  ab.setCursor(100, 50); 
  ab.print(killz); 
  }
 // if on title page and a button is pressed, play
  if (ab.pressed(A_BUTTON) && (gamestate == 0)){
    gamestate = 1;
  }
// if on PLAY page and B button is pressed, PAUSE
  if (ab.pressed(B_BUTTON) && (gamestate == 1)){
    gamestate = 2;
  }
  // if on PAUSE page and B button is pressed, play
  if (ab.pressed(A_BUTTON) && (gamestate == 2)){
    gamestate = 1;
  }
   // if on PAUSE page and B button is pressed, play
  if (ab.pressed(A_BUTTON) && (gamestate == 3)){
    gamestate = 0;
  }
  
  if (gamestate == 1) {
 // print  hp 
  ab.setCursor((0), (55)); 
      ab.print("HP");
  // print the players hp
  ab.setCursor((20), (55)); 
      ab.print(ehp);

      ab.setCursor((40), (55)); 
      ab.print("y");
  // print the ehp
  ab.setCursor((55), (55)); 
      ab.print(buly);
   ab.setCursor((80), (55)); 
      ab.print("bulx");
  // print the ehp
  ab.setCursor((105), (55)); 
      ab.print(bulx);
     
      ab.drawBitmap(locx, locy, player, 16, 8, WHITE);
      ab.drawBitmap(elocx, elocy, enemy, 16, 8, WHITE);
  }
if (gamestate == 2) {
 // print  pause 
      ab.setCursor((30), (25)); 
      ab.print("PAUSE");
      ab.setCursor((17), (55)); 
      ab.print("A to UNPAUSE");
}

if (gamestate == 3) {
 // print  game over 
      ab.setCursor((30), (25)); 
      ab.print("GAME OVER");
      ab.setCursor((17), (55)); 
      ab.print("A to RESET");
}   
//about bullet
    // bullet
       //if a bullet is not on the screen and player presses a shoot
  if (ab.pressed(A_BUTTON) && (gamestate == 1) && (bulx == 0)){
      bulx = (locx + 16);
      buly = (locy);
      buls = bulx;
  }
   //if bullet is within a given range of enemy enemy hp = ehp-1
  if ((bulx <= elocx) && (bulx >= (elocx + 16))&& (buly >= elocyt) && ((buly - 3) <= elocy) && (gamestate == 1)) {
    ehp -= 1;
    killz += 1;
  }

 // move the players bullet forward 2 px untill it falls off the screen if with a delay without a delay
    while ((gamestate == 1) && (bulx <= 128) && (bulx > 0) && ab.everyXFrames(60)){
      bulx += 1;
      ab.setCursor((bulx), (buly)); 
    ab.print("-");
  }


 if ((bulx > 128) && (gamestate == 1)) {
    
    bulx = 0;
    buly = 0;
  }

  
     // if enemy is higher than player go down
  if ((gamestate == 1) && (enemyex == 1) && (elocy < locy) && ab.everyXFrames(5)&& (elocx >= (locx + 8))) {
     elocx -= 1;
     elocy += 1;
    
  }  
       // if enemy is lower than player go forward and up
  if ((gamestate == 1) && (enemyex == 1) && (elocy > locy) && ab.everyXFrames(10) && (elocx >= (locx + 8))) {
     elocx -= 1;
     elocy -= 1;
    
  } 
    // if enemy is behind player walk him off screen 
   if ( (gamestate == 1) && (enemyex == 1) && ab.everyXFrames(5) && (elocx <= (locx)) ) {
      elocx -= 1;
      
   }
  // if enemy is at same height as player go forward and shoot
   if ( (gamestate == 1) && (enemyex == 1) && (elocy == locy) && (elocx >= locx + 20) && (elocx <= locx +40) && ab.everyXFrames(5) && (ebulx == 0)) {
      //go forward
      elocx -= 1;
      
    
      //shoot
      
      
      
  }
    // if enemy is at same height as player and has already shot go forward 
   if ( (gamestate == 1) && (enemyex == 1) && (elocy == locy) && (ebulx > 0) && ab.everyXFrames(5)) {
      elocx -= 1;
      //go forward
    ; 
   }
   // if enemy is  within 18 px  x of player go up 
   if ((gamestate == 1) && (enemyex == 1) && (elocx <= (locx + 18)) && ab.everyXFrames(5)) {
     
     elocy -= 10;
    
  }
    
   

  

    // if enemy falls off the screen set it back  
  if (elocx < 0) {
    elocx = 128;
    ebulx = 0;
    ebulx = 0;
    elocy = (random(0, 30));
    
  }
    if (elocy < 0) {
    elocx = 128;
    ebulx = 0;
    ebulx = 0;
    elocy = (random(0, 30));
    
  }
    if (elocy > 55) {
    elocx = 128;
    ebulx = 0;
    ebulx = 0;
    elocy = (random(0, 30));
    
  }
   
 
    // if enemy bullet falls off the screen set it back to 0 
  if ((ebulx < 0) && (gamestate == 1)) {
    ebulx = 0;
    ebuly = 0;
  }
       // move the enemy bullet backward 1 px untill it falls off the screen if with a delay without a delay
    while ((gamestate == 1) && (ebulx > 0) && ab.everyXFrames(5)){
      ebulx -= 1;
      ebulm = cMillis; //previous bullet move = current miliseconds
    ab.setCursor((ebulx), (ebuly)); 
      ab.print("-");
      
  }
  if ((gamestate == 1) && (life == 0)) {
    //reset all variables and go back to the title screen

    gamestate = 0;
  }
ab.display();
}
