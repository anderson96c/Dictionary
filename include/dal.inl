/// DAL
template <typename Key, typename Data, typename KeyComparator>
DAL<Key, Data, KeyComparator>::DAL(int _MaxSz)
	: mi_Length(0)        //Logical size
	, mi_Capacity(_MaxSz) //Physical size
	, mpt_Data(nullptr)   //Storage
{
	if(_MaxSz < 0)
	{
		throw std::invalid_argument( "[DAL()]: Tamanho invalido!" );	
	}
	mpt_Data = new NodeAL[_MaxSz];
}

template <typename Key, typename Data, typename KeyComparator>
int DAL<Key, Data, KeyComparator>::_search(const Key & _z) const
{
	//Functor
	KeyComparator cmp;

	for(auto i = 0; i < mi_Length ; i++)
	{
		//If equal to _z we found it
		if(not cmp(mpt_Data[i].id,_z) and not cmp(_z,mpt_Data[i].id))
		{   //Return the address
			return i;
		}
	}
	//Not in the Dict
	return -1;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{

	// If it's empty, there's nothing to remove
	if(mi_Length == 0)
		throw std::out_of_range("[remove()]: Can not remove an element from an empty Dictionary");

	//Get the address of _x
	auto ads = _search(_x);
	//If it's the last one
	if(ads == (mi_Length-1))
	{
		//Get the info
		_s = mpt_Data[ads].info;
		//Decreases logical size
		mi_Length--;
		return true;
	}
	else if(ads != -1)
	{
		//Get the info
		_s = mpt_Data[ads].info;
		//Cover the element to be removed	
		std::copy( &mpt_Data[ads+1], &mpt_Data[mi_Length+1], &mpt_Data[ads]);
		//Decreases logical size
		mi_Length--;

		return true;
	}
	//It's not in the Dict
	return false;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search(const Key & _x, Data & _s) const
{
	//Get the address of _x
	auto ads = _search(_x);
	//Checkes if it's in the Dict
	if(ads != -1)
	{
		_s = mpt_Data[ads].info;
		return true;
	}
	//It's not in the Dict
	else
		return false;


}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::insert(const Key & _newKey, const Data & _newInfo)
{	
	//If full
	if(mi_Length == mi_Capacity)
		throw std::out_of_range("[insert()]: Can not insert an element in a full Dictionary");
	//Get the address
	auto ads = _search(_newKey);

	//The key is already on the list
	if(ads != -1)
		return false;

	//else
	mpt_Data[mi_Length].id = _newKey;
	mpt_Data[mi_Length].info = _newInfo;
	mi_Length++;

	return true;
}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::min() const
{
	if(mi_Length == 0)
		throw std::out_of_range("[min()]: Can not recover an element from an empty Dictionary");

	KeyComparator cmp;
	Key min = mpt_Data[0].id;
	//Runs the list looking for the smallest key
	for(auto i(1); i!=mi_Length; i++){
		//Compares 'min' with the key
		if(cmp(mpt_Data[i].id, min))
			//If the key is smaller, aplies to min
			min = mpt_Data[i].id;
	}
	return min;

}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::max() const
{

	if(mi_Length == 0)
		throw std::out_of_range("[max()]: Can not recover an element from an empty Dictionary");


	KeyComparator cmp;
	Key max = mpt_Data[0].id;

	//Runs the list looking for the biggest key
	for(auto i(1); i<mi_Length; i++){
		//Compares 'max' with the key
		if(cmp(max, mpt_Data[i].id))
			//If the key is bigger, aplies to max
			max = mpt_Data[i].id;
	}
	return max;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const
{

	//Empty Dict
	if(mi_Length == 0)
		throw std::out_of_range("[sucessor()]: Can not recover an element from an empty Dictionary");
	//The key _x is not in the Dict
	if(_search(_x) == -1)
		return false;

	KeyComparator cmp;
	//Defines sucessor as the max of Dict
	_y = max();

	for(auto i(0); i<mi_Length; i++)
	{
		//Checks if the key is between _x and sucessor
		if(cmp(_x, mpt_Data[i].id) and cmp(mpt_Data[i].id, _y))
			//If it is, aplies the key to sucessor
			//sucessor = mpt_Data[i].id;
			_y = mpt_Data[i].id;
	}

	return true;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const
{
	//Empty Dict
	if(mi_Length == 0)
		throw std::out_of_range("[predecessor()]: Can not recover an element from an empty Dictionary");
	//The key _x is not in the Dict
	if(_search(_x) == -1)
		return false;

	KeyComparator cmp;
	//Defines predecessor as the min of Dict
	_y = min();

	for(auto i(0); i<mi_Length; i++)
	{
		if(cmp(mpt_Data[i].id, _x) and cmp( _y, mpt_Data[i].id))
			_y = mpt_Data[i].id;
	}

	return true;

}

/*
		************** / * DSAL * / *****************           	
*/
template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search(const Key & _x) const
{
	//Gets the length from the DAL class
	auto Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	int left = 0 , right = Length_-1;

	KeyComparator cmp;

	//Ordinary binary search
	while(left <= right)
	{
		int middle = (left+right)/2;

		auto result = DAL<Key, Data, KeyComparator>::mpt_Data[middle].id;

		if(not cmp(_x,result) and not cmp(result, _x))
		{	return middle;}
		else if (cmp(_x, result))
			right = middle -1;
		else 
			left = middle+1;
	}
	//If it's not in the Dict
	return -1;


}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert(const Key & _newKey, const Data & _newInfo)
{
	//Get the elements from DAL class
	auto & Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto & Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;
	auto Capacity_ = DAL<Key, Data, KeyComparator>::mi_Capacity;

	auto check = _search(_newKey);

	//Dict is full
	if(Length_ == Capacity_)
		throw std::out_of_range("[insert()]: Can not insert an element in a full Dictionary");
	//The key is already in the Dict
	if(check != -1)
		return false;

	KeyComparator cmp;

	int ads = -1;
	int try_ = 0;

	//Getting the biggest key that is smaller than the newKey
	while(try_ < Length_)
	{
		if(cmp(Data_[try_].id, _newKey))
			ads = try_;
		try_++;
	}

	//The newKey is smaller than every key in the Dict
	if(ads == -1)
	{
		//Push every element one step foward
		for(auto i(Length_); i>0; i--)
		{
			Data_[i].id = Data_[i-1].id;
			Data_[i].info = Data_[i-1].info;
		}
		//Inserts the element in the begin of the Dict
		Data_[0].id = _newKey;
		Data_[0].info = _newInfo;
		Length_++;
		return true;
	}
	//The newKey is bigger than every key in the Dict
	else if(ads == Length_-1)
	{
		//Inserts it in the end of the Dict
		Data_[Length_].id = _newKey;
		Data_[Length_].info = _newInfo;
		Length_++;
		return true;
	}
	//The newKey will be in the Middle of the dict
	//and will be insert in the ads+1 position
	else
	{
		//Push every element after the ads+1 position
		for(auto i(Length_); i>ads+1; i--)
		{
			Data_[i].id = Data_[i-1].id;
			Data_[i].info = Data_[i-1].info;
		}
		//Insert the element in ads+1
		Data_[ads+1].id = _newKey;
		Data_[ads+1].info = _newInfo;
		Length_++;
		return true;
	}
	return false;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{
	//Get the elements from DAL class
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;
	if(Length_ == 0)
		throw std::out_of_range("[remove() Can not remove an element from an empty Dictionary");

	auto ads = _search(_x);

	if(ads == (Length_-1))
	{
		_s = Data_[ads].info;
		Length_--;
	}
	//Checks if its in the Dict
	else if(ads != -1)
	{
		_s = Data_[ads].info;
		std::copy( &Data_[ads+1], &Data_[Length_+1], &Data_[ads] );
		Length_--;
	}

		return false;



}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::min() const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		throw std::out_of_range("[min()]: Can not recover an element from an empty Dictionary");
		//As the first one has the smallest key, just returns it
		return Data_[0].id;

}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::max() const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		throw std::out_of_range("[max()]: Can not recover an element from an empty Dictionary");
		//As the last one has the biggest key, just returns it
		return Data_[Length_-1].id;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		throw std::out_of_range("[sucessor()]: Can not recover an element from an empty Dictionary");

	auto ads = _search(_x);
	//Not in the Dict
	if(ads == -1)
		return false;
	//Last one, no sucessor
	if(ads == Length_-1)
		return false;
	//As the Dict is sorted by key order, just return the next one
	_y = Data_[ads+1].id;
	return true;	
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		throw std::out_of_range("[predecessor()]: Can not recover an element from an empty Dictionary");

	auto ads = _search(_x);
	//Not in the Dict
	if(ads == -1)
		return false;
	//First one, no predecessor
	if(ads == 0)
		return false;
	//As the Dict is sorted by key order, just return the one before
	_y = Data_[ads-1].id;
	return true;
}