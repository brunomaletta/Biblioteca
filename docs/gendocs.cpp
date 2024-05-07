#include <bits/stdc++.h>
#include <dirent.h>

namespace fs = std::filesystem;
using namespace std;

#define RED "\033[0;31m"
#define RESET "\033[0m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define NO_BOLD "\033[0m"

bool LOOK_FOR_HASH_IN_FILE = false;
int HASH_LEN = 3;

string NO_HASH = "nohash";
string NO_PRINT = "noprint";

string PATH = "../Codigo/";
string docs_path = "../content/docs/";
string link = "https://github.com/brunomaletta/Biblioteca/tree/master/";

#ifdef __clang__
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
           "| clang -E -x c++ -dD -P - | tr -d '[:space:]' | md5sum | cut -c-";
#else
string hash_cmd = "sed -n 1','10000' p' tmp.cpp | sed '/^#w/d' "
"| cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-";
#endif

bool print_all = false;
bool overwrite = false;

void strip(string& str) {
    if (str.length() == 0) return;

    auto start_it = str.begin();
    auto end_it = str.rbegin();
    while (isspace(*start_it)) {
        ++start_it;
        if (start_it == str.end()) break;
    }
    while (isspace(*end_it)) {
        ++end_it;
        if (end_it == str.rend()) break;
    }
    int start_pos = start_it - str.begin();
    int end_pos = end_it.base() - str.begin();
    str = start_pos <= end_pos ? string(start_it, end_it.base()) : "";
}


bool is_comment(string line) {
	while (line.size() and (line[0] == ' ' or line[0] == '\t'))
		line = line.substr(1);
	bool comment = line.size() == 0;
	if (line.size() >= 2 and line.substr(0, 2) == "//") comment = true;
	if (line.size() >= 2 and line.substr(0, 2) == "/*") comment = true;
	return comment;
}

