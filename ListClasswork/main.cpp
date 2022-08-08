#include <iostream>
#include<exception>
using namespace std;
using std::cout;
using std::endl;




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

	class Iterator
	{
		Element* Temp;

	public:

		Iterator(Element* Temp): Temp(Temp)
		{
			cout << "ItConstructor\t" << this << endl;
				
		}

		~Iterator()
		{
			cout << "ItDestructor\t" << this << endl;

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

		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;

		}

		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
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

	class ReverseIterator
	{
		Element* Temp;

	public:

		ReverseIterator(Element* Temp) : Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;


		}
		
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;


		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;

		}
		
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;

		}

		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;

		}

		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;

		}

		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		
		bool operator!=(const ReverseIterator& other)const
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



	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}


	ReverseIterator rbegin()
	{
		return Tail;
	}

	ReverseIterator rend()
	{
		return nullptr;
	}




	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstructor\t" << this << endl;
	}

	List(const initializer_list<int>& il) :List()
	{
		/*for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);*/

		for (int i : il)push_back(i);

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
		size++;
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

	void insert(int data, int index)
	{
		if (index > size)throw out_of_range("Error: Out of range exception in insert() function");
			//throw exception("Error: Out of range");
		if (index == 0)return push_front(data);
		if (index == size)return push_back(data);

		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(data, Temp, Temp->pPrev);
		size++;
	}

	void erase(int index)
	{
		if (index >= size)throw out_of_range("Error: Out of range exception in erase() function");
		if (index == 0)return pop_front();
		
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
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
		cout << "Количество элементов " << size << endl;
	}

	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов " << size << endl;
	}
		




};



//#define BASE_CHECK




void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	try
	{
		list.erase(index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
#endif // BASE_CHECK

	List list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
		cout << i << tab;
	cout << endl;

	List::ReverseIterator rend = list.rend();
	for (List::ReverseIterator rit = list.rbegin(); rit != rend; ++rit)
	{
		cout << *rit << tab;

	}
	cout << endl;



}