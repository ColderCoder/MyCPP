
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <math.h>
using namespace std;

typedef double (*operation_unary)(double);
typedef double (*operation_binary)(double, double);

class Operator {
private:
	int priority;
public:
	Operator() {}
	Operator(int p) :priority(p) {}
	bool operator>(const Operator r) { return priority > r.priority; }
	bool operator>=(const Operator r) { return priority >= r.priority; }
	bool operator<(const Operator r) { return priority < r.priority; }
	bool operator<=(const Operator r) { return priority <= r.priority; }
};

class UnaryOperator :public Operator {
private:
	operation_unary operation;
public:
	const bool atRight;
	UnaryOperator() :atRight(false) {}
	UnaryOperator(operation_unary ope) :operation(ope), Operator(10), atRight(false) {}
	UnaryOperator(operation_unary ope, bool right) :operation(ope), Operator(0), atRight(right) {}
	double call(double a) { return (*operation)(a); }
};

class BinaryOperator :public Operator {
private:
	operation_binary operation;
public:
	BinaryOperator() {}
	BinaryOperator(operation_binary ope, int p) :operation(ope), Operator(p) {}
	double call(double a, double b) { return (*operation)(a, b); }
};

namespace operations {
	//function std::round() is C++11's, add it manually in VS2010
	double round(double number)
	{
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}
	double nega(double a) { return -a; }
	double add(double a, double b) { return a + b; }
	double sub(double a, double b) { return a - b; }
	double mul(double a, double b) { return a * b; }
	double div(double a, double b) { if (b == 0)throw exception("DIV/0"); return a / b; }
	double fac(double a) {
		if (a < 0 || abs(a - operations::round(a)) > 1e-10) throw exception("cannot factory decimal");
		int n = operations::round(a);
		int r = 1;
		while (n) {
			r *= n--;
		}
		return (double)r;
	}
}

map<string, UnaryOperator*> UnaryOperators;
map<string, BinaryOperator*> BinaryOperators;

void initOperators() {
	static bool inited = false;
	if (inited) return;
	inited = true;

	UnaryOperators["-"] = new UnaryOperator(operations::nega);
	UnaryOperators["!"] = new UnaryOperator(operations::fac, true);
	UnaryOperators["sin"] = new UnaryOperator(sin);
	UnaryOperators["cos"] = new UnaryOperator(cos);
	UnaryOperators["tan"] = new UnaryOperator(tan);
	UnaryOperators["sqrt"] = new UnaryOperator(sqrt);


	BinaryOperators["+"] = new BinaryOperator(operations::add, 1);
	BinaryOperators["-"] = new BinaryOperator(operations::sub, 1);
	BinaryOperators["*"] = new BinaryOperator(operations::mul, 2);
	BinaryOperators["/"] = new BinaryOperator(operations::div, 2);
	BinaryOperators["^"] = new BinaryOperator(pow, 3);
}

namespace NodeType {
	enum Type {
		number, ope1, ope2, leftb
	};
}

union NodeValue {
	double number;
	UnaryOperator* unaryOperator;
	BinaryOperator* binaryOperator;
};

class Node {
public:
	Node() {}
	Node(double n) :type(NodeType::number) { value.number = n; }
	Node(UnaryOperator* n) :type(NodeType::ope1) { value.unaryOperator = n; }
	Node(BinaryOperator* n) :type(NodeType::ope2) { value.binaryOperator = n; }
	NodeType::Type type;
	NodeValue value;
};

bool isNumber(const char c) {
	return (c >= '0' && c <= '9') || c == '.';
}
namespace PrevType {
	enum Type {
		number, leftb, rightb, ope1, ope2
	};
}

char buf[200];

PrevType::Type prevtype;

int parseNumber(queue<Node>& queue, const char* input, int start) {
	int len = 0;
	for (char c = input[len + start]; c && isNumber(c); ++len, c = input[len + start]) {
		buf[len] = c;
	}
	buf[len] = 0;
	queue.push(Node(atof(buf)));
	prevtype = PrevType::number;
	return len + start;
}

int parseUnaryOperator(queue<Node>& queue, stack<Node>& stack, const char* input, int start) {
	int len = 0;
	memset(buf, 0, sizeof(buf));
	UnaryOperator* ope = 0;
	for (char c = input[len + start];
		c && !isNumber(c) && c != '(' && c != ')' && c != ' ';
		++len, c = input[len + start]) {
		buf[len] = c;
		ope = UnaryOperators[buf];
		if (ope)break;
	}
	if (!ope) throw exception("unknown operator");
	if (ope->atRight) {
		queue.push(Node(ope));
	}
	else {
		while (!stack.empty() && stack.top().type != NodeType::leftb && *ope < (*stack.top().value.unaryOperator)) {
			queue.push(stack.top());
			stack.pop();
		}
		stack.push(Node(ope));
		prevtype = PrevType::ope1;
	}
	return len + start + 1;
}

