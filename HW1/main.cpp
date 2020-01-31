/**
Kevin Ruby
Homework 1
This program is a two-player maze game. The User can pick their name and select the number of enemies that will be spawned into the game.  
*/

#include "Maze.h"
#include <iostream>
#include <math.h>
using namespace std;


int main(){
	//USER: enter in your name. DO NOT change "true" here.
	Player p("kevin",true);
	////////////////////////
	
	Maze m;
	
	
	//USER: can change the "2" in the following function call. THis will change number of enemies in board.
	m.NewGame(&p,2);
	/////////////////////////
	
	// this runs the game. Leave alone.
	while(!m.IsGameOver()){
		Player  * current = m.GetNextPlayer();
		m.TakeTurn(current);	
	}
	cout<<endl;
	cout<< p.Stringify();
	cout<<endl;
	return 0;
}