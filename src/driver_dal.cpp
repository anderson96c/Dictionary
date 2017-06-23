#include <iostream>
#include <cassert>
#include <string>
#include "../include/dal.h"

class MyKeyComparator{
	public:
		bool operator()(const int &lhs, const int &rhs) const{
			return lhs < rhs;
		}
};

int main(){
	
	{
		std::cout << "##################################### >>DAL TEST<< #####################################\n\n";
		DAL<int, std::string, MyKeyComparator> myList(50);
		std::string name1, name2;

		// Testing Insert
		std::cout << "Testing Insert():\n";
		myList.insert(23,"Ahri");
		myList.insert(1, "Mordekaizer");
		myList.insert(645, "Aloi");
		myList.insert(147, "Ezio");
		myList.insert(9999999, "Leroy Jenkins");


		std::cout << myList << std::endl;		// Operator <<
		std::cout << ">> Insert() works\n";
		
		// Testing Remove
		myList.remove(645, name1);
		myList.remove(147, name2);
		std::cout << "Removed: " << name1 << " and " << name2 << ".\n";
		assert(name1 == "Aloi");
		assert(name2 == "Ezio");
		std::cout << "Passed!\n";
		std::cout << myList << "\n";
		
		// Testing Search
		std::cout << "Searching for key '1'...\n";
		assert(myList.search(1, name1));
		std::cout << "Recovered from search: " << name1 << "\n";
		assert(myList.search(147, name2) == false);	//Removed
		std::cout << "Passed!\n";

		std::cout << std::endl;
		/// Testing Min and Max
		std::cout << "Testing max() and min():\n";
		myList.search(myList.min(), name1);
		myList.search(myList.max(), name2);
		std::cout << "Info in min(): " << name1 << " Info in max(): " << name2 << "\n";
		assert(name1 == "Mordekaizer");
		assert(name2 == "Leroy Jenkins");
		std::cout << "Passed!\n";

		std::cout << std::endl;
		/// Testing Predecessor and Sucessor
		std::cout << "Testing Predecessor and Sucessor of key '23': \n";
		int prd, scs;
		assert(myList.predecessor(23, prd));
		assert(myList.sucessor(23, scs));
		std::cout << "Predecessor: " << prd << "\n";
		std::cout << "Sucessor: " << scs << "\n";
		assert(prd == 1);
		assert(scs == 9999999);
		std::cout << "Passed!\n";

		std::cout << "\n\n\n";

	}
	
	{
		std::cout << "##################################### >>DSAL TEST<< #####################################\n\n";
		DSAL<int, std::string, MyKeyComparator> myList(50);
		std::string name1, name2;

		// Testing Insert
		std::cout << "Testing Insert():\n";
		myList.insert(23,"Ahri");
		myList.insert(1, "Mordekaizer");
		myList.insert(645, "Aloi");
		myList.insert(147, "Ezio");
		myList.insert(9999999, "Leroy Jenkins");


		std::cout << myList << std::endl;		// Operator <<
		std::cout << ">> Insert() works\n";
		
		// Testing Remove
		myList.remove(645, name1);
		myList.remove(147, name2);
		std::cout << "Removed: " << name1 << " and " << name2 << ".\n";
		assert(name1 == "Aloi");
		assert(name2 == "Ezio");
		std::cout << "Passed!\n";
		std::cout << myList << "\n";
		
		// Testing Search
		std::cout << "Searching for key '1'...\n";
		assert(myList.search(1, name1));
		std::cout << "Recovered from search: " << name1 << "\n";
		assert(myList.search(147, name2) == false);	//Removed
		std::cout << "Passed!\n";

		std::cout << std::endl;
		/// Testing Min and Max
		std::cout << "Testing max() and min():\n";
		myList.search(myList.min(), name1);
		myList.search(myList.max(), name2);
		std::cout << "Info in min(): " << name1 << " Info in max(): " << name2 << "\n";
		assert(name1 == "Mordekaizer");
		assert(name2 == "Leroy Jenkins");
		std::cout << "Passed!\n";

		std::cout << std::endl;
		/// Testing Predecessor and Sucessor
		std::cout << "Testing Predecessor and Sucessor of key '23': \n";
		int prd, scs;
		assert(myList.predecessor(23, prd));
		assert(myList.sucessor(23, scs));
		std::cout << "Predecessor: " << prd << "\n";
		std::cout << "Sucessor: " << scs << "\n";
		assert(prd == 1);
		assert(scs == 9999999);
		std::cout << "Passed!\n";

		std::cout << "\n\n\n";

	}

}