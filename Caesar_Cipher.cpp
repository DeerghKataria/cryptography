#include <iostream>
using namespace std;

void caesarEncrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char character = text[i];
        if (isalpha(character)) {
            char base = (islower(character)) ? 'a' : 'A';
            character = base + (character - base + shift) % 26;
            text[i] = character;
        }
    }
}

void caesarDecrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char character = text[i];
        if (isalpha(character)) {
            char base = (islower(character)) ? 'a' : 'A';
            character = base + (character - base - shift + 26) % 26;
            text[i] = character;
        }
    }
}

int main() {
    char message[100];
    int key;
    
    cout << "Enter a message: ";
    cin.getline(message, 100);
    
    cout << "Enter key: ";
    cin >> key;
    
    // Encryption
    caesarEncrypt(message, key);
    cout << "Encrypted message: " << message << endl;
    
    // Decryption
    caesarDecrypt(message, key);
    cout << "Decrypted message: " << message << endl;
    
    return 0;
}
