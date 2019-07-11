#include <iostream>
#include <string>

class VigenereCipher {
    const int llb = 97, 
              lub = 122, 
              ulb = 65,
              uub = 90;
    std::string cipherText, cipherKey;

    public:
        std::string cipher(std::string plainText, std::string cipherKey);
    
    protected:
        bool isLowerCase(char inChar);
        bool isUpperCase(char inChar);
        bool inBounds(char inChar);
        int getFloor(char inChar);
        char caesar(char inChar, int offset);
        void correctKey();
        void vigenere();
};

std::string VigenereCipher::cipher(std::string plainText, std::string plainKey) {
    cipherText = plainText;
    cipherKey  = plainKey;

    // remove bad stuff from the key
    correctKey();

    vigenere();

    return cipherText;
}

bool VigenereCipher::isLowerCase(char inChar) {
    return (inChar >= llb && inChar <= lub);
}

bool VigenereCipher::isUpperCase(char inChar) {
    return (inChar >= ulb && inChar <= uub);
}

bool VigenereCipher::inBounds(char inChar) {
    if (isLowerCase(inChar)) {
        return true;
    } else if (isUpperCase(inChar)) {
        return true;
    }

    return false;
}

int VigenereCipher::getFloor(char inChar) {
    return isLowerCase(inChar) ? llb : ulb;
}

char VigenereCipher::caesar(char inChar, int offset) {
    auto floor = getFloor(inChar);

    return (((inChar + offset) - (floor + 97)) % 26) + floor;
}

void VigenereCipher::correctKey() {
    for (auto i = 0; i < cipherKey.length(); i++) {
        if (!inBounds(cipherKey[i])) {
            cipherKey.erase(i, 1);
        }

        if (isUpperCase(cipherKey[i])) {
            cipherKey[i] += 32;
        }
    }
}

void VigenereCipher::vigenere() {
    auto key_pos = 0;

    for (auto i = 0; i < cipherText.length(); i++) {
        if (key_pos > cipherKey.length()) {
            key_pos = 0;
        }

        cipherText[i] = caesar(cipherText[i], cipherKey[key_pos]);

        key_pos++;
    }
}

int main (int argc, char *argv[]) {
    std::string key;
    std::string input;
    VigenereCipher* vigenere = new VigenereCipher();

    std::cout << "Password: ";
    std::getline(std::cin, key);

    std::cout << "Phrase  : ";
    std::getline(std::cin, input);

    input = vigenere->cipher(input, key);

    std::cout << "Result  : " << input << std::endl;

    std::cout << "Press any key to exit...";
    getchar();

    return 0;
}