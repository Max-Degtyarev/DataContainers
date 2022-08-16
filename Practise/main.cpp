#include<iostream>
using namespace std;
using std::cout;


#define tab "\t"
#define delimiter "\n----------------------\n"

class List;

class Element
{
	int Data;
	Element* pNext;
	static int count;

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
		count++;
		cout << "ElementConstructor: " << this << endl;
	}

	~Element()
	{
		count--;
		cout << "ElementDestructor: " << this << endl;
	}

	friend class List;
	friend class Iterator;
	friend class Stack;
	friend List operator+(const List& left, const List& right);



};

int Element::count = 0;


class Iterator
{
	Element* Temp;

public:

	Iterator(Element* Temp = nullptr):Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;

	}
	~Iterator()
	{
		cout << endl;
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator == (const Iterator& other)const
	{
		return this->Temp == other.Temp;

	}
	
	bool operator != (const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}

	int& operator*()
	{
		return Temp->Data;
	}




};



class List
{
protected:
	Element* Head;
	unsigned int size;

public:


	Element* get_Head()const
	{
		return Head;
	}

	void set_Head(Element* Head)
	{
		this->Head = Head;
	}

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	List()
	{
		Head = nullptr;
		size = 0;
		cout << "ListConstructor: " << this << endl;
	}


	List(initializer_list<int> il) :List()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
		
	}


	List(int arr[], const int n)
	{
		Element* New = new Element(arr[0]);
		Head = New;
		Element* Temp = Head;
		//cout << sizeof(arr) / sizeof(arr[0]) << endl;
		for (int i = 1; i < n; i++)
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
		cout << "ValuesConstructor\t" << this << endl;

	}


	List(const List& other) : List()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;
		cout << "CopyConstructor\t" << this << endl;

	}


	/*List(const List& other)
	{
		this->Head = nullptr;
		Element* Temp = other.get_Head();
		while (Temp)
		{
			this->push_back(Temp->get_Data());
			Temp = Temp->get_pNext();
		}
		cout << "CopyConstructor\t" << this << endl;

	}*/
	
	List(List&& other):List()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor\t" << this << endl;

	}

	
	~List()
	{
		while (Head) pop_front();
		//clear();
		cout << "ListDestructor: " << this << endl;
	}



	//  Operators

	/*List& operator=(const List& other)
	{
		this->Head = nullptr;
		Element* Temp = other.get_Head();
		while (Temp)
		{
			this->push_back(Temp->get_Data());
			Temp = Temp->get_pNext();
		}
		cout << "CopyAssignment\t" << this << endl;
		return *this;
	}*/
	
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;

		}
		cout << "CopyAssignment\t" << this << endl;
		return *this;

	}

	List& operator=(List&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment\t" << this << endl;
		return *this;
	}

	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/

		Head = new Element(Data, Head);
		size++;


	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void pop_front()
	{
		Element* buffer = Head;
		Head = Head->pNext;
		delete buffer;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index > size)return;
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
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
		size--;
	}

	void print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	
	void clear()
	{
		while (Head)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}
	}

	friend List operator+(const List& left, const List& right);
	friend class Element;

};


List operator+(const List& left, const List& right)
{
	/*List list_buffer;
	Element* Temp = left.get_Head();
	Element* Temp_2 = right.get_Head();
	while (Temp)
	{
		list_buffer.push_back(Temp->get_Data());
		Temp = Temp->get_pNext();
	}

	while (Temp_2)
	{
		list_buffer.push_back(Temp_2->get_Data());
		Temp_2 = Temp_2->get_pNext();
	}
	return list_buffer;*/

	List cat = left;
	/*Element* Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator + " << endl;
	return cat;

}


class Stack :private List
{
public:

	unsigned int get_size()const
	{
		return size;
	}
	
	void push(int data)
	{
		List::push_front(data);
	}
	
	void pop()
	{
		List::pop_front();
	}

	const int& top()const
	{
		return Head->Data;
	}
	int& top()
	{
		return Head->Data;
	}

	void print()const
	{
		List::print();

	}



};


//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY
//#define INITIALIZING


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	List list;
	int n;
	cout << "Введите размер списка: "; cin >> n;
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

	/*int arr[] = { 3, 5, 8, 13, 21 };
	List list_4(arr, sizeof(arr) / sizeof(arr[0]));
	list_4.print();


	List list_5 = { 2, 8, 14, 25, 32 };
	list_5.print();*/

	cout << delimiter << endl;
	List list_6 = list;
	list_6.print();
	cout << delimiter << endl;

	List list_7;
	list_7 = list_3;
	list_7.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	cout << delimiter << endl;

	List list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;

	List list3;
	list3 = list1 + list2;
	list3.print();

	cout << delimiter << endl;


#endif // COUNT_CHECK


#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	// range-based for
	// цикл for на основе диапазона, цикл for для контейнеров
	for (int i : arr)
		cout << i << tab;
	cout << endl;
	// Итератора i последовательно принимает значение каждого элемента массива

#endif // RANGE_BASED_ARRAY


#ifdef INITIALIZING
	List list = { 3, 5, 8, 13, 21, 56, 78, 85 };
	//list.print();

	for (int i : list)
		cout << i << tab;
	cout << endl;

	/*for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;*/


#endif // INITIALIZING

	Stack stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	cout << stack.get_size() << endl;
	stack.print();
	for (; stack.get_size(); stack.pop())
		cout << stack.top() << endl;
	stack.print();



}