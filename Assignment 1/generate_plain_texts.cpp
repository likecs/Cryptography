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

int main() {

	freopen("key.txt", "r", stdin);
	freopen("plaintext.txt", "w", stdout);
	
	init_encode();
	init_decode();
	init_ciphers();

	string key;
	cin >> key;
	int key_length = key.length();

	for(int i = 0; i < MAX; ++i) {
		string plaintext = hex_xor(key, ciphers[i]);

		int limit = min(key_length, (int)ciphers[i].length());

		for(int j = 0; j < limit; j += 2) {
			string to_decode = "";
			to_decode += plaintext[j];
			to_decode += plaintext[j + 1];
			string decoded = hex_string(to_decode);
			cout << decoded;
		}
		cout << "\n";
	}

	return 0;
}