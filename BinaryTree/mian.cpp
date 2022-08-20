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
		this->clear(this->Root);
		cout << "TDestructor\t" << this << endl;
	}

	void Insert(int Data)
	{
		Insert(Data, Root);
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
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);

	}
	
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
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



public:

	
	void erase(int m, Element* Root)
	{
		if (Root == nullptr)
		{
			cout << "������� �������� ��� � ������" << endl;
			return;
		}
		if (Root->Data == m)
		{
			cout << "�������� ���� � ������" << endl;
			delete Root;
			return;
		}
		if (m < Root->Data)erase(m, Root->pLeft);
		else erase(m, Root->pRight);

	}


	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}


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






void main()
{
	setlocale(LC_ALL, "");

	srand(time(NULL));

	int n = rand() % 14 + 1; 
	//cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		//int number = rand() % 30;
		//cout << number << tab;
		tree.Insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << "����������� �������� ������: " << tree.minValue() << endl;

	cout << "������������ �������� ������: " << tree.maxValue() << endl;

	cout << "���������� ��������� � ������: " << tree.Count() << endl;
	
	cout << "����� ��������� ������: " << tree.Sum() << endl;

	cout << "�������-�������������� ��������� ������: " << tree.Avg() << endl;

	cout << "������� ������: " << tree.depth() << endl;

	int m;
	cout << "������� �������� ��� �������� "; cin >> m;
	tree.erase(m, tree.getRoot());
	tree.print();
	cout << endl;
	
	Tree tree2 = { 3, 5, 8, 13, 21 };
	tree2.print();
	cout << endl;


	int t;
	cout << "������� ������ ������: "; cin >> t;
	UniqueTree u_tree;
	for (int i = 0; i < t; i++)
	{
		u_tree.Insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "����� ��������� ������: " << u_tree.Sum() << endl;
	cout << "�������-�������������� ��������� ������: " << u_tree.Avg() << endl;


	Tree deep_tree = { 50, 25, 75, 16, 32, 64, 85, 14, 12 };
	cout << "����������� �������� ������: " << deep_tree.minValue() << endl;
	deep_tree.print();
	cout << endl;
	cout << "������� ������: " << deep_tree.depth() << endl;



}