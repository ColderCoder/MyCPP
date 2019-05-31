# include"calc.h"
# include<iostream>

int main()
{
	char input [200];
	memset(input, 0, sizeof(input));
	std::cout << "Please input your notation and press Enter:\n";
	std::cin >> input;
	std::cout <<std::endl<<"The result is:\n"<< calc(input)<<std::endl;
	return 0;
}
