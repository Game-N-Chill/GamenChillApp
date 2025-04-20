
#include "MKTG.hpp"

static std::string getSubLine(std::string line, size_t index)
{
    std::string subLine = line.substr(0, index);
    size_t first = 0;
    size_t last = subLine.size() - 1;

    if ((subLine[first] == '\"' && subLine[last] == '\"') || (subLine[first] == '\'' && subLine[last] == '\'')) {
        subLine = subLine.substr(first + 1, last - 1);
    }

    return subLine;
}

std::vector<std::string> lineParser(std::string line)
{
    std::vector<std::string> vec;
    size_t index = 0;
    bool inString = false;

    while (!line.empty()) {
        if (index == line.size() || line[index] == ' ') {
            if (index == 0) {
                line.erase(0, 1);
                continue;
            }
            if (inString && index < line.size()) {
                index++;
                continue;
            }

            vec.push_back(getSubLine(line, index));
            line.erase(0, index + 1);
            index = 0;
        } else {
            if (line[index] == '\'' || line[index] == '\"') {
                inString = !inString;
            }
            index++;
        }
    }

    return vec;
}
