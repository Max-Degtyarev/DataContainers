#include <iostream>
#include<ctime>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

string Factory();

#define tab "\t"

class Element
{
	int Data;
	string goods;
	Element* pNext; // Адрес следующего элемента

public:
	Element(int Data, string goods = "", Element* pNext = nullptr) : Data(Data), goods(goods), pNext(pNext)
	{
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class ForwardList;
	friend class Queue;

};


class ForwardList
{
protected:
	Element* Head; // Голова списка

public:
	ForwardList()
	{
		Head = nullptr; //Когда голова списка указывает на 0, список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding Elements


	

	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Присоеденили новый элемент к списку (к началу списка)
		New->pNext = Head;
		//3) Говорим, что новый элемент является головой списка
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


	// Removing elements


	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента
		Element* erased = Head;
		//2) Исключаем элемент из списка
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete erased;

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

	// Methods

	void print()const
	{
		Element* Temp = Head; 
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}
	}

	friend class Queue;

};


class Queue: public ForwardList
{
	
	Queue* top;
	string goods;


public:

	Queue() : ForwardList()
	{
		

	}


	void set_goods(string goods)
	{
		this->goods = goods;

	}



	void push_back(int Data, string goods)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data, goods);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;

	}

	void service(int n)
	{
		int m = 0;
		while (m != n)
		{
			set_goods(Factory());
			this->pop_front();
			m++;
		}

	}


	void pop_front()
	{
		//srand(NULL);

		//Element* erased = Head;
		
		cout << "Покупатель " << Head->Data << " " << goods << /* << Number() << Price()*/ endl;

		Head = Head->pNext;
		
		//delete erased;

	}

	




	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << "Покупатель " << Temp->Data << endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}
	}




};

string Factory()
{
	//srand(time(NULL));
	int index;
	string goods;
	//do
	{
		index = rand() % 3 + 1;
		if (index == 1)goods = "Колбаса";
		if (index == 2)goods = "Пиво";
		if (index == 3)goods = "Хлеб";
		if (index == 4)goods = "Мясо";
	} //while (goods == Head->goods);

	return goods;
}

class Stack :private ForwardList
{

public:
	unsigned int get_size()const
	{
		//return size;

	}

	void push_front(int Data)
	{


	}


};





//#define LIST_CHECK
//#define LIST_CHECK_2



void main()
{
	setlocale(LC_ALL, "");
#ifdef LIST_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);

	}
	list.print();
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс элемента для добавления: "; cin >> index;
	list.insert(value, index);
	list.print();
	int index_2;
	cout << "Введите индекс элемента для удаления: "; cin >> index_2;
	list.erase(index_2);
	list.print();
#endif // LIST_CHECK

#ifdef LIST_CHECK_2
	srand(time(NULL));

	Queue queue1;
	int n;
	cout << "Введите количество покупателей ожидающих открытие магазина: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		queue1.push_back(i + 1, Factory());

	}
	queue1.print();
	cout << endl << "После открытия магазина: " << endl;
	queue1.service(n);
#endif // LIST_CHECK_2


	Stack stack;
	stack



}