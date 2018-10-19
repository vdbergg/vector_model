#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "vector_model.h"
#include <set>
#include <string.h>
#include <sstream>
#include <stdlib.h>

using namespace std;

string PATH = "/home/berg/CLionProjects/RI/vector_model/";

ofstream logDebug;

struct DocPayload {
    double frequency;
    double weight;
    double norm;
} mDocPayload;

struct TermPayload {
    double idf;
    double maxWeight;
    map<int, DocPayload> docsPerTerm;
} mTermPayload;

struct QueryPayload {
    double norm;
    map<string, double> queryWithWeight;
} mQueryPayload;

struct SimilarityPayload {
    int docId;
    string doc;
    double similarity;
};

map<string, TermPayload> mInvertedList;
vector<double> nNormsPerDoc;
vector<double> mSimilaritiesPerDoc;

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

    readFile.open(PATH + "indexer/norms_per_doc.txt");
    if (readFile.is_open()) {
        string inputFile;

        while (readFile >> inputFile) {
            vector<string> docsWithNorm = splitString(inputFile, ';');

            for (int i = 0; i < docsWithNorm.size(); i++) {
                vector<string> normPerDoc = splitString(docsWithNorm[i], ',');
                int docId = stoi(normPerDoc[0]);
                double norm = stod(normPerDoc[1]);
                nNormsPerDoc.push_back(norm);
            }
        }
        readFile.close();
    } else return 1;

    readFile.open(PATH + "indexer/indexation.txt");
    if (readFile.is_open()) {
        string word;

        while (readFile >> word) {

            vector<string> termAndPayload = splitString(word, '|');
            string term = termAndPayload[0];
            double idf = stod(termAndPayload[1]);
            double maxWeight = stod(termAndPayload[2]);

            map<int, DocPayload> docs;
            vector<string> docIdAndPayload = splitString(termAndPayload[3], ';');

            for (int i = 0; i < docIdAndPayload.size(); i++) {
                vector<string> payload = splitString(docIdAndPayload[i], ',');
                int docId = stoi(payload[0]);
                int frequency = stoi(payload[1]);
                double weight = stod(payload[2]);

                mDocPayload.frequency = frequency;
                mDocPayload.weight = weight;
                mDocPayload.norm = nNormsPerDoc.at(docId);
                docs[docId] = mDocPayload;
            }

            mTermPayload.idf = idf;
            mTermPayload.maxWeight = maxWeight;
            mTermPayload.docsPerTerm = docs;
            mInvertedList[term] = mTermPayload;
        }

        readFile.close();
    } else return 1;

    return 0;
}

int buildQueryPayload(string query) {
    cout << "Converting query to payload..." << endl;

    vector<string> words = splitString(query, ' ');

    map<string, double> queryWithWeight;
    double sumWeightSquared = 0;

    for (int i = 0; i < words.size(); i++) {
        string word = words[i];

        bool termNotIndexed = mInvertedList.find(word) == mInvertedList.end();
        if (!termNotIndexed) {
            int occurrence = 0;
            for (int j = 0; j < words.size(); j++) {
                if (word == words[j]) occurrence++;
            }

            double weight = mInvertedList[word].idf * occurrence;
            sumWeightSquared += pow(weight, 2);
            queryWithWeight[word] = weight;
        }
    }
    mQueryPayload.queryWithWeight = queryWithWeight;
    mQueryPayload.norm = sqrt(sumWeightSquared);

    return 0;
}

int termProcessing(string query) {
    readIndexation();

    buildQueryPayload(query);

    cout << "Calculating partial similarities..." << endl;

    long DOC_SIZE = nNormsPerDoc.size();

    double accumulators[DOC_SIZE];

    map<string, double> queryWithWeight = mQueryPayload.queryWithWeight;
    for (map<string, double>::iterator it = queryWithWeight.begin(); it != queryWithWeight.end(); ++it) {
        string word = it->first;

        for (int j = 0; j < DOC_SIZE; j++) {
            map<int, DocPayload> invertedListDocs = mInvertedList[word].docsPerTerm;

            double partialSimilarity = invertedListDocs[j].weight * mQueryPayload.queryWithWeight[word];
            accumulators[j] += partialSimilarity;
        }
    }

    cout << "Calculating full similarities..." << endl;

    for (int i = 0; i < DOC_SIZE; i++) {
        double similarity = accumulators[i] / ((nNormsPerDoc[i]) * mQueryPayload.norm);
        mSimilaritiesPerDoc.push_back(similarity);
    }

    return 0;
}

string findDocumentById(int docId) {
    vector<string> filesPath = {
            PATH + "cfc/cf74",
            PATH + "cfc/cf75",
            PATH + "cfc/cf76",
            PATH + "cfc/cf77",
            PATH + "cfc/cf78",
            PATH + "cfc/cf79"
    };

    ifstream readFile;

    int documents = -1;

    for (unsigned i = 0; i < filesPath.size(); i++) {
        readFile.open(filesPath.at(i));

        if (readFile.is_open()) {
            string line;
            vector<string> linesDoc;

            while (getline(readFile, line)) {
                if (line == "") {
                    linesDoc.clear();
                    continue;
                }
                linesDoc.push_back(line);

                documents += 1;
                if (documents == docId) {
                    string doc = "";

                    for (int j = 0; j < linesDoc.size(); j++) {
                        string word;
                        istringstream tmp(linesDoc[j]);

                        while (tmp >> word) doc += word + " ";
                        doc += "\n";
                    }
                    return doc;
                };
            }
            readFile.close();
        };
    }
    return "";
}

bool compareBySimilarity(const SimilarityPayload &a, const SimilarityPayload &b) {
    return a.similarity < b.similarity;
}

void printResults() {
    logDebug.open(PATH + "log.txt");

    vector<SimilarityPayload> similarities;

    for (int i = 0; i < mSimilaritiesPerDoc.size(); i++) {
        if (mSimilaritiesPerDoc.at(i) > 0.000000) {
            SimilarityPayload similarityPayload;
            similarityPayload.docId = i;
            similarityPayload.similarity = mSimilaritiesPerDoc.at(i);
            similarities.push_back(similarityPayload);
        }
    }
    cout << "Sorting full similarities..." << endl;

    sort(similarities.begin(), similarities.end(), compareBySimilarity);

    cout << "Printing full similarities..." << endl;

    for (int i = 0; i < 21; i++) {
        SimilarityPayload similarityPayload = similarities.at(i);
        similarityPayload.doc = findDocumentById(similarityPayload.docId);

        logDebug << to_string(similarityPayload.docId) + " -> " + to_string(similarityPayload.similarity) + "\n";
        logDebug << similarityPayload.doc + "\n\n";

        cout << to_string(similarityPayload.docId) + " -> " + to_string(similarityPayload.similarity) + "\n" << endl;
        cout << similarityPayload.doc + "\n\n" << endl;
    }

    logDebug.close();
}

int runTermProcessing() {
    string query = "What are the effects of calcium on the physical properties of mucus from CF patients?"; //readInput();
    termProcessing(query);
    printResults();

    return 0;
}
