#include<iostream>
#include<ctime>
using std::cout;
using std::cin;
using std::endl;

#define DEBUG

#define tab "\t"
#define delimiter "\n-------------------------------------------\n"

class Tree
{

protected:
	class Element
	{

		int Data;
		Element* pLeft;
		Element* pRight;

	public:

		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor\t" << this << endl;
#endif // DEBUG


		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}

		friend class Tree;
		friend class UniqueTree;

	}*Root;

public:

	Element* getRoot()const
	{
		return Root;

	}

	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}


		
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			Insert(*it, Root);
		}
	}

	~Tree()
	{
		clear(Root);
		
		cout << "TDestructor\t" << this << endl;
	}

	void Insert(int Data)
	{
		Insert(Data, Root);
	}

	void erase(int Data)
	{
		erase(Data, Root);
	}


	int minValue()const
	{
		return minValue(Root);
	}

	int maxValue()const
	{
		return maxValue(Root);
	}

	int Count()const
	{
		return Count(Root);
	}

	int Sum()const
	{
		return Sum(Root);

	}

	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);

	}


	int depth()const
	{
		return depth(Root);
	}

	void clear()
	{
		clear(Root);
		
	}


	void print()const
	{
		print(Root);
	}



private:

	void Insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}
		if (Root == nullptr)
		{
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				Insert(Data, Root->pLeft);
			}
		}
		else
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				Insert(Data, Root->pRight);
			}
		}
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				//Root->Data = maxValue(Root->pLeft);
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}


			}

		}

	}




	/*int minValue()const
	{
		Element* Temp = this->Root;
		while (Temp->pLeft)Temp = Temp->pLeft;
		return Temp->Data;
	}


	int maxValue()const
	{
		Element* Temp = this->Root;
		while (Temp->pRight)Temp = Temp->pRight;
		return Temp->Data;
	}*/


	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);

	}
	
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root == nullptr ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}


	int Count(Element* Root)const
	{
		/*if (Root == nullptr)
		{
			return 0;
		}
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;*/

		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;

	}


	int Sum(Element* Root)const
	{
		/*if (Root == nullptr)
		{
			return 0;
		}
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;*/

		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;

	}


	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ? depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;

	}


	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}




public:

	
	/*void erase(int m, Element* Root)
	{
		if (Root == nullptr)
		{
			cout << "Данного значения нет в дереве" << endl;
			return;
		}
		if (Root->Data == m)
		{
			cout << "Значение есть в дереве" << endl;
			delete Root;
			return;
		}
		if (m < Root->Data)erase(m, Root->pLeft);
		else erase(m, Root->pRight);

	}*/


	


	void print(Element* Root)const
	{
		if (Root == nullptr)
		{
			return;
		}
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}



};


class UniqueTree : public Tree
{

	void Insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
		}
		if (Root == nullptr)
		{
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				Insert(Data, Root->pLeft);
			}
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				Insert(Data, Root->pRight);
			}
		}
	}

public:
	void Insert(int Data)
	{
		Insert(Data, Root);
	}




};


#define BASE_CHECK
#define UINT unsigned int

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	srand(time(NULL));

	int n = rand() % 14 + 1;
	//cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		//int number = rand() % 30;
		//cout << number << tab;
		tree.Insert(rand() % 100);
	}
	tree.print();
	cout << endl;


	tree.clear();
	cout << "Минимальное значение дерева: " << tree.minValue() << endl;

	cout << "Максимальное значение дерева: " << tree.maxValue() << endl;

	cout << "Количество элементов в дереве: " << tree.Count() << endl;

	cout << "Сумма элементов дерева: " << tree.Sum() << endl;

	cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << endl;

	cout << "Глубина дерева: " << tree.depth() << endl;


	tree.print();
	cout << endl;

	Tree tree2 = { 3, 5, 8, 13, 21 };
	tree2.print();
	cout << endl;


	int t;
	cout << "Введите размер дерева: "; cin >> t;
	UniqueTree u_tree;
	for (int i = 0; i < t; i++)
	{
		u_tree.Insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << u_tree.Avg() << endl;

#endif // BASE_CHECK


	Tree deep_tree = { 50, 25, 75, 16, 32, 64, 85, 14, 12 };
	deep_tree.print();
	cout << endl;
	cout << "Глубина дерева: " << deep_tree.depth() << endl;

	int value;
	cout << "Введите значение для удаления "; cin >> value;
	deep_tree.erase(value);
	deep_tree.print();





	char sym[] = "Hello";


	using C = int;

	typedef unsigned int uint;
	uint a;
	cout << typeid(a).name() << endl;


}