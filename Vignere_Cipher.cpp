#include <iostream>
#include <string>
using namespace std;

class VigenereCipher {
public:
    string key;

    VigenereCipher(string key) {
        for (int i = 0; i < key.size(); ++i) {
            if (key[i] >= 'A' && key[i] <= 'Z')
                this->key += key[i];
            else if (key[i] >= 'a' && key[i] <= 'z')
                this->key += key[i] + 'A' - 'a';
        }
    }

    string encrypt(string plaintext) {
        string ciphertext;
        for (int i = 0, j = 0; i < plaintext.length(); ++i) {
            char c = plaintext[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            ciphertext += (c + key[j] - 2 * 'A') % 26 + 'A';
            j = (j + 1) % key.length();
        }
        return ciphertext;
    }

    string decrypt(string ciphertext) {
        string plaintext;
        for (int i = 0, j = 0; i < ciphertext.length(); ++i) {
            char c = ciphertext[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            plaintext += (c - key[j] + 26) % 26 + 'A';
            j = (j + 1) % key.length();
        }
        return plaintext;
    }
};

int main() {
    VigenereCipher vigenere("WELCOME");
    string originalMessage = "deerghkataria";
    string encryptedMessage = vigenere.encrypt(originalMessage);
    string decryptedMessage = vigenere.decrypt(encryptedMessage);

    cout << "Deergh Kataria A2305220099" << endl;
    cout << " " << endl;
    cout << "Original Message: " << originalMessage << endl;
    cout << "Encrypted Message: " << encryptedMessage << endl;
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
