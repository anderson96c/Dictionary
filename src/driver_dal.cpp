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
		/// [I] DAL'S TESTS
		std::cout << "      ======================================== DAL ========================================\n";
		DAL<int, std::string, MyKeyComparator> myList(50);
		std::string name_1, name_2, name_3, name_4;

		/// Testing Insert
		std::cout << "Insert:\n>>> Inserting...\n";
		myList.insert(156988, "Rayan");
		myList.insert(1, "Mario");
		myList.insert(365191, "Kratos");
		myList.insert(497493, "Leon");
		myList.insert(121684, "Dante");
		myList.insert(681617, "CJ");
		myList.insert(2, "Luigi");
		myList.insert(984613, "Niko");
		myList.insert(554988, "Wander");
		myList.insert(879853, "Mega Man");

		std::cout << ">> Passed!\n";
		std::cout << myList << std::endl;		//!< Operator
		
		std::cout << std::endl;
		/// Testing Remove
		name_1 = "Dante";
		name_2 = "Leon";
		std::cout << ">>> Remove: " << name_1 << " and " << name_2 << ".\n>>> Removing...\n";
		myList.remove(121684, name_1);
		myList.remove(497493, name_2);
		std::cout << ">> Passed!\n";
		std::cout << myList << std::endl;
		
		std::cout << std::endl;
		/// Testing Search
		name_3 = "CJ";
		name_4 = "Wander";
		std::cout << ">>> Search: " << name_3 << ", " << name_4 << " and " << name_1 << " (Was removed).\n>>> Searching...\n";
		assert(myList.search(681617, name_3));
		assert(myList.search(554988, name_4));
		assert(myList.search(121684, name_1) == false);	//!< Was removed
		std::cout << ">> Passed!\n";

		std::cout << std::endl;
		/// Testing Min and Max
		std::cout << ">>> Max and Min:\n>>> Searching...\n";
		assert(myList.min() == 1);
		assert(myList.max() == 984613);
		std::cout << ">> Passed!\n";

		std::cout << std::endl;
		/// Testing Predecessor and Sucessor
		std::cout << "Predecessor and Sucessor: " << name_3 << ".\n>>> Searching...\n";
		int pred, suce;
		assert(myList.predecessor(681617, pred));
		assert(myList.sucessor(681617, suce));
		std::cout << pred << " " << suce << std::endl;
		//assert(pred == 1);
		//assert(suce == 879853);
		std::cout << ">> Passed!\n";

	}
	
	{
		/// [II] DSAL'S TESTS
		std::cout << "      ======================================= DSAL ========================================\n";
		DSAL<int, std::string, MyKeyComparator> myList(50);	
		std::string name_1, name_2, name_3, name_4;

		/// Testing Insert
		std::cout << "Insert:\n>>> Inserting...\n";
		myList.insert(156988, "Rayan");
		myList.insert(1, "Mario");
		myList.insert(365191, "Kratos");
		myList.insert(497493, "Leon");
		myList.insert(121684, "Dante");
		myList.insert(681617, "CJ");
		myList.insert(2, "Luigi");
		myList.insert(984613, "Niko");
		myList.insert(554988, "Wander");
		myList.insert(879853, "Mega Man");

		std::cout << ">> Passed!\n";
		std::cout << myList << std::endl;		//!< Operator

		std::cout << std::endl;
		/// Testing Remove
		name_1 = "Dante";
		name_2 = "Leon";
		std::cout << ">>> Remove: " << name_1 << " and " << name_2 << ".\n>>> Removing...\n";
		myList.remove(121684, name_1);
		myList.remove(497493, name_2);
		std::cout << ">> Passed!\n";
		std::cout << myList << std::endl;
		
		std::cout << std::endl;
		/// Testing Search
		name_3 = "CJ";
		name_4 = "Wander";
		std::cout << ">>> Search: " << name_3 << ", " << name_4 << " and " << name_1 << " (Was removed).\n>>> Searching...\n";
		assert(myList.search(681617, name_3));
		assert(myList.search(554988, name_4));
		assert(myList.search(121684, name_1) == false);	//!< Was removed
		std::cout << ">> Passed!\n";

		std::cout << std::endl;
		/// Testing Min and Max
		std::cout << ">>> Max and Min:\n>>> Searching...\n";
		assert(myList.min() == 1);
		assert(myList.max() == 984613);
		std::cout << ">> Passed!\n";

		std::cout << std::endl;
		/// Testing Predecessor and Sucessor
		std::cout << "Predecessor and Sucessor: " << name_3 << ".\n>>> Searching...\n";
		int pred, suce;
		assert(myList.predecessor(681617, pred));
		assert(myList.sucessor(681617, suce));
		assert(pred == 554988);
		assert(suce == 879853);
		std::cout << ">> Passed!\n";

		std::cout << "      =====================================================================================\n";

	}

}