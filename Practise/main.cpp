#include<iostream>
using namespace std;


#define tab "\t"

class Element
{
	int Data;
	Element* pNext;

public:

	Element* get_pNext()const
	{
		return pNext;
	}

	int get_Data()const
	{
		return Data;
	}

	void set_pNext(Element* pNext)
	{
		this->pNext = pNext;

	}

	void set_Data(int Data)
	{
		this->Data = Data;
	}

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "ElementConstructor: " << this << endl;
	}

	~Element()
	{
		cout << "ElementDestructor: " << this << endl;
	}

	friend class List;

};


class List
{
	Element* Head;

public:


	Element* get_Head()const
	{
		return Head;
	}

	void set_Head(Element* Head)
	{
		this->Head = Head;
	}

	List()
	{
		Head = nullptr;
		cout << "ListConstructor: " << this << endl;
	}

	List(int arr[])
	{
		Element* New = new Element(arr[0]);
		Head = New;
		Element* Temp = Head;
		//cout << sizeof(arr) / sizeof(arr[0]) << endl;
		for (int i = 1; i < 5; i++)
		{
			Element* New = new Element(arr[i]);
			Temp->pNext = New;
			Temp = Temp->pNext;
		}


	}

	List(int val1, int val2, int val3, int val4, int val5)
	{
		int arr[] = { val1, val2, val3, val4, val5 };
		Element* New = new Element(arr[0]);
		Head = New;
		Element* Temp = Head;
		for (int i = 1; i < 5; i++)
		{
			Element* New = new Element(arr[i]);
			Temp->pNext = New;
			Temp = Temp->pNext;
		}


	}

	List(const List& other)
	{
		this->Head = nullptr;
		Element* Temp = other.get_Head();
		while (Temp)
		{
			this->push_front(Temp->get_Data());
			Temp = Temp->get_pNext();
		}
		cout << "CopyConstructor\t" << this << endl;

	}
	
	List(List&& other)
	{
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "MoveConstructor\t" << this << endl;

	}

	
	~List()
	{
		cout << "ListDestructor: " << this << endl;
	}


	List& operator=(const List& other)
	{
		this->Head = nullptr;
		Element* Temp = other.get_Head();
		while (Temp)
		{
			this->push_front(Temp->get_Data());
			Temp = Temp->get_pNext();
		}
		cout << "CopyAssignment\t" << this << endl;
		return *this;
	}
	
	List& operator=(List&& other)
	{
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "MoveAssignment\t" << this << endl;
		return *this;
	}









	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;

	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;

	}

	void pop_front()
	{
		Element* buffer = Head;
		Head = Head->pNext;
		delete buffer;

	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;

	}


	void insert(int Data, int index)
	{
		if (index == 0)
		{
			return push_front(Data);
		}
		else
		{
			Element* New = new Element(Data);
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			New->pNext = Temp->pNext;
			Temp->pNext = New;
		}

	}

	void erase(int index)
	{
		if (index == 0)
		{
			return pop_front();
		}
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}

			Element* erased = Temp->pNext;
			Temp->pNext = Temp->pNext->pNext;
			delete erased;
		}

	}

	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << endl;
	}

	void del()
	{
		while (Head)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}
	}

		



	

};


//Должен в обратном порядке выводить список

List& operator+(const List& left, const List& right)
{
	List list_buffer;
	Element* Temp = left.get_Head();
	Element* Temp_2 = right.get_Head();
	while (Temp)
	{
		list_buffer.push_front(Temp->get_Data());
		Temp = Temp->get_pNext();
	}

	while (Temp_2)
	{
		list_buffer.push_front(Temp_2->get_Data());
		Temp_2 = Temp_2->get_pNext();
	}
	return list_buffer;

	/*Element* Temp_2 = list_buffer.get_Head();
	while (Temp_2->get_pNext())Temp_2 = Temp_2->get_pNext();
	Temp_2->set_pNext(right.get_Head());
	return list_buffer;*/


}





void main()
{
	setlocale(LC_ALL, "");

	List list;
	int n;
	cout << "Введите размер списка :"; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int value, index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс элемента для добавления: "; cin >> index;
	list.insert(value, index);
	list.print();
	int index_2;
	cout << "Введите индекс элемента для удаления: "; cin >> index_2;
	list.erase(index_2);
	list.print();



	List list_2;
	for (int i = 0; i < n; i++)
	{
		list_2.push_back(rand() % 50);
	}
	list_2.print();
	cout << endl;

	List list_3 = list + list_2;
	cout << "Конкатенация списков: " << endl;
	list_3.print();

	cout << endl;
	list.print();
	cout << endl;
	list_2.print();


	int arr[] = { 3, 5, 8, 13, 21 };
	List list_4 = (arr);
	list_4.print();


	List list_5 = { 2, 8, 14, 25, 32 };
	list_5.print();

	List list_6 = list;
	list_6.print();

	List list_7;
	list_7 = list_5;
	list_7.print();




	list.del();
	list_2.del();
	list_3.del();
	list_4.del();
	list_5.del();
	list_6.del();
	list_7.del();



}