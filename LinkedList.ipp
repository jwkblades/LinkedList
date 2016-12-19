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
		head = new Node(item);
		tail = head;
	}
	else
	{
		Node* temp = new Node(item);
		temp->previous(tail);
		tail->next(temp);
		tail = temp;
	}
}

template<typename T> void LinkedList<T>::prepend(const T& item)
{
	if (!head)
	{
		 head = new Node(item);
		 tail = head;
	}
	else
	{
		Node* temp = new Node(item);
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

	Node* node = iter.node();
	Node* tempPrev = node->previous();
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

template<typename T> LinkedList<T>::iterator::iterator(LinkedList<T>::Node* initial)
{
	mCursor = initial;
	mValid = true;
}
template<typename T> LinkedList<T>::iterator::~iterator(void)
{
	mCursor = NULL;
	mValid = false;
}

template<typename T> typename LinkedList<T>::Node* LinkedList<T>::iterator::node(void) const
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

template<typename T> LinkedList<T>::Node::Node(const T& item)
{
	mPayload = item;
	mNext = mPrevious = NULL;
}
template<typename T> LinkedList<T>::Node::~Node(void)
{
	mPrevious = NULL;
	delete mNext;
	mNext = NULL;
}

template<typename T>  void LinkedList<T>::Node::next(LinkedList<T>::Node* const n)
{
	mNext = n;
}
template<typename T> typename LinkedList<T>::Node* LinkedList<T>::Node::next(void) const
{
	return mNext;
}

template<typename T>  void LinkedList<T>::Node::previous(LinkedList<T>::Node* const p)
{
	mPrevious = p;
}
template<typename T> typename LinkedList<T>::Node* LinkedList<T>::Node::previous(void) const
{
	return mPrevious;
}

template<typename T>  T& LinkedList<T>::Node::payload(void)
{
	return mPayload;
}
template<typename T>  const T& LinkedList<T>::Node::payload(void) const
{
	return mPayload;
}
