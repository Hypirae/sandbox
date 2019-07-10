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
#define CAESAR 65

// Signatures
void normalize(std::string &input);
void vigenere(std::string &input, std::string &key);
//char calculate(int inchar, int offset);

int main (int argc, char *argv[]) {
    std::string key;
    std::string input;

    std::cout << "Password: ";
    std::getline(std::cin, key);

    std::cout << "Phrase  : ";
    std::getline(std::cin, input);

    normalize(key);
    normalize(input);

    vigenere(input, key);

    std::cout << "Result  : " << input << std::endl;

    #if STANDALONE == 1
    std::cout << "Press any key to exit...";
    getchar();
    #endif

    return 0;
}

// Normalize the input to contain only uppercase letters
void normalize(std::string &input) {
    for (auto i = 0; i < input.length(); i++) {
        // if in lower ASCII range
        if (input[i] >= LLB && input[i] <= LUB) {
            input[i] -= 32;
        } 
        
        // if outside of higher ASCII range
        else if (!(input[i] >= ULB && input[i] <= UUB)) {
            input[i] = SPACE;
        }
    }
}

// Perform the vigenere cipher
void vigenere(std::string &input, std::string &key) {
    const auto key_length = key.length();
    auto key_step = 0;

    // calculate the caesar cipher for the character
    auto calculate = [](auto inchar, auto offset) {
        if (inchar == SPACE) {
            return SPACE;
        }

        return (((inchar + offset) - (CAESAR * 2)) % 26) + CAESAR;
    };

    for (auto i = 0; i < input.length(); i++) {
        if (key[key_step] == SPACE) {
            key_step++;
        }

        if (key_step == key_length) {
            key_step = 0;
        }

        if (input[i] != SPACE) {
            input[i] = calculate(input[i], key[key_step]);
            key_step++;
        }
    }
}