#include <iostream>
using namespace std;
//The node data type

template<typename T>
class node
{
public:
	T data;
	node* next;

	//Constructors

	node()
	{
		this->next = NULL;
	}

	node(T data)
	{
		this->data = data;
		this->next = NULL;
	}

};



//Linked List class to manage member functions and store head

template<typename T>
class linkedList
{
public:
	node<T>* head;
	node<T>* tail;

	//Member Functions

	void addFront(T data)
	{
		if (head == NULL)
		{
			node <T>* temp = new node<T>(data);
			head = temp;
			tail = head;
			return;
		}

		node<T>* temp = new node<T>(data);
		temp->next = head;
		head = temp;
	}

	void addBack(T data)
	{
		if (head == NULL)
		{
			head = new node<T>(data);
			tail = head;
		}

		else
		{
			tail->next = new node<T>(data);
			tail = tail->next;
		}
	}

	//Print function
	void print()
	{
		node<T>* temp = head;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	T getLast()
	{
		return tail->data;
	}

	//Function to delete at a given position
	void deleteAt(int n)
	{
		node <T>* current = head;
		node <T>* previous = NULL;

		if (n == 0)
		{
			head = head->next;
			delete current;
			return;
		}


		previous = current;
		current = current->next;

		int i = 1;
		while (current != tail)
		{
			if (i == n)
			{
				previous->next = current->next;
				delete current;
				return;
			}
			previous = current;
			current = current->next;
			i++;
		}

		if (i == n)
		{
			delete current;
			tail = previous;
			tail->next = NULL;
			return;
		}


		cout << "Element to delete is out of bounds\n";
		return;


	}

	//Function to find mid point
	node <T>* midPoint()
	{
		node <T>* slow = head;
		node <T>* fast = head->next;

		while (fast != NULL && fast->next != NULL)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}

	T topElement()
	{
		return tail->data;
	}


	//Function to get the size of LL
	int size()
	{
		int size = 0;
		node<T>* temp = head;
		while (temp != NULL)
		{
			temp = temp->next;
			size++;
		}
		return size;
	}


	//Constructor
	linkedList(T data)
	{
		this->head->data = data;
		tail = head;
	}

	linkedList()
	{
		this->head = NULL;
		tail = head;
	}

};