#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
random_device rd;
mt19937 ser(rd());
vector<string>wd;
map<string, vector<string>>wg;
bool issep(char s) {
	return s == '.' || (s == ',' && 0)
	       || s == '?' || s == '!' || s == '\n';
}
string normal(string s) {
	while (s.front() == ' ')
		s.erase(0, 1);
	while (s.back() == ' ')
		s.pop_back();
	transform(s.begin(), s.end(),
	s.begin(), [](char c) {
		return isalpha(c) ? tolower(c) : c;
	});
	return s;
}
void learn(string s) {
	//split to sentences
	vector<string>t;//all the sentences in it
	string f;
	for (auto i : s)
		if (issep(i)) {
			t.push_back(f);
			f.clear();
		} else f.push_back(i);
	if (f.size())
		t.push_back(f);
	//learn every sentence
	for (int _pt = 0; _pt < t.size(); _pt++) {
		auto i = t[_pt];
		//split to words
		vector<string>w;//all the words in it
		f.clear();
		for (auto j : i)
			if (j == ' ') {
				w.push_back(f);
				f.clear();
			} else f.push_back(j);
		if (f.size())
			w.push_back(f);
		//normal every word
		for (int j = 0; j < w.size(); j++)
			w[j] = normal(w[j]);
		//learn words
		wd.push_back(w.front());
		for (int j = 1; j < w.size(); j++)
			wg[w[j - 1]].push_back(w[j]);
	}
}
void request() {
	if (!wd.size())
		return;
	for (string s = wd[ser() % wd.size()];
	     cout << s << ' ',
	     wg[s].size(); s = wg[s][ser() % wg[s].size()]);
	puts("");
}
void prelearn() {
	ifstream tb;
	tb.open("data.txt", ios::in);
	string td, t;
	while (getline(tb, t))
		td += t;
	tb.close();
	learn(td);
}
void cmd(string s) {
	if(s.size()>2&&s[2]=='s'){
		stringstream ss;
		ss<<s;
		string t;
		ss>>t>>t;
		
	}
}
void run(string s) {
	if (s.size() && s.front() == '$')
		cmd(s);
	else {
		learn(s);
		request();
	}
}
int main() {
	prelearn();
//	learn("hello,i am dan.");
	for (string s; getline(cin, s); )
		run(s);
}
