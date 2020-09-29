#include <iostream>
using namespace std;
struct node {

	double data{};
	node* left = nullptr;
	node* right = nullptr;
	node* parent = nullptr;
	string color;
};

class rbTree {
	float sum = 0;
	int sizenode = 0;
	double suma = 0;
	node* root;

public:
	rbTree() : root(nullptr) {}

	node* GetRoot() { return root; }
	//Добавление элмента в дерево
	void InsertNode(double stuff) {
		if (root == nullptr) {
			root = new node();
			root->data = stuff;
			root->parent = nullptr;
			root->color = "BLACK";
			cout << "Элемент добавлен.\n";
		}
		else {
			auto linker = GetRoot();
			node* newnode = new node();
			newnode->data = stuff;
			sizenode++;
			while (linker != nullptr) {
				if (linker->data > stuff) {
					if (linker->left == nullptr) {
						linker->left = newnode;
						newnode->color = "RED";
						newnode->parent = linker;
						cout << "Элемент добавлен.\n"; break;
					}
					else { linker = linker->left; }
				}
				else {
					if (linker->right == nullptr) {
						linker->right = newnode;
						newnode->color = "RED";
						newnode->parent = linker;
						cout << "Элемент добавлен.\n"; break;
					}
					else { linker = linker->right; }
				}
			}
			Fixup(newnode);
		}
	}
	//Балансировка дерева
	void Fixup(node* z) {
		while (z->parent->color == "RED") {
			auto grandparent = z->parent->parent;
			auto uncle = GetRoot();
			if (z->parent == grandparent->left) {
				if (grandparent->right) { uncle = grandparent->right; }
				if (uncle->color == "RED") {
					z->parent->color = "BLACK";
					uncle->color = "BLACK";
					grandparent->color = "RED";
					if (grandparent->data != root->data) { z = grandparent; }
					else { break; }
				}
				else if (z == grandparent->left->right) {
					LeftRotate(z->parent);
				}
				else {
					z->parent->color = "BLACK";
					grandparent->color = "RED";
					RightRotate(grandparent);
					if (grandparent->data != root->data) { z = grandparent; }
					else { break; }
				}
			}
			else {
				if (grandparent->left) { uncle = grandparent->left; }
				if (uncle->color == "RED") {
					z->parent->color = "BLACK";
					uncle->color = "BLACK";
					grandparent->color = "RED";
					if (grandparent->data != root->data) { z = grandparent; }
					else { break; }
				}
				else if (z == grandparent->right->left) {
					RightRotate(z->parent);
				}
				else {
					z->parent->color = "BLACK";
					grandparent->color = "RED";
					LeftRotate(grandparent);
					if (grandparent->data != root->data) { z = grandparent; }
					else { break; }
				}
			}
		}
		root->color = "BLACK";
	}
	//Передвижение влево
	void LeftRotate(node* x) {
		node* nw_node = new node();
		if (x->right->left) { nw_node->right = x->right->left; }
		nw_node->left = x->left;
		nw_node->data = x->data;
		nw_node->color = x->color;
		x->data = x->right->data;

		x->left = nw_node;
		if (nw_node->left) { nw_node->left->parent = nw_node; }
		if (nw_node->right) { nw_node->right->parent = nw_node; }
		nw_node->parent = x;

		if (x->right->right) { x->right = x->right->right; }
		else { x->right = nullptr; }

		if (x->right) { x->right->parent = x; }
	}
	//Передвижение вправо
	void RightRotate(node* x) {
		node* nw_node = new node();
		if (x->left->right) { nw_node->left = x->left->right; }
		nw_node->right = x->right;
		nw_node->data = x->data;
		nw_node->color = x->color;

		x->data = x->left->data;
		x->color = x->left->color;

		x->right = nw_node;
		if (nw_node->left) { nw_node->left->parent = nw_node; }
		if (nw_node->right) { nw_node->right->parent = nw_node; }
		nw_node->parent = x;

		if (x->left->left) { x->left = x->left->left; }
		else { x->left = nullptr; }

		if (x->left) { x->left->parent = x; }
	}
	//Прямой обход дерева
	void PreOrder(node* temp)
	{
		if (!temp) { return; }
		cout << "--> " << temp->data << "<" << temp->color << ">";
		PreOrder(temp->left);
		PreOrder(temp->right);
	}
	//Симметричный обход дерева
	void SymmetricOrder(node* temp) {
		if (!temp) { return; }
		SymmetricOrder(temp->left);
		cout << "--> " << temp->data << "<" << temp->color << ">";
		SymmetricOrder(temp->right);
	}
	//Нахождение суммы
	void Summa(node* temp) {
		if (!temp) { return; }
		Summa(temp->left);
		sum += temp->data;
		Summa(temp->right);
	}

	//Получение суммы
	double getSum() {
		return sum;
	}
	//Получение размера узлов
	int getSizeNode()
	{
		return sizenode;
	}
	//Средние арифметическое узлов
	double getSr()
	{
		double summa = getSum();
		double node = getSizeNode();
		double sr = summa / node;
		return sr;
	}
};

void menu() {
	cout << "\n__________________________________________";
	cout << "\n\n1. Добавить элемент в дерево";
	cout << "\n2. Прямой обход дерева";
	cout << "\n3. Симметричный обход дерева";
	//cout << "\n4. Сумма значений листьев";
	//cout << "\n5. Среднее арифметическое узлов";
	cout << "\n3. Выход.";
	cout << "\n__________________________________________";
	cout << "\nВаш выбор -- ";
}


int main() {
	setlocale(LC_ALL, "ru");
	rbTree demo;
	int info;
	double input;
	menu();
	cin >> info;
	while (info != 6) {
		switch (info) {
		case 1: cout << "\nВведите элемент -- ";
			cin >> input; demo.InsertNode(input);
			break;

		case 2: cout << "\nПрямой обход дерева -- ";
			demo.PreOrder(demo.GetRoot());
			cout << endl;
			break;

		case 3: cout << "Симметричный обход дерева ";
			demo.SymmetricOrder(demo.GetRoot());
			cout << endl;
			break;

		case 4: cout << "Сумма значений листьев - ";
			demo.Summa(demo.GetRoot());
			cout << demo.getSum() << endl;
			break;

		case 5: cout << "Среднее арифметическое всех узлов - ";
			cout << demo.getSr();
			break;
		default: cout << "Ошибка! Выберите значение от 1 до 6.\n";
		}
		cout << "\nВаш выбор?";
		cin >> info;
	}
	cout << "\nВыход...";
	return 0;
}