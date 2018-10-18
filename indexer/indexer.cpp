#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "indexer.h"
#include <map>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

string PATH = "/home/vdberg/CLionProjects/vector_model/";

vector<string> filesPath = {
        PATH + "cfc/cf74",
        PATH + "cfc/cf75",
        PATH + "cfc/cf76",
        PATH + "cfc/cf77",
        PATH + "cfc/cf78",
        PATH + "cfc/cf79"
};

vector<vector<string>> collection;

map<string, map<int, int>> vocabulary;

string wordFormat(string word) {
    char chars[] = "\"()@#$%¨&*+=[]/|{}`};:><?!,.'";

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

            string line;
            while (getline(readFile, line)) {
                if (line == "") {
                    collection.push_back(doc);
                    doc.clear();
                    continue;
                };

                string word;
                istringstream tmp(line);

                while (tmp >> word) {
                    word = wordFormat(word);
                    if (!any_of(word.begin(), word.end(), ::isdigit) && word.length() > 2) {
                        doc.push_back(word);
                    }
                }
            }

            readFile.close();
        } else return 1;
    }
    return 0;
}

int writeFile () {
    ofstream write;
    write.open (PATH + "indexer/indexation.txt");

    if (write.is_open()) {
        for (map<string, map<int, int>>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it) {
            string occurrencesPerDoc, occurrencesPerDocPrint;

            for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                string documentId = to_string(it2->first);
                string occurrences = to_string(it2->second);

//                occurrencesPerDocPrint += "(" + documentId + ", " + occurrences + "); ";

                occurrencesPerDoc += occurrencesPerDoc.empty() ?
                                     documentId + "," + occurrences : ";" + documentId + "," + occurrences;
            }
//            cout<< it->first + " -> " + occurrencesPerDocPrint << endl;
            write << it->first + ";" + occurrencesPerDoc + "\n";
        }

        write.close();
    }
    write.open (PATH + "indexer/collection_size.txt");
    if (write.is_open()) write << collection.size();

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

int readQuery() {
    ifstream readFile;

    readFile.open(PATH + "/cfc/cfquery");

    vector<map<string, map<int, int>>> queryList;

    if (readFile.is_open()) {
        string line;

        while (getline(readFile, line)) {
            if (line.find("QU") != string::npos) {
                line.erase(0, 3); // Remove QU e espaço

                string word;
                istringstream tmp(line);

                map<string, map<int, int>> queryPerString;

                while (tmp >> word) {
                    if (!any_of(word.begin(), word.end(), ::isdigit) && word.length() > 1) {
                        word = wordFormat(word);
                        bool termNotContained = vocabulary.find(word) == vocabulary.end();
                        if (!termNotContained) {
                            queryPerString[word] = vocabulary.at(word);
                        }
                    }
                }
                queryList.push_back(queryPerString);
            }
        }
        readFile.close();

        for (map<string, map<int, int>>::iterator it = queryList[0].begin(); it != queryList[0].end(); ++it) {
            string occurrencesPerDoc, occurrencesPerDocPrint;

            for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                string documentId = to_string(it2->first);
                string occurrences = to_string(it2->second);

                occurrencesPerDoc += occurrencesPerDoc.empty() ?
                                     documentId + "," + occurrences : ";" + documentId + "," + occurrences;
            }
            cout<< it->first + " -> " + occurrencesPerDoc << endl;
        }
    } else return 1;
}

int index() {
    cout << "Indexing..." <<endl;
    extractCollectionFromFiles();
    buildVocabulary();
    cout << "Indexed" <<endl;
}
