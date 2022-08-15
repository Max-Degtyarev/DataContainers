#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;


#define tab "\t"
#define delimiter "\n-----------------------------------------------------------\n"

class List;

class Element
{
	int data;
	Element* pNext;
	Element* pPrev;

public:

	Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :data(data), pNext(pNext), pPrev(pPrev)
	{
#ifdef DEBUG
		cout << "ElementConstructor:\t" << this << endl;
#endif // DEBUG

	}

	~Element()
	{
#ifdef DEBUG
		cout << "ElementDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class List;
	friend class Iterator;
	friend List operator+(const List& left, const List& right);
	friend class Stack;
};



class Iterator
{
	Element* Temp;

public:

	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor\t" << this << endl;
	}
	~Iterator()
	{
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

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->data;
	}
	int& operator*()
	{
		return Temp->data;
	}



};




class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;

public:

	unsigned int get_size()const
	{
		return size;
	}


	Iterator begin()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}

	Iterator end()const
	{
		return nullptr;
	}
	Iterator end()
	{
		return nullptr;
	}

	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "ListConstructor:\t" << this << endl;
	}

	template<typename T>
	List(initializer_list<T> il) : List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	List(const List& other) :List()
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor\t\t" << this << endl;
	}


	List(List&& other) :List()
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = other.Tail = nullptr;
		other.size = 0;
		cout << "MoveConstructor:\t" << this << endl;

	}




	~List()
	{
		while (Head)pop_front();
		//while (Tail)pop_back();
		cout << "ListDestructor:\t\t" << this << endl;
	}


	void push_front(int data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Element* New = new Element(data);
			Head = Tail = New;
			size++;
		}
		/*else if (Head->pNext == nullptr)
		{
			Element* New = new Element(data, Head);
			Head->pPrev = Head = New;
			Tail = New->pNext;
			size++;
		}*/
		else
		{
			Element* New = new Element(data, Head);
			Head = Head->pPrev = New;
			//Head = New;
			size++;
		}
	}

	void push_back(int data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(data);
		else if (Head->pNext == nullptr)
		{
			Element* New = new Element(data, nullptr, Head);
			Head->pNext = Tail = New;
			//Tail = New;
			size++;
		}
		else
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext)Temp = Temp->pNext;
			Element* New = new Element(data, nullptr, Temp->pNext);
			Temp->pNext->pNext = Tail = New;
			//Tail = New;
			size++;
		}

	}

	void pop_front()
	{
		if (Head->pNext == nullptr && Tail->pPrev == nullptr)
		{
			Tail = nullptr;
			delete Head;
			Head = nullptr;
			size--;
		}
		else
		{
			Element* buffer = Head;
			Head->pNext->pPrev = nullptr;
			Head = Head->pNext;
			delete buffer;
			size--;
		}
	}


	void pop_back()
	{
		
		if (Head->pNext == nullptr)return pop_front();
		else
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext)Temp = Temp->pNext;
			cout << "Пассажир " << Temp->data << endl;
			Tail = Temp->pNext->pPrev;
			delete Temp->pNext;
			Temp->pNext = nullptr;
			size--;
		}
	}


	void insert(int data, int index)
	{
		if (index == 0)return push_front(data);
		else if (index == size)return push_back(data);
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
			{
				Temp = Temp->pNext;
			}
			Element* New = new Element(data, Temp->pNext);
			New->pPrev = Temp->pNext->pPrev;
			Temp->pNext->pPrev = New;
			Temp->pNext = New;
			size++;

		}
	}


	void erase(int index)
	{
		if (index == 0)return pop_front();
		else if (index == size - 1)return pop_back();
		else if (index < 0 || index > size - 1)return;
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
			Element* buffer = Temp;
			Temp->pPrev->pNext = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			delete buffer;
			size--;
		}
	}



	List& operator=(const List& other)
	{
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment\t\t" << this << endl;
		return *this;

	}

	List& operator=(List&& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = other.Tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment\t\t" << this << endl;
		return *this;

	}


	void print()const
	{
		cout << "Голова: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->pPrev << tab << Temp->data << tab << Temp->pNext << endl;
		}
		cout << "Хвост: " << Tail << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}

	friend List operator+(const List& left, const List& right);
	friend class Stack;

};


class Stack: public List
{
	Stack* top;
	Stack* bottom;

public:

	Stack() :List()
	{
		top = nullptr;
		bottom = nullptr;
	}
	
	~Stack(){}


	void get_out()
	{
		cout << "Пассажир " << Tail->data << endl;
		while(Head)this->pop_back();

	}

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << "Пассажир " << Temp->data << endl;
		}
		
	}







};




List operator+(const List& left, const List& right)
{
	List cat = left;
	/*Element* Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->data);
		Temp = Temp->pNext;
	}*/
	for (int i : right)cat.push_back(i);
	//for (Iterator it = right.Head; it != nullptr; ++it)cat.push_back(*it);
	return cat;

}


//#define HOME_WORK_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef HOME_WORK_CHECK
	List list;
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.print();


	cout << delimiter;
	list.pop_front();
	list.print();

	cout << delimiter;
	list.pop_back();
	list.print();

	cout << delimiter;
	int m;
	int index;
	cout << "Введите добавляемое значение: "; cin >> m;
	cout << "Введите индекс для вставки значения: ";
	do
	{
		cin >> index;
		if (index > list.get_size() || index < 0)
			cout << "Индекс должен быть в диапазоне от 0 до " << list.get_size() << endl;

	} while (index > list.get_size() || index < 0);
	list.insert(m, index);
	list.print();


	cout << delimiter;
	int index2;
	cout << "Введте индекс элемента для удаления (в диапазоне от 0 до " << list.get_size() - 1 << "):"; cin >> index2;
	list.erase(index2);
	list.print();


	cout << delimiter;
	List list2 = list;
	list2.print();


	cout << delimiter;
	List list3;
	list3 = list2;
	list3.print();


	cout << delimiter;
	List list4 = list + list2;
	list4.print();

	cout << delimiter;
	List list5 = { 5, 6, 8, 12, 23 };
	list5.print();

	cout << delimiter;
	List list6;
	list6 = list5 + list4;
	list6.print();


	cout << delimiter;
	for (int i : list5)
		cout << i << tab;
	cout << endl;


	cout << delimiter;
#endif // HOME_WORK_CHECK

	//List list = { 3,5,8,13,21 };
	////for (int i : list)cout << i << "\t"; cout << endl;
	//list.print();



	Stack stack1;
	int n1, n2, n3;
	cout << "Введите количество людей на первой остановке: "; cin >> n1;
	for (int i = 0; i < n1; i++)
	{
		stack1.push_back(i + 1);

	}
	stack1.print();

	cout << "Введите количество людей на второй остановке: "; cin >> n2;
	for (int i = 0; i < n2; i++)
	{
		stack1.push_back(i + (n1 + 1));

	}
	stack1.print();

	cout << "Введите количество людей на третьей остановке: "; cin >> n3;
	for (int i = 0; i < n3; i++)
	{
		stack1.push_back(i + (n1 + n2 + 1));

	}
	stack1.print();

	cout << "Выход пассажиров на конечной остановке: " << endl;
	stack1.get_out();








}



