#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

vector<int> compress(string uncompressed) {
    int dictSize = 256;
    map<string, int> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary[string(1, i)] = i;

    string w = "";
    vector<int> result;
    for (char c : uncompressed) {
        string wc = w + c;
        if (dictionary.count(wc))
            w = wc;
        else {
            result.push_back(dictionary[w]);
            dictionary[wc] = dictSize++;
            w = string(1, c);
        }
    }

    if (!w.empty())
        result.push_back(dictionary[w]);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: lzw <text_to_compress>" << endl;
        return 1;
    }
    string input = argv[1];
    vector<int> compressed = compress(input);
    cout << "[+] Original size: " << input.length() << " bytes" << endl;
    cout << "[+] Compressed code values: ";
    for (int code : compressed) {
        cout << code << " ";
    }
    cout << endl;
    cout << "[+] Compressed size: " << compressed.size() * sizeof(int) << " bytes (as integers)" << endl;
    return 0;
}