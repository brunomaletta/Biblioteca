#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

string path = "../Codigo/";

void printa_arquivo(string s, bool skip = false) {
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and skip) continue;
		cout << line << endl;
	}
}

string getName(string s) {
	ifstream fin(s.c_str());
	string line;
	getline(fin, line);
	return line.substr(3);
}

void printa_listing(string sub, string f, bool skip = false) {
	cout << "\\subsection{";
	if (skip) cout << getName(f);
	else cout << sub;
	cout << "}\n";
	cout << "\\begin{lstlisting}\n";
	printa_arquivo(f, skip);
	cout << "\\end{lstlisting}\n\n";
}

void vai(string s, bool x = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) vai(s+"/"+string(entry->d_name));
		else {
			string s2 = string(entry->d_name);
			printa_listing(s2.substr(0, s2.size()-4), s+"/"+entry->d_name, true);
		}
	} else if (x) printa_listing(s.substr(path.size()), s);
}

void printa_section(string s) {
	cout << "\n\n";

	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% " << s << "\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	cout << "\\section{" << s << "}\n\n";
}

int main() {
	printa_arquivo("comeco.tex");
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		printa_section(entry->d_name);

		vai(path + string(entry->d_name));
	}

	printa_section("Extra");

	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type == DT_DIR) continue;

		vai(path + string(entry->d_name), true);
	}

	cout << "\\end{document}\n";
	return 0;
}
