#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << word1 << ", " << word2 << ", " << msg << endl;
    exit(1);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.size() != str2.size()) return false;

    int diff_count = 0;
    for (size_t i = 0; i < str1.size(); i++) {
        if (str1[i] != str2[i]) {
            diff_count++;
            if (diff_count > d) return false;
        }
    }
    return diff_count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};

    queue<vector<string>> ladders;
    set<string> visited;
    
    ladders.push({begin_word});
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int size = ladders.size();
        set<string> level_visited;

        for (int i = 0; i < size; i++) {
            vector<string> ladder = ladders.front();
            ladders.pop();

            string last_word = ladder.back();
            for (const string& word : word_list) {
                if (visited.count(word) == 0 && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladders.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }

        for (const string& word : level_visited) {
            visited.insert(word);
        }
    }

    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("load words", "can't open file", "");
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }


    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); i++) {
            cout << ladder[i];
            if (i != ladder.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    string file_name = "words.txt";

    load_words(word_list, file_name);

    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}

