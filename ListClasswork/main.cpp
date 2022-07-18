#include <iostream>
using namespace std;


#define tab "\t"
#define delimiter "\n------------------------------\n"


class List
{
	class Element
	{
		int data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :data(data), pNext(pNext), pPrev(pPrev)
		{
			cout << "ElementConstructor\t" << this << endl;
		}
		~Element()
		{
			cout << "ElementDestructor\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	//Element* Head;
	//Element* Tail;
	unsigned int size;


public:

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstructor\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "ListDestructor\t" << this << endl;
	}

	//Adding Elements

	void push_front(int data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(data);
		}
		else
		{
			Head = Head->pPrev = new Element(data, Head);
		}
		size++;

	}


	void push_back(int data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(data);
		}
		else
		{
			Tail = Tail->pNext = new Element(data, nullptr, Tail);
		}
	}


	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr);
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}

	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}







	// Methods

	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� " << size << endl;
	}

	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� " << size << endl;
	}
		

};





void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();




}