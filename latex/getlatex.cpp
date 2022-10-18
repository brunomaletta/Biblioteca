#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"

string path = "../Codigo/";
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6";
string hash_line_cmd = "sed -n 1','1' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-3";

string exec(string cmd) {
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) throw runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	result.pop_back();
	return result;
}

string get_hash_arquivo(string s) {
	ifstream fin(s.c_str());
	ofstream tmp("tmp.cpp", ios::out);
	string line;
	while (getline(fin, line)) tmp << line << '\n';
	fin.close();
	tmp.close();
	string hash = exec(hash_cmd);
	return hash;
}

bool find_in_file(string s, string t) {
	ifstream fin(s.c_str());
	bool found = false;
	string line;
	while (getline(fin, line)) {
		for (int i = int(t.size()) - 1; i < line.size(); i++) {
			if (line.substr(i - t.size() + 1, t.size()) == t) {
				found = true;
				break;
			}
		}
	}
	return found;
}

bool is_comment(string line) {
	while (line.size() and (line[0] == ' ' or line[0] == '\t'))
		line = line.substr(1);
	bool comment = line.size() == 0;
	if (line.size() >= 2 and line.substr(0, 2) == "//") comment = true;
	if (line.size() >= 2 and line.substr(0, 2) == "/*") comment = true;
	return comment;
}

void printa_arquivo_codigo(string s, bool extra = false) {
	cout << "\\begin{lstlisting}\n";
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	bool started_code = false;
	while (getline(fin, line)) {
		if (count++ < 2 and !extra) continue;
		
		bool comment = is_comment(line);
		if (!comment) started_code = true;

		if (!extra and started_code) {
			ofstream tmp("tmp.cpp", ios::out);
			tmp << line;
			tmp.close();
			string hash = comment ? "   " : exec(hash_line_cmd);
			cout << hash << " ";
		}
		cout << line << endl;
	}
	fin.close();
	cout << "\\end{lstlisting}\n\n";
}

void printa_arquivo(string s, bool extra = false) {
	ifstream fin(s.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and !extra) continue;
		cout << line << endl;
	}
	fin.close();
}

string get_name(string s) {
	ifstream fin(s.c_str());
	string line;
	getline(fin, line);
	fin.close();
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

void printa_listing(string sub, string f, bool extra = false) {
	if (!extra) {
		if (!find_in_file(f, get_hash_arquivo(f)))
			cerr << RED << "WARNING" << RESET << ": hash nao encontrado para: "
			<< f.substr(10) << '\n';
	}

	cout << "\\subsection{";
	if (!extra) printa_cuidado(get_name(f));
	else printa_cuidado(sub);
	cout << "}\n";

	printa_arquivo_codigo(f, extra);
}

void vai(vector<pair<string, string>>& files, string s, bool extra = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while (entry = readdir(dp)) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) vai(files, s + "/" + string(entry->d_name), extra);
		else {
			if (!extra) files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
			else printa_listing(entry->d_name, s + "/" + entry->d_name, extra);
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
	printa_arquivo("comeco.tex", true);
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
			printa_listing(f.substr(0, f.size() - 4), path);
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
