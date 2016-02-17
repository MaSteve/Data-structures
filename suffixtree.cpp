#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

struct node {
	string pattern;
	bool isword;
	bool issuffix;
	int nodes;
	unordered_map <char, node*> map;

	node() { isword = issuffix = false; pattern = ""; nodes = 0; }

	node(string pattern, bool isword, bool issuffix, unordered_map<char, node*> & map) {
		this->pattern = pattern;
		this->isword = isword;
		this->issuffix = issuffix;
		this->map = map;
	}

	void insert(string word, int i, bool isword) {
		if (i < word.length()) {
			if (nodes == 0) pattern = word.substr(i, word.length()-i);
			else {
				int j;
				for (j = 0; i < word.length() && j < pattern.length() && word[i] == pattern[j]; i++, j++);
				if (j == pattern.length()) {
					if (i < word.length()) {
						if (!map.count(word[i])) map.insert(pair<char, node*>(word[i], new node()));
						map[word[i]]->insert(word, i, isword);
					}
				} else {
					unordered_map <char, node*> aux = map;
					map = unordered_map <char, node*>();
					map.insert(pair<char, node*>(pattern[j], new node(pattern.substr(j, pattern.length()-j), isword, issuffix, aux)));
					pattern = pattern.substr(0, j);
					issuffix = false;
					this->isword = false;
					if (i < word.length()) {
						map.insert(pair<char, node*>(word[i], new node()));
						map[word[i]]->insert(word, i, isword);
					}
				}
				//if (!map.count(word[i])) map.insert(pair<char, node*>(word[i], new node(, isword, issuffix, map)));
				//else map[word[i]]->insert(word, i+1, isword);
			}
			if (i >= word.length() - 1 || nodes == 0) {
				issuffix  = true;
				this->isword |= isword;
				nodes++;
			}
		}
	}
	
	int search(string word, int i) {
		int j;
		for (j = 0; i < word.length() && j < pattern.length() && word[i] == pattern[j]; i++, j++);
		if (j == pattern.length() - 1) {
			if (i == word.length() - 1) return isword? 2: issuffix? 1: 0;
			else {
				if (i >= word.length() || !map.count(word[i])) return 0;
				return map[word[i]]->search(word, i);
			}
		} else return 0;
	}
};

struct suffixtrie {
	node* root;

	suffixtrie() { root = new node(); }

	~suffixtrie() { delete root; }

	void insert(string word) {
		for (int j = word.length() - 1; j >= 0; j--) {
			if (j == 0) root->insert(word, j, true);
			else root->insert(word, j, false);
		}
	}

	int search(string word) { return root->search(word, 0); }

	void clear() { delete root; root = new node(); }
};

int main() {
	return 0;
}