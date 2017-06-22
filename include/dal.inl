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
int DAL<Key, Data, KeyComparator>::_search(Key & _z)
{

	KeyComparator cmp;
	Key k;
	int i;

	for(i(0); i < mi_Length i++)
	{

		k = mpt_Data[i].id;

		if(not cpm(k,_z) and not cpm(k,_z)){
			return i;
		}
	}

	return i;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{

	// If it's empty, there's nothing to remove
	if(mi_Length == 0)
		return false;

	auto ads = _search(_x);
	//Checkes if it's in the Dict
	if(ads != mi_Length)
	{

		if(not ads == (mi_Length-1))
			std::copy( &mpt_Data[ads+1], &mpt_Data[mi_Length+1], &mpt_Data[ads] );
		mi_Length--;

		return true;

	}
	//It's not in the Dict
	else
		return false;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search(const Key & _x, Data & _s)
{

	auto ads = _search(_x);
	//Checkes if it's in the Dict
	if(ads != mi_Length)
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
	if(mi_Length < mi_Capacity)
	{
		//Checks if it's already in the list and get the address
		auto ads = _search(_newKey);

		mpt_Data[ads].id = _newKey;
		mpt_Data[ads].info = _newInfo;
		if(ads == mi_Length)
			mi_Length++;

		return true
	}

	else
		return false
}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::min() const
{
	if(mi_Length == 0)
		throw std::out_of_range("[min()]: Can not recover an element from an empty Dictionary")

	KeyComparator cmp;
	Key min;

	for(auto i(0); i!=mi_Length-1; i++){
		if(cmp(mpt_Data[i].id,mpt_Data[i+1].id))
			min = mpt_Data[i].id;
		else
			min = mpt_Data[i+1].id;
	}
	return min;

}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::max() const
{

	if(mi_Length == 0)
		throw std::out_of_range("[max()]: Can not recover an element from an empty Dictionary")


	KeyComparator cmp;
	Key max;

	for(auto i(0); i!=mi_Length-1; i++){
		if(cmp(mpt_Data[i].id,mpt_Data[i+1].id))
			max = mpt_Data[i+1].id;
		else
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
	if(_search(x) == mi_Length)
		return false;

	KeyComparator cmp;
	//Define sucessor como o max do Dict
	Key sucessor = max();

	for(auto i(0); i<mi_Length; i++)
	{
		if(cmp(_x, mpt_Data[i].id) and cpm(mpt_Data[i].id, sucessor))
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
	if(_search(x) == mi_Length)
		return false;

	KeyComparator cmp;
	//Define predecessor como o max do Dict
	Key predecessor = min();

	for(auto i(0); i<mi_Length; i++)
	{
		if(cmp(mpt_Data[i].id, _x) and cpm( predecessor, mpt_Data[i].id))
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
	auto length = DAL<Key, Data, KeyComparator>::mi_Length
	auto left =0 , right = length-1;

	KeyComparator cmp;

	while(left <= right)
	{
		int middle = (left-right)/2;

		auto result = DAL<Key, Data, KeyComparator>::m_data[middle].id;

		if(not cmp(_x,result) and not cmp(result, _x))
			return middle;
		else if (cmp(_x, result))
			right = middle -1;
		else 
			left = middle+1;
	}

	return length;

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert(const Key & _newKey, const Data & _newInfo)
{
	auto &length = DAL<Key, Data, KeyComparator>::mi_Length;
	auto &data = DAL<Key, Data, KeyComparator>::mpt_Data;
	auto capacity = DAL<Key, Data, KeyComparator>::mi_Capacity;

	auto ads = _search(_newKey);

	//Dict is full
	if(length == capacity)
		return false;
	//The element is already in the Dict
	if(ads != length)
		return false;

	KeyComparator cmp;

	
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s)
{

}

template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::min() const
{

}

template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::max() const
{

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const
{

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const
{

}