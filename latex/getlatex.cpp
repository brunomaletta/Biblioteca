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

void vai(string s, bool x = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) vai(s+"/"+string(entry->d_name));
		else {
			string s2 = string(entry->d_name);
			cout << "\\subsection{" << s2.substr(0, s2.size()-4) << "}\n";
			cout << "\\begin{lstlisting}\n";
			printa_arquivo(s+"/"+entry->d_name, true);
			cout << "\\end{lstlisting}\n\n";
		}
	} else if (x) {
		cout << "\\subsection{" << s.substr(path.size()) << "}\n";
		cout << "\\begin{lstlisting}\n";
		printa_arquivo(s);
		cout << "\\end{lstlisting}\n\n";
	}
}

int main() {
	printa_arquivo("comeco.tex");
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		cout << "\n\n";
		for (int i = 0; i < 20; i++) cout << "%";
		cout << "\n%\n% " << entry->d_name << "\n%\n";
		for (int i = 0; i < 20; i++) cout << "%";
		cout << "\n\n";

		cout << "\\section{" << entry->d_name << "}\n\n";

		vai(path + string(entry->d_name));
	}

	cout << "\n\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% EXTRA\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	cout << "\\section{Extra}\n\n";

	dp = opendir(path.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type == DT_DIR) continue;

		vai(path + string(entry->d_name), true);
	}

	cout << "\\end{document}\n";
	return 0;
}
