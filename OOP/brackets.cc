#include "iostream"
#include "vector"
#include "string"

using namespace std;

// NOT DONE

namespace MyNamespace
{
    class Bracks {

        public:
        Bracks(){
            string str;
            vector vec;
            uint32_t brack_count;
        };

        void readStr(){
            getline(cin, this->str);
        }

        void putToVec(){
            int c = this->str.length;
            for (int i = 0; i < c; ++i){
                string tmp = this->str[i];
                if (tmp == '(' or ')'){
                    this->vec.push(tmp);
                }
            }
        }

        void brackCount(){
            int c = this->vec.length();
            for (int i = 0; i < c; ++i){
                char ch = 
            }
        }
    }
}