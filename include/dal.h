#ifndef _DAL_H_
#define _DAL_H_

#include <iostream>
#include <string>
#include <stdexcept>

template <typename Key, typename Data, typename KeyComparator>
class DAL{

	protected:
		struct NodeAL{
			Key id;
			Data info;
		};

		static const int SIZE = 50;
		int mi_Length;
		int mi_Capacity;
		NodeAL *mpt_Data;

		int _search(const Key & _z) const;

	public:
		/// [I] SPECIAL MEMBERS
		DAL(int _MaxSz = SIZE);
		virtual ~DAL(){
			delete [] mpt_Data;
		};

		/// [II] FUNCTIONS
		bool remove(const Key & _x, Data & _s);
		bool search(const Key & _x, Data & _s) const;
		bool insert(const Key & _newKey, const Data & _newInfo);
		Key min() const;
		Key max() const;
		bool sucessor(const Key & _x, Key & _y) const;
		bool predecessor(const Key & _x, Key & _y) const;

		inline friend std::ostream &operator<<(std::ostream & _os, const DAL& _oList){
			_os << "[ ";
			for(int i(0); i < _oList.mi_Lenght; i++){
				_os << "{id: " << _oList.mpt_Data[i].id << ", info: "
					<< _oList.mpt_Data[i].info << "} ";
			}
			_os << "]";
			return _os;
		}

};

template <typename Key, typename Data, typename KeyComparator>
class DSAL : public DAL<Key, Data, KeyComparator>{

	public:
		DSAL(int _MaxSz) 
			: DAL<Key, Data, KeyComparator>(_MaxSz)
		{ /* Empty */ };
		virtual ~DSAL()
		{ /* Empty */ };

		bool remove(const Key & _x, Data & _s);
		bool insert(const Key & _novaID, const Data & _novaInfo);
		Key min() const;
		Key max() const;
		bool sucessor(const Key & _x, Key & _y) const;
		bool predecessor(const Key & _x, Key & _y) const;

	private:
		int _search(const Key & _x) const;

};

#include "dal.inl"

#endif