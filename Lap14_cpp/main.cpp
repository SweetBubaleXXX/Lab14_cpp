#include <iostream>

using std::cin, std::cout, std::endl;

struct Node
{
	char value = 0;
	Node* prev = nullptr;
	Node* next = nullptr;

	Node(Node* prevNode = nullptr, Node* nextNode = nullptr)
	{
		this->prev = prevNode;
		this->next = nextNode;
	}

	Node(char value, Node* prevNode = nullptr, Node* nextNode = nullptr)
	{
		this->value = value;
		this->prev = prevNode;
		this->next = nextNode;
	}
};

struct Chain
{
	Node* start = nullptr;
	Node* end = nullptr;

	int getSize()
	{
		return size;
	}

	void clear()
	{
		while (size) pop();
	}

	void pop()
	{
		Node* node = start;
		start = node->prev;
		if (start)
			start->next = nullptr;
		else
			end = nullptr;
		size--;
		delete node;
	}


	void push(char value)
	{
		Node* node = new Node(value, nullptr, end);
		if (size)
			end->prev = node;
		else
			start = node;
		end = node;
		size++;
	}
	void reduce()
	{
		Node* node = end;
		while (node && node->next)
		{
			Node* duplicate;
			while (duplicate = searchDuplicate(node))
				remove(duplicate);
			node = node->next;
		}
	}

	void remove(Node* node)
	{
		if (!node) return;
		if (node->prev)
			node->prev->next = node->next;
		else
			end = node->next;
		if (node->next)
			node->next->prev = node->prev;
		else
			start = node->prev;
		size--;
		delete node;
	}

	Node* searchDuplicate(Node* existing)
	{
		if (!start) return nullptr;
		Node* node = start;
		while ((node == existing || node->value != existing->value) && node->prev)
			node = node->prev;
		if (node != existing && node->value == existing->value)
			return node;
		return nullptr;
	}

	void print()
	{
		Node* node = start;
		if (node)
		{
			cout << node->value;
			node = node->prev;
		}
		while (node)
		{
			cout << " <- " << node->value;
			node = node->prev;
		}
		cout << endl;
	}

private:
	int size = 0;
};

int main()
{
	int n;
	cout << "Enter number of symbols: ";
	cin >> n;
	cin.clear();
	cin.ignore();

	char* symbols = new char[n];
	cout << "Enter symbols (no spaces): ";
	for (int i = 0; i < n; i++) symbols[i] = getchar();

	Chain* chain = new Chain();
	for (int i = 0; i < n; i++) chain->push(symbols[i]);

	chain->print();
	chain->reduce();
	chain->print();

	delete[] symbols;
	chain->clear();

	return 0;
}
