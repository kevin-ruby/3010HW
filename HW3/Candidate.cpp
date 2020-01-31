#include "Candidate.h"
#include iostream

using namepspace std;


string StringifyParty(Party p){
	if (p ==0){
		return "One";
	}
	else if (p == 1 ){
		return "Two";
	}
	else if (p == 2){
		return "Three";
	}
	else {
		return "None";
	}
}

int Candidate::candidate_count_ = 0;

Candidate::Candidate(string nm, Party p ){
	name_ = nm;
	party_ = p;
	id_ = Candidate::candidate_count_;
	Candidate::candidate_count_ ++;
}