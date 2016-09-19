#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include "ciphers.h"
#include "utils.h"

using namespace std;

const int MAX = 10;						//number of ciphers

int max_size = 0;						//stores the maximum size of the cipher texts, also assumed to be size of key
string final_key;						//final key in hexadecimal form used to generate all cipher text
string plain_text[MAX];					//plaintext of all the cipher-texts in hexadecimal form
string xor_ciphers_space[MAX];			//ciphers[i] xor with string of spaces (in hexadecimal form)
string xor_ciphers[MAX][MAX];			//ciphers[i] xorred with other ciphers[j], i != j (in hexadecimal form)
map<int, int> space_positions;			//count of poisition which may contain space in cipher
vector<int> spaces;						//likely position of spaces in cipher[i]
set<int> known_key_positions;			//positions in final_key known, as per the statistics chosen

//'*' everwhere refers to unknown value

//Initialise all plaintexts to be unknown
void init_plain_texts() {
	for(int i = 0; i < MAX; ++i) {
		for(size_t j = 0; j < ciphers[i].size(); j += 1) {
			plain_text[i] += '*';
		}
	}
}

void init_final_key() {
	//find the optimal size of key
	for(int i = 0; i < MAX; ++i) {
		max_size = max(max_size, (int)ciphers[i].length());
	}
	//As (x xor 0 = x), final_key is initially set to 0, assuming ciphers and plaintext are same
	final_key = "";
	for(int i = 0; i < max_size; ++i) {
		final_key += '0';
	}
}

void init_xor_ciphers() {
	for(int i = 0; i < MAX; ++i) {
		//String xor with itself will gives "0...0"
		//But it is of no use, hence initialise to empty string
		xor_ciphers[i][i] = "";
		//Use the fact that xor is coomutative
		for(int j = 0; j < i; ++j) {
			xor_ciphers[i][j] = hex_xor(ciphers[i], ciphers[j]);
			xor_ciphers[j][i] = xor_ciphers[i][j];
		}
	}
}

void init_xor_spaces() {
	//Space in hexamdecimal is '20'
	//Thus for upper part(even index), xor it with '2'
	//and for lower part(odd index), xor it with '0'
	for(int i = 0; i < MAX; ++i) {
		xor_ciphers_space[i] = "";
		for(int j = 0; j < ciphers[i].size(); ++j) {
			if (j & 1) {
				xor_ciphers_space[i] += hex_xor(ciphers[i][j], '0');
			}
			else {
				xor_ciphers_space[i] += hex_xor(ciphers[i][j], '2');
			}
		}
	}
}

void analyse_spaces() {
	for(int i = 0; i < MAX; ++i) {
		spaces.clear();
		space_positions.clear();
		for(int j = 0; j < MAX; ++j) {
			if (j != i) {
				//xor_ciphers[i][j] has length of larger cipher text
				//For analysing spaces in cipher[i], only considering xor_cipher till size of cipher[i]
				for(int k = 0; k < ciphers[i].length(); k += 2) {
					if (is_alpha(xor_ciphers[i][j][k], xor_ciphers[i][j][k+1])) {
						//(k/2) is chosen as when converting string to hexadecimal, each character contributes 2 hexadecimal numbers
						space_positions[k/2] += 1;
					}
				}
			}
		}
		//Statistical test : If a space is found atleast 7 out of 9 times in the xor with other ciphers, it is assumed to space(' ')
		//Can be changed for getting differnt results
		for(map<int,int>::iterator it = space_positions.begin(); it != space_positions.end(); ++it) {
			if (it->second >= 7) {
				spaces.push_back(it->first);
			}
		}
		//Recreate the final key from the assumed (known) space positions
		for(size_t j = 0; j < spaces.size(); j += 1) {
			//retreive indices of string in hexadecimal form
			int idx = spaces[j] * 2;
			final_key[idx] = xor_ciphers_space[i][idx];
			final_key[idx + 1] = xor_ciphers_space[i][idx + 1];
			known_key_positions.insert(spaces[j]);
		}
	}
}

void find_plain_texts() {
	for(int i = 0; i < MAX; ++i) {
		string temp = hex_xor(ciphers[i], final_key);
		for(set<int>::iterator it = known_key_positions.begin(); it != known_key_positions.end(); ++it) {
			int idx = (*it) * 2;
			if (idx > plain_text[i].size()) {
				break;
			}
			plain_text[i][idx] = temp[idx];
			plain_text[i][idx + 1] = temp[idx + 1];
		}
	}
}

int main(int argc, char const *argv[]) {
	//Initialisation part
	init_encode();
	init_decode();
	init_ciphers();
	init_final_key();
	init_plain_texts();
	init_xor_ciphers();
	init_xor_spaces();

	//Analyse the probable position of spaces in key and cipher text
	analyse_spaces();

	//Find the probable plain texts from the assumed key
	find_plain_texts();

	//Find the plain text you want to decipher
	int plain_text_index = 0;
	for(int i = 0; argv[1][i] != '\0'; ++i) {
		plain_text_index = plain_text_index * 10 + (argv[1][i] - '0');
	}
	//0-based indexing
	plain_text_index -= 1;

	ofstream output_file;
	output_file.open(argv[2], ios::out);

	//output the plain text as per the statistical assumptions in required file
	//'*' in file denotes unknown character
	output_file << hex_string(plain_text[plain_text_index]) << "\n";

	output_file.close();

	return 0;
}