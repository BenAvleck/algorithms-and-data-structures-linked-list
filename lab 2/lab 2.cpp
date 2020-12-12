#include <iostream>
#include <string>
#include <vector>

using namespace std;


template <typename T>
class List
{
public:
	List();
	~List();

	void showList();
	void removing_firsr_half();
	List<T>* CoppyList();
	T& GetData(int index);
	void removing_every_n(int index);
	void sort();
	static void coppyAndGlue(const List<T>* firstlist, const List<T>* secondlist);
	void glue( List<T>* otherList);
	void moveBy(int index, int _moveBy);
	T pop_back();
	T removeAt(int index);
	void insert(T data, int index);
	void push_front(T data);
	void clear();
	T pop_front();
	void push_back(T data);
	int GetSize() { return Size; }

	T& operator[](const int index);
private:
	template <typename T>
	struct Node
	{
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T>* head;
	Node<T>* tail;
};

template <typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;	
}

template <typename T>
List<T>::~List()
{
	clear();
}
template<typename T>
void List<T>::showList()
{
	for (int i = 0; i < this->GetSize(); i++)
		cout << this->GetData(i) << endl;

	cout << "\n\n";
}

template<typename T>
List<T>* List<T>::CoppyList()
{
	List<T>* newList = new List<T>;
	Node<T>* show = head;
	for (int i = 0; i < Size; i++)
	{
		newList->push_back(show->data);
		show = show->pNext;
	}

	return newList;
}

template<typename T>
T& List<T>::GetData(int index)
{
	Node<T>* show = head;
	if (index == 0) { return show->data; }

	else
	{
		for (int i = 0; i < index; i++)
			show = show->pNext;
		return show->data;
	}
}

template<typename T>
void List<T>::removing_firsr_half()
{
	int index = 2;
	for (int i = index - 2; i < this->Size; i += index)
	{
		removeAt(i);
		i--;
	}
}

template<typename T>
void List<T>::removing_every_n(int index)
{
	if (index == 1)
	{
		clear();
		return;
	}

	for (int i = index - 1; i < this->Size; i += index)
	{
		removeAt(i);
		i--;
	}
}

template <typename T>
void List<T>::sort() {

	Node<T>* left = this->head;                 //Первый элемент — это пусть будет голова
	Node<T>* right = this->head->pNext;          //Второй элемент — это пусть будет следующий за головой элемент

	Node<T>* temp = new Node<T>;              //Временное звено для хранения переставляемого всех значений переставляемого звена

	while (left->pNext) {                 //Обходим по всем звеньям, за исключением крайнего правого
		while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
			if ((left->data) > (right->data)) {        //Проверяем необходимость перестановки
				temp->data = left->data;               //И переставляем все внутренние элементы, за исключением указателей связи, местами
				left->data = right->data;             //Сейчас у нас имеется только x, поэтому только его
				right->data = temp->data;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
			}
			right = right->pNext;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
		}
		left = left->pNext;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
		right = left->pNext;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
	
	}
}

template<typename T>
static void List<T>::coppyAndGlue(const List<T>* firstlist, const List<T>* secondlist)
{
	List<T>* new_list = firstlist->CoppyList();
	Node<T>* current = new_list->head;
	for (int i = 0; i < new_list->Size; i++)
		current = current->pNext;
	current->pNext = secondlist->CoppyList()->head;
	return new_list;
}

template<typename T>
void List<T>::glue( List<T>* otherList)
{
	Node<T>* current = this->head;
	for (int i = 0; i < Size -1; i++)
		current = current->pNext;
	current->pNext = otherList->head;
	Size += otherList->Size;
	otherList->Size = 0;
	otherList->head = nullptr;
}

template<typename T>
void List<T>::moveBy(int index, int _moveBy)
{
	if (_moveBy == 0)
		return;
	else if (index < 0 || index >= Size)
		throw exception("Invalid index!");
	else if (index + _moveBy == Size || index + _moveBy < 0)
		throw exception("Out of range!");
	else if (index + _moveBy == Size - 1)
	{	
		T data = removeAt(index);
		push_back(data);
	}
	else if (index + _moveBy == 0)
	{
		T data = removeAt(index);
		push_front(data);
	}
	else if (index + _moveBy < Size - 1 && index + _moveBy > 0)
	{
		T data = removeAt(index);
		insert(data, index + _moveBy);
	}
}

