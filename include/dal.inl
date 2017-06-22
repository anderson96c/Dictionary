/// DAL
template <typename Key, typename Data, typename KeyComparator>
DAL<Key, Data, KeyComparator>::DAL(int _MaxSz)
	: mi_Length(0)        //Logical size
	, mi_Capacity(_MaxSz) //Physical size
	, mpt_Data(nullptr)   //Storage
{
	if(_MaxSz < 0)
	{
		throw std::invalid_argument( "[DAL()]: Tamanho de lista invalido!" );	
	}
	mpt_Data = new NodeAL[_MaxSz];
}

template <typename Key, typename Data, typename KeyComparator>
int DAL<Key, Data, KeyComparator>::_search(const Key & _z) const
{

	KeyComparator cmp;
	Key k;

	for(auto i = 0; i < mi_Length ; i++)
	{
		k = mpt_Data[i].id;

		if(not cmp(k,_z) and not cmp(_z,k))
		{
			return i;
		}
	}
	return -1;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{

	// If it's empty, there's nothing to remove
	if(mi_Length == 0)
		return false;

	auto ads = _search(_x);
	//Checkes if it's in the Dict
	if(ads == (mi_Length-1))
	{
		_s = mpt_Data[ads].info;
		mi_Length--;
		return true;
	}
	else if(ads != -1)
	{
		_s = mpt_Data[ads].info;		
		std::copy( &mpt_Data[ads+1], &mpt_Data[mi_Length+1], &mpt_Data[ads]);
		mi_Length--;

		return true;
	}
	//It's not in the Dict
	return false;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search(const Key & _x, Data & _s) const
{

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
	if(mi_Length == mi_Capacity)
		return false;

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

	for(auto i(1); i!=mi_Length; i++){
		if(cmp(mpt_Data[i].id, min))
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


	for(auto i(1); i<mi_Length; i++){
		if(cmp(max, mpt_Data[i].id))
			max = mpt_Data[i].id;
	}
	return max;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const
{

	//Empty Dict
	if(mi_Length == 0)
		return false;
	//The key _x is not in the Dict
	if(_search(_x) == -1)
		return false;

	KeyComparator cmp;
	//Define sucessor como o max do Dict
	Key sucessor = max();

	for(auto i(0); i<mi_Length; i++)
	{
		if(cmp(_x, mpt_Data[i].id) and cmp(mpt_Data[i].id, sucessor))
			sucessor = mpt_Data[i].id;
	}

	_y = sucessor;

	return true;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const
{
	//Empty Dict
	if(mi_Length == 0)
		return false;
	//The key _x is not in the Dict
	if(_search(_x) == -1)
		return false;

	KeyComparator cmp;
	//Define predecessor como o max do Dict
	Key predecessor = min();

	for(auto i(0); i<mi_Length; i++)
	{
		if(cmp(mpt_Data[i].id, _x) and cmp( predecessor, mpt_Data[i].id))
			predecessor = mpt_Data[i].id;
	}

	_y = predecessor;

	return true;

}

/*
		************** / * DSAL * / *****************           	
*/
template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search(const Key & _x) const
{
	auto Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto left = 0 , right = Length_-1;

	KeyComparator cmp;

	while(left <= right)
	{
		int middle = (left-right)/2;

		auto result = DAL<Key, Data, KeyComparator>::mpt_Data[middle].id;

		if(not cmp(_x,result) and not cmp(result, _x))
			return middle;
		else if (cmp(_x, result))
			right = middle -1;
		else 
			left = middle+1;
	}

	return -1;

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert(const Key & _newKey, const Data & _newInfo)
{
	auto & Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto & Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;
	auto Capacity_ = DAL<Key, Data, KeyComparator>::mi_Capacity;

	auto check = _search(_newKey);

	//Dict is full
	if(Length_ == Capacity_)
		return false;
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
		for(auto i(Length_); i>0; i--)
		{
			//
			Data_[i].id = Data_[i-1].id;
			Data_[i].info = Data_[i-1].info;
		}
		Data_[0].id = _newKey;
		Data_[0].info = _newInfo;
		Length_++;
		return true;
	}
	//The newKey is smaller than every key in the Dict
	else if(ads == Length_-1)
	{
		Data_[Length_].id = _newKey;
		Data_[Length_].info = _newInfo;
		Length_++;
		return true;
	}
	//The newKey will be in the Middle of the dict
	//and will be insert in the ads+1 position
	else
	{
		for(auto i(Length_); i>ads+1; i--)
		{
			Data_[i].id = Data_[i-1].id;
			Data_[i].info = Data_[i-1].info;
		}
		Data_[ads+1].id = _newKey;
		Data_[ads+1].info = _newInfo;
		Length_++;
		return true;
	}




	
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;
	if(Length_ == 0)
		//throw std::out_of_range("[remove() Can not remove an element from an empty Dictionary");
		return false;

	auto ads = _search(_x);
	//Not in the Dict
	if(ads != Length_)
	{
		_s = Data_[ads].info;
	if(not ads == (Length_-1))
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

		return Data_[0].id;

}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::max() const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		throw std::out_of_range("[max()]: Can not recover an element from an empty Dictionary");

		return Data_[Length_-1].id;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		return false;

	auto ads = _search(_x);

	if(ads == Length_)
		return false;
	if(ads == Length_-1)
		return false;

	_y = Data_[ads+1].id;
	return true;	
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const
{
	auto &Length_ = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &Data_ = DAL<Key, Data, KeyComparator>::mpt_Data;

	if(Length_ == 0)
		return false;

	auto ads = _search(_x);

	if(ads == Length_)
		return false;
	if(ads == 0)
		return false;

	_y = Data_[ads-1].id;
	return true;
}