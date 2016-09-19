#include <map>

//Decimal to Hexadecimal convertor
std::map<int, char> hex_decode;

void init_decode() {
	hex_decode[0] = '0';
	hex_decode[1] = '1';
	hex_decode[2] = '2';
	hex_decode[3] = '3';
	hex_decode[4] = '4';
	hex_decode[5] = '5';
	hex_decode[6] = '6';
	hex_decode[7] = '7';
	hex_decode[8] = '8';
	hex_decode[9] = '9';
	hex_decode[10] = 'a';
	hex_decode[11] = 'b';
	hex_decode[12] = 'c';
	hex_decode[13] = 'd';
	hex_decode[14] = 'e';
	hex_decode[15] = 'f';
}
