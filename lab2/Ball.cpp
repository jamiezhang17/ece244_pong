//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Jamie Zhang, Sept 15 2026

// brief breakdown
// represents the balls' properties
// (x,y)
// vx, vy (velocity)
// width, height, id 
// ball position is updated in each time step 

#include <iostream>
using namespace std;
#include "Ball.h"
#include "Player.h"


Ball::Ball(){
    height = 1;
    width = 1;
}

Ball::Ball(double a, double b, double vx, double vy, int num){
    x = a;
    y = b;
    velocity_x = vx;
    velocity_y = vy;
    id = num;
}

double Ball::getX(){
    return x;
}

int Ball::getID(){
    return id;
}

void Ball::update(){
    velocity_y = velocity_y - 0.02 * timeStep; // velocity of y
    y = y + velocity_y * timeStep; // new y position = old y position + displacement of y

    x = x + velocity_x * timeStep; // new x position = old x position + displacement of x
}

int Ball::overlap(Ball& b){
    return NO_OVERLAP;
}

int Ball::overlap(Player& p){
    double x1, x2, y1, y2, x_overlap, y_overlap_top, y_overlap_bottom, min_y_overlap;

    // paddle/player coordinates 
    x1 = p.getX();
    y1 = p.getY();

    // ball coordinates 
    x2 = x; 
    y2 = y; 

    // calculate the overlaps 
    // note: ball cannot collide with the left side of the paddle
    x_overlap = (x1 + p.getWidth()) - x2;
    y_overlap_top = (y1 + p.getHeight()) - y2; 
    y_overlap_bottom = (y2 + height) - y1;

    // we need a range of values that are valid for ball-paddle collision 
    // there is a collision if one of the following happens: 
        // x_overlap >= 0 (bcuz if not collision, x2 > x1 + paddle width and will result in a negative value)
        //   max x_overlap < ball width 
        // y_overlap_top >= 0 (bcuz if not collision, y2 > y1+paddle height)
        // y_overlap_bottom >= 0 (bcuz if not collision, y1 > y2 + paddle height will result in a negative value)
        
    // if 0 <= x_overlap < ball width AND (ball hits top OR ball hits bottom), then:
        // if y overlaps > x_overlap, return vertical_overlap 
        // if x_overlaps >= y overlaps (AKA else), return horizontal_overlap 
    if (x_overlap >= 0) { 
        
        if (y_overlap_top >= 0 && y_overlap_bottom >= 0){
            // get the min y overlap to compare with x overlap 
            if (y_overlap_top > y_overlap_bottom){
                min_y_overlap = y_overlap_bottom;
            }
            else if (y_overlap_top <= y_overlap_bottom){
                min_y_overlap = y_overlap_top;
            }

            if ((min_y_overlap > x_overlap)){  
                return VERTICAL_OVERLAP;
            }
            else { 
                return HORIZONTAL_OVERLAP;
            }
        }
    }

    return NO_OVERLAP;
}



void Ball::bounce(Ball arr[], int ballCount, Player player){ // note: arr[] and player are pass by value (copied), so changes here will not affect original 
    // for a ball: 
        // if x-coordinate is beyond right (WIDTH-1) wall OR ball hits paddle side, flip the ball's velocity_x sign
        // if y-coord is beyong top (HEIGHT-1) or bottom (0) wall OR ball hits paddle top/bottom, flip the ball's velocity_y sign
    if ((overlap(player) == VERTICAL_OVERLAP) || (x >= WIDTH - 1)){
        velocity_x = (-1.0) * velocity_x;
    }

    if ((y <= 0 || y >= HEIGHT - 1) || (overlap(player) == HORIZONTAL_OVERLAP)){
        velocity_y = (-1.0) * velocity_y;
    }
    
}


void Ball::draw(Screen& screen_to_draw_to){
    screen_to_draw_to.addPixel(x, y, 'o');
}