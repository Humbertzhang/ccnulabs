#include <iostream>
#include <queue>
#include <algorithm>
#include <stdio.h>
#define N 10

using namespace std;

struct process {
    int pid;
    int entertime;
    int runtime;
	int level;
	int waittime;
};


void ProcessHandler(process* processes, int method);

bool fifosort(process j1, process j2);
bool levelsort(process j1, process j2);

int timeadd(int current, int added);
int timemin(int now, int before);

int main() {
	process processes[N];
    for(int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &processes[i].pid, &processes[i].entertime, &processes[i].runtime, &processes[i].level);
		processes[i].waittime = 0;
    }
	printf("fifo:\n");
	printf("pid level waittime current entertime\n");
	ProcessHandler(processes, 1);

	printf("level first:\n");
	printf("pid level waittime current entertime\n");
	ProcessHandler(processes, 3);

	printf("时间片调度:\n");
	printf("pid level waittime current entertime\n");
	ProcessHandler(processes, 2);

	printf("多级调度:\n");
	printf("pid level waittime current entertime\n");
	ProcessHandler(processes, 4);
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


bool fifosort(process p1, process p2) {
    return p1.pid > p2.pid;
}

bool levelsort(process p1, process p2) {
    if(p1.level != p2.level) {
		return p1.level > p2.level;
	}
	else {
		return p1.entertime > p2.entertime;
	}
}

