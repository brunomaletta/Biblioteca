#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

string path = "../Codigo/";
string hash_cmd = "sed -n 1','1' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-3";

string exec(string cmd) {
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) throw runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	return result;
}

void printa_arquivo_codigo(string s, bool skip = false) {
	cout << "\\begin{lstlisting}\n";
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and skip) continue;
		
		if (skip) {
			ofstream tmp("tmp.cpp", ios::out);
			tmp << line;
			tmp.close();
			string hash = exec(hash_cmd);
			hash.pop_back();
			cout << hash << " ";
		}
		cout << line << endl;
	}
	cout << "\\end{lstlisting}\n\n";
}

void printa_arquivo(string s, bool skip = false) {
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and skip) continue;
		cout << line << endl;
	}
}

string get_name(string s) {
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
	if (skip) printa_cuidado(get_name(f));
	else printa_cuidado(sub);
	cout << "}\n";

	printa_arquivo_codigo(f, skip);
}

void vai(vector<pair<string, string>>& files, string s, bool x = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) vai(files, s + "/" + string(entry->d_name), x);
		else {
			if (!x) files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
			else printa_listing(entry->d_name, s + "/" + entry->d_name, false);
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

string lower(string s) {
	for (char& c : s) if (c >= 'A' and c <= 'Z') c ^= 32;
	return s;
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

		vector<pair<string, string>> files;
		vai(files, path + dir);

		sort(files.begin(), files.end(), [&](auto f1, auto f2) {
			return lower(get_name(f1.second)) < lower(get_name(f2.second));
		});

		cerr << "=== " << dir << " ===" << endl;
		for (auto [f, path] : files) {
			printa_listing(f.substr(0, f.size() - 4), path, true);
			cerr << get_name(path) << endl;
		}
		cerr << endl;
	}

	cout << "\\pagebreak" << endl;
	printa_section("Extra");
	vector<pair<string, string>> files;
	vai(files, path + "Extra", true);

	cout << "\\end{document}\n";
	return 0;
}
