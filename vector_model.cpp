#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "vector_model.h"
#include <sstream>

using namespace std;

const double COLLECTION_SIZE = 6;

map<string, map<int, int>> invertedList;
map<string, double> idfPerTerm;

vector<string> splitString(string text, char character) {
    stringstream test(text);
    string line;
    vector<string> item;

    while (getline(test, line, character)) item.push_back(line);

    return item;
}

int readIndexation() {
    cout<< "Reading indexation..." << endl;

    ifstream readFile;
    readFile.open("/home/berg/CLionProjects/RI/tp1/indexation.txt");

    if (readFile.is_open()) {
        string word;

        while (readFile >> word) {

            vector<string> termAndOccurrences = splitString(word, ';');
            string term = termAndOccurrences[0];

            map<int, int> docs;
            for (int i = 1; i < termAndOccurrences.size(); i++) {
                vector<string> docIdAndOccurrences = splitString(termAndOccurrences[i], ',');
                int docId = stoi(docIdAndOccurrences[0]);
                int occurrences = stoi(docIdAndOccurrences[1]);

                docs[docId] = occurrences;
            }

            double reason = COLLECTION_SIZE / (termAndOccurrences.size() - 1);
            idfPerTerm[term] = log(reason);
            invertedList[term] = docs;
        }

        readFile.close();
    } else return 1;

    cout<< "Read finished" << endl;

    return 0;
}