#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>

#define _KEY_WORD_END "waiting for your expanding"

using namespace std;

/*************************全局变量**********************************/


typedef struct {
    int typenum;
    char * word;
} WORD;
char input[255];
char token[255] = "";
int p_input;        /*输入换缓冲区指针（指向数组中元素）*/
int p_token;        /*单词缓冲区指针*/
char ch;            /*当前读入的字符*/
char* rwtab[] = {"begin", "if", "then", "while", "do", "end", _KEY_WORD_END};   /*关键词组*/


/*****************************函数定义******************************/
WORD* scaner();
char m_getch();
void getbc();
void concat();
int letter();
int digit();
int reserve();
void retract();
char* dtb();


int main() {
	// file set up
	ifstream in("inputfile");
	while(!in.eof()){
		in.getline(input, 100);
		break;
	}
	
	ofstream out("outfile");

    int over = 1;
    WORD* oneword = new WORD;
    p_input = 0;

    while(over < 1000 && over != -1) {
        oneword = scaner();
        if (oneword->typenum < 1000) {
			out << "(" << oneword->typenum << ", " << oneword->word << " )\n";
        }
        over = oneword->typenum;
    }
	out << "(" << 0 << ", " << "#" << " )\n";
	out.close();
    return 0;
}

WORD* scaner() {
    WORD* myword = new WORD;
    myword -> typenum = 10;
    myword -> word = "";
    p_token = 0;
    m_getch();
    getbc();
    if(letter()) {
        while(letter() || digit()) {
            concat();
            m_getch();
        }
        retract();
        myword->typenum=reserve();
        myword->word=token;
        return myword;
    }
    else if(digit()) {
        while (digit()) {
            concat();
            m_getch();
        }
        retract();
        myword->typenum = 11;
        myword->word = token;
        return myword;
    }
    else {
        switch (ch) {
            case '=':
                m_getch();
                if(ch == '=') {
                    myword->typenum=39;
                    myword->word = "==";
                    return myword;
                }
                retract();
                myword->typenum=21;
                myword->word = "=";
                return myword;
                break;
            case '+':
                myword->typenum = 22;
                myword->word = "+";
                return myword;
                break;
            case '-':
                myword->typenum = 23;
                myword->word = "-";
                return myword;
                break;
            case '*':
                myword->typenum = 24;
                myword->word = "*";
                return myword;
                break;
            case '/':
                myword->typenum = 25;
                myword->word = "/";
                return myword;
                break;
            case '(':
                myword->typenum = 26;
                myword->word = "(";
                return myword;
                break;
            case ')':
                myword->typenum = 27;
                myword->word = ")";
                return myword;
                break;
            case '[':
                myword->typenum = 28;
                myword->word = "[";
                return myword;
                break;
            case ']':
                myword->typenum = 29;
                myword->word = "]";
                return myword;
                break;
            case '{':
                myword->typenum = 30;
                myword->word = "{";
                return myword;
                break;
            case '}':
                myword->typenum = 31;
                myword->word = "}";
                return myword;
                break;
            case ',':
                myword->typenum = 32;
                myword->word = ",";
                return myword;
                break;
            case ':':
				m_getch();
				if(ch == '=') {
					myword->typenum = 18;
					myword->word = ":=";
					return myword;
					break;
				}
				retract();
                myword->typenum = 17;
                myword->word = ":";
                return myword;
                break;
            case ';':
                myword->typenum = 34;
                myword->word = ";";
                return myword;
                break;
            case '>':
                m_getch();
                if(ch == '=') {
                    myword->typenum = 37;
                    myword->word = ">=";
                    return myword;
                }
                // else
                retract();
                myword->typenum = 35;
                myword->word = ">";
                return myword;
                break;
            case '<':
                m_getch();
                if(ch == '=') {
                    myword->typenum = 37;
                    myword->word = "<=";
                    return myword;
                }
                // else
                retract();
                myword->typenum = 35;
                myword->word = "<";
                return myword;
                break;
            case '!':
                m_getch();
                if(ch == '=') {
                    myword->typenum = 40;
                    myword->word = "!=";
                    return myword;
                }
                retract();
                myword->typenum = -1;
                myword->word = "ERROR";
                return myword;
                break;
            case '\0':
                myword->typenum = 1000;
                myword->word = "OVER";
                return myword;
                break;
            default:myword->typenum = -1; myword->word="ERROR"; return myword;
        }
    }


}


char m_getch() {
    ch = input[p_input];
    p_input = p_input + 1;
    return ch;
}

void getbc() {
    while(ch == ' ' || ch == 10) {
        ch = input[p_input];
        p_input += 1;
    }
}

void concat() {
    token[p_token] = ch;
    p_token += 1;
    token[p_token] = '\0';
}

int letter() {
    if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
        return 1;
    } else {
        return 0;
    }

}

int digit() {
    if(ch >= '0' && ch <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int reserve() {
    int i = 0;
    while(strcmp(rwtab[i], _KEY_WORD_END)){
        if(!strcmp(rwtab[i], token)) {
            return i+1;
        }
        i += 1;
    }
    return 10;
}

void retract() {
    p_input -= 1;
}

char* dtb() {
    string s = "";
    int num = 0;
    int i =0;
    while(token[i] != '\0') {
        i++;
    }
    i -= 1;
    while(i > 0) {
        num = num*10 + token[i] - '0';
    }

    while(num != 0){
        if(num % 2 == 0){
            s = s + "0";
            num /= 2;
        }
        else if (num % 2 == 1){
            s = s + "1";
            num /= 2;
        }
    }
    char* ret = &s[0u];
    return ret;
}
