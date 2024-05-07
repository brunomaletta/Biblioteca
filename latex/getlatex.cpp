#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"

bool LOOK_FOR_HASH_IN_FILE = false;
int HASH_LEN = 3;

string NO_HASH = "nohash";
string NO_PRINT = "noprint";

string path = "../Codigo/";
#ifdef __clang__
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
           "| clang -E -x c++ -dD -P - | tr -d '[:space:]' | md5sum | cut -c-";
#else
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-";
#endif

bool print_all = false;

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

// linhas [l, r], hash de tamanho size
string get_hash_arquivo(string s, int size, int l = 0, int r = 1e9) {
	ifstream fin(s.c_str());
	ofstream tmp("tmp.cpp", ios::out);
	string line;
	for (int i = 0; i <= r; i++) {
		if (!getline(fin, line)) break;
		if (i >= l) tmp << line << '\n';
	}
	fin.close();
	tmp.close();
	string hash = exec(hash_cmd + to_string(size));
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

vector<string> split(string line, char c) {
	vector<string> ret;
	string cur;
	line.push_back(c);
	for (char at : line) {
		if (at == c) {
			if (cur.size()) ret.push_back(cur);
			cur.clear();
			continue;
		}
		cur += at;
	}
	return ret;
}

set<string> get_flags(string file) {
	ifstream fin(file.c_str());
	string line;
	getline(fin, line);
	fin.close();
	while (line.size() and line[0] != '[') line = line.substr(1);
	if (!line.size() or line.back() != ']') return {};
	vector<string> flags = split(line.substr(1, line.size() - 2), ',');
	return set<string>(flags.begin(), flags.end());
}

void remove_flags(string& line) {
	int has_flags = 0;
	for (char c : line) {
		if (has_flags == 0 and c == '[') has_flags++;
		if (has_flags == 1 and c == ']') has_flags++;
	}
	if (has_flags != 2) return;
	int idx = -1;
	for (int i = 0; i < line.size(); i++) if (line[i] == '[') {
		idx = i;
		break;
	}
	while (line.size() > idx) line.pop_back();
	while (line.size() and line.back() == ' ') line.pop_back();
}

void printa_arquivo_codigo(string file, bool extra = false) {
	cout << "\\begin{lstlisting}\n";
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	bool started_code = false;
	int depth = 0;
	stack<int> st;
	for (int line_idx = 0; getline(fin, line); line_idx++) {
		int start_line = line_idx;
		if (count++ < 2 and !extra) continue;

		for (char c : line) {
			if (c == '{') depth++, st.push(line_idx);
			if (c == '}') depth--, start_line = st.top(), st.pop();
		}
		
		bool comment = is_comment(line);
		if (!comment) started_code = true;

		if (!extra and started_code) {
			string hash = get_hash_arquivo(file, HASH_LEN, start_line, line_idx);

			if (comment) {
				if (depth != 0) {
					for (int i = 0; i < HASH_LEN + 1; i++)
						cout << " ";
				}
			} else cout << hash << " ";
		}
		cout << line << endl;
	}
	fin.close();
	cout << "\\end{lstlisting}\n\n";
}

void printa_arquivo(string file, bool extra = false) {
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	while (getline(fin, line)) {
		if (count++ < 2 and !extra) continue;
		cout << line << endl;
	}
	fin.close();
}

string get_name(string file) {
	ifstream fin(file.c_str());
	string line;
	getline(fin, line);
	fin.close();
	remove_flags(line);
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

bool printa_listing(string sub, string file, bool extra = false) {
	set<string> flags = get_flags(file);

	if (!print_all and flags.count(NO_PRINT)) return false;

	if (LOOK_FOR_HASH_IN_FILE and !extra and !flags.count(NO_HASH)) {
		if (!find_in_file(file, get_hash_arquivo(file, HASH_LEN)))
			cerr << RED << "WARNING" << RESET << ": hash nao encontrado para: "
			<< file.substr(10) << '\n';
	}

	cout << "\\subsection{";
	if (!extra) printa_cuidado(get_name(file));
	else printa_cuidado(sub);
	cout << "}\n";

	printa_arquivo_codigo(file, extra);
	return true;
}

void dfs(vector<pair<string, string>>& files, string s, bool extra = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while ((entry = readdir(dp))) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) dfs(files, s + "/" + string(entry->d_name), extra);
		else {
			if (!extra) files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
			else printa_listing(entry->d_name, s + "/" + entry->d_name,
					extra and strcmp(entry->d_name, "vimrc"));
			//	A condicao acima printa o hash do vimrc.
			//	Para tirar, deixar apenas "extra".
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

int main(int argc, char** argv) {
	if (argc > 1) {
		string arg1(argv[1]);
		if (arg1 == "--printall") {
			print_all = true;
			cerr << "Printing all files..." << endl << endl;
		}
	}

	printa_arquivo("comeco.tex", true);
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(path.c_str());
	if (dp != nullptr) while ((entry = readdir(dp))) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		string dir(entry->d_name);
		if (dir == "Extra") continue;
		printa_section(dir);

		vector<pair<string, string>> files;
		dfs(files, path + dir);

		sort(files.begin(), files.end(), [&](auto f1, auto f2) {
			return lower(get_name(f1.second)) < lower(get_name(f2.second));
		});

		cerr << "=== " << dir << " ===" << endl;
		for (auto [f, path] : files) {
			bool printed = printa_listing(f.substr(0, f.size() - 4), path);
			if (printed) cerr << get_name(path) << endl;
		}
		cerr << endl;
	}

	cout << "\\pagebreak" << endl;
	printa_section("Extra");
	vector<pair<string, string>> files;
	dfs(files, path + "Extra", true);

	cout << "\\end{document}\n";
	return 0;
}