void remove_comment(string &line){
	if (line.size() >= 2 and line.substr(0, 2) == "//")
		line = line.substr(2);
	if (line.size() >= 2 and line.substr(0, 2) == "/*")
		line = line.substr(2);
	if (line.size() >= 2 and line.substr(line.size() - 2, 2) == "*/")
		line = line.substr(0, line.size() - 2);
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

pair<vector<string>, vector<string>> get_code(string file){
	ifstream fin(file.c_str());
	string line;
	int count = 0;
	bool started_code = false;
	int depth = 0;
	stack<int> st;
	vector<string> comment_lines;
	vector<string> code_lines;
	for (int line_idx = 0; getline(fin, line); line_idx++) {
		int start_line = line_idx;
		if (count++ < 2) continue;

		for (char c : line) {
			if (c == '{') depth++, st.push(line_idx);
			if (c == '}') depth--, start_line = st.top(), st.pop();
		}
		
		bool comment = is_comment(line);
		if (!comment) started_code = true;
		if (started_code) {
			code_lines.push_back(line);
		} else {
			comment_lines.push_back(line);
		}
	}
	fin.close();

	return {comment_lines, code_lines};
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

void dfs(vector<pair<string, string>>& files, string s, bool extra = false) {
	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(s.c_str());
	if (dp != nullptr) while ((entry = readdir(dp))) {
		if (entry->d_name[0] == '.') continue;	

		if (entry->d_type == DT_DIR) dfs(files, s + "/" + string(entry->d_name), extra);
		else {
			files.emplace_back(entry->d_name, s + "/" + string(entry->d_name));
		}
	}
}

string lower(string s) {
	for (char& c : s) if (c >= 'A' and c <= 'Z') c ^= 32;
	return s;
}

time_t get_current_time(){
	auto now = std::chrono::system_clock::now();
	return std::chrono::system_clock::to_time_t(now);
}

string time_to_string(time_t time, string format = "%Y-%m-%dT%H:%M:%S%z"){
    std::tm* now_tm = std::localtime(&time);
    // Format the time using stringstream
    std::stringstream ss;
    ss << std::put_time(now_tm, format.c_str());
    return ss.str();
}

string get_docs_path(string code_path) {
	code_path.replace(code_path.find(".cpp"), sizeof(".cpp") - 1, ".md");
	code_path.erase(0, PATH.size());
	code_path.insert(0, docs_path);
	return code_path;
}

string get_original_link(string path_code) {
	// Remove '../' from path_code
	path_code.replace(path_code.find("../"), sizeof("../") - 1, "");
	return link + path_code;
}

void create_code_file(string path_docs, string path_code, string title) {
	// pair < comments, code >
	pair<vector<string>, vector<string>> code = get_code(path_code);

	ofstream out(path_docs);
	out << "---" << endl;
	out << "weight: 10" << endl;
	out << "title: \"" << title << "\"\n";
	out << "draft: false" << endl;
	out << "toc: true" << endl;
	out << "date: \"" << time_to_string(get_current_time()) << "\"" << endl;
	out << "publishdate: \"" << time_to_string(get_current_time()) << "\"" << endl;
	out << "description: " << "\"\"" << endl;
	out << "---" << endl << endl;

	out << "## Sobre" << endl;
	for (auto line : code.first) {
		remove_comment(line);
		out << line << endl << endl;
	}

	string full_link = get_original_link(path_code);
	string short_link = full_link.substr(full_link.find_last_of("/") + 1);

	out << "Link original: [" << short_link << "](" << full_link << ")" << endl;
	out << endl;

	out << "## Código" << endl;
	out << "```cpp" << endl;
	for (auto line : code.second) {
		out << line << endl;
	}
	out << "```" << endl;
	out.close();
}

void create_default_index(string path_index, string index_title) {
	string date = time_to_string(get_current_time());
	
	ofstream out(path_index);
	out << "---" << endl;
	out << "weight: 10" << endl;
	out << "title: \"" << index_title << "\"\n";
	out << "draft: false" << endl;
	// out << "toc: true" << endl;
	out << "date: \"" << date << "\"" << endl;
	out << "description: " << "\"\"" << endl;
	out << "publishdate: \"" << date << "\"" << endl;
	out << "---" << endl;
	out.close();
}

void create_section(string path) {
	// Check if directory exists
	string dir = docs_path + path;
	if (fs::is_directory(fs::path(dir))){
		// Check if dir + '/_index.md' exists
		string index = dir + "/_index.md";
		if (!fs::exists(fs::path(index))) {
			cerr << "Creating index file: " << index << endl;
			create_default_index(index, path);
		}
	}
	else {
		cerr << "Creating directory: " << dir << endl;
		fs::create_directory(fs::path(dir));
		// print type of dir
		string index = dir + "/_index.md";
		create_default_index(index, path);
	}
}

int main(int argc, char** argv) {
	if (argc > 1) {
		string arg1(argv[1]);
		if (arg1 == "--overwrite") {
			overwrite = true;
			cerr << "Rewriting all docs files..." << endl << endl;
		}
	}

	struct dirent* entry = nullptr;
	DIR* dp = nullptr;
	dp = opendir(PATH.c_str());
	if (dp != nullptr) while ((entry = readdir(dp))) {
		if (entry->d_name[0] == '.') continue;
		if (entry->d_type != DT_DIR) continue;

		string dir(entry->d_name);
		cout << RED << "=== " << dir << " ===" << RESET << endl;
		create_section(dir);
		if (dir == "Extra") continue;

		vector<pair<string, string>> files;
		dfs(files, PATH + dir);
		
		// print all files
		for (auto [f, f_path] : files) {
			string title = get_name(f_path);
			strip(title);
			string path_docs = get_docs_path(f_path);
			cout << CYAN << "\t" << title << RESET << endl;
			cerr << "\t" << f_path << " -> " << path_docs << endl;

			if (overwrite) {
				create_code_file(path_docs, f_path, title);
			}
			else{
				if (!fs::exists(fs::path(path_docs))) {
					create_code_file(path_docs, f_path, title);
				}
				else {
					cerr << "File already exists: " << path_docs << endl;
				}
			}
		}
	}

	// printa_section("Extra");
	vector<pair<string, string>> files;
	// dfs(files, path + "Extra", true);

	return 0;
}
