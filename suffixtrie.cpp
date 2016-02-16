#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

struct node {
	bool isword;
	bool issuffix;
	unordered_map <char, node*> map;

	node() { isword = issuffix = false; }

	void insert(string word, int i, bool isword) {
		if (i < word.length()) {
			if (!map.count(word[i])) map.insert(pair<char, node*>(word[i], new node()));
			map[word[i]]->insert(word, i+1, isword);
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