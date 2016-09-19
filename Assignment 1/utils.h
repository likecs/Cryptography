//Contains a list of utility functions
#include "decode.h"
#include "encode.h"

using namespace std;

//Returns the ascii value in decimal 
int get_ascii(char a, char b) {
	return (hex_encode[a] << 4) + hex_encode[b];
}

//Checks if given hexadecimal ascii value lies in range of alphabets ('a' - 'z', 'A' - 'Z')
bool is_alpha(char a, char b) {
	int ascii_value = get_ascii(a, b);
	return (ascii_value >= 65 && ascii_value <= 90) || (ascii_value >= 97 && ascii_value <= 122);
}

//Checks if given hexadecimal ascii value is that of space (' ') or not
bool is_space(char a, char b) {
	int ascii_value = get_ascii(a, b);
	return ascii_value == 32;
}

//Utility function to convert string to Hexadeimal equivalent
string string_hex(string cipher) {
	string result = "";
	for(int i = 0; i < cipher.length(); ++i) {
		//Each character in string will correspond to 2 hexadecimal ascii values
		char to_decode = cipher[i];
		int value = (int)to_decode;
		int lower_part = value & 15;
		int upper_part = (value - lower_part) >> 4;
		result += hex_decode[upper_part];
		result += hex_decode[lower_part];
	}
	return result;
}

//Utility function to convert Hexadecimal to string
//'*' indicates the hexadecimal value is unknown
string hex_string(string plain) {
	string result = "";
	for(int i = 0; i < plain.length(); i += 2) {
		if (plain[i] == '*') {
			result += '*';
		}
		else {
			char to_encode1 = plain[i];
			char to_encode2 = plain[i + 1];
			int to_decode = (hex_encode[to_encode1] << 4) + hex_encode[to_encode2];
			result += (char)to_decode;
		}
	}
	return result;
}

//Returns the hexadecimal xor of 2 hexadecimal numbers
char hex_xor(char a, char b) {
	int to_decode = hex_encode[a] ^ hex_encode[b];
	return hex_decode[to_decode];
}

//Utility function to generate the hexadecimal xor of 2 given strings
//The resulting string is padded with the remaining charcters of the larger string
string hex_xor(string cipher1, string cipher2) {
	string result = "";
	if (cipher1.length() > cipher2.length()) {
		for(int i = 0; i < cipher2.length(); ++i) {
			result += hex_xor(cipher1[i], cipher2[i]);
		}
		for(int i = cipher2.length(); i < cipher1.length(); ++i) {
			result += cipher1[i];
		}
	}
	else {
		for(int i = 0; i < cipher1.length(); ++i) {
			result += hex_xor(cipher1[i], cipher2[i]);
		}
		for(int i = cipher1.length(); i < cipher2.length(); ++i) {
			result += cipher2[i];
		}
	}
	return result;
}
