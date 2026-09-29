//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file


// brief breakdown
// initializes components 
// receives user input 
// updates game state
// checks for paddle/ball collisions
// updates scores
// ends game

#include <string>
#include "Ball.h"
#include "Globals.h"
#include "Player.h"

#include "Screen.h"
#include "io.h"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    // TODO: ECE 244 Student: Complete the game loop here only!
    // ECE 244 Student: DO NOT edit any other segments of this file!

    int flag = 0; // prevents the paddle from immediately shrinking and balls added all at once

    // ---- handling input, updating the balls, game progression happens for simulation_fps number of iterations ---------
    for (int step = 0; step < simulation_fps; step++) {

      // ---------   handle input ----------
      char input = get_input();
      if (input == 'q'){
        gameEnded = true; 
        continue; 
      }

      if (input != '\0'){
        if ((player.getY() >= 0) && (player.getY() <= HEIGHT - player.getHeight())){ // make sure y is in bounds first 
          player.update(input); // the player moves, call the player object's Player class function
        }  
      }
      // ------------------------------------- 

      // -------- update the existing balls ----------
      for (int i = 0; i < ballCount; i++){  
        balls_array[i].update(); // update current ball positions and velocities 
        
        // detect collision with paddle
        int collision = balls_array[i].overlap(player);
        if ((collision == HORIZONTAL_OVERLAP) || (collision == VERTICAL_OVERLAP)){
          score++; // if current ball collides with paddle, score++ 
          flag = 1;
        }

        // bounce/change current ball's velocity signs 
        balls_array[i].bounce(balls_array, i, player); 

        // get the current ball's x-coord, if it's past the left wall, game over
        if (balls_array[i].getX() < 0){ 
          gameEnded = true;
          continue;
        } 
      }
      // ------------------------------------------------
    } 
    // ------------------------------------------------------------------------------------------


    // --------- game progression ---------------
    if ((score % 2 == 0) && (score != 0) && (flag == 1)){ // every two hits, decrease paddle size 
      player.decreaseHeight(1);
    }

    if ((score % 5 == 0) && (score != 0) && (ballCount < max_ballCount) && (flag == 1)){ // every 5 hits and if ballCount < max_ballCount, add a new ball 
      balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0, ballCount); 
      ballCount++;
    }
    // -------------------------------------------


    // ----- drawing the screens after running simulation for simulation_fps number of times -------
    player.draw(screen); 
    for (int i = 0; i < ballCount; i++){
      balls_array[i].draw(screen); 
    }
    // ----------------------------------


    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}