template<typename T>
T List<T>::pop_back()
{
	T data = removeAt(Size - 1);
	return data;
}

template<typename T>
T List<T>::removeAt(int index)
{
	T data;
	if (index == 0)
		data = pop_front();
	else
	{
		Node<T>* previous = this->head;
		
		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;

		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		data = toDelete->data;
		delete toDelete;
		Size--;
	}
	return data;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
		push_front(data);
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		previous->pNext = new Node<T>(data, previous->pNext);
		++Size;
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	++Size;
}

template<typename T>
void List<T>::clear()
{
	while (Size) { pop_front(); }
}

template<typename T>
T List<T>::pop_front()
{
	Node<T>* temp = this->head;
	this->head = this->head->pNext;
	T data = temp->data;
	delete temp;
	--Size;
	return data;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
		head = new Node<T>(data);
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	++Size;
}

template <typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
			return current->data;
		current = current->pNext;
	}
}

int stateMenu;
void Menu()
{
	cout << "(0) exit" << endl
		<< "(1) data input" << endl
		<< "(2) fulfill the work condition" << endl
		<< "(3) Show" << endl
		<< "(4) removeAt" << endl
		<< "(5) pop_back" << endl
		<< "(6) removing_every_n" << endl
		<< "(7) moveBy" << endl
		<< "(8) insert" << endl
		<< "(9) clear" << endl
		<< "(10) pop_front" << endl
		<< "(11) push_back" << endl
		<< "(12) push_front" << endl
		<< "(13) sort" << endl
		<< "Make your choice:";
	cin >> stateMenu;

}



int main()
{
	Menu();
	string a;
	string d;
	int actions,
		n = 0;
	List<string>* list = new List<string>();
	List<string>* surname = new List<string>();
	List<string>* surname2 = surname->CoppyList();


	while (stateMenu != 0)
	{
		switch (stateMenu)
		{
		case 1:
			system("cls");
			cout << "Enter n:";
			cin >> n;

			for (int i = 0; i < n; i++)
				list->push_back("Mihailov " + to_string(i + 1));


			system("pause");
			system("cls");
			Menu();
			break;

		case 2:
			system("cls");



			for (int i = 0; i < 20; i++)
				surname->push_back("Mihailov " + to_string(i + 1));

			surname->showList();

			surname2 = surname->CoppyList();
			surname2->showList();


			surname2->removing_every_n(2);
			surname->removing_firsr_half();

			surname->showList();
			surname2->showList();

			system("pause");
			system("cls");
			Menu();
			break;
		case 3:
			system("cls");

			list->showList();

			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");

			cout << "Enter index: ";
			cin >> n;
			list->removeAt(n);

			system("pause");
			system("cls");
			Menu();
			break;
		case 5:
			system("cls");
			list->pop_back();

			system("pause");
			system("cls");
			Menu();
			break;
		case 6:
			system("cls");

			cout << "Enter index: ";
			cin >> n;

			list->removing_every_n(n);

			system("pause");
			system("cls");
			Menu();
			break;
		case 7:
			system("cls");

			cout << "Enter index: ";
			cin >> n;
			int moveBy;
			cout << "Enter number of shifts: ";
			cin >> moveBy;
			list->moveBy(n, moveBy);

			system("pause");
			system("cls");
			Menu();
			break;

		case 8:
			system("cls");

			cout << "Enter index: ";
			cin >> n;
			
			cout << "Enter data: ";
			cin >> a;
			list->insert(a, n);

			system("pause");
			system("cls");
			Menu();
			break;
		case 9:
			system("cls");

			list->clear();

			system("pause");
			system("cls");
			Menu();
			break;
		case 10:
			system("cls");

			list->pop_front();

			system("pause");
			system("cls");
			Menu();
			break;
		case 11:
			system("cls");
			
			cout << "Enter Data ";
			cin >> d;
			list->push_back(d);


			system("pause");
			system("cls");
			Menu();
			break;
		case 12:
			system("cls");

			cout << "Enter Data ";
			cin >> d;
			list->push_front(d);

			system("pause");
			system("cls");
			Menu();
			break;
		case 13:
			system("cls");

			list->sort();
			list->showList();
			system("pause");
			system("cls");
			Menu();
			break;
		}
	}
}