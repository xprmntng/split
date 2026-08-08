#include <sstream>

#include "split.hpp"

using std::vector;
using std::string;
using std::istringstream;
using std::getline;

namespace split {
    vector<string> split(const string& str, char delimeter) {
        vector<string> pieces;

        istringstream stream(str);
        string piece;
        while (getline(stream, piece, delimeter)) {
            pieces.push_back(piece);
        }
        // Edge case where the last character in the string is the delimeter
        bool trailing = !str.empty() && str.back() == delimeter;
        if (trailing) {
            // Add an empty string, representing the empty string to the right of the ending
            // delimeter
            pieces.push_back("");
        }
        return pieces;
    }
}
