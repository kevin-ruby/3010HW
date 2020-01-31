#include <map>
#include "Candidate.h"

#ifndef _DISTRICT_H_
#define _DISTRICT_H_

class District{
	public:
		District();
		District(int id);
		void Convert(Party o, Party n, int num);
		Party MajorityParty(Party cp);
		std::map<Party, int> get_district_map(){ return district_map_; };
		int get_id(){ retur id_;};
		int get_square_miles(){ return area_; };

		
	


		District operator = District (&dis);
		friend std::ostream& operator<<(std::ostream& os, District& dis);

	private:
		int area_;
		std::map<Party, int> district_map_;
		int id_;
		static int party_count_;

};


#endif