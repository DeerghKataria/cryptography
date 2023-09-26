#include<iostream>
#include<vector>
using namespace std;

int modularInverse(int a, int m) {
    a = a % m;
    for (int x = -m; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    // Return -1 to indicate that no modular inverse exists.
    return -1;
}

void getCofactorMatrix(vector<vector<int>>& matrix, vector<vector<int>>& temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int calculateDeterminant(vector<vector<int>>& matrix, int n, int N) {
    int determinant = 0;
    if (n == 1)
        return matrix[0][0];
    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactorMatrix(matrix, temp, 0, f, n);
        determinant += sign * matrix[0][f] * calculateDeterminant(temp, n - 1, N);
        sign = -sign;
    }
    return determinant;
}

void calculateAdjointMatrix(vector<vector<int>>& matrix, vector<vector<int>>& adjMatrix, int N) {
    if (N == 1) {
        adjMatrix[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int>> temp(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            getCofactorMatrix(matrix, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjMatrix[j][i] = (sign) * (calculateDeterminant(temp, N - 1, N));
        }
    }
}

bool calculateInverseMatrix(vector<vector<int>>& matrix, vector<vector<int>>& inverseMatrix, int N) {
    int det = calculateDeterminant(matrix, N, N);
    if (det == 0) {
        cout << "Inverse does not exist";
        return false;
    }
    int invDet = modularInverse(det, 26);
    vector<vector<int>> adjMatrix(N, vector<int>(N));
    calculateAdjointMatrix(matrix, adjMatrix, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverseMatrix[i][j] = (adjMatrix[i][j] * invDet) % 26;
    return true;
}

void hillCipherEncrypt(vector<vector<int>>& keyMatrix, string& message) {
    int n = keyMatrix.size();
    int padding = (n - message.size() % n) % n;
    for (int i = 0; i < padding; i++) {
        message += 'x';
    }
    int k = 0;
    string encryptedMessage = "";
    while (k < message.size()) {
        for (int i = 0; i < n; i++) {
            int sum = 0;
            int temp = k;
            for (int j = 0; j < n; j++) {
                sum += (keyMatrix[i][j] % 26 * (message[temp++] - 'a') % 26) % 26;
                sum = sum % 26;
            }
            encryptedMessage += (sum + 'a');
        }
        k += n;
    }
    cout << "Encrypted Message: " << encryptedMessage << '\n';
}

void hillCipherDecrypt(vector<vector<int>>& keyMatrix, string& message) {
    int n = keyMatrix.size();
    int k = 0;
    string decryptedMessage = "";
    while (k < message.size()) {
        for (int i = 0; i < n; i++) {
            int sum = 0;
            int temp = k;
            for (int j = 0; j < n; j++) {
                sum += ((keyMatrix[i][j] + 26) % 26 * (message[temp++] - 'a') % 26) % 26;
                sum = sum % 26;
            }
            decryptedMessage += (sum + 'a');
        }
        k += n;
    }
    int lastCharIndex = decryptedMessage.size() - 1;
    while (decryptedMessage[lastCharIndex] == 'x') {
        lastCharIndex--;
    }
    cout << "Decrypted Message: ";
    for (int i = 0; i <= lastCharIndex; i++) {
        cout << decryptedMessage[i];
    }
    cout << '\n';
}

int main() {
    int n;
    cout << "Enter the size of the key matrix: ";
    cin >> n;
    cout << "Enter the key matrix:\n";
    vector<vector<int>> keyMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> keyMatrix[i][j];
        }
    }

    cout << "Enter the message to encrypt/decrypt: ";
    string message;
    cin >> message;

    vector<vector<int>> inverseMatrix(n, vector<int>(n));
    if (calculateInverseMatrix(keyMatrix, inverseMatrix, n)) {
        cout << "Inverse exists\n";

        int choice;
        cout << "Enter 1 for encryption or 2 for decryption: ";
        cin >> choice;

        if (choice == 1) {
            hillCipherEncrypt(keyMatrix, message);
        }
        else if (choice == 2) {
            hillCipherDecrypt(inverseMatrix, message);
        }
        else {
            cout << "Invalid choice. Please enter 1 for encryption or 2 for decryption.";
        }
    }

    return 0;
}
