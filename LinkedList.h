#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include <cstdlib>

template<typename T>
class LinkedList
{
private:
	/**
	 * Forward declaration of the Node sub-class, since the iterator will need to
	 * know about it.
	 */
	template<typename _T = T> class Node;

public:
	/**
	 * List constructor. Sets up a blank (empty) list.
	 */
	LinkedList(void);
	/**
	 * List destructor. Cleans up all the nodes and items in the list. Leaving it
	 * empty.
	 */
	~LinkedList(void);

	/**
	 * Append an item to the end of the list.
	 *
	 * @param item The item to be added to the list.
	 */
	void append(const T& item);
	/**
	 * Prepend an item to the beginning of the list.
	 *
	 * @param item The item to be added to the list.
	 */
	void prepend(const T& item);

	/**
	 * A list iterator class. It is capable of moving forwards and backwards
	 * through the items in the list and being used to access individual items.
	 * Further, it is also used to remove 1 or more items from the list.
	 */
	class iterator
	{
	public:
		/**
		 * Constructor.
		 *
		 * @param initial The initial node for the iterator to point at. This is
		 *     defaulted to NULL.
		 */
		iterator(Node<T>* initial = NULL);
		/**
		 * Destructor.
		 */
		~iterator(void);

		/**
		 * Access the item in the list.
		 *
		 * NOTE: This currently doesn't actually verify that the iterator is valid
		 *       before attempting to access the item it contains. That is left as an
		 *       excercise for the user.
		 *
		 * @returns The item in the list that the iterator is currently on.
		 */
		T& operator*(void);
		const T& operator*(void) const;
		T& operator->(void);
		const T& operator->(void) const;

		/**
		 * Check if two iterators are the same.
		 *
		 * @param other The other iterator to compare against.
		 * @returns True if the iterators are the same, false otherwise.
		 */
		bool operator==(const LinkedList<T>::iterator& other) const;
		/**
		 * Check if two iterators are not the same.
		 *
		 * @param other The other iterator to compare against.
		 * @returns True if the iterators are different, false otherwise.
		 */
		bool operator!=(const LinkedList<T>::iterator& other) const;
	
		/**
		 * Assign this iterator to a source iterator.
		 *
		 * @param src The source iterator.
		 * @returns This iterator after all modifications have beeen made to it.
		 */
		LinkedList<T>::iterator& operator=(const LinkedList<T>::iterator& src);

		/**
		 * Move the iterator forward.
		 *
		 * @returns This iterator after moving.
		 */
		LinkedList<T>::iterator& operator++(void);
		LinkedList<T>::iterator& operator++(int);

		/**
		 * Move the iterator backward.
		 *
		 * @returns This iterator after moving.
		 */
		LinkedList<T>::iterator& operator--(void);
		LinkedList<T>::iterator& operator--(int);
	private:
		/**
		 * Explicitly tell the compiler that LinkedList<T> is allowed to access an
		 * iterator's private members.
		 */
		friend class LinkedList<T>;
		/**
		 * Retrieve a raw node from an iterator.
		 *
		 * @returns The node that contains the item that the iterator is on.
		 */
		Node<T>* node(void) const;

		/**
		 * Determine if the iterator is valid or not.
		 *
		 * NOTE: This is the same as just checking `mValid`, but provides a function
		 *       to call instead of simply looking at the raw member variables.
		 *
		 * @returns True if the iterator is valid, false otherwise.
		 */
		bool isValid(void) const;
		/**
		 * Mark this iterator as invalid. If an iterator is not valid, it should
		 * likely throw when a user attempts to access or modify it (THIS IS LEFT UP
		 * TO THE USER!).
		 */
		void invalidate(void) const;

		mutable bool mValid;
		Node<T>* mCursor;
	};

	/**
	 * Erase a single item from the list.
	 *
	 * @param iter An iterator on the item that you wish to have removed from the
	 *     list.
	 */
	void erase(const LinkedList<T>::iterator& iter);
	/**
	 * Erase a sequence of items from the list.
	 *
	 * @param iter The first item to be removed from the list.
	 * @param endIter The iterator one past the last item you wish to have removed
	 *     from the list.
	 */
	void erase(const LinkedList<T>::iterator& iter, const LinkedList<T>::iterator& endIter);

	/**
	 * Retrieve an iterator at the beginning of the list.
	 */
	LinkedList<T>::iterator begin(void);
	/**
	 * Retrieve an iterator at the end of the list.
	 */
	LinkedList<T>::iterator end(void);
	//LinkedList<T>::const_iterator begin(void) const;
	//LinkedList<T>::const_iterator end(void) const;


	//typedef LinkedList<const T>::iterator const_iterator;
private:

	/**
	 * A Node class that is private to the LinkedList, since in theory nobody
	 * outside of the list should need to know, or modify raw Nodes themselves.
	 */
	template<typename _T>
	class Node
	{
	public:
		/**
		 * Construct a node.
		 *
		 * @param item The payload the Node contains.
		 */
		Node(const _T& item);
		/**
		 * Destructor. This function has the added side-effect that it removes all
		 * Nodes further down the chain from it!
		 */
		~Node(void);

		/**
		 * Retrieve the next Node, or set the next Node.
		 */
		void next(Node<_T>* const n);
		Node<_T>* next(void) const;

		/**
		 * Retrieve the previous Node, or set the previous Node.
		 */
		void previous(Node<_T>* const p);
		Node<_T>* previous(void) const;

		/**
		 * Retrieve the Node's payload.
		 */
		_T& payload(void);
		const _T& payload(void) const;

	private:
		_T mPayload;
		Node<_T>* mPrevious;
		Node<_T>* mNext;
	};

	Node<T>* head;
	Node<T>* tail;
};

#include "LinkedList.ipp"

#endif
