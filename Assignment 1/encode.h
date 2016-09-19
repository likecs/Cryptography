#include <map>

//Hexadecimal to decimal convertor
std::map<int, int> hex_encode;

void init_encode() {
	hex_encode['0'] = 0;
	hex_encode['1'] = 1;
	hex_encode['2'] = 2;
	hex_encode['3'] = 3;
	hex_encode['4'] = 4;
	hex_encode['5'] = 5;
	hex_encode['6'] = 6;
	hex_encode['7'] = 7;
	hex_encode['8'] = 8;
	hex_encode['9'] = 9;
	hex_encode['a'] = 10;
	hex_encode['b'] = 11;
	hex_encode['c'] = 12;
	hex_encode['d'] = 13;
	hex_encode['e'] = 14;
	hex_encode['f'] = 15;
}
