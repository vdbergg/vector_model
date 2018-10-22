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

ofstream logDebug, writeFile;

struct DocPayload {
    double frequency;
    double weight;
    double norm;
} mDocPayload;

struct TermPayload {
    double idf;
    double maxWeight;
    map<int, DocPayload> docsWithWeight;
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
vector<SimilarityPayload> mSimilarities;

vector<string> mQueryList;

vector<string> splitString(string text, char character) {
    stringstream test(text);
    string line;
    vector<string> item;

    while (getline(test, line, character)) item.push_back(line);

    return item;
}

int readIndexation() {
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
            mTermPayload.docsWithWeight = docs;
            mInvertedList[term] = mTermPayload;
        }

        readFile.close();
    } else return 1;

    return 0;
}

int buildQueryPayload(string query) {
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
    buildQueryPayload(query);

    long DOC_SIZE = nNormsPerDoc.size();
    double accumulators[DOC_SIZE] = { 0 };
    map<string, double> queryWithWeight = mQueryPayload.queryWithWeight;

    for (map<string, double>::iterator it = queryWithWeight.begin(); it != queryWithWeight.end(); ++it) {
        string word = it->first;

        for (int j = 0; j < DOC_SIZE; j++) {
            map<int, DocPayload> invertedListDocs = mInvertedList[word].docsWithWeight;

            double partialSimilarity = invertedListDocs[j].weight * mQueryPayload.queryWithWeight[word];
            accumulators[j] += partialSimilarity;
        }
    }

    SimilarityPayload similarityPayload;

    for (int i = 0; i < DOC_SIZE; i++) {
        double temp = nNormsPerDoc[i] * mQueryPayload.norm;

        if (temp > 0.0 && nNormsPerDoc[i] > 0.0) {
            double similarity = accumulators[i] / temp;

            similarityPayload.docId = i;
            similarityPayload.similarity = similarity;

            mSimilarities.push_back(similarityPayload);
        }
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

    bool docFounded = false;

    for (unsigned i = 0; i < filesPath.size(); i++) {
        readFile.open(filesPath.at(i));

        if (readFile.is_open()) {
            string line;
            vector<string> linesDoc;
            int countLine = 1;

            while (getline(readFile, line)) {
                if (line == "") {
                    if (docFounded) {
                        string doc = "";

                        for (int j = 0; j < linesDoc.size(); j++) {
                            string word;
                            istringstream tmp(linesDoc[j]);

                            while (tmp >> word) doc += word + " ";
                            doc += "\n";
                        }
                        readFile.close();

                        return doc;
                    }

                    linesDoc.clear();
                    countLine = 1;
                }

                if (countLine == 1 && line.find("PN") != string::npos) {
                    countLine++;
                    linesDoc.push_back(line);
                } else if (countLine == 2 && !docFounded && line.find("RN") != string::npos) {
                    string temp = line;
                    temp.erase(0, 3); // Remove RN e espaço
                    int fileDocId = stoi(temp) - 1; // Trato os docId começando de 0 nas listas

                    if (fileDocId == docId) docFounded = true;

                    countLine++;
                }

                if (docFounded) linesDoc.push_back(line);
            }
        };
        readFile.close();
    }
    return "";
}

bool compareBySimilarity(const SimilarityPayload &a, const SimilarityPayload &b) {
    return a.similarity > b.similarity;
}

void printResults() {
    sort(mSimilarities.begin(), mSimilarities.end(), compareBySimilarity);

    for (int i = 0; i < 20; i++) {
        SimilarityPayload similarityPayload = mSimilarities.at(i);
        similarityPayload.doc = findDocumentById(similarityPayload.docId);

        logDebug << "Similarity -> " + to_string(similarityPayload.similarity) + "\n";
        writeFile << to_string(similarityPayload.docId + 1) + "|" + to_string(similarityPayload.similarity) + "\n";
        logDebug << similarityPayload.doc + "\n\n";
    }
}

int readQuery() {
    ifstream readFile;

    readFile.open(PATH + "/cfc/cfquery");

    if (readFile.is_open()) {
        string line;
        string lines = "";

        bool isQuery = false;

        while (getline(readFile, line)) {
            if (line.find("NR") != string::npos) {
                isQuery = false;
                mQueryList.push_back(lines);
                lines = "";
            }

            if (isQuery) {
                line.erase(0, 3); // 3 espaços
                lines += " " + line;
            } else if (line.find("QU") != string::npos) {
                isQuery = true;
                line.erase(0, 3); // Remove QU e espaço
                lines += line;
            }
        }
        readFile.close();
    } else return 1;
}

int runTermProcessing() {
    logDebug.open(PATH + "log.txt");
    writeFile.open(PATH + "result.txt");

    readIndexation();
    readQuery();

    for (int i = 0; i < mQueryList.size(); i++) {
        string query = mQueryList.at(i);
        termProcessing(query);

        logDebug << "Query: " + query + "\n\n";
        writeFile << to_string(i + 1) + "|" + query + "\n";
        cout << "Query " + to_string(i) + ": " + query + "\n";
        printResults();
    }

    logDebug.close();
    writeFile.close();

    return 0;
}

int main() {
    runTermProcessing();

    return 0;
}
