#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Узел дерева
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// Функция для выделения нового узла дерева
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}
// Объект сравнения, который будет использоваться для упорядочивания кучи
struct comporator
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
// пройти по дереву Хаффмана и сохранить коды Хаффмана в map 
void Encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}
	Encode(root->left, str + "0", huffmanCode);
	Encode(root->right, str + "1", huffmanCode);
}
// проходим по дереву Хаффмана и декодируем закодированную строку
void Decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] == '0')
		Decode(root->left, index, str);
	else
		Decode(root->right, index, str);
}

bool cmp(pair<char, int>& a,
	pair<char, int>& b)
{
	return a.second > b.second;
}
bool cmp2(pair<char, string>& a,
	pair<char, string>& b)
{
	return a.second > b.second;
}


// Строим дерево Хаффмана
void HuffmanTree(string text)
{
	double sr = 0;
	vector<double> probability;
	vector<double> kol;
	vector<char> symbols;
	double ver = 0;
	int counter = 0;
	double len = text.length();
	// подсчитываем частоту появления каждого символа и сохраняем в freq
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}
	cout << "      Таблица вероятностей" << endl;
	cout << "Символ" << "\t" << "Количество" << "\t" << "Вероятность" << endl;
	//выводим таблицу вероятностей
	for (auto it = freq.begin(); it != freq.end(); ++it)
	{
		symbols.push_back((char)it->first);
		counter++;
		ver = (double)it->second / len;
		probability.push_back(ver);
		kol.push_back(it->second);
		cout << it->first << "\t" << it->second << "\t\t" << ver << endl;
	}
	cout << endl;
	cout << "Сортированная таблица вероятностей" << endl;
	cout << "Символ" << "\t" << "Количество" << "\t" << "Вероятность" << endl;
	vector<pair<char, int> > A; //создаем вектор для сортирвоки
	for (auto& it : freq) { //c map все передаем в вектор
		A.push_back(it);
	}
	sort(A.begin(), A.end(), cmp); //сортируем
	for (auto& it : A) {
		ver = (double)it.second / len;
		cout << it.first << "\t"
			<< it.second << "\t\t" << ver << endl;
	}
	// Создаем приоритетную очередь для хранения активных узлов
	priority_queue<Node*, vector<Node*>, comporator> pq;
	// Создаем листовой узел для каждого символа и добавляем его в приоритетную очередь pq
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	// делаем, пока в очереди не будет более одного узла
	while (pq.size() != 1)
	{
		// Удаляем два узла с наивысшим приоритетом
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();
		// Создаем новый внутренний узел с этими двумя узлами
		int sum = left->freq + right->freq;
		//Добавляем новый узел в приоритетную очередь.
		pq.push(getNode('\0', sum, left, right));
	}
	// корень хранит указатель на корень дерева Хаффмана
	Node* root = pq.top();
	// пройти по дереву Хаффмана и сохранить коды Хаффмана в huffmanCode
	unordered_map<char, string> huffmanCode;
	Encode(root, "", huffmanCode);
	vector<double> bit;
	cout << endl;
	//вывод дерева Хаффмана
	cout << "Дерево Хаффмана\n";
	for (auto pair : huffmanCode) {
		cout << pair.first << "-" << pair.second << '\n';
		bit.push_back(pair.second.size());
	}
	cout << endl;
	cout << "Сортированное Дерево Хаффмана\n";
	vector<pair<char, string> > B; //создаем вектор для сортирвоки
	for (auto& it : huffmanCode) { //c map все передаем в вектор
		B.push_back(it);
	}
	sort(B.begin(), B.end(), cmp2); //сортируем
	vector<pair<char, string> > v1;
	vector<pair<char, string> > v2;
	vector<pair<char, string> > v3;
	for (auto& it : B) {
		if (it.second.size() > 4)
		{
			v1.push_back(it);
		}
		else if (it.second.size() > 3)
		{
			v2.push_back(it);
		}
		else if (it.second.size() > 2)
		{
			v3.push_back(it);
		}
	}
	for (auto& it : v1)//выводим сортированное дерево
	{
		cout << it.first << "-" << it.second << endl;
	}
	for (auto& it : v2)
	{
		cout << it.first << "-" << it.second << endl;
	}
	for (auto& it : v3)
	{
		cout << it.first << "-" << it.second << endl;
	}
	double ascii = 8 * len;
	double huff = 0;
	double res = 0;
	double res2 = 0;
	//считаем коэффициенты сжатия относительно кодировки ASCII
	for (int i = 0; i < counter; i++) {
		huff += kol[i] * bit[i];
	}
	for (int i = 0; i < counter; i++) {
		res = ascii / huff;
	}
	cout << endl;
	cout << "Коэффициент сжатия относительно ASCII = " << res << endl;
	//считаем коэффициенты сжатия относительно равномерного кода
	for (int i = 0; i < counter; i++) {
		res2 = len * ceil(log2(counter)) / huff;
	}
	cout << "Коэффициент сжатия относительно равномерного кода = " << res2 << endl;
	//считаем среднюю длину полученного кода
	for (int i = 0; i < counter; i++) {
		sr += probability[i] * bit[i];
	}
	cout << "Средняя длина кода = " << sr << endl;
	//считаем дисперсию
	double dis = 0;
	for (int i = 0; i < counter; i++) {
		double k = (bit[i] - sr);
		dis += probability[i] * pow(k, 2);
	}
	cout << "Дисперсия = " << dis << endl;

	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	cout << "\nКодированная строка :\n" << str << '\n';
	int index = -1;
	cout << "\nДекодированная строка: \n";
	while (index < (int)str.size() - 2) {
		Decode(root, index, str);
	}

	sort(probability.begin(), probability.end(), greater<double>());
	sort(kol.begin(), kol.end(), greater<double>());
	cout << endl;

}

int main()
{
	setlocale(LC_ALL, "RU");
	string text = "ославская лидия ярославовна";
	HuffmanTree(text);
	return 0;
}
