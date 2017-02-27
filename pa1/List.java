//-----------------------------------------------------------------------------
//  Jerry Liu
//  jelliu ID:1410172
//  CMPS101
//  pa1
//  List.java
//  An ADT that uses nodes to create a list.
//-----------------------------------------------------------------------------

public class List {
	private class Node {
		// Fields
		int data;
		Node previous;
		Node next;

		// Constructor
		Node(int data) {
			this.data = data;
			next = null;
		}

		// toString(): overrides Object's toString() method
		public String toString() {
			return String.valueOf(data);
		}

		// equals(): overrides Object's equals() method
		public boolean equals(Object x) {
			boolean eq = false;
			Node that;
			if (x instanceof Node) {
				that = (Node) x;
				eq = (this.data == that.data);
			}
			return eq;
		}
	}

	// Fields
	private Node front;
	private Node back;
	private int length;
	private Node cursor;
	private int index;

	// Constructor
	// Creates a new empty list.
	List() {
		front = back = cursor = null;
		length = 0;
		index = -1;
	}

	// Access functions
	// Returns the number of elements in this List.
	int length() {
		return length;
	}

	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index() {
		return index;
	}

	// Returns front element. Pre: length()>0
	int front() {
		if (length > 0) {
			return front.data;
		}
		throw new RuntimeException("List Error: front() called on empty List");
	}

	// Returns back element. Pre: length()>0
	int back() {
		if (length > 0) {
			return back.data;
		}
		throw new RuntimeException("List Error: back() called on empty List");
	}

	// Returns cursor element. Pre: length()>0, index()>=0
	int get() {
		if (length > 0 && index() >= 0) {
			return cursor.data;
		}
		throw new RuntimeException("List Error: get() called on empty List");
	}

	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	boolean equals(List L) {
		if (length == L.length) {
			Node cur = front;
			L.moveFront();
			while (cur != null) {
				if (cur.data != L.get()){
					return false;
				}
				cur = cur.next;
				L.moveNext();
			}
			return true;
		}
		return false;
	}
	// Manipulation procedures

	// Resets this List to its original empty state.
	void clear() {
		front = back = cursor = null;
		length = 0;
		index = -1;
	}

	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront() {
		if (length > 0) {
			cursor = front;
			index = 0;
		}
	}

	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() {
		if (length > 0) {
			cursor = back;
			index = length -1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev() {
		if (cursor != null) {
			if (cursor != front) {
				cursor = cursor.previous;
				index--;
			} else {
				cursor = null;
				index = -1;
			}
		}
	}

	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (cursor != null) {
			if (cursor != back) {
				cursor = cursor.next;
				index++;
			} else {
				cursor = null;
				index = -1;
			}
		}
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data) {
		Node newNode = new Node(data);
		if (length == 0) {
			front = back = cursor = newNode;
			length = 1;
			index = 0;
		} else {
			newNode.next = front;
			front.previous = newNode;
			front = cursor = newNode;
			length++;
			index = 0;
		}
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data) {
		Node newNode = new Node(data);
		if (length == 0) {
			front = back = cursor = newNode;
			length = 1;
			index = 0;
		} else {
			newNode.previous = back;
			back.next = newNode;
			back = cursor = newNode;
			length++;
			index = length - 1;
		}

	}

	// Insert new element before cursor.
	// Pre: length()>0,index()>=0
	void insertBefore(int data) {
		if (length > 0 && index >= 0) {
			Node newNode = new Node(data);
			if (index != 0) {			
				cursor.previous.next = newNode;
				newNode.previous = cursor.previous;
				newNode.next = cursor;
				cursor.previous = newNode;
			} else {
				newNode.next = front;
				front.previous = newNode;
				front = newNode;
			}
			
			cursor = newNode;
			length++;
		} else {
			throw new RuntimeException("List Error: insertBefore() called on empty List");
		}
	}

	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0

	void insertAfter(int data) {
		if (length > 0 && index >= 0) {
			Node newNode = new Node(data);
			if (index != length -1) {
				cursor.next.previous = newNode;
				newNode.previous = cursor;
				newNode.next = cursor.next;
				cursor.next = newNode;
			} else {
				back.next = newNode;
				newNode.previous = back;
				back = newNode;
			}
			
			cursor = newNode;
			length++;
			index++;
		} else {
			throw new RuntimeException("List Error: insertAfter() called on empty List");
		}
	}

	// Deletes the front element. Pre: length()>0
	void deleteFront() {
		if (length > 0) {
			Node newFront = front.next;
			newFront.previous = null;
			front = newFront;
		} else {
			throw new RuntimeException("List Error: deleteFront() called on empty List");
		}
	}

	// Deletes the back element. Pre: length()>0
	void deleteBack() {
		if (length > 0) {
			Node newBack = back.previous;
			newBack.next = null;
			back = newBack;
		} else {
			throw new RuntimeException("List Error: deleteBack() called on empty List");
		}
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete() {
		if (length > 0 && index >= 0) {
			Node prev = cursor.previous;
			Node next = cursor.next;
			prev.next = next;
			length--;
			cursor = null;
			index = -1;
		} else {
			throw new RuntimeException("List Error: deleteBack() called on empty List");
		}
	}

	// Other methods
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString() {
		Node cur = front;
		String str = "";
		while (cur != null) {
			str = str + cur.data + " ";
			cur = cur.next;
		}
		return str;
	}

	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy() {
		List l = new List();
		Node cur = front;
		while (cur != null) {
			l.append(cur.data);
			cur = cur.next;
		}
		return l;
	}
}
