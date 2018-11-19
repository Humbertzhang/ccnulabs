#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

typedef struct {
    int typenum;
    char word[255];
} WORD ;

WORD gw;
WORD input[100];

int windex = 0;
int kk = 0;

void scannext();
void lrparser();
void yucu();
void statement();
void expression();
void term();
void factor();

int main() {
    FILE* f = fopen("outfile", "r");
    int count = 0;
    while( fscanf(f, "(%d, %s )\n", &input[count].typenum, input[count].word ) != -1) {
		count += 1;
	}
	/*for(int i = 0; i < count; i++){
		printf("string: %d %s\n", input[i].typenum, input[i].word);
	}*/
	scannext();
	lrparser();
    return 0;
}


void scannext() {
    gw = input[windex];
    windex += 1;
}

void lrparser() {
    if (gw.typenum == 1) {
        scannext();
        yucu();
        if(gw.typenum == 6) {
            scannext();
            if(gw.typenum == 0 && kk == 0) {
                cout << "success" << endl;
            }
        }
        else {
            if(kk != 1) {
                cout << "缺end错误" << endl;
                kk = 1;
            }
        }
    }
    else {
        cout << "begin错误." << endl;
        kk = 1;
    }
    return;
}

void yucu() {
    statement();
    while(gw.typenum == 34) {
        scannext();
        statement();
    }
    return;
}

void statement() {
    if(gw.typenum == 10) {
        scannext();
        if(gw.typenum == 18) {
            scannext();
            expression();
        }
        else {
            cout << "赋值号错误" << endl;
            kk = 1;
        }
    }
    else {
        cout << "语句错误" << endl;
        kk = 1;
    }
    return;
}


void expression() {
    term();
    while(gw.typenum == 22 || gw.typenum == 23) {
        scannext();
        term();
    }
    return;
}

void term() {
    factor();
    while(gw.typenum == 24 || gw.typenum == 25) {
        scannext();
        factor();
    }
    return;
}

void factor() {
    if(gw.typenum == 10 || gw.typenum == 11) {
        scannext();
    }
    else if(gw.typenum == 26) {
        scannext();
        expression();
        if(gw.typenum == 27) {
            scannext();
        }
        else {
            cout << ") 错误" << endl;
            kk = 1;
        }
    }
    else {
        cout << "factor:表达式错误" <<endl;
        kk = 1;
    }
    return;
}

