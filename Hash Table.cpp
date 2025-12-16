#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstdlib>
using namespace std;


// Q1: Find pairs that sum to a target

void findPairs(vector<int>& nums, int target) {
    unordered_set<int> seen;
    cout << "Target = " << target << endl;

    for (int i = 0; i < nums.size(); i++) {
        int x = nums[i];
        int y = target - x;

        if (seen.count(y)) {
            cout << "(" << x << ", " << y << ")" << endl;
        }

        seen.insert(x);
    }
}


// sort for string

string sortString(string s) {
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            if (s[j] < s[i]) {
                char tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
    return s;
}

// Q2: 

void findAnagrams(vector<string> words) {
    vector<bool> used(words.size(), false);

    for (int i = 0; i < words.size(); i++) {
        if (used[i] == false) {
            string baseSorted = sortString(words[i]);
            vector<string> group;
            group.push_back(words[i]);
            used[i] = true;

            for (int j = i + 1; j < words.size(); j++) {
                string compareSorted = sortString(words[j]);
                if (compareSorted == baseSorted) {
                    group.push_back(words[j]);
                    used[j] = true;
                }
            }

            if (group.size() > 1) {
                for (int k = 0; k < group.size(); k++) {
                    cout << group[k] << " ";
                }
                cout << endl;
            }
        }
    }
}


// Q3: 

class HT_6 {
    vector<int> _data;
    const int N = 13;

public:
    int collisions;

    HT_6() {
        _data = vector<int>(N, -1);
        collisions = 0;
    }

    int hash(int value) {
        return value % N;
    }

    void add(int value) {
        int index = hash(value);
        int step = 0;

        while (_data[(index + step * step) % N] != -1) {
            collisions = collisions + 1;
            step = step + 1;
        }

        _data[(index + step * step) % N] = value;
    }

    bool find(int value) {
        int index = hash(value);
        int step = 0;

        while (_data[(index + step * step) % N] != -1) {
            if (_data[(index + step * step) % N] == value) {
                return true;
            }
            step = step + 1;
        }

        return false;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << "[" << i << "]=" << _data[i] << endl;
        }
        cout << "collisions = " << collisions << endl << endl;
    }
};


// Q4: 

class HT_7 {
    vector<int> _data;
    const int N = 13;

public:
    int collisions;

    HT_7() {
        _data = vector<int>(N, -1);
        collisions = 0;
    }

    int hash1(int value) {
        return value % N;
    }

    int hash2(int value) {
        return 1 + (value % (N - 1));
    }

    void add(int value) {
        int h1 = hash1(value);
        int h2 = hash2(value);
        int step = 0;

        while (_data[(h1 + step * h2) % N] != -1) {
            collisions = collisions + 1;
            step = step + 1;
        }

        _data[(h1 + step * h2) % N] = value;
    }

    bool find(int value) {
        int h1 = hash1(value);
        int h2 = hash2(value);
        int step = 0;

        while (_data[(h1 + step * h2) % N] != -1) {
            if (_data[(h1 + step * h2) % N] == value) {
                return true;
            }
            step = step + 1;
        }

        return false;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << "[" << i << "]=" << _data[i] << endl;
        }
        cout << "collisions = " << collisions << endl << endl;
    }
};

int main() {
    // Q1 test
    if (false) {
        vector<int> nums;
        nums.push_back(2);
        nums.push_back(4);
        nums.push_back(3);
        nums.push_back(7);
        nums.push_back(1);
        nums.push_back(5);
        nums.push_back(9);
        findPairs(nums, 10);
    }

    // Q2 test
    if (false) {
        vector<string> words;
        words.push_back("art");
        words.push_back("rat");
        words.push_back("tar");
        words.push_back("taco");
        words.push_back("cato");
        findAnagrams(words);
    }

    // Q3 test
    if (false) {
        HT_6 table;
        vector<int> vals;
        for (int i = 0; i < 8; i++) {
            int v = rand() % 50;
            table.add(v);
            vals.push_back(v);
            cout << " " << v;
        }
        cout << endl;
        table.print();
        int x = vals[rand() % 8];
        cout << x << " is" << (table.find(x) ? "" : " not") << " in table" << endl;
    }
}