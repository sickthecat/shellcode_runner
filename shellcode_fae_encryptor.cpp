#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class RC4 {
public:
    RC4(const std::vector<unsigned char>& key) {
        for (int i = 0; i < 256; ++i) {
            S[i] = i;
        }

        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + key[i % key.size()]) % 256;
            std::swap(S[i], S[j]);
        }
    }

    void encrypt(std::vector<unsigned char>& data) {
        int i = 0, j = 0;
        for (size_t k = 0; k < data.size(); ++k) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            std::swap(S[i], S[j]);
            data[k] ^= S[(S[i] + S[j]) % 256];
        }
    }

private:
    int S[256];
};

int main() {
    std::string key = "c60b710754e906a1609330e70760c2db"; // Replace with your key
    std::vector<unsigned char> keyBytes(key.begin(), key.end());

    std::ifstream inFile("update.bin", std::ios::binary);
    std::vector<unsigned char> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    RC4 rc4(keyBytes);
    rc4.encrypt(fileData);

    std::ofstream outFile("encrypted_update.bin", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(fileData.data()), fileData.size());
    outFile.close();

    return 0;
}
