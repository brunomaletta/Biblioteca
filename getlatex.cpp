#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

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
			cout << "\\lstinputlisting[firstline=3]{" << s.substr(9) << "/" << entry->d_name << "}\n\n";
		}
	} else if (x) {
		cout << "\\subsection{" << s.substr(9) << "}\n";
		cout << "\\lstinputlisting[firstline=3]{" << s.substr(9) << "}\n\n";
	}
}

int main() {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir("./Codigo/");
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		cout << "\n\n";
		for (int i = 0; i < 20; i++) cout << "%";
		cout << "\n%\n% " << entry->d_name << "\n%\n";
		for (int i = 0; i < 20; i++) cout << "%";
		cout << "\n\n";

		cout << "\\section{" << entry->d_name << "}\n\n";

		vai("./Codigo/" + string(entry->d_name));
	}

	cout << "\n\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n%\n% EXTRA\n%\n";
	for (int i = 0; i < 20; i++) cout << "%";
	cout << "\n\n";

	dp = opendir("./Codigo/");
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type == DT_DIR) continue;

		vai("./Codigo/" + string(entry->d_name), true);
	}
	return 0;
}
