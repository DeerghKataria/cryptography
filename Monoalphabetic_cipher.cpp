#include <iostream>
using namespace std;

string monoalphabeticEncrypt(string message, string alphabet, string substitution) {
    string ciphertext;
    for (int i = 0; i < message.size(); i++) {
        char character = message[i];
        int index = alphabet.find(character);
        if (index != string::npos) {
            // Replace the character with its substitution from the key.
            ciphertext.push_back(substitution[index]);
        } else {
            // If the character is not in the alphabet (e.g., space or punctuation), add it unchanged.
            ciphertext.push_back(character);
        }
    }
    return ciphertext;
}

string monoalphabeticDecrypt(string ciphertext, string alphabet, string substitution) {
    string plaintext;
    for (int i = 0; i < ciphertext.size(); i++) {
        char character = ciphertext[i];
        int index = substitution.find(character);
        if (index != string::npos) {
            // Replace the character with its original character from the alphabet.
            plaintext.push_back(alphabet[index]);
        } else {
            // If the character is not in the substitution (e.g., space or punctuation), add it unchanged.
            plaintext.push_back(character);
        }
    }
    return plaintext;
}

int main() {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string substitution = "qazwsxedcrvbtgynhujmikolp";
    string message = "deerghkataria";
    
    string cipherText = monoalphabeticEncrypt(message, alphabet, substitution);
    cout << "Encrypted Cipher Text: " << cipherText << endl;
    
    string plainText = monoalphabeticDecrypt(cipherText, alphabet, substitution);
    cout << "Decrypted Plain Text: " << plainText << endl;
    
    return 0;
}
