#include <iostream>
#include <string>

#ifndef _CANDIDATE_H_
#define _CANDIDATE_H_

using namespace std;

enum Party{One,Two,Three,None};

string StringifyParty(Party p);

class Candidate {
public:
	Candidate(string nm,Party p);
	Party get_party(){ return party_; };
	string get_name(){ return name_; };
	int get_id(){ return id_;};
	int get_candidate_count(){ return candiate_count_; };


	friend std::ostream& operator<<(std::ostream& os, Candidate& c);

private:
	Party party_;
	string name_;
	int id_;
	static int candidate_count_;
 
};

#endif