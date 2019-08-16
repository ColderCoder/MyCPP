#include<iostream>
#include<vector>
#include<string>
#include<exception>
using namespace std;

bool stob(string);

template<typename T>
class Matrix
{
public:
	Matrix() {};
	Matrix(string in1, string in2, int type, int ope) {
		m=n=m2=n2=1;
		switch (ope)
		{
		case 4://num-multiply
			if (in2.length() != 1)
				throw exception("the secondary input must be of one element to do the num-multiply");
		case 1://+
		case 2://-
		case 3://x
			parse1(in1, type, ope);
			parse2(in2, type, ope);
			break;
		case 5://transpose
			parse1(in1, type, ope);
			break;
		default:
			break;
		}
	}
	~Matrix() {};

	//parse input1
	void parse1(string in, int type, int ope) {//containerlize the input string
		int ptr = 0;
		//get n
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == ' ') n++;
			else if (in[i] == '\r') break;
		}
		//get m 
		int counter = 0;//count the element per row (n)
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == ' ' || in[i] == '\r'||i==in.length()-1) {
				++counter;
				switch (type)
				{
				case 0:
					M1.push_back(stoi(in.substr(ptr, i - ptr+1)));
					break;
				case 1:
					M1.push_back(stof(in.substr(ptr, i - ptr+1)));
					break;
				case 2:
					M1.push_back(stob(in.substr(ptr, i - ptr + 1)));
					break;
				default:
					throw exception("invalid data type!");
					break;
				}
				ptr = i + 1;
			}
			else if (in[i] == '\n') {
				if (in[i - 1] == '\r') {
					if (counter == n) {
						++m; ++ptr;
						counter = 0;
					}
					else
					throw exception("NOT a Matrix");
				}
				else throw exception("Unexpected Error");
			}
		}
		//if (in.length() != m * n)throw exception("invalid matrix input!");
	}

	//parse input2
	void parse2(string in, int type, int ope) {//containerlize the input string
		int ptr = 0;
		//get n2
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == ' ') n2++;
			else if (in[i] == '\r') break;
		}
		if (n2 == 0) n2++;
		//get m2
		int counter = 0;//count the element per row (n)
		for (int i = 0; i < in.length(); i++) {
			if (in[i] == ' ' || in[i] == '\r' || i == in.length() - 1) {
				++counter;
				switch (type)
				{
				case 0:
					M2.push_back(stoi(in.substr(ptr, i - ptr + 1)));
					break;
				case 1:
					M2.push_back(stof(in.substr(ptr, i - ptr + 1)));
					break;
				case 2:
					M2.push_back(stob(in.substr(ptr, i - ptr + 1)));
					break;
				default:
					throw exception("invalid data type!");
					break;
				}
				ptr = i + 1;
			}
			else if (in[i] == '\n') {
				if (in[i - 1] == '\r') {
					if (counter == n2) {
						++m2; ++ptr;
						counter = 0;
					}
					else
						throw exception("NOT a Matrix");
				}
				else throw exception("Unexpected Error");
			}
		}
		//if (in.length() != m2 * n2)throw exception("invalid matrix input!");
	}


	bool stob(string sub) {//string to boolean
		if (sub.length() <= 2) {
			if (sub[0] == '1')return 1;
			else if (sub[0] == '0')return 0;
			else throw exception("boolean matrix contains invalid data!!");
		}
		else
			throw exception("boolean matrix contains invalid data!");
	}


	string add() {
		if (n != n2 || m != m2)throw exception("two matrices not match");
		string result;
		for (int i = 0; i < M1.size(); i++) {
			T tmp = M1[i] + M2[i];
			string temp = to_string(static_cast<long long>(tmp));
			if ((i + 1) / n * n != i + 1) {
				result = result + temp + " ";
			}
			else
				result = result + temp + "\r\n";
		}
		return result;
	}

	string minus() {
		if (n != n2 || m != m2)throw exception("two matrices not match");
		string result;
		for (int i = 0; i < M1.size(); i++) {
			T tmp = M1[i] - M2[i];
			string temp = to_string(static_cast<long long>(tmp));
			if ((i + 1) / n * n != i + 1) {
				result = result + temp + " ";
			}
			else
				result = result + temp + "\r\n";
		}
		return result;
	}

	string multiply() {
		if (n != m2)
			throw exception("two matrices not match");
		
		string result;
		for (int i = 0; (i < m * n2)&& M1.size()>0&& M2.size()>0; i++) {
			int a = i / n2, b = i % n2; //a row, b column
			int index1 = a * n, index2 = b; //index of M1, M2
			T sum = 0;
			for (int j=0; j < n; j++) {
				sum += M1[index1] * M2[index2];
				index1++;
				index2 += n2;
			}
			result += to_string(sum);
			if ((i + 1) % n2 == 0)result += "\r\n";
			else result += " ";
		}
		return result;
	}

	string num_mul() {
		string result;
		for (int i = 0; i < M1.size(); i++) {
			T tmp = M1[i] * M2[0];
			string temp = to_string(tmp);
			if ((i + 1) / n * n != i + 1) {
				result = result + temp + " ";
			}
			else
				result = result + temp + "\r\n";
		}
		return result;
	}

	string transpose() {
		string result;
		int index = 0; //the index of the original
		for (int i = 0; i < M1.size(); i++) {
			result += to_string(M1[index]);
			//index change:
			if ((i+1)/m*m==i+1) index = index - (m - 1) * n + 1;
			else index += n;
			//append space or return:
			if ((i + 1) / m * m == i + 1)result += "\r\n";
			else result += " ";
		}
		return result;
	}

