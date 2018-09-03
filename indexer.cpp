#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "indexer.h"
#include <map>
#include <string.h>
#include <vector>

using namespace std;

vector<string> filesPath = {
    "/home/berg/Downloads/cfc/cf74",
    "/home/berg/Downloads/cfc/cf75",
    "/home/berg/Downloads/cfc/cf76",
    "/home/berg/Downloads/cfc/cf77",
    "/home/berg/Downloads/cfc/cf78",
    "/home/berg/Downloads/cfc/cf79"
};

vector<vector<string>> collection;

map<string, map<int, int>> vocabulary;

string wordFormat(string word) {
    char chars[] = "\"()@#$%¨&*+=[]/|{}`};:><,.'";

    transform(word.begin(), word.end(), word.begin(), ::tolower);

    for (unsigned int j = 0; j < strlen(chars); ++j) {
        word.erase(remove(word.begin(), word.end(), chars[j]), word.end());
    }

    return word;
}

int extractCollectionFromFiles() {
    ifstream readFile;

    for (unsigned i = 0; i < filesPath.size(); i++) {
        readFile.open(filesPath.at(i));

        vector<string> doc;

        if (readFile.is_open()) {
            string word;

            while (readFile >> word) {
                if (!any_of(word.begin(), word.end(), ::isdigit)) {
                    word = wordFormat(word);
                    doc.push_back(word);
                }
            }

            collection.push_back(doc);
            readFile.close();
        } else return 1;
    }

    return 0;
}

int writeFile () {
    ofstream write;
    write.open ("/home/berg/CLionProjects/RI/tp1/indexation.txt");

    if (write.is_open()) {
        for (map<string, map<int, int>>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it) {
            string occurrencesPerDoc, occurrencesPerDocPrint;

            for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                string documentId = to_string(it2->first);
                string occurrences = to_string(it2->second);

                occurrencesPerDocPrint += "(" + documentId + ", " + occurrences + "); ";

                occurrencesPerDoc += occurrencesPerDoc.empty() ?
                                     documentId + "," + occurrences : ";" + documentId + "," + occurrences;
            }
            cout<< it->first + " -> " + occurrencesPerDocPrint << endl;
            write << it->first + ";" + occurrencesPerDoc + "\n";
        }

        write.close();
    }
    return 0;
}

    int buildVocabulary() {
    for (unsigned i = 0; i < collection.size(); i++) {
        vector<string> doc = collection.at(i);

        for (unsigned j = 0; j < doc.size(); j++) {
            string term = doc.at(j);

            map<int, int> occurrencesPerDoc;
            bool termNotContained = vocabulary.find(term) == vocabulary.end();

            if (termNotContained) {
                occurrencesPerDoc = { {i, 1} };
            } else {
                occurrencesPerDoc = vocabulary.at(term);
                bool docIdNotContained = occurrencesPerDoc.find(i) == occurrencesPerDoc.end();

                if (docIdNotContained) {
                    occurrencesPerDoc[i] = 1;
                } else {
                    int occurrences = occurrencesPerDoc.at(i);
                    occurrencesPerDoc[i] = occurrences + 1;
                }
            }
            vocabulary[term] = occurrencesPerDoc;
        }
    }
    writeFile();
}

int index() {
    cout << "Indexing..." <<endl;
    extractCollectionFromFiles();
    buildVocabulary();
    cout << "Indexed" <<endl;
}
