#include <iostream>
using namespace std;


#define tab "\t"

class Element
{
	int Data;
	Element* pNext; // Адрес следующего элемента

public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;


};


class ForwardList
{
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



};



//Head == nullptr;
//Head->pNext == nullptr;




void main()
{
	setlocale(LC_ALL, "");
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





}