private:
	vector<T>M1;
	vector<T>M2;
	string result;
	int m , n; //of size m x n 
	int m2, n2; //size of the second matrix 
};

string matrix_API(string in1, string in2, int type, int operation) {
	//type: 0-integer; 1-float number; 2-boolean
	//operation: 1+; 2-; 3 multiply; 4 num-multiply; 5 transpose
	string result;
	//initialize matrix class
	if (type == 0) {
		if (operation == 1) { Matrix<long long> matrix(in1, in2, 0, 1); result = matrix.add(); }
		else if (operation == 2) { Matrix<long long> matrix(in1, in2, 0, 2); result = matrix.minus(); }
		else if (operation == 3) { Matrix<long long> matrix(in1, in2, 0, 3); result = matrix.multiply(); }
		else if (operation == 4) { Matrix<long long> matrix(in1, in2, 0, 4); result = matrix.num_mul(); }
		else if (operation == 5) { Matrix<long long> matrix(in1, in2, 0, 5); result = matrix.transpose(); }
		else throw exception("invalid operation");
	}
	else if (type == 1) {
		if (operation == 1) { Matrix<long double> matrix(in1, in2, 1, 1); result = matrix.add(); }
		else if (operation == 2) { Matrix<long double> matrix(in1, in2, 1, 2); result = matrix.minus(); }
		else if (operation == 3) { Matrix<long double> matrix(in1, in2, 1, 3); result = matrix.multiply(); }
		else if (operation == 4) { Matrix<long double> matrix(in1, in2, 1, 4); result = matrix.num_mul(); }
		else if (operation == 5) { Matrix<long double> matrix(in1, in2, 1, 5); result = matrix.transpose(); }
		else throw exception("invalid operation");
	}
	else if (type == 2) {
		if (operation == 1) { Matrix<bool> matrix(in1, in2, 2, 1); result = matrix.add(); }
		else if (operation == 2) { Matrix<bool> matrix(in1, in2, 2, 2);  result = matrix.minus(); }
		else if (operation == 3) { Matrix<bool> matrix(in1, in2, 2, 3); result = matrix.multiply(); }
		else if (operation == 4) { Matrix<bool> matrix(in1, in2, 2, 4); result = matrix.num_mul(); }
		else if (operation == 5) { Matrix<bool> matrix(in1, in2, 2, 5); result = matrix.transpose(); }
		else throw exception("invalid operation");
	}
	else
		throw exception("invalid data type!");

	return result;
}


