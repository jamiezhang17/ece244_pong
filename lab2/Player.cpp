//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Jamie Zhang, Sept 15 2026

// brief breakdown 
// controls paddle 
// (x,y)
// width, height 
// speed 
// every 2 hits, paddle height decreases by 1 unit, min height = 3



#include <iostream>
using namespace std; 
#include "Player.h"

// default constructor
Player::Player(){
    width = 1;
}

// initialization constructor 
Player::Player(double a, double b, int h){
    height = h; // set the data member height value to parameter height
    x = a;
    y = b;
}

double Player::getX(){
    return x;
}

double Player::getY(){
    return y;
}

int Player::getHeight(){
    return height;
}

int Player::getWidth(){
    return width;
}

void Player::decreaseHeight(int delta_to_decrease_by){
    if (height > 3){ // minimum height is 3
        height = height - delta_to_decrease_by; // if height is greater than 3, keep decreasing height
    }
}

void Player::update(char c){
    if (c == 'A' && y <= HEIGHT - height - 2){ // move up if up arrow
        y = y + 2;
    }
    else if (c == 'B' && y >= 2){ // move down if down arrow 
        y = y - 2;
    }
}


void Player::draw(Screen& screen_to_draw_to){ 

    for (int i = 0; i < height; i++){ // for each pixel of the paddle
        screen_to_draw_to.addPixel(x, y + i, '#'); // call the specific function addPixel of the screen_to_draw_to object (paddle is vertical)
    }
    
}