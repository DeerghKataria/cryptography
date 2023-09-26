#include <iostream>
#include <vector>
using namespace std;

const char playfairMatrix[5][5] = {
    {'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'K'},
    {'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

void inputMessage(vector<char>& message) {
    char c;
    while (1) {
        c = getchar();
        if (c >= 97 && c <= 122)
            c -= 32;
        if (c == '\n')
            break;
        else if (c == ' ')
            continue;
        else if (c == 'J')
            message.push_back('I');
        message.push_back(c);
    }
    return;
}

void getPosition(char p, int& row, int& col) {
    if (p < 'J') {
        row = (p - 65) / 5;
        col = (p - 65) % 5;
    }
    else if (p > 'J') {
        row = (p - 66) / 5;
        col = (p - 66) % 5;
    }
    return;
}

void sameRow(int row, vector<char>& code, int col1, int col2) {
    code.push_back(playfairMatrix[row][(col1 + 4) % 5]);
    code.push_back(playfairMatrix[row][(col2 + 4) % 5]);
    return;
}

void sameColumn(int col, vector<char>& code, int row1, int row2) {
    code.push_back(playfairMatrix[(row1 + 4) % 5][col]);
    code.push_back(playfairMatrix[(row2 + 4) % 5][col]);
    return;
}

void differentRowColumn(int row1, int col1, vector<char>& code, int row2, int col2) {
    code.push_back(playfairMatrix[row1][col2]);
    code.push_back(playfairMatrix[row2][col1]);
    return;
}

void encryptPlayfair(vector<char> message, int length) {
    vector<char> code;
    int i = 0, j = 0;
    int row1, col1, row2, col2;
    while (i < length) {
        getPosition(message[i], row1, col1);
        i++;
        getPosition(message[i], row2, col2);
        if (row1 == row2) {
            sameRow(row1, code, col1, col2);
        }
        else if (col1 == col2) {
            sameColumn(col1, code, row1, row2);
        }
        else {
            differentRowColumn(row1, col1, code, row2, col2);
        }
        i++;
    }
    cout << "\nEncrypted Code: ";
    for (j = 0; j < code.size(); j++) {
        if (code[j] == 'X')
            continue;
        cout << code[j];
    }
    return;
}

void decryptPlayfair(vector<char> message, int length) {
    vector<char> decoded;
    int i = 0, j = 0;
    int row1, col1, row2, col2;
    while (i < length) {
        getPosition(message[i], row1, col1);
        i++;
        getPosition(message[i], row2, col2);
        if (row1 == row2) {
            // In decryption, we move left instead of right
            decoded.push_back(playfairMatrix[row1][(col1 + 1) % 5]);
            decoded.push_back(playfairMatrix[row2][(col2 + 1) % 5]);
        }
        else if (col1 == col2) {
            // In decryption, we move up instead of down
            decoded.push_back(playfairMatrix[(row1 + 1) % 5][col1]);
            decoded.push_back(playfairMatrix[(row2 + 1) % 5][col2]);
        }
        else {
            decoded.push_back(playfairMatrix[row1][col2]);
            decoded.push_back(playfairMatrix[row2][col1]);
        }
        i++;
    }
    cout << "\nDecoded Message: ";
    for (j = 0; j < decoded.size(); j++) {
        if (decoded[j] == 'X')
            continue;
        cout << decoded[j];
    }
    return;
}

int main() {
    int choice;
    cout << "Enter 1 for encryption or 2 for decryption: ";
    cin >> choice;
    cin.ignore();  // Clear the newline character from the buffer

    vector<char> message;
    cout << "Enter the Message: ";
    inputMessage(message);
    int length = message.size();

    if (choice == 1) {
        encryptPlayfair(message, length);
    }
    else if (choice == 2) {
        decryptPlayfair(message, length);
    }
    else {
        cout << "Invalid choice. Please enter 1 for encryption or 2 for decryption.";
    }

    cout << endl;

    return 0;
}
