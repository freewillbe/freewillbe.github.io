#include <iostream>                 #include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
                                    vector<string> split(string str, string pattern) {
    vector<string> ret;
    if (pattern.empty()) return ret;
    size_t start = 0, index = str.find_first_of(pattern, 0);                while (index != str.npos) {
        if (start != index) ret.push_back(str.substr(start, index - start));
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty()) ret.push_back(str.substr(start));
    return ret;
}

int main() {
    string line, cmd, keyword, knowledge;
    vector<pair<string, string>> data;
    while (true) {
        cout << "请输入指令（1.提问 2.添加知识 3.退出）：" << endl;
        getline(cin, cmd);
        if (cmd == "1") {
            cout << "请输入问题：" << endl;
            getline(cin, line);
            bool found = false;
            for (auto &d : data) {
                auto keywords = split(d.first, ",");
                for (auto &keyword : keywords) {
                    if (line.find(keyword) != string::npos) {
                        found = true;
                        cout << d.second << endl;
                        break;
                    }
                }
                if (found) break;
            }
            if (!found) {
                cout << "我还不知道 呢，您可以教我一下~" << endl;
            }
        } else if (cmd == "2") {
            cout << "请输入关键词：" << endl;
            getline(cin, keyword);
            cout << "请输入知识，以 空行结束：" << endl;
            knowledge = "";
            while (true) {
                string temp;
                getline(cin, temp);
                if (temp.empty()) break;
                knowledge += temp + "\n";
            }
            data.push_back(make_pair(keyword, knowledge));
            cout << "已添加知识：" << knowledge << endl;
        } else if (cmd == "3") {
            break;
        } else {
            cout << "指令无效，请重 新输入！" << endl;
        }
    }
    return 0;
}
