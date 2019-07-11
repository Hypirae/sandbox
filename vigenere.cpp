#include <iostream>
#include <string>

// Stand-alone
// This flag enables code to allow the binary to operate apart from a terminal
#define STANDALONE 1

// ASCII bound constraints
#define ULB 65  // A
#define UUB 90  // Z
#define LLB 97  // a
#define LUB 122 // z

// Space ASCII code
#define SPACE 32

// Value to floor for Caesar
// 65 - CAESAR = 0
#define U_CAESAR 65
#define L_CAESAR 97

// Signatures
//void normalize(std::string &input);
bool inBounds(int inchar);
int getFloor(int inchar);
int caesar(int inchar, int offset);
int getKeyChar(std::string& key, int pos);
void vigenere2(std::string& input, std::string& key);

int main (int argc, char *argv[]) {
    std::string key;
    std::string input;

    std::cout << "Password: ";
    std::getline(std::cin, key);

    std::cout << "Phrase  : ";
    std::getline(std::cin, input);

    //normalize(key);
    //normalize(input);

    vigenere2(input, key);

    std::cout << "Result  : " << input << std::endl;

    #if STANDALONE == 1
    std::cout << "Press any key to exit...";
    getchar();
    #endif

    return 0;
}

// Check whether the character is withing one of our two bounds
// TODO: Make this whole thing more DRY
bool inBounds(int inchar) {
	if (inchar >= LLB && inchar <= LUB) {
		return true;
	}
	else if (inchar >= ULB && inchar <= UUB) {
		return true;
	}

	return false;
}

// Get the bound floor for the select character
// TODO: Make this whole thing more DRY
int getFloor(int inchar) {
	if (inchar >= LLB && inchar <= LUB) {
		return L_CAESAR;
	}
	else if (inchar >= ULB && inchar <= UUB) {
		return U_CAESAR;
	}

	return false;
}

// Calculate the caesar cipher for the character
int caesar(int inchar, int offset) {
	auto floor = getFloor(inchar);

	return (((inchar + offset) - (floor * 2)) % 26) + floor;
}

// Get the next valid key character
// TODO: handle edge cases better
int getKeyChar(std::string& key, int pos) {
	auto brk = 0;

	// loop through the key to get the next valid character
	while (brk < key.length()) {
		if (pos > key.length()) {
			pos = 0;
		}

		if (inBounds(key[pos])) {
			return key[pos];
		}

		brk++;
		pos++;
	}
}

void vigenere2(std::string& input, std::string& key) {
	auto key_pos = 0;
	char key_char;

	for (auto i = 0; i < input.length(); i++) {
		if (inBounds(input[i])) {

			// BUG: If the key has invalid characters this will not track the position right
			key_char = getKeyChar(key, key_pos);
			key_pos++;

			input[i] = caesar(input[i], key_char);
		}
	}
}