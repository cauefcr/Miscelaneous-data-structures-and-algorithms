#include <iostream>

using namespace std;

//compilar com g++ arquivo.c -o arquivo -std=c++11
typedef struct no {
	no* next;
	int val;
} no;

typedef struct lista {
	no* head;
	no* tail;
} lista;

typedef struct noc {
	noc* next;
	char c;
} noc;

typedef struct chr_lst {
	noc* head;
	noc* tail;
} chr_lst;

typedef struct nos {
	nos* next;
	string val;
} nos;

typedef struct str_lst {
	nos* head;
	nos* tail;
} str_lst;

lista* reverter(lista* lst) { // 1
	lista* reverse = new lista();
	no* tmp = lst->head;
	while (tmp != nullptr) { // para todos os elementos
		no* node = new no(); // crie um novo nó
		node->val = tmp->val;
		if (reverse->head == nullptr) { // empilha
			reverse->head = node;
			reverse->tail = node;
		} else {
			node->next = reverse->head;
			reverse->head = node;
		}
		tmp = tmp->next;
	}
	return reverse;
}

void push_back(lista* lst, int value) { // 1
	no* node = new no();
	node->val = value;
	if (lst->head == nullptr) {
		lst->head = node;
		lst->tail = node;
	} else {
		(lst->tail)->next = node;
		lst->tail = node;
	}
	return;
}

void push_back(chr_lst* lst, char c) { // 2
	noc* node = new noc();
	node->c = c;
	if (lst->head == nullptr) {
		lst->head = node;
		lst->tail = node;
	} else {
		node->next = (lst->tail)->next;
		(lst->tail)->next = node;
		lst->tail = node;
	}
	return;
}

void stack(lista* lst, int val) { // 3
	no* node = new no();
	node->val = val;
	if (lst->head == nullptr) {
		lst->head = node;
		lst->tail = node;
	} else {
		node->next = lst->head;
		lst->head = node;
	}
}

int unstack(lista* lst) { // 3
	no* tmp = lst->head;
	if (tmp == nullptr) {
		return 0;
	}
	int val = tmp->val;
	lst->head = tmp->next;
	delete (tmp);
	return val;
}

void stack(chr_lst* lst, char c) { // 4,5
	noc* node = new noc();
	node->c = c;
	if (lst->head == nullptr) {
		lst->head = node;
		lst->tail = node;
	} else {
		node->next = lst->head;
		lst->head = node;
	}
}

char unstack(chr_lst* lst) { // 4,5
	noc* tmp = lst->head;
	if (tmp == nullptr) {
		return '\0';
	}
	char c = tmp->c;
	lst->head = tmp->next;
	delete (tmp);
	return c;
}

void print_list(lista* lst) {
	no* tmp = lst->head;
	while (tmp != nullptr) {
		cout << tmp->val << ", ";
		tmp = tmp->next;
	}
	cout << "\n";
}

void print_list(chr_lst* lst) {
	noc* tmp = lst->head;
	while (tmp != nullptr) {
		if (tmp->c != '\r')
			cout << tmp->c;
		tmp = tmp->next;
	}
	cout << "\n";
}

void queue(chr_lst* lst, char c) { // 5
	stack(lst, c);
}

char unqueue(chr_lst* lst) { // 5
	if (lst->head != nullptr) {
		chr_lst* tmp_stack = new chr_lst();
		char value, c;
		for (value = unstack(lst); value != '\0'; value = unstack(lst)) {
			c = value;
			stack(tmp_stack, value);
		}
		for (value = unstack(tmp_stack); value != '\0';
		     value = unstack(tmp_stack)) {
			if (value != c) {
				stack(lst, value);
			}
		}
		delete (tmp_stack);
		return c;
	}
	return '\0';
}

void queue(str_lst* lst, string val) { // 6
	nos* node = new nos();
	node->val = val;
	if (lst->head == nullptr) {
		lst->head = node;
		lst->tail = node;
	} else {
		(lst->tail)->next = node;
		lst->tail = node;
	}
}

string unqueue(str_lst* lst) { // 6
	if (lst->head == nullptr) {
		return "";
	}
	nos* tmp = lst->head;
	string str = tmp->val;
	lst->head = tmp->next;
	if (lst->head == nullptr) {
		lst->tail = nullptr;
	}
	delete (tmp);
	return str;
}

int main(void) { //deve-se comentar os outros exemplos, caso queira testar um exemplo
	// 1 reverter lista
	lista* lst = new lista();
	push_back(lst, 1);
	push_back(lst, 2);
	push_back(lst, 3);
	push_back(lst, 4);
	print_list(lst);
	print_list(reverter(lst));

	// 2 fim/começo
	string input = "james [Bond, ]bond!";
	// cin >> input;
	noc* actual_tail = new noc();
	chr_lst* out = new chr_lst();
	push_back(out, '\r'); // gambiarra :^)

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '[') {
			actual_tail = out->tail;
			out->tail = out->head;
		} else if (input[i] == ']') {
			if (actual_tail != nullptr) {
				out->tail = actual_tail;
			}
		} else { push_back(out, input[i]); }
	}
	print_list(out);

	// 3 calculadora polonesa
	lista* polish_calc = new lista();
	string input;
	int var2, var1;
	while (cin >> input) { // stdin, pra ser útil, ctrl+d para parar, ouctrl + z no windows 
		if ((input[0] >= '0') && (input[0] <= '9')) {
			stack(polish_calc, stoi(input));
		}
		else {
			var2 = unstack(polish_calc);
			var1 = unstack(polish_calc);
			switch (input[0]) {
			case '*':
				stack(polish_calc, var1 * var2);
				break;
			case '-':
				stack(polish_calc, var1 - var2);
				break;
			case '+':
				stack(polish_calc, var1 + var2);
				break;
			case '/':
				stack(polish_calc, var1 / var2);
				break;
			case '%':
				stack(polish_calc, var1 % var2);
				break;
			}
		}
	}
	cout << unstack(polish_calc);

	// 4 balanceamento
	string input;
	cin >> input;
	char unstacked;
	chr_lst* the_list = new chr_lst();
	for (auto chr : input) {
		if ((chr == '(') || (chr == '{') || (chr == '[')) {
			stack(the_list, chr);
		} else {
			if ((chr == ')') || (chr == '}') || (chr == ']')) {
				unstacked = unstack(the_list);
				switch (chr) {
				case '}':
					if (unstacked != '{') {
						cout << "Desbalanceado";
						return 1;
					}
					break;
				case ')':
					if (unstacked != '(') {
						cout << "Desbalanceado";
						return 1;
					}
					break;
				case ']':
					if (unstacked != '[') {
						cout << "Desbalanceado";
						return 1;
					}
					break;
				}
			}
		}
	}
	if (unstack(the_list) == '\0') {
		cout << "Balanceado!";
	} else {
		cout << "Desbalanceado";
		return 1;
	}

	// 5 fila com duas pilhas (queue = stack(),
	// unqueue = multiplos unstacks()
	// até chegar no ultimo elemento 
	chr_lst* the_list = new chr_lst();
	char chr;
	for (chr = 'a'; chr <= 'z'; chr++) {
		queue(the_list, chr);
	}
	while (chr != '\0') {
		chr = unqueue(the_list);
		cout << chr;
	}

	// 6
	string input;
	int max;
	cin >> max;
	str_lst* cinema = new str_lst();
	for (int i = 0; i < max; i++) {
		cin >> input;
		if (input == "X") {
			unqueue(cinema);
		} else { queue(cinema, input); }
	}
	while ((input = unqueue(cinema)) != "") {
		cout << input << " ";
	}
}