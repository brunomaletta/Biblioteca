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
	if (line[2] == ' ') return line.substr(3);
	return line.substr(2);
}

void printa_cuidado(string s) {
	for (char c : s) {
		if (c == '^') cout << '\\';
		cout << c;
		if (c == '^') cout << "{}";
	}
}

void printa_listing(string sub, string f, bool skip) {
	cout << "\\subsection{";
	if (skip) printa_cuidado(getName(f));
	else printa_cuidado(sub);
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

		if (entry->d_type == DT_DIR) vai(s+"/"+string(entry->d_name), x);
		else {
			string s2 = string(entry->d_name);
			if (!x) printa_listing(s2.substr(0, s2.size()-4), s+"/"+entry->d_name, true);
			else printa_listing(s2, s+"/"+entry->d_name, false);
		}
	}
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

		string dir(entry->d_name);
		if (dir == "Extra") continue;
		printa_section(dir);
		vai(path + dir);
	}

	cout << "\\pagebreak" << endl;
	printa_section("Extra");
	vai(path + "Extra", true);

	cout << "\\end{document}\n";
	return 0;
}
