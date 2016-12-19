template<typename T> LinkedList<T>::LinkedList(void)
{
	head = tail = NULL;
}

template<typename T> LinkedList<T>::~LinkedList(void)
{
	tail = NULL;
	delete head;
	head = NULL;
}

template<typename T> void LinkedList<T>::append(const T& item)
{
	if (!head)
	{
		head = new Node<T>(item);
		tail = head;
	}
	else
	{
		Node<T>* temp = new Node<T>(item);
		temp->previous(tail);
		tail->next(temp);
		tail = temp;
	}
}

template<typename T> void LinkedList<T>::prepend(const T& item)
{
	if (!head)
	{
		 head = new Node<T>(item);
		 tail = head;
	}
	else
	{
		Node<T>* temp = new Node<T>(item);
		head->previous(temp);
		temp->next(head);
		head = temp;
	}
}

template<typename T> void LinkedList<T>::erase(const LinkedList<T>::iterator& iter)
{
	if (!iter.isValid())
	{
		throw "error, invalid iterator";
	}

	Node<T>* node = iter.node();
	Node<T>* tempPrev = node->previous();
	node->next()->previous(tempPrev);
	tempPrev->next(node->next());
	node->next(NULL);

	delete node;
	iter.invalidate();
}

template<typename T> void LinkedList<T>::erase(const LinkedList<T>::iterator& iter, const LinkedList<T>::iterator& endIter)
{
	LinkedList<T>::iterator nextIter;
	LinkedList<T>::iterator internalIter = iter;
	for (nextIter = iter; nextIter != endIter;)
	{
		internalIter = nextIter;
		nextIter++;
		erase(internalIter);
	}
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::begin(void)
{
	return LinkedList<T>::iterator(head);
}
template<typename T> typename LinkedList<T>::iterator LinkedList<T>::end(void)
{
	return LinkedList<T>::iterator(NULL);
}

template<typename T> LinkedList<T>::iterator::iterator(LinkedList<T>::Node<T>* initial)
{
	mCursor = initial;
	mValid = true;
}
template<typename T> LinkedList<T>::iterator::~iterator(void)
{
	mCursor = NULL;
	mValid = false;
}

template<typename T> LinkedList<T>::Node<T>* LinkedList<T>::iterator::node(void) const
{
	return mCursor;
}

template<typename T> T& LinkedList<T>::iterator::operator*(void)
{
	return mCursor->payload();
}
template<typename T> const T& LinkedList<T>::iterator::operator*(void) const
{
	return mCursor->payload();
}
template<typename T> T& LinkedList<T>::iterator::operator->(void)
{
	return mCursor->payload();
}
template<typename T> const T& LinkedList<T>::iterator::operator->(void) const
{
	return mCursor->payload();
}

template<typename T> bool LinkedList<T>::iterator::isValid(void) const
{
	return mValid;
}
template<typename T> void LinkedList<T>::iterator::invalidate(void) const
{
	mValid = false;
}


template<typename T> bool LinkedList<T>::iterator::operator==(const LinkedList<T>::iterator& other) const
{
	return other.mCursor == mCursor;
}
template<typename T> bool LinkedList<T>::iterator::operator!=(const LinkedList<T>::iterator& other) const
{
	return other.mCursor != mCursor;
}


template<typename T> typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++(void)
{
	return (*this)++;
}
template<typename T> typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator++(int)
{
	mCursor = mCursor->next();
	return *this;
}

template<typename T> typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator--(void)
{
	return (*this)--;
}
template<typename T> typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator--(int)
{
	mCursor = mCursor->previous();
	return *this;
}

template<typename T> typename LinkedList<T>::iterator& LinkedList<T>::iterator::operator=(const LinkedList<T>::iterator& src)
{
	if (*this == src)
	{
		return *this;
	}

	mValid = src.mValid;
	mCursor = src.mCursor;
	return *this;
}

template<typename T> template<typename _T> LinkedList<T>::Node<_T>::Node(const _T& item)
{
	mPayload = item;
	mNext = mPrevious = NULL;
}
template<typename T> template<typename _T> LinkedList<T>::Node<_T>::~Node(void)
{
	mPrevious = NULL;
	delete mNext;
	mNext = NULL;
}

template<typename T> template<typename _T> void LinkedList<T>::Node<_T>::next(LinkedList<T>::Node<_T>* const n)
{
	mNext = n;
}
template<typename T> template<typename _T> LinkedList<T>::Node<_T>* LinkedList<T>::Node<_T>::next(void) const
{
	return mNext;
}

template<typename T> template<typename _T> void LinkedList<T>::Node<_T>::previous(LinkedList<T>::Node<_T>* const p)
{
	mPrevious = p;
}
template<typename T> template<typename _T> LinkedList<T>::Node<_T>* LinkedList<T>::Node<_T>::previous(void) const
{
	return mPrevious;
}

template<typename T> template<typename _T> _T& LinkedList<T>::Node<_T>::payload(void)
{
	return mPayload;
}
template<typename T> template<typename _T> const _T& LinkedList<T>::Node<_T>::payload(void) const
{
	return mPayload;
}
