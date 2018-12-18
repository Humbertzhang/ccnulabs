#include <iostream>
#include <list>
#include <vector>

#define NNode 10
#define NRequest 5

using namespace std;

typedef struct node {
    int startadd;
    int endadd;
    int size;
    node* next;
} MNode;

int requests[NRequest];

void firstfit(MNode * head);
void bestfit(MNode * head);
void worstfit(MNode * head);

int main() {
    MNode* head;
    head = new MNode();
    MNode* head2 = head;

    cout << "input " << NNode << " start and end infos" << endl;

    for(int i = 0; i < NNode; i++) {
        MNode * n;
        n = new MNode();
        cin >> n->startadd >> n->endadd;
        n->size = n->endadd - n->startadd;

        head->next = n;
        head = n;
    }
    cout << "input " << NRequest << " requests size." << endl;
    for (int i = 0; i < NRequest; i+=1) {
        cin >> requests[i];
    }
    head2 = head2->next;
    cout << "first fit" << endl;
    firstfit(head2);
    cout << "best fit " << endl;
    bestfit(head2);
    cout << "wrost fit" << endl;
    worstfit(head2);

    return 0;
}


void firstfit(MNode * head){
    for(int i = 0; i < NRequest; i++) {
        int flag = 0;
        int rsize = requests[i];
        MNode* h = head;
        while(h != NULL) {
            if(h->size >= rsize) {
                cout << "node(start address " << h->startadd <<  " end address:" << h->endadd << " size:" << h->size
                            << ")"  << "was allocate for request:" << rsize << endl;
                h->startadd += rsize;
                h->size = h->endadd - h->startadd;
                flag = 1;
                break;
            }
            else {
                h = h->next;
            }
        }
        if(flag == 0) {
            cout << "request:" << rsize << " can't be fit" << endl;
        }
    }
}

void bestfit(MNode * head){
    for(int i = 0; i < NRequest; i++) {
        MNode* h = head;
        int minsize = INT32_MAX;
        int rsize = requests[i];

        while(h != NULL) {
            if(h->size >= rsize && h->size < minsize) {
                minsize = h->size;
            }
            h = h->next;
        }
        if(minsize == INT32_MAX) {
            cout << "request:" << rsize << " can't be fit" << endl;
            continue;
        }
        MNode* h2 = head;
        while(h2 != NULL) {
            if(h2->size == minsize) {
                cout << "node(start address " << h2->startadd <<  " end address:" << h2->endadd << " size:" << h2->size
                     << ")"  << "was allocate for request:" << rsize << endl;
                h2->startadd += rsize;
                h2->size = h2->endadd - h2->startadd;
                break;
            }
            h2 = h2->next;
        }
    }
}
void worstfit(MNode * head)
{
    for(int i = 0; i < NRequest; i++) {
        MNode * h = head;
        int maxsize = 0;
        int rsize = requests[i];

        while(h != NULL) {
            if(h->size >= rsize && h->size >= maxsize) {
                maxsize = h->size;
            }
            h = h -> next;
        }

        if(maxsize == 0) {
            cout << "request:" << rsize << " can't be fit" << endl;
            continue;
        }

        MNode* h2 = head;
        while(h2 != NULL) {
            if(h2->size == maxsize) {
                cout << "node(start address " << h2->startadd <<  " end address:" << h2->endadd << " size:" << h2->size
                     << ")"  << "was allocate for request:" << rsize << endl;
                h2->startadd += rsize;
                h2->size = h2->endadd - h2->startadd;
                break;
            }
            h2 = h2->next;
        }


    }
}
