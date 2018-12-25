#include <iostream>
#include <list>

#define N 12
#define S 3
using namespace std;

int requests[N] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
int spaces[S];

void FIFO();
void LRU();

int main() {
    cout << "FIFO" << endl;
    FIFO();
    cout << "LRU" << endl;
    LRU();
    return 0;
}

void FIFO()
{
    int mpagetime = 0;
    int fifo_requests[N];
    // 初始化请求
    for(int i = 0; i < N; i++) {
        fifo_requests[i] = requests[i];
    }
    // 初始化空闲空间
    for(int i = 0; i < S; i++) {
        spaces[i] = 0;
    }

    for(int i = 0; i < N; i++) {
        int request = fifo_requests[i];
        cout << "请求:" << request ;
        int mpageflag = 1;
        for(int j = 0; j < S; j++) {
            if (request == spaces[j]) {
                mpageflag = 0;
            }
        }
        if(mpageflag == 0) {
            cout << " 命中:" << request;
        } else {
            mpagetime += 1;
            cout << " 缺页:" << request;

            int has_space = 0;
            for(int q = 0; q < S; q++) {
                if(spaces[q] == 0) {
                    has_space = 1;
                    spaces[q] = request;
                    break;
                }
            }
            // 没有空闲页面，淘汰最前面的那个页面
            if (has_space == 0) {
                int dropped = spaces[0];
                // 覆盖掉最前面的页面（淘汰）
                for(int k = 0; k < S-1; k++) {
                    spaces[k] = spaces[k+1];
                }
                spaces[S-1] = request;
                cout << " 淘汰:" << dropped;
            }
        }
        cout << endl;
    }

    cout << "总缺页次数:" << mpagetime << endl;
    cout << "缺页率:" << double(mpagetime) / N << endl;
}

/**
 * 命中缓存：将页面放到链表头部.
 * 未命中：将页面插入到链表头，如果大于链表最大大小（3），则pop_back
 */
void LRU()
{
    int mpagetime = 0;
    int lru_requests[N];
    for(int i = 0; i < N; i++) {
        lru_requests[i] = requests[i];
    }
    list<int> spaces;


    for(int i = 0; i < N; i++) {
        int request = lru_requests[i];
        cout << "请求:" << request ;
        int msflag = 1;

        for(auto it = spaces.begin(); it != spaces.end(); it++) {
            if (*it == request) {
                cout << " 命中:" << request;
                //命中放到链表头
                int head = *it;
                spaces.erase(it);
                spaces.push_front(head);
                msflag = 0;
                break;
            }
        }
        if(msflag == 1) {
            // 缺页，判断原有多少
            cout << " 缺页:" << request;
            mpagetime += 1;

            if(spaces.size() < 3) {
                spaces.push_front(request);
            }
            else {
                spaces.push_front(request);
                int tail = spaces.back();
                cout << " 淘汰:" << tail;
                spaces.pop_back();
            }
        }
        cout << endl;
    }
    cout << "总缺页次数:" << mpagetime << endl;
    cout << "缺页率:" << double(mpagetime) / N << endl;
}
