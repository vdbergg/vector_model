#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "indexer.h"
#include <map>
#include <math.h>
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
}

int writeIndexationFile() {
    ofstream write;
    write.open(PATH + "indexer/indexation.txt");

    if (write.is_open()) {
        string indexation;

        for (map<string, map<int, int>>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it) {
            string occurrencesPerDoc, occurrencesPerDocPrint;

            map<int, int> docWithOccurrencesPerTerm = it->second;
            double reason = (double) collection.size() / docWithOccurrencesPerTerm.size();
            double idfPerTerm = log(reason);

            double maxWeight = 0;

            for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                string documentId = to_string(it2->first);
                int occurrences = it2->second;
                double weight = idfPerTerm * occurrences;

                if (weight > maxWeight) maxWeight = weight;

//                occurrencesPerDocPrint += "(" + documentId + ", " + occurrences + "," + to_string(weight) + "); ";

                if (occurrencesPerDoc.empty()) {
                    occurrencesPerDoc += documentId + "," + to_string(occurrences) + "," + to_string(weight);
                } else {
                    occurrencesPerDoc += ";" + documentId + "," + to_string(occurrences) + "," + to_string(weight);
                }
            }
//            cout<< it->first + " | " + to_string(idfPerTerm) + " | " + to_string(maxWeight) + " -> " + occurrencesPerDocPrint << endl;
            indexation += it->first + "|" + to_string(idfPerTerm) + "|" + to_string(maxWeight) + "|" + occurrencesPerDoc + "\n";
        }
        write << indexation;
        write.close();
    } else return 1;

    write.open(PATH + "indexer/norms_per_doc.txt");
    if (write.is_open()) {
        string norms;

        for (int j = 0; j < collection.size(); j++) {
            double sumWeightSquared = 0;

            for (map<string, map<int, int>>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it) {
                map<int, int> docWithOccurrencesPerTerm = it->second;
                double reason = (double) collection.size() / docWithOccurrencesPerTerm.size();
                double idfPerTerm = log(reason);

                bool docIdNotContained = docWithOccurrencesPerTerm.find(j) == docWithOccurrencesPerTerm.end();

                if (!docIdNotContained) {
                    sumWeightSquared += pow(idfPerTerm * docWithOccurrencesPerTerm[j], 2);
                }
            }

            double norm = sqrt(sumWeightSquared);

            norms += norms.empty() ? to_string(j) + "," + to_string(norm) : ";" + to_string(j) + "," + to_string(norm);
        }
        write << norms;
        write.close();
    } else return 1;

    return 0;
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
    writeIndexationFile();
    cout << "Indexed" <<endl;
}
