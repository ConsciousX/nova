#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    {
        regex reg("\\b(sub)([^ ]*)");

        string str("this subject has a submarine as a subsequence");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("the|top|coder");

        string str("Marius is one of the topcoders");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("(top|coder)+");

        string str("this regex matches topcoder and also codertop");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("1{2,4}");

        string str("101+10=111, 11111=10000+1111");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("([a-z]+).\1");

        string str("top-topcoder|coder");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("[^b-d]at");

        string str("bat hat cat rat");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }
    {
        regex reg("<([a-zA-Z][a-zA-Z0-9]*)()|[^>]*)>(.*)</\1>");

        string str("<font size=\"2\">TopCoder is the</font> <b>best</b>");
        sregex_iterator it(str.begin(), str.end(), reg);
        sregex_iterator end;

        while (it != end)
        {
            cout<<"Found the text "<<it->str()<<" staring at index "<<it->position()<< " and ending at index "<<it->position()+it->length()<<endl;
            ++it;
        }
    }


    return 0;
}
    

   
