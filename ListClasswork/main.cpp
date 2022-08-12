﻿#include <iostream>
#include<exception>
using namespace std;
using std::cout;
using std::endl;



#define tab "\t"
#define delimiter "\n------------------------------\n"

template<typename T>
class List
{

	class Element
	{
		T data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();

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

		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other)const;

		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;

	};



public:

	class ConstIterator:public ConstBaseIterator
	{
		
	public:

		ConstIterator(Element* Temp);

		~ConstIterator();

		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);

		
	};


	class ConstReverseIterator:public ConstBaseIterator
	{
		

	public:

		ConstReverseIterator(Element* Temp);
		
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		
		ConstReverseIterator operator++(int);

		ConstReverseIterator& operator--();

		ConstReverseIterator operator--(int);
				

	};

	class Iterator : public ConstIterator
	{

	public:

		Iterator(Element* Temp = nullptr):ConstIterator(Temp){}
		~Iterator(){}

		T& operator*();

	};

	
	class ReverseIterator :public ConstReverseIterator
	{
		
	public:

		ReverseIterator(Element* Temp = nullptr):ConstReverseIterator(Temp){}
		~ReverseIterator(){}

		T& operator*();

	};




	ConstIterator cbegin()const;

	ConstIterator cend()const;


	ConstReverseIterator crbegin()const;

	ConstReverseIterator crend()const;

	Iterator begin();

	Iterator end();

	ReverseIterator rbegin();

	ReverseIterator rend();


	List();

	List(const initializer_list<T>& il);

	List(const List<T>& other);

	List(List<T>&& other);

	~List();

	// Operators

	List<T>& operator=(const List<T>& other);

	List<T>& operator=(List<T>&& other)noexcept;


	//Adding Elements

	void push_front(T data);


	void push_back(T data);


	void pop_front();

	void pop_back();

	void insert(T data, int index);

	void erase(int index);


	// Methods

	void print()const;

	void reverse_print()const;
		


};


//////////////////////////////////////////////////////////////////
//////////////      Element             //////////////////////
//////////////////////////////////////////////////////////////////


template<typename T>
List<T>::Element::Element(T data, Element * pNext, Element * pPrev) :data(data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "ElementConstructor\t" << this << endl;
#endif // DEBUG

}

template<typename T>
List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "ElementDestructor\t" << this << endl;
#endif // DEBUG

}




//////////////////////////////////////////////////////////////////
//////////////      ConstBaseIterator              //////////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp)
{
#ifdef DEBUG
	cout << "CBItConstructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "CBItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;

}

template<typename T>
bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>
const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->data;

}





//////////////////////////////////////////////////////////////////
//////////////      ConstIterator              //////////////////////
//////////////////////////////////////////////////////////////////


template <typename T>
List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CItConstructor\t" << this << endl;
#endif // DEBUG


}

template <typename T>
List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CItDestructor\t" << this << endl;
#endif // DEBUG
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;

}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}


template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;

}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}





//////////////////////////////////////////////////////////////////
//////////////      ConstReversIterator              //////////////////////
//////////////////////////////////////////////////////////////////


template<typename T>
List<T>::ConstReverseIterator::ConstReverseIterator(Element * Temp) : ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T>
List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "CRItDestructor:\t" << this << endl;
#endif // DEBUG

}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;

}

template <typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;

}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;

}

template<typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;

}


//////////////////////////////////////////////////////////////////
//////////////      Iterator & ReverseIterator    //////////////////////
//////////////////////////////////////////////////////////////////

template<typename T>
T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->data;
}

template<typename T>
T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->data;
}




//////////////////////////////////////////////////////////////////
//////////////       List             //////////////////////
//////////////////////////////////////////////////////////////////


template<typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}

template<typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template<typename T>typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}

template<typename T>typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}

template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}


template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}


template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}



template<typename T>
List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "ListConstructor\t" << this << endl;
}



template<typename T>
List<T>::List(const initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);

	//for (int i : il)push_back(i);

}

template<typename T>
List<T>::List(const List<T>& other) : List()
{
	/*for (ConstIterator it = other.cbegin(); it != other.cend(); ++it)
	{
		push_back(*it);

	}*/
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;

}

template<typename T>
List<T>::List(List<T>&& other) :List()
{
	*this = std::move(other);
	cout << "LMoveConstructor:\t" << this << endl;
}



template<typename T>
List<T>::~List()
{
	while (Head)pop_front();
	cout << "ListDestructor\t" << this << endl;
}

// Operators


template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (List<T>::ConstIterator it = other.cbegin(); it != other.cend(); ++it)
		push_back(*it);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other)noexcept
{
	if (this == &other)return *this;
	while (Head)pop_front();
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;
	other.Head = nullptr;
	other.Tail = nullptr;
	other.size = 0;
	cout << "LMoveAssignment:\t" << this << endl;
	return *this;

}


//Adding Elements

template <typename T>
void List<T>::push_front(T data)
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

template <typename T>
void List<T>::push_back(T data)
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

template <typename T>
void List<T>::pop_front()
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

template <typename T>
void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

template <typename T>
void List<T>::insert(T data, int index)
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

template <typename T>
void List<T>::erase(int index)
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

template<typename T>
void List<T>::print()const
{
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов " << size << endl;
}

template <typename T>
void List<T>::reverse_print()const
{
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов " << size << endl;
}


template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{

	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
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

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	//for (int i : list1)cout << i << tab; cout << endl;
	
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;


	List<double> d_list = { 1.5, 2.7, 3.14, 8.3 };
	d_list.print();

	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator rit = d_list.rbegin(); rit != d_list.rend(); ++rit)
		cout << *rit << tab;
	cout << endl;







}