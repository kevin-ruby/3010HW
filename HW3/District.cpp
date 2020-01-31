#include "District.h"

int District::party_count_ = 4;


District::District(int id){
	for (int i=1; i< party_count_;i++){
		district_map_.insert({Party::One, rand()%10});
		district_map_.insert({Party::Two, rand()%10});
		district_map_.insert({Party::Three, rand()%10});
		district_map_.insert({Party::None, rand()%10});
	}
	area_ = rand() %25 + 5;
	id_ = id;
}


void District::Convert(Party o, Party n , int num){
	district_map_[o] = district_map_[o] - num;
	district_map_[n] = district_map_[n] + num
}

Party District::MajorityParty(Party cp){
	int max =-100;
	Party p = Party::None;

	for (typename std::map<Party, int>::iterator it = district_map_.begin(); it != district_map_.end();it++){
		if (it -> second > max and it -> first != cp){
			max = it->second;
			p = it-> first;
		}
	}

	return p;
}
