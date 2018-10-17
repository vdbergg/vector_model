#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "vector_model.h"
#include <sstream>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

map<string, map<int, int>> invertedList;
map<string, int> queryDoc;
map<string, double> idfPerTerm;
map<int, double> normsPerDoc;

double COLLECTION_SIZE = 0;

map<int, double> similaritiesPerDoc;

vector<string> splitString(string text, char character) {
    stringstream test(text);
    string line;
    vector<string> item;

    while (getline(test, line, character)) item.push_back(line);

    return item;
}

int readIndexation() {
    cout<< "Reading indexation..." << endl;

    ifstream readFile, fileCollectionSize;
    readFile.open("/home/berg/CLionProjects/RI/tp1/indexation.txt");
    fileCollectionSize.open("/home/berg/CLionProjects/RI/tp1/collection_size.txt");

    if (fileCollectionSize.is_open()) {
        string word;
        while (fileCollectionSize >> word) COLLECTION_SIZE = stoi(word);
        fileCollectionSize.close();
    }

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

    return 0;
}

int convertQueryToDoc(string query) {
    istringstream tmp(query);
    string word;

    vector<string> words;
    while(tmp >> word) words.push_back(word);

    for (int i = 0; i < words.size(); i++) {
        string term = words[i];
        int occurrence = 0;

        for (int j = 0; j < words.size(); j++) {
            if (term == words[j]) occurrence++;
        }
        queryDoc[term] = occurrence;
    }

    return 0;
}

double weight(int docId, string term) {
    double idfTerm = idfPerTerm[term];
    long tf = invertedList[term][docId];

    return idfTerm * tf;
}

double weightQuery(string term) {
    double idfTerm = idfPerTerm[term];
    long tf = queryDoc[term];

    return idfTerm * tf;
}

int calculateNorms() {
    cout << "Calculating norm..." << endl;

    for (int i = 0; i < COLLECTION_SIZE; i++) {
        double norm = 0;

        for (map<string, map<int, int>>::iterator it = invertedList.begin(); it != invertedList.end(); ++it) {
            string term = it->first;
            norm += pow(weight(i, term), 2);
        }
        normsPerDoc[i] = sqrt(norm);
    }

    return 0;
}

double calculateQueryNorm() {
    double norm = 0;

    for (map<string, int>::iterator it = queryDoc.begin(); it != queryDoc.end(); ++it) {
        string term = it->first;
        norm += pow(weightQuery(term), 2);
    }
    return sqrt(norm);
}

int termProcessing(string query) {
    cout << "Converting query to doc..." << endl;

    convertQueryToDoc(query);

    cout << "Calculating partial similarities..." << endl;

    double accumulators[(int) COLLECTION_SIZE];

    for (map<string, map<int, int>>::iterator it = invertedList.begin(); it != invertedList.end(); ++it) {
        string term = it->first;
        double weightQueryPerTerm = weightQuery(term);

        for (map<int, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            int docId = it2->first;
            double partialSimilarity = weight(docId, term) * weightQueryPerTerm;
            accumulators[docId] += partialSimilarity;
        }
    }

    cout << "Calculating query norm..." << endl;

    double queryNorm = calculateQueryNorm();

    cout << "Calculating full similarities..." << endl;

    for (int i = 0; i < COLLECTION_SIZE; i++) {
        double similarity = (accumulators[i] / normsPerDoc[i]) * queryNorm;
        similaritiesPerDoc[i] = similarity;
    }

    cout << "Sorting similarities..." << endl;

    typedef function<bool(pair<int, double>, pair<int, double>)> Comparator;

    Comparator compFunctor = [](pair<int, double> elem1, pair<int, double> elem2) {
        return elem1.second < elem2.second;
    };

    set<pair<int, double>, Comparator> setOfWords(
        similaritiesPerDoc.begin(), similaritiesPerDoc.end(), compFunctor
    );

    cout << "Printing similarities..." << endl;

    for (pair<int, double> element : setOfWords) {
        cout << element.first << " -> " << element.second << endl;
    }

    return 0;
}

string readInput() {
    string str;
    cout << "Enter query: ";
    getline(cin, str);

    return str;
}

int printSimilaritiesPerDoc() {
    cout << "Printing similarities..." << endl;

    for (map<int, double>::iterator it = similaritiesPerDoc.begin(); it != similaritiesPerDoc.end(); ++it) {
        int docId = it->first;
        double similarity = it->second;
        cout << to_string(docId) + " -> " + to_string(similarity) << endl;
    }

    return 0;
}

int runTermProcessing() {
    calculateNorms();

    while (true) {
        string query = readInput();
        termProcessing(query);
//        printSimilaritiesPerDoc();
    }

    return 0;
}
