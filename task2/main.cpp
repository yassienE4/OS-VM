/*
Implement a program to count the frequency of words in a text file. The text file is partitioned
into N segments. Each segment is processed by a separate thread that outputs the intermediate
frequency count for its segment. The main process waits until all the threads complete; then it
computes the consolidated word-frequency data based on the individual threads’ output.
*/

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadData {
    int id;
    const string* text;
    size_t start;
    size_t end;
    unordered_map<string, long long> localCount;
};

vector<pair<size_t, size_t>> buildSegments(const string& text, int N)
{
    vector<pair<size_t, size_t>> segments;
    segments.reserve(N);
    
    size_t len = text.size();
    size_t start = 0;

    for (int i = 0; i < N; ++i) {
        if (start >= len) {
            segments.push_back({len, len});
            continue;
        }

        size_t remaining = len - start;
        size_t target = (i == N - 1) ? len : (start + remaining / (N - i));
        size_t end = target;

        if (end < len) {
            while (end < len && isalnum(static_cast<unsigned char>(text[end]))) {
                end++;
            }
        }

        if (i == N - 1)
            end = len;

        segments.push_back({start, end});
        start = end;
    }

    return segments;
}

bool readWholeFile(const string& path, string& out) {
    ifstream in(path, ios::binary);
    if (!in) return false;

    out.assign(istreambuf_iterator<char>(in),
               istreambuf_iterator<char>());
    return true;
}


void* multiCounter(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    const string& s = *(data->text);

    string word;
    word.reserve(32);

    for (size_t i = data->start; i < data->end; ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);

        if (isalnum(static_cast<unsigned char>(c))) {
            word.push_back(static_cast<char>(tolower(c)));
        } else {
            if (!word.empty()) {
                data->localCount[word]++;
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        data->localCount[word]++;
    }

    // Print intermediate results
    pthread_mutex_lock(&print_mutex);
    cout << "\n=== Thread " << data->id
         << " segment [" << data->start << ", " << data->end << ") ===\n";

    for (const auto& kv : data->localCount) {
        cout << kv.first << ": " << kv.second << endl;
    }
    pthread_mutex_unlock(&print_mutex);

    pthread_exit(nullptr);
    return nullptr;
}


int main(int argc, char** argv)
{
    if (argc < 3) {
        // need 2 arguments to run
        cerr << "Usage: " << argv[0] << " <text_file> <N_threads>\n";
        return 1;
    }

    string filePath = argv[1];
    int N = atoi(argv[2]);

    if (N <= 0) 
    {
        cerr << "Error: N_threads must be > 0\n";
        return 1;
    }

    string text;
    // load txt into text
    if (!readWholeFile(filePath, text)) {
        cerr << "Error: Cannot open file.\n";
        return 1;
    }
    
    // get N segment indexes 
    auto segments = buildSegments(text, N);

    vector<pthread_t> threads(N);
    vector<ThreadData> threadData(N);

    for (int i = 0; i < N; ++i) {
        threadData[i].id = i;
        threadData[i].text = &text;
        threadData[i].start = segments[i].first;
        threadData[i].end = segments[i].second;

        if (pthread_create(&threads[i], nullptr, multiCounter, &threadData[i]) != 0) {
            cerr << "Error creating thread " << i << endl;
            return 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], nullptr);
    }

    unordered_map<string, long long> globalCount;
    for (int i = 0; i < N; ++i) {
        for (const auto& kv : threadData[i].localCount) {
            globalCount[kv.first] += kv.second;
        }
    }

    vector<pair<string, long long>> sorted(globalCount.begin(), globalCount.end());

    sort(sorted.begin(), sorted.end(),
        [](const pair<string, long long>& a,
           const pair<string, long long>& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

        
    cout << "\nCONSOLIDATED WORD FREQUENCY\n";
    for (const auto& kv : sorted) {
        cout << kv.first << ": " << kv.second << endl;
    }

    pthread_mutex_destroy(&print_mutex);

    return 0;
}