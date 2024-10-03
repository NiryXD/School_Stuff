#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

const size_t ALPHABET_SIZE = 26;

class VigenereCipher {
  private:
    string mKey;
    char mVTable[ALPHABET_SIZE][ALPHABET_SIZE];
    string makeKeystream(const string& message) const; // Private function

  public:
    VigenereCipher(const string& key);
    string encrypt(const string& message) const;
    string decrypt(const string& message) const;
    string getKeystream(const string& message) const; // New public function
    void printVTable() const;
};

// Definition of private function to create the keystream
string VigenereCipher::makeKeystream(const string& message) const {
    string stream;
    size_t index = 0;
    for (char a : message) {
        if (isalpha(a)) {
            stream += (mKey[index % mKey.length()]);
            ++index;
        } else {
            stream += a;
        }
    }
    return stream;
}

// Constructor for VigenereCipher, builds the 26x26 Vigenère table
VigenereCipher::VigenereCipher(const string& key) {
    for (size_t a = 0; a < ALPHABET_SIZE; ++a) {
        for (size_t b = 0; b < ALPHABET_SIZE; ++b) {
            mVTable[a][b] = 'a' + (a + b) % ALPHABET_SIZE;
        }
    }
    mKey = key;
}

// Encryption method
string VigenereCipher::encrypt(const string& message) const {
    string keyStream = makeKeystream(message);
    string encrypted;

    for (size_t a = 0, index = 0; a < message.length(); ++a) {
        if (isalpha(message[a])) {
            char eChar = mVTable[(mKey[index % mKey.length()]) - 'a'][(message[a] - 'a')];
            encrypted += eChar;
            ++index;
        } else {
            encrypted += message[a];
        }
    }
    return encrypted;
}

// Decryption method
string VigenereCipher::decrypt(const string& message) const {
    string keyStream = makeKeystream(message);
    string decrypted;

    for (size_t a = 0, index = 0; a < message.length(); ++a) {
        if (isalpha(message[a])) {
            char key = (mKey[index % mKey.length()]);
            char eChar = (message[a]);
            char dChar = 'a' + ((eChar - key + 26) % 26);
            decrypted += dChar;
            ++index;
        } else {
            decrypted += message[a];
        }
    }
    return decrypted;
}

// Function to expose the keystream (public)
string VigenereCipher::getKeystream(const string& message) const {
    return makeKeystream(message); // Calls the private keystream generator
}

// Prints the Vigenère table (for debugging or educational purposes)
void VigenereCipher::printVTable() const {
    for (size_t a = 0; a < ALPHABET_SIZE; a++) {
        for (size_t b = 0; b < ALPHABET_SIZE; b++) {
            cout << " " << mVTable[a][b] << " ";
        }
        cout << endl;
    }
}

int main() {
    string key, message;
    char mode;

    // Get key from the user
    cout << "Enter the encryption key: ";
    getline(cin, key);

    // Get message from the user
    cout << "Enter the message: ";
    getline(cin, message);

    // Get mode (encrypt or decrypt)
    cout << "Enter mode (e for encrypt, d for decrypt): ";
    cin >> mode;

    VigenereCipher cipher(key);

    if (mode == 'e') {
        string encryptedMessage = cipher.encrypt(message);
        cout << "Encrypted Message: " << encryptedMessage << endl;
        cout << "Keystream: " << cipher.getKeystream(message) << endl; // Access the keystream
    } else if (mode == 'd') {
        string decryptedMessage = cipher.decrypt(message);
        cout << "Decrypted Message: " << decryptedMessage << endl;
        cout << "Keystream: " << cipher.getKeystream(message) << endl; // Access the keystream
    } else {
        cerr << "Invalid mode. Choose 'e' for encryption or 'd' for decryption." << endl;
        return 1;
    }

    return 0;
}
