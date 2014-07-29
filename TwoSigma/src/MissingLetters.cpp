#include "MissingLetters.h"
#include <vector>

using namespace std;

string MissingLetters::getMissingLetters(const string &sentence)
{
    vector<bool> matched(26, false);
    char cur;
    for (size_t i = 0; i<sentence.length(); ++i)
    {
        cur = sentence[i];

        if (cur >= 'A' && cur <= 'Z')
        {
            matched[cur - 'A'] = true;
        }
        else if (cur >= 'a' && cur <= 'z')
        {
            matched[cur - 'a'] = true;
        }
    }

    string ret;
    for (size_t i = 0; i < 26; ++i)
    {
        if (!matched[i])
        {
            ret.push_back('A' + i);
        }
    }

    return ret;
}

