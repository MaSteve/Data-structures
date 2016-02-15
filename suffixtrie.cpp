#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

struct node {
	bool isword;
	bool issuffix;
	char c;
	unordered_map <char, node*> map;

	node() { isword = issuffix = false; }

	void insert(string word, int i, bool isword) {
		if (i < word.length()) {
			for (int j = word.length() - 1; j >= i; j--) {
				if (!map.count(word[j])) map.insert(pair<char, node*>(word[j], new node()));
				if (j == i) map[word[j]]->insert(word, j+1, isword);
				else map[word[j]]->insert(word, j+1, false);
			}
			if (i == word.length() - 1) {
				issuffix  = true;
				this->isword |= isword;
			}
		}
	}
	
	int search(string word, int i) {
		if (i >= word.length() || !map.count(word[i])) return 0;
		if (i == word.length() - 1) return isword? 2: issuffix? 1: 0;
		return map[word[i]]->search(word, i + 1);
	}
};

struct suffixtrie {
	node* root;

	suffixtrie() { root = new node(); }

	~suffixtrie() { delete root; }

	void insert(string word) { root->insert(word, 0, true); }

	int search(string word) { return root->search(word, 0); }
};