void ProcessHandler(process* processes, int method)
{
	if(method == 1 || method == 3) {
		int waittimeall = 0;
		int current = 0;
		vector<process> pv;

		int countjob = 0;
		int i = 0;
		while(countjob < N) {
			// 执行
			if(pv.size() == 0) {
				pv.push_back(processes[i]);
				current = processes[i].entertime;
				i += 1;
			}
			process p = *(pv.end()-1);
			p.waittime = timemin(current, p.entertime);
			waittimeall += p.waittime;
			current = timeadd(current, p.runtime);
			countjob += 1;
			pv.pop_back();
			printf("%d    %d       %d      %d     %d\n", p.pid, p.level ,p.waittime, current, p.entertime);

			// 继续入队
			for( ; i < N; ) {
				if( timemin(current, processes[i].entertime) >= 0 ) {
					pv.push_back(processes[i]);
					i += 1;
				} else {
					break;
				}
			}
			// 根据 method 不同进行排序
			// FIFO
			if (method == 1) {
				sort(pv.begin(), pv.end(), fifosort);
			}
			// 优先数
			else if(method == 3) {
				sort(pv.begin(), pv.end(), levelsort);
			}
		}
		printf("waittime average: %d\n", waittimeall/N);
	}
	// 时间片
	else if(method == 2) {
		// 将时间片设置为5每片
		int TIMESLICE = 5;
		int waittimeall = 0;
		int countjob = 0;
		int current = processes[0].entertime;
		int counter = 0;
		vector<process> pv;

		while(countjob < N) {
			// 到时间的进程入v
			for(int i =0; i < N; i++) {
				if(processes[i].entertime == current) {
					pv.push_back(processes[i]);
				}
			}
			current = timeadd(current, TIMESLICE);
			// 一个进程使用掉时间片，如果此时runtime = 0，则countjob += 1
			// 其他进程增加等待时间
			if(counter >= pv.size()){
				counter = 0;
			}
			pv[counter].runtime -= TIMESLICE;
			printf("%d    %d       %d      %d     %d\n", pv[counter].pid, pv[counter].level, pv[counter].waittime, current, pv[counter].entertime);
			for(int i = 0; i < pv.size(); i++) {
				if(i != counter) {
					pv[i].waittime += TIMESLICE;
				}
			}
			if(pv[counter].runtime == 0) {
				countjob += 1;
				waittimeall += pv[counter].waittime;
				pv.erase(pv.begin() + counter);
			}
			counter += 1;
		}
		printf("waittime average: %d\n", waittimeall/N);
	}
	else if(method == 4) {
		deque<process> q1;
		deque<process> q2;
		deque<process> q3;
		int waittimeall = 0;
		int TIMESLICE = 5;
		int q1t = 10;
		int q2t = 20;
		int q3t = 30;
		int countjob = 0;
		int current = processes[0].entertime;
		q1.push_back(processes[0]);
        int entered[N] = {0};
		int changeflag = 0;
		while(countjob < N) {
			changeflag = 0;
			// 判断q1 q2 q3 是否empty.
			if(!q1.empty()) {
				process pfn = q1.front();
				process* pf;
				for(int j = 0; j < q1t && !q1.empty(); j += TIMESLICE) {
					pf = &q1.front();
					pf->runtime -= TIMESLICE;
					current = timeadd(current, TIMESLICE);
					printf("%d    %d     %d     %d     %d\n", pf->pid, pf->level, pf->waittime, current, pf->entertime);
					int q1size = q1.size();
					int q2size = q2.size();
					int q3size = q3.size();
					for(int i = 0; i < q1size; i++){
						if(q1[i].pid != pf->pid) {
							q1[i].waittime += TIMESLICE;
						}
					}
					for(int i = 0; i < q2size; i++) {
						q2[i].waittime += TIMESLICE;
					}
					for(int i = 0; i < q3size; i++) {
						q3[i].waittime += TIMESLICE;
					}
					// 一个进程结束
					if(pf->runtime == 0) {
						q1.pop_front();
						countjob += 1;
						changeflag = 1;
						waittimeall += pf->waittime;
					}
					// 检查有没有新进程进来
					for(int i = 0; i < N; i++) {
						if(processes[i].entertime == current && !entered[i]) {
							q1.push_back(processes[i]);
							entered[i] = 1;
						}
					}
				}
				if (pf->pid == pfn.pid && !changeflag)  {
					q1.pop_front();
					q2.push_back(*pf);
				}
			} else if (!q2.empty()) {
				int stopflag = 0;
				int changeflag = 0;
				process pfn = q2.front();
				process* pf;
				for(int j = 0; j < q2t && !q2.empty(); j+= TIMESLICE) {
					pf = &q2.front();
					printf("%d     %d     %d     %d     %d\n", pf->pid, pf->level, pf->waittime, current, pf->entertime);
					pf->runtime -= TIMESLICE;
					current = timeadd(current, TIMESLICE);
					for(int i = 0; i < q2.size(); i++) {
						if(q2[i].pid != pf->pid) {
							q2[i].waittime += TIMESLICE;
						}
					}
					for(int i = 0; i < q3.size(); i++) {
						q3[i].waittime += TIMESLICE;
					}
					if(pf->runtime == 0) {
						q2.pop_front();
						countjob += 1;
						changeflag = 1;
						waittimeall += pf->waittime;
					}
					// 检查有没有新进程进来
                    for(int i = 0; i < N; i++) {
                        if (processes[i].entertime == current && !entered[i]) {
                            q1.push_back(processes[i]);
                            entered[i] = 1;
                            stopflag = 1;
                        }
                    }
					if (stopflag == 1) {
						break;
					}
				}
				if(pf->pid == pfn.pid && !changeflag) {
					q2.pop_front();
					q3.push_back(*pf);
				}

			} else if (!q3.empty()) {
				int stopflag = 0;
				process* pf;
				for(int j = 0; j < q3t && !q3.empty(); j+= TIMESLICE) {
					pf = &q3.front();
					printf("%d    %d    %d     %d     %d\n", pf->pid, pf->level, pf->waittime, current, pf->entertime);
					pf->runtime -= TIMESLICE;
					current = timeadd(current, TIMESLICE);
					for(int i = 0; i < q3.size(); i++) {
						if(q3[i].pid != pf->pid) {
							q3[i].waittime += TIMESLICE;
						}
					}
					if(pf->runtime == 0) {
						q3.pop_front();
						countjob += 1;
						waittimeall += pf->waittime;
					}
					// 检查有没有新进程进来
                    for(int i = 0; i < N; i++) {
                        if (processes[i].entertime == current && !entered[i]) {
                            q1.push_back(processes[i]);
                            entered[i] = 1;
                            stopflag = 1;
                        }
                    }
                    if (stopflag == 1) {
						break;
					}
				}
			} else {
				for(int i = 0; i < N; i++) {
					if(processes[i].entertime >= current) {
						q1.push_back(processes[i]);
						current = processes[i].entertime;
						break;
					}
				}
			}
		}
		printf("waittime average: %d\n", waittimeall/N);
	}
}