int parseBinaryOperator(queue<Node>& queue, stack<Node>& stack, const char* input, int start) {
	int len = 0;
	memset(buf, 0, sizeof(buf));
	BinaryOperator* ope = 0;
	for (char c = input[len + start];
		c && !isNumber(c) && c != '(' && c != ')' && c != ' ';
		++len, c = input[len + start]) {
		buf[len] = c;
		ope = BinaryOperators[buf];
		if (ope)break;
	}
	if (!ope) {
		return parseUnaryOperator(queue, stack, input, start);
	};
	while (!stack.empty() && stack.top().type != NodeType::leftb && *ope < (*stack.top().value.binaryOperator)) {
		queue.push(stack.top());
		stack.pop();
	}
	stack.push(Node(ope));
	prevtype = PrevType::ope2;
	return len + start + 1;
}

int parseLeftBracket(queue<Node>& queue, stack<Node>& stack, const char* input, int start) {
	Node n;
	n.type = NodeType::leftb;
	stack.push(n);
	prevtype = PrevType::leftb;
	return ++start;
}

int parseRightBracket(queue<Node>& queue, stack<Node>& stack, const char* input, int start) {
	Node n;
	bool foundleft = false;
	while (!stack.empty() && !foundleft) {
		n = stack.top();
		stack.pop();
		switch (n.type)
		{
		case NodeType::ope1:
		case NodeType::ope2:
			queue.push(n);
			break;
		case NodeType::leftb:
			foundleft = true;
			break;
		default:
			throw exception("should not happen");
			break;
		}
	}
	if (!foundleft) throw exception("can not find corresponding left bracket");
	prevtype = PrevType::rightb;
	return ++start;
}

void parse(queue<Node>& queue, const char* input) {
	int ptr = 0;
	stack<Node> stack;
	bool previsnumberorrightb = false;
	while (input[ptr]) {
		if (input[ptr] == ' ') {
			++ptr;
			continue;
		}
		if (isNumber(input[ptr])) {
			ptr = parseNumber(queue, input, ptr);
			continue;
		}
		if (input[ptr] == '(') {
			ptr = parseLeftBracket(queue, stack, input, ptr);
			continue;
		}
		if (input[ptr] == ')') {
			ptr = parseRightBracket(queue, stack, input, ptr);
			continue;
		}
		if (ptr > 0 && (prevtype == PrevType::number || prevtype == PrevType::rightb)) {
			ptr = parseBinaryOperator(queue, stack, input, ptr);
			continue;
		}
		ptr = parseUnaryOperator(queue, stack, input, ptr);
	}
	while (!stack.empty()) {
		Node n = stack.top();
		stack.pop();
		switch (n.type)
		{
		case NodeType::ope1:
		case NodeType::ope2:
			queue.push(n);
			break;
		default:
			throw exception("can not find corresponding right bracket");
			break;
		}
	}
}

double calculate(queue<Node>& queue) {
	Node node;
	stack<double> ops;

	if (queue.empty()) throw exception("cannot calculate empty queue");
	node = queue.front();
	queue.pop();
	if (node.type != NodeType::number) throw exception("no number provided");
	ops.push(node.value.number);
	while (!queue.empty()) {
		node = queue.front();
		queue.pop();
		double op1, op2;
		switch (node.type)
		{
		case NodeType::number:
			ops.push(node.value.number);
			break;
		case NodeType::ope1:
			if (ops.empty()) throw exception("no enough number provided for ope1");
			op1 = ops.top();
			ops.pop();
			ops.push(node.value.unaryOperator->call(op1));
			break;
		case NodeType::ope2:
			if (ops.size() < 2) throw exception("no enough number provided for ope2");
			op2 = ops.top();
			ops.pop();
			op1 = ops.top();
			ops.pop();
			ops.push(node.value.binaryOperator->call(op1, op2));
			break;
		default:
			throw exception("should not happen");
			break;
		}
	}
	if (ops.size() != 1) throw exception("mult numbers are given");
	return ops.top();
}

double calc(const char* input) {
	initOperators();
	queue<Node> queue;
	parse(queue, input);
	return calculate(queue);
}

