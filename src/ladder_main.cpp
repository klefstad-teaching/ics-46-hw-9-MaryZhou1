#include "ladder.h"

int main() {
    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;

    // check first and last
    if (start == end){
        error("start", "end", "can't be equal");
    }

    // Dictionary of words
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);

    return 0;
}
