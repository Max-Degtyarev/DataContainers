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

	class ConstBaseIterator
	{

	protected:
		Element* Temp;

	public:

		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "CBItConstructor:\t" << this << endl;
		}
		~ConstBaseIterator()
		{
			cout << "CBItDestructor:\t" << this << endl;
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;

		}

		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->data;

		}

	};



public:

	class ConstIterator:public ConstBaseIterator
	{
		
	public:

		ConstIterator(Element* Temp): ConstBaseIterator(Temp)
		{
			cout << "CItConstructor\t" << this << endl;
				
		}

		~ConstIterator()
		{
			cout << "CItDestructor\t" << this << endl;

		}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;

		}

		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;

		}

		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		
	};


	class ConstReverseIterator:public ConstBaseIterator
	{
		

	public:

		ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp)
		{
			cout << "CRItConstructor:\t" << this << endl;


		}
		
		~ConstReverseIterator()
		{
			cout << "CRItDestructor:\t" << this << endl;

		}

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;

		}
		
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;

		}

		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;

		}

		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;

		}
				

	};

	class Iterator : public ConstIterator
	{

	public:

		Iterator(Element* Temp = nullptr):ConstIterator(Temp){}

		int& operator*()
		{
			return Temp->data;
		}

	};

	
	class ReverseIterator :public ConstReverseIterator
	{
		
	public:

		ReverseIterator(Element* Temp = nullptr):ConstReverseIterator(Temp){}

		int& operator*()
		{
			return Temp->data;
		}

	};






	ConstIterator cbegin()const
	{
		return Head;
	}

	ConstIterator cend()const
	{
		return nullptr;
	}


	ConstReverseIterator crbegin()
	{
		return Tail;
	}

	ConstReverseIterator crend()
	{
		return nullptr;
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
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstructor\t" << this << endl;
	}

	List(const initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);

		//for (int i : il)push_back(i);

	}

	List(const List& other): List()
	{
		for (ConstIterator it = other.cbegin(); it != other.cend(); ++it)
		{
			push_back(*it);

		}

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



List operator+(const List& left, const List& right)
{

	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		cat.push_back(*it);
		//(*it) *= 100;

	}
	return cat;
}



//#define BASE_CHECK
//#define ITERATORS_CHECK_1
#define ITERATORS_CHECK_2



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

#ifdef ITERATORS_CHECK_1
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
#endif // ITERATORS_CHECK_1

	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	//for (int i : list1)cout << i << tab; cout << endl;
	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;


	


}