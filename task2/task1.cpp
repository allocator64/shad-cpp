#include <iostream>
#include <string>

enum state_t {
    no_comment,
    line_comment,
    multiline_comment,
    characters
};

std::string remove_comments(const std::string &s) {
    std::string res;

    size_t idx = 0;
    state_t state = no_comment;

    while (idx < s.size()) {
        if (state == no_comment) {
            if (s[idx] == '/' && (idx + 1 < s.size() && s[idx + 1] == '/')) {
                idx += 2;
                state = line_comment;
            } else if (s[idx] == '/' &&
                    (idx + 1 < s.size() && s[idx + 1] == '*')) {
                idx += 2;
                state = multiline_comment;
            } else if (s[idx] == '"') {
                idx++;
                state = characters;
            } else {
                res += s[idx++];
            }
        } else if (state == line_comment) {
            if (s[idx] == '\n') {
                state = no_comment;
                res += s[idx];
            }
            idx++;
        } else if (state == multiline_comment) {
            if (s[idx] == '*' && (idx + 1 < s.size() && s[idx + 1] == '/')) {
                idx += 2;
                state = no_comment;
            } else {
                idx++;
            }
        } else if (state == characters) {
            res += s[idx];
            if (s[idx] == '"')
                state = no_comment;
            idx++;
        }
    }

    return res;
}

int main(int argc, char **argv) {
    std::string buf, line;
    while (std::getline(std::cin, line))
        buf += line + "\n";
    std::cout << remove_comments(buf);
    return 0;
}
