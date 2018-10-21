//
// Created by berg on 12/10/18.
//

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "MinHeap.h"

using namespace std;

string PATH = "/home/berg/CLionProjects/RI/vector_model/";

ofstream logDebug;

struct TermPayload {
    double maxWeight;
    map<int, double> docsWithWeight;
};

struct DocPayload {
    int docId;
    double score;
    string doc;
    int position
};

map<string, TermPayload> mInvertedList;
map<string, TermPayload> mQueryList;

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

    readFile.open(PATH + "indexer/indexation.txt");
    if (readFile.is_open()) {
        string word;

        while (readFile >> word) {

            vector<string> termAndPayload = splitString(word, '|');
            string term = termAndPayload[0];
            double maxWeight = stod(termAndPayload[2]);

            map<int, double> docsWithWeight;
            vector<string> docIdAndPayload = splitString(termAndPayload[3], ';');

            for (int i = 0; i < docIdAndPayload.size(); i++) {
                vector<string> payload = splitString(docIdAndPayload[i], ',');

                int docId = stoi(payload[0]);
                double weight = stod(payload[2]);
                docsWithWeight[docId] = weight;
            }

            TermPayload termPayload;
            termPayload.maxWeight = maxWeight;
            termPayload.docsWithWeight = docsWithWeight;

            mInvertedList[term] = termPayload;
        }

        readFile.close();
    } else return 1;

    return 0;
}

int buildQueryPayload(string query) {
    cout << "Converting query to payload..." << endl;

    vector<string> words = splitString(query, ' ');

    for (int i = 0; i < words.size(); i++) {
        string word = words[i];

        bool isIndexed = !(mInvertedList.find(word) == mInvertedList.end());
        if (isIndexed) {
            double maxWeight = mInvertedList[word].maxWeight;
            map<int, double> queryWithWeight = mInvertedList[word].docsWithWeight;

            TermPayload termPayload;
            termPayload.maxWeight = maxWeight;
            termPayload.docsWithWeight = queryWithWeight;

            mQueryList[word] = termPayload;
        }
    }
    return 0;
}

void init(vector<string> queryTerms) {

}

void next(double threshold) {

}

void wand(string query) {
    buildQueryPayload(query);

    MinHeap minHeap(10);
    double threshold = INT_MIN;

    DocPayload[] cursors = new DocPayload[mQueryList.size()];

    for (int i = 0; i < cursors.length(); i++) {
        cursors[i].position = -1;
    }

    vector<string> queryTerms;

    for (map<string, TermPayload>::iterator it = mQueryList.begin(); it != mQueryList.end(); ++it) {
        queryTerms.push_back(it->first);
    }

    for (int i = 0; i < queryTerms.size(); i++) {
        string term = queryTerms.at(i);

        map<int, double> docsWithWeight = mQueryList[term].docsWithWeight;
        int positionInPostingLists = 0;

        for (map<int, double>::iterator it = docsWithWeight.begin(); it != docsWithWeight.end(); ++it) {
            int position = cursors.at(i).position;

            if (position == -1) {
                position += 1;

                DocPayload docPayload;
                docPayload.docId = it->first;
                docPayload.score = it->second;
                docPayload.position = positionInPostingLists;

                cursors[i] = docPayload;

            }

            positionInPostingLists++;
        }
    }
}

int main() {
    logDebug.open(PATH + "log.txt");

    readIndexation();

    string query = "What are the effects of calcium on the physical properties of mucus from CF patients?";

    wand(query);

    logDebug.close();

    return 0;
}
