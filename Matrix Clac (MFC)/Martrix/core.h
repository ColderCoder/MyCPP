#pragma once
#include <string>
#include <exception>
std::string matrix_API(std::string in1, std::string in2, int type, int operation);
//type: 0-integer; 1-float number; 2-boolean
//operation: 1+; 2-; 3 multiply; 4 num-multiply; 5 transpose