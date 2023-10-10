#include <iostream>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

struct charUsage {
    char c;
    int count;
};

struct valueUsage {
    string value;
    int count;
    int order;
};

void addValueToArray(string &str_in, struct valueUsage valueUsageArray[], int &valueUsageArraySize) {
    int i;
    for (i = 0; i < valueUsageArraySize; i++) {
        if (valueUsageArray[i].value.compare(str_in) == 0) {
            valueUsageArray[i].count++;
            break;
        }
    }
    if (valueUsageArraySize > 24999) {
        cout << "Word Count has been exceeded" << endl;
        exit(-1);
    }
    if (i == valueUsageArraySize) {
        valueUsageArray[valueUsageArraySize].count = 1;
        valueUsageArray[valueUsageArraySize].value = str_in;
        valueUsageArray[valueUsageArraySize].order = i;
        valueUsageArraySize++;
    }
}

void sortValueUsage(struct valueUsage valueUsageArray[], int valueUsageArraySize) {
    int maxCount = 0;
    int maxIndex = 0;
    for (int i = 0; i < valueUsageArraySize; i++) {
        maxCount = valueUsageArray[i].count;
        maxIndex = i;
        for (int j = i+1; j < valueUsageArraySize; j++) {
            if (valueUsageArray[j].count > maxCount) {
                maxCount = valueUsageArray[j].count;
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            string tempBuffer = valueUsageArray[i].value;
            int tempCount = valueUsageArray[i].count;
            int tempOrder = valueUsageArray[i].order;
            valueUsageArray[i].value = valueUsageArray[maxIndex].value;
            valueUsageArray[i].count = valueUsageArray[maxIndex].count;
            valueUsageArray[i].order = valueUsageArray[maxIndex].order;
            valueUsageArray[maxIndex].value = tempBuffer;
            valueUsageArray[maxIndex].count = tempCount;
            valueUsageArray[maxIndex].order = tempOrder;
        }
    }

    int startIndex = -1;
    int stopIndex = 0;
    int minOrder = 0;
    int minIndex= 0;
    for (int h = 0; h < valueUsageArraySize; h++) {
        if (valueUsageArray[h].count != valueUsageArray[h + 1].count) {
            if (startIndex != -1) {
                stopIndex = h;
                for (int l = startIndex; l < stopIndex; l++) {
                    minOrder = valueUsageArray[l].order;
                    minIndex = l;
                    for (int j = l+1; j <= stopIndex; j++) {
                        if (valueUsageArray[j].order < minOrder) {
                            minOrder = valueUsageArray[j].order;
                            minIndex = j;
                        }
                    }
                    if (minIndex != l) {
                        string tempBuffer = valueUsageArray[l].value;
                        int tempCount = valueUsageArray[l].count;
                        int tempOrder = valueUsageArray[l].order;
                        valueUsageArray[l].value = valueUsageArray[minIndex].value;
                        valueUsageArray[l].count = valueUsageArray[minIndex].count;
                        valueUsageArray[l].order = valueUsageArray[minIndex].order;
                        valueUsageArray[minIndex].value = tempBuffer;
                        valueUsageArray[minIndex].count = tempCount;
                        valueUsageArray[minIndex].order = tempOrder;
                    }
                }
                startIndex = -1;
            }
        } else {
            if (startIndex == -1) {
                startIndex = h;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        if (valueUsageArray[i].count != 0) {
            cout << "  No. " << i << ": " << valueUsageArray[i].value << '\t' << valueUsageArray[i].count
                 << endl;
        }
    }
}

// Selection sort technique
void sortCharUsage(struct charUsage charUsageArray[]) {
    int maxCount = 0;
    int maxIndex = 0;
    for (int i = 0; i < 5; i++) {
        maxCount = charUsageArray[i].count;
        maxIndex = i;
        for (int j = i + 1; j < 256; j++) {
            if (charUsageArray[j].count > maxCount) {
                maxCount = charUsageArray[j].count;
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            char tempC = charUsageArray[i].c;
            int tempCount = charUsageArray[i].count;
            charUsageArray[i].c = charUsageArray[maxIndex].c;
            charUsageArray[i].count = charUsageArray[maxIndex].count;
            charUsageArray[maxIndex].c = tempC;
            charUsageArray[maxIndex].count = tempCount;
        }
    }
    int startIndex = -1;
    int stopIndex = 0;
    int minAscii = 0;
    int minIndex= 0;
    for (int h = 0; h < 256; h++) {
        if (charUsageArray[h].count != charUsageArray[h + 1].count) {
            if (startIndex != -1) {
                stopIndex = h;
                for (int l = startIndex; l < stopIndex; l++) {
                    minAscii = charUsageArray[l].c;
                    minIndex = l;
                    for (int j = l + 1; j <= stopIndex; j++) {
                        if (charUsageArray[j].c < minAscii) {
                            minAscii = charUsageArray[j].c;
                            minIndex = j;
                        }
                    }
                    if (minIndex != l) {
                        char tempBuffer = charUsageArray[l].c;
                        int tempCount = charUsageArray[l].count;
                        charUsageArray[l].c = charUsageArray[minIndex].c;
                        charUsageArray[l].count = charUsageArray[minIndex].count;
                        charUsageArray[minIndex].c = tempBuffer;
                        charUsageArray[minIndex].count = tempCount;
                    }
                }
                startIndex = -1;
            }
        } else {
            if (startIndex == -1) {
                startIndex = h;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        cout <<  "  No. " << i << ": ";
        switch (charUsageArray[i].c) {
            case '\n':
                cout << "\\n";
                break;
            case '\t':
                cout << "\\t";
                break;
            default:
                cout << charUsageArray[i].c;
                break;
        }
       cout << '\t' << charUsageArray[i].count << endl;
    }

}

int main() {
    char buffer[256] = {0};
    int bufferIndex = 0;
    bool charType = false;
    bool numType = false;
    ifstream my_file;
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    int diffChars = 0;
    struct charUsage charUsageArray[256] = {0};
    struct valueUsage* idUsageArray = new valueUsage[25000];
    int idUsageArraySize = 0;
    struct valueUsage* numUsageArray = new valueUsage[25000];
    int numUsageArraySize = 0;
    char c;

    for (int i = 0; i < 256; i++) {
        charUsageArray[i].c = i;
        charUsageArray[i].count = 0;
    }

    for (int i = 0; i < 25000; i++) {
        idUsageArray[i].value = "";
        idUsageArray[i].count = 0;
        idUsageArray[i].order = -1;
        numUsageArray[i].value = "";
        numUsageArray[i].count = 0;
        numUsageArray[i].order = -1;
    }
    //string my_fileName;
    //cin >> my_fileName;
    //my_file.open(my_fileName, std::ifstream::binary);

    // If the file was successfully opened then start the word count
    //if (my_file.is_open()) {

        while (cin.peek() != EOF) {
            cin.read(&c, 1);
            charCount++;
            charUsageArray[(int)c].count++;
            //cout << c << endl;
            //cout << (int)c << endl;
            if (charUsageArray[(int)c].count== 1) {
                diffChars++;
            }
            // Update Line count
            if (c == '\n') {
                // cout << "Adding 1" << (int)c << endl;
                lineCount++;
            }

            if (c >= 48 && c <= 57) {
                numType = true;
                buffer[bufferIndex] = c;
                bufferIndex++;
                if (bufferIndex >= 255) {
                    buffer[bufferIndex] = '\0';
                    cout << "Word " << buffer << " too long!! Exit." << endl;
                    if (idUsageArray != nullptr) {
                        delete[] idUsageArray;
                    }
                    if (numUsageArray != nullptr) {
                        delete[] numUsageArray;
                    }
                    return -1;
                }
            } else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
                if (numType && !charType) {
                    buffer[bufferIndex] = '\0';
                    wordCount++;
                    //cout << buffer << endl;
                    string str_in(buffer);
                    bufferIndex = 0;
                    addValueToArray(str_in, numUsageArray, numUsageArraySize);
                    numType = false;
                }
                charType = true;
                buffer[bufferIndex] = tolower(c);
                bufferIndex++;
                if (bufferIndex >= 255) {
                    buffer[bufferIndex] = '\0';
                    cout << "Word " << buffer << " too long!! Exit." << endl;
                    if (idUsageArray != nullptr) {
                        delete[] idUsageArray;
                    }
                    if (numUsageArray != nullptr) {
                        delete[] numUsageArray;
                    }

                    return -1;
                }
            } else {
                if (bufferIndex != 0) {
                    buffer[bufferIndex] = '\0';
                    wordCount++;
                    //cout << buffer << endl;
                    string str_in(buffer);
                    bufferIndex = 0;
                    if (numType && !charType) {
                        addValueToArray(str_in, numUsageArray, numUsageArraySize);
                    } else {
                        addValueToArray(str_in, idUsageArray, idUsageArraySize);
                    }
                }

                charType = false;
                numType = false;
            }
        }
        // Special case for no end word/file delimiter
        if (bufferIndex != 0) {
            buffer[bufferIndex] = '\0';
            wordCount++;
            string str_in(buffer);
            if (numType && !charType) {
                addValueToArray(str_in, numUsageArray, numUsageArraySize);
            } else {
                addValueToArray(str_in, idUsageArray, idUsageArraySize);
            }
        }
#if 0
        if (numType && charType) {
            idCount++;
        }
#endif
        my_file.close();
    } else {
       // cout << "Usage: " << argv[0] << " < input.txt" << endl;
        if (idUsageArray != nullptr) {
            delete[] idUsageArray;
        }
        if (numUsageArray != nullptr) {
            delete[] numUsageArray;
        }

        return -1;
    }

    //Lines, Words, Characters
    cout << lineCount << " " << wordCount << " " << charCount << endl;
    if (diffChars >= 5) {
        cout << "Total " << diffChars << " different characters, 5 most used characters:" << endl;
    } else {
        cout << "Total " << diffChars << " different characters, " << diffChars <<" most used characters:" << endl;
    }
    sortCharUsage(charUsageArray);
    cout << endl;
    if (idUsageArraySize >= 5) {
        cout << "Total " << idUsageArraySize << " different identifiers, 5 most used identifiers:" << endl;
    } else {
        cout << "Total " << idUsageArraySize << " different identifiers, "<< idUsageArraySize << " most used identifiers:" << endl;
    }
    sortValueUsage(idUsageArray, idUsageArraySize);
    cout << endl;
    if (numUsageArraySize >= 5) {
        cout << "Total " << numUsageArraySize << " different numbers, 5 most used numbers:" << endl;
    } else {
        cout << "Total " << numUsageArraySize << " different numbers, "<< numUsageArraySize <<" most used numbers:" << endl;

    }
    sortValueUsage(numUsageArray, numUsageArraySize);
    if (idUsageArray != nullptr) {
        delete[] idUsageArray;
    }
    if (numUsageArray != nullptr) {
        delete[] numUsageArray;
    }

    return 0;
}
