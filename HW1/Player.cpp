#include "Player.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


/**
    Player constructer

    @param name, bool value to specify is player is human or enemy.
    @return NA.
*/
Player::Player(const string name, const bool is_human){
	name_=name;
	is_human_=is_human;
	points_ = 0;
	
}


/**
   changes the private value points_ for current player.

    @param new points value.
    @return NA.
*/
void Player::ChangePoints(const int x){
	points_ += x;
}

/**
    sets position struct for a player

    @param position struct.
    @return NA.
*/
void Player::SetPosition(Position pos){
	pos_.row = pos.row;
	pos_.col = pos.col;
}

/**
    to nicely display player and points.
    @param NA
    @return string containing said information.
*/
string Player::Stringify(){ 
	string out = "Player: " + name_ +"  Points:  " + std::to_string(points_);	
	return out;
}

/**
    converts a position to an easy to read "up,down,left,right" to be stored in a vector to display later in MAZE CLASS. 

    @param position struct
    @return string of directions..
*/

string Player::ToRelativePosition(Position other){
// 	string total = "";
	
	if (other.col == pos_.col){
		if (other.row < pos_.row){
			return "UP";
		}
		else if (other.row >pos_.row){
			return "DOWN";
		}
	}
	else if (other.row == pos_.row){
		if (other.col < pos_.col){
			return "LEFT";
		}
		else if (other.col >pos_.col){
			return "RIGHT";
		}
		
	}
}