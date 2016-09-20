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

string decrypted_10 = "The whole point of cryptography is to keep the plaintext secret from eavesdroppers also called adversaries, attackers, interceptors, interlopers, intruders, opponents, or simply the enemy. Eavesdroppers are assumed to have complete access to the communications between the sender and receiver. Cryptanalysis is the science of recovering the plaintext of a message without access to the key. Successful cryptanalysis may recover the plaintext or the key. It also may find weaknesses in a cryptosystem that eventually lead to the previous results. (The loss of a key through noncryptanalytic means is called a compromise.)";

int main() {

	freopen("key.txt", "w", stdout);
	
	init_encode();
	init_decode();
	init_ciphers();

	string hex_form = string_hex(decrypted_10);

	string key = hex_xor(hex_form, ciphers[9]);

	cout << key << "\n";

	return 0;
}