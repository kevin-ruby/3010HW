#include "Maze.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
/* time */
using namespace std;


/**
    Constructer for Board Class. Here, we create a 4 by 4 game board to be played.

    @param N/A - constructer
    @return N/A.
*/
Board::Board(){
	//fill board with all empties
	int v1 = 0;
	for (int i=0; i<4; i++){
		for (int j=0;j<4;j++){
			arr_[i][j] = SquareType::Empty;
		}
	}
	
	//set these... they will always start in these positions no matter what
	arr_[0][0] = SquareType::Human;
	arr_[3][3] = SquareType::Exit;
	//arr_[]
	//to calculate percentages
	srand(time(0));
	for (int i=0; i<4; i++){
		for (int j=0;j<4;j++){
			if (arr_[i][j] == SquareType::Empty){ //not human or exit
				v1 = rand() % 100 + 1;
				if (v1 >=1 and v1 <= 20){ // 20 percent
					arr_[i][j] = SquareType::Wall;
				}
				if (v1 >= 21 and v1 < 31){ // 10 percent
					arr_[i][j]= SquareType::Treasure;
				}
			}
		}
	}	
}

/**
    Returns the SquareType at any given position in board.

    @param position struct.
    @return SquareType.
*/

SquareType Board::get_square_value (Position pos) const{
	return arr_[pos.row][pos.col];
}

/**
    sets a square value at a given position on the board

    @param position,squareType.
    @return NA.
*/
void Board::SetSquareValue(Position pos, SquareType value){
	arr_[pos.row][pos.col] = value;
}

/**
    Returns a vector full of possible moves that the current player can go.

    @param Player *pointer.
    @return Vector of available positions
*/
vector<Position> Board::GetMoves(Player *p){
	
	
	Position po = p ->get_position();
	int Row = po.row;
	int Col = po.col;
	
	int rows = rows_;
	int cols = cols_;
	
	vector<Position> mv;
	
	if (Col !=0){
		Position l;
		l.col = Col - 1;
		l.row = Row;
		if (get_square_value(l) != SquareType::Wall){
			mv.push_back(l);
		}
		
	}
	if (Col < 3){
		Position l;
		l.col = Col + 1;
		l.row = Row;
		if (get_square_value(l) != SquareType::Wall){
			mv.push_back(l);
		}
	}
	if (Row !=0){
		Position l;
		l.col = Col;
		l.row = Row - 1;
		if (get_square_value(l) != SquareType::Wall){
			mv.push_back(l);
		}
	}
	if (Row < 3){
		Position l;
		l.col = Col;
		l.row = Row + 1;
		if (get_square_value(l) != SquareType::Wall){
			mv.push_back(l);
		}
	}
	return mv;
}


/**
    returns a bool value based on if move is a valid move. A valid move is defined in PDF of assigmment: humans die if they touch enemies, enemies cant touch eachother, etc.

    @param pPlayer, position
    @return True or false.
*/
bool Board::MovePlayer(Player *p, Position pos){
// 	SquareType sq = arr_[pos.row][pos.col];
	
	//cout << "human" <<p->is_human()<<endl;
		if (p->is_human()){
			if (get_square_value(pos) == SquareType::Wall){
				return false;
			}
			if (get_square_value(pos) == SquareType::Treasure){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Human);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
				p->ChangePoints(100);
				return true;
			}
			if (get_square_value(pos) == SquareType::Empty){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Human);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
				return true;
			}
			if (get_square_value(pos) == SquareType::Human){
				return false;
			}
			if (get_square_value(pos) == SquareType::Enemy){
				Position prev = p -> get_position();
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
				return true;
			}
			if (get_square_value(pos) == SquareType::Exit){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Human);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
				return true;
			}
		}
		else{
			//cout<<"hello!"<<endl;
			if (get_square_value(pos) == SquareType::Wall){
				return false;
			}
			if (get_square_value(pos) == SquareType::Treasure){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Enemy);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
				
// 				cout<<"YEAH"<<endl;
				return true;
			}
			if (get_square_value(pos) == SquareType::Empty){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Enemy);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
// 				cout<<"YEAH"<<endl;
				return true;
			}
			if (get_square_value(pos) == SquareType::Human){
				Position prev = p -> get_position();
				SetSquareValue(pos, SquareType::Enemy);
				p -> SetPosition(pos);
				SetSquareValue(prev, SquareType::Empty);
// 				cout<<"YEAH"<<endl;
				return true;
			}
			if (get_square_value(pos) == SquareType::Enemy){
				return false;
			}
			if (get_square_value(pos) == SquareType::Exit){
				return false;
			}
		}
		
	
}


/**
    see who is on exit square

    @param NA.
    @return value at exit square of array.
*/
SquareType Board::GetExitOccupant(){
	return arr_[3][3];
}

/**
    Maze constructer, makes new board

    @param na
    @return na
*/
Maze::Maze(){
	Board *b = new Board;
	board_ = b;
}

/**
    creats new game with user player, adds enemies based on user input. FUnction sets position values for user and enemies player class. 

    @param human player, number of enemies.
    @return NA.
*/

void Maze::NewGame(Player *human, const int enemies){
	turn_count_ = 0;
	
	Position init;
	init.row=0;
	init.col=0;
	human -> SetPosition(init);
		
	players_.push_back(human);
	for (int i =0; i< enemies; i++){
		std::string name = "enemy"+ std::to_string(i);
		//cout <<name<<endl;
		Player *enemy = new Player(name,false);
		players_.push_back(enemy);
		
	}
	
	
// 	for (int i=0;i<players_.size();i++){
// 		cout << players_[i]->Stringify()<<endl;
// 	}
// 	string out1 = players_[0]->Stringify();
// 	string out2 = players_[1]->Stringify();
// 	string out3 = players_[2]->Stringify();
	
// 	cout << out1<<endl;
// 	cout << out2<<endl;
// 	cout << out3<<endl;
	
	vec_size_ = players_.size();
	tracker_=0;
	int count=0;
	int setCount=1;
	
	for (int i=0;i<4;i++){
		for (int j =0; j<4;j++){
			
				Position p;
				p.row=i;
				p.col=j;
				if (this->board_->get_square_value(p)==SquareType::Empty){
					this->board_->SetSquareValue(p,SquareType::Enemy);
					count++;
					Player *set = players_[setCount];
					set->SetPosition(p);
					setCount ++;
					if (count == enemies){
						break;
					}
				}
		}
		if (count == enemies){
			break;
		}
	}
	cout<< *board_ <<endl;
	
	
/**
    returnd bool value to check if game is over. Game is over when humans are gone, or human staps on exit spot.

    @param na.
    @return true or false.
*/
	
}

bool Maze::IsGameOver(){
	
	//step 2, GAME COUNT function.
	if (turn_count_ == 20){
		cout<< "You have reached tuen count!! GAME OVER!"<<endl;
		return true;
	}
	
	
	Position exit;
	exit.row = 3;
	exit.col = 3;
	//human on exit
	if (this->board_->get_square_value(exit) == SquareType::Human){
		return true;
	}
	// chech if humans are present in any position on board
	int humanCount=0;
	for (int i=0;i<4;i++){
		for (int j =0; j<4;j++){
				Position p;
				p.row=i;
				p.col=j;
				if (this->board_->get_square_value(p)==SquareType::Human){
					humanCount += 1;
				}
		}
	}
	if (humanCount == 0){
		cout<<"ENEMIES ATE YOU! GAME OVER!"<<endl;
		return true;
	}
	else if (humanCount!=0){
		return false;
	}
	if (this->board_->get_square_value(exit) == SquareType::Human){
		cout<<"YOU WON! NICE!!!"<<endl;
		return true;
	}
}

/**
    this function handeles user input. We display the available moves, then wait for a user input. We then move the player based on the user input

    @param player.
    @return NA.
*/
void Maze::TakeTurn(Player *p){
	
	cout << p-> get_name()<< ":   Possible positions: " ;
	vector<Position> v = board_ ->GetMoves(p);
	for (int i=0;i<v.size();i++){
		cout << p-> ToRelativePosition(v[i])<<" ";
	}
	cout<<endl;
	string choice;
	cout<< "Pick choice:";
	
	cin >> choice;
	for (int i=0;i<choice.length();i++){
		choice[i]=tolower(choice[i]);
	}
	
	if (choice =="right"){
		Position n = p -> get_position();
		n.col += 1;
		board_ -> MovePlayer(p,n);
	}
	else if (choice =="left"){
		Position n = p -> get_position();
		n.col -= 1;
		board_ -> MovePlayer(p,n);
	}
	else if (choice =="up"){
		Position n = p -> get_position();
		n.row -= 1;
		board_ -> MovePlayer(p,n);
	}
	else if (choice == "down"){
		Position n = p -> get_position();
		n.row += 1;
		board_ -> MovePlayer(p,n);
		//cout<< n.row << n.col<<endl;
	}
	
	cout<< *board_ <<endl;
	turn_count_++;
}


/**
    Returns a player that is up next vector.

    @param NA.
    @return The next player object in the players_ vector (assuming the vector wraps from the end to the front...).
*/
Player * Maze::GetNextPlayer(){
	
	//cout <<tracker_<<endl;
	vector<Player*> vec = players_;
	Player * r = vec[tracker_];
	if (tracker_ < vec_size_ -1){
		tracker_++;
	}
	else {
		tracker_=0;
	}
	return r;
}