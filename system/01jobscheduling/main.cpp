#include <iostream>
#include <queue>
#include <algorithm>
#include <stdio.h>
#define N 7

using namespace std;

struct job {
    int jid;
    int entertime;
    int runtime;
    double rate=0;
};


void JobHandler(job* jobs, int method);

bool fifosort(job j1, job j2);
bool minsort(job j1, job j2);
bool hrrnsort(job j1, job j2);

int timeadd(int current, int added);
int timemin(int now, int before);

int main() {
    job jobs[N];
    for(int i = 0; i < N; i++) {
        scanf("%d %d %d", &jobs[i].jid, &jobs[i].entertime, &jobs[i].runtime);
    }

	cout << endl;
    cout << "FIFO" << endl;
    cout << "jid  entertime  runtime current" << endl;
    JobHandler(jobs, 0);
    cout << endl;

    cout << "短作业优先" << endl;
    cout << "jid  entertime  runtime current" << endl;
    JobHandler(jobs, 1);
    cout << endl;

    cout << "HRRN" << endl;
    cout << "jid  entertime  runtime current" << endl;
    JobHandler(jobs, 2);
    return 0;
}

// 返回格式化时间
int timeadd(int current, int added){
    int currenthour = current/100;
    int currentmin = (current - currenthour*100) + added;
    currenthour = currenthour + currentmin / 60;
    currentmin = currentmin-(currentmin/60)*60;
    return currenthour*100 + currentmin;
}

// 返回差距的分钟数
int timemin(int now, int before){
    int hour = (now/100) - (before/100);
    int min = now%100 - before%100;
    return hour * 60 + min;
}

bool hrrnsort(job j1, job j2) {
    return j1.rate < j2.rate;
}

bool fifosort(job j1, job j2) {
    return j1.jid > j2.jid;
}

bool minsort(job j1, job j2) {
    return j1.runtime > j2.runtime;
}

// method: 0  1  2
void JobHandler(job* jobs, int method)
{
    int current = 0;
    vector<job> jv;

    int countjob = 0;
    int i = 0;

    while(countjob < N) {
        // 执行任务
        if(jv.size() == 0) {
            jv.push_back(jobs[i]);
            current = jobs[i].entertime;
            i += 1;
        }
        job j = *(jv.end()-1);
        current = timeadd(current, j.runtime);
        printf("%d     %d        %d       %d\n", j.jid, j.entertime, j.runtime, current);
        countjob += 1;
        jv.pop_back();

        // 继续入队
        for( ; i < N; ) {
            if( timemin(current, jobs[i].entertime) >= 0 ) {
                jv.push_back(jobs[i]);
                i += 1;
            } else {
                break;
            }
        }
        // 根据 method 不同进行排序
        // FIFO
        if (method == 0) {
            sort(jv.begin(), jv.end(), fifosort);
        }
        // 短作业优先
        else if(method == 1) {
            sort(jv.begin(), jv.end(), minsort);
        }
        // 最优XX优先
        else if(method == 2) {
            // 计算rate, 根据rate排序
            for (int k = 0; k < jv.size(); k++) {
                jv[k].rate = (timemin(current, jv[k].entertime) + double(jv[k].runtime)) / double(jv[k].runtime);
            }
            sort(jv.begin(), jv.end(), hrrnsort);
        }

    }
}


