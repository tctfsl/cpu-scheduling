#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Process.hpp"

using namespace std;

void ganttChart(vector<int> ganttTimer);
void setProcess(vector<Process> &pList);
void RoundRobin(vector<Process> pList, int timeQuantum, double &avgTTRR, double &avgWTRR, vector<int> &ganttTimerRR);
void ThreeLevel(vector<Process> pList, int timeQuantum, double &avgTTTL, double &avgWTTL, vector<int> &ganttTimerTL);
void SJF(vector<Process> pList, double &avgTTSJF, double &avgWTSJF, vector<int> &ganttTimerSJF);

int main() {
  double avgTTRR = 0;
  double avgWTRR = 0;
  double avgTTTL = 0;
  double avgWTTL = 0;
  double avgTTSJF = 0;
  double avgWTSJF = 0;
  int timeQuantum;
  vector<int> ganttTimerRR;
  vector<int> ganttTimerTL;
  vector<int> ganttTimerSJF;
  vector<Process> pList;
  
  cout << "Enter a time quantum: ";
  cin >> timeQuantum;
  
  setProcess(pList);
  RoundRobin(pList, timeQuantum, avgTTRR, avgWTRR, ganttTimerRR);
  ThreeLevel(pList, timeQuantum, avgTTTL, avgWTTL, ganttTimerTL);
  SJF(pList, avgTTSJF, avgWTSJF, ganttTimerSJF);
  
  cout << "Round Robin: " << endl;
  ganttChart(ganttTimerRR);
  
  cout << endl << "Three Level Scheduling: " << endl;
  ganttChart(ganttTimerTL);
  
  cout << endl << "SJF: " << endl;
  ganttChart(ganttTimerSJF);
  
  cout << "Round Robin:" << endl
       << "Average Turnaround Time: " << avgTTRR << endl
       << "Average Wait Time: " << avgWTRR << endl << endl;
  
  cout << "Three Level Scheduling:" << endl
       << "Average Turnaround Time: " << avgTTTL << endl
       << "Average Wait Time: " << avgWTTL << endl;
  
  cout << "Short Job First:" << endl
       << "Average Turnaround Time: " << avgTTSJF << endl
       << "Average Wait Time: " << avgWTSJF << endl;
}

void ganttChart(vector<int> ganttTimer) {
  vector<int> vList;                  //variation list
  vector<int> dList;                  //duration list
  bool hasCheckedGanttTimer = false;  //has thoroughly check the gantt timer
  int checkedVectorIndex = 0;         //checked index of the gantt tiemr
  int duration = 0;
  int timer = 0;
  
  //LABEL 1 OF 2: SORTING THE VECTOR
  while (!(hasCheckedGanttTimer)) {
    //If checking the first element of the vector, and
    //Else if checking other element of the vector.
    if (checkedVectorIndex == 0) {
      //Records the variation number
      //Increment the duration
      vList.push_back(ganttTimer.front());
      duration++;
    }
    else {
      if (checkedVectorIndex == ganttTimer.size()) {
        dList.push_back(duration);
      }
      else {
        if (ganttTimer[checkedVectorIndex] == ganttTimer[checkedVectorIndex - 1]) {
          duration++;
        }
        else {
          dList.push_back(duration);
          duration = 0;
          
          vList.push_back(ganttTimer[checkedVectorIndex]);
          duration++;
        }
      }
    }
    checkedVectorIndex++;
    
    if (checkedVectorIndex > ganttTimer.size()) {
      hasCheckedGanttTimer = true;
    }
  }
  
  //LABEL 2 OF 2: SHOWING THE GANTT CHART
  for (int i = 0; i < vList.size(); i++) {      //For-Loop 1
    cout << "+---";
  }
  cout << "+" << endl;
  
  for (int j = 0; j < vList.size(); j++)      //For-Loop 1
  {
    if (vList[j] < 10) {
      if (vList[j] == -1) {
        cout << "|   ";
      }
      else {
        cout << "| P" << vList[j];
      }
    }
    else {
      cout << "|P" << vList[j];
    }
  }
  cout << "|" << endl;
  
  for (int k = 0; k < dList.size(); k++) {      //For-Loop 1
    cout << "+---";
  }
  cout << "+" << endl;
  
  for (int l = 0; l < vList.size(); l++)      //For-Loop 1
  {
    if (l == 0) {
      cout << left << setw(4) << timer;
    }
    else {
      cout << left << setw(4) << (timer += dList[l - 1]);
    }
  }
  cout << (timer += dList.back()) << endl;
  
  /*
  Result:
  +---+			<= constructed by for-loop 1
  | PX|			<= constructed by for-loop 2, X is an integer
  +---+			<= constructed by for-loop 3
  n   m			<= constructed by for-loop 4, n and m are integers where n < m
  */
}

void setProcess(vector<Process> &pList) {
  bool inRange = false;
  int numberOfProcess = 0;
  
  for (int i = 0; !inRange; i++) {
    if (i != 0) {
      cout << "Invalid input, please enter a number in range [3, 10]" << endl << endl;
    }
    
    cout << "Enter a number of process for this simulation, the acceptable range is [3, 20]" << endl
         << "Number of Process: ";
    cin >> numberOfProcess;
    
    if ((numberOfProcess > 2) && (numberOfProcess < 11)) {
      inRange = true;
    }
  }
  
  for (int j = 0; j < numberOfProcess; j++) {
    int arriveTime, burstTime, priority;
    
    if (j == 0) {
      cout << endl << "Enter the information of each process in this format:" << endl
           << "ArriveTime, BurstTime, Priority" << endl << endl;
    }
    
    cout << "P" << (j + 1) << ": ";
    cin >> arriveTime >> burstTime >> priority;
    
    Process temp((j + 1), arriveTime, burstTime, priority);
    pList.push_back(temp);
  }
  
  cout << endl;
}

void RoundRobin(vector<Process> pList, int timeQuantum, double &avgTTRR, double &avgWTRR, vector<int> &ganttTimerRR) {
  bool hasSkipped = false;
  int runTime = 0;
  int timeLeft = 0;
  int totalBurstTime = 0;
  Process executingProcess(-1, 0, 0, 0);
  vector<int> ganttTimer;
  vector<Process> queue;
  
  for (int i = 0; i < pList.size(); i++) {
    totalBurstTime += pList[i].getBurstTime();
  }
  
  timeLeft = timeQuantum;
  
  while (totalBurstTime > 0) {
    vector<Process> tempQueue;
    
    //If have completed a cycle.
    if (!hasSkipped) {
      for (int i = 0; i < pList.size(); i++) {
        if (pList[i].getArriveTime() == runTime) {
          Process tempProcess;
          tempProcess = pList[i];
          tempQueue.push_back(tempProcess);
        }
      }
      
      if (tempQueue.size() > 1) {
        for (int i = 0; i < (tempQueue.size() - 1); i++) {
          for (int j = 0; j < ((tempQueue.size() - i) - 1); j++) {
            if (tempQueue[j].getPriority() > tempQueue[j + 1].getPriority()) {
              Process swappableProcess = tempQueue[j];
              tempQueue[j] = tempQueue[j + 1];
              tempQueue[j + 1] = swappableProcess;
            }
          }
        }
      }
      
      //If queue is empty, or
      //there is at least a process ready to be executed.
      if (queue.empty()) {
        for (int i = 0; i < tempQueue.size(); i++) {
          queue.push_back(tempQueue[i]);
        }
      }
      else {
        for (int i = 0; i < tempQueue.size(); i++) {
          int addingMode = -1;
          int checkedPriority = tempQueue[i].getPriority();
          int designatedIndex = (queue.size() - 1);
          
          for (int j = (queue.size() - 1); j > -1; j--) {
            bool isLowerPriority = (checkedPriority >= queue[j].getPriority());
            
            if (isLowerPriority) {
              addingMode = 1;
              break;
            }
            else {
              addingMode = 0;
              designatedIndex = j;
            }
          }
          
          if ((addingMode == 1) && (designatedIndex == (queue.size() - 1))) {
            queue.push_back(tempQueue[i]);
          }
          else {
            queue.insert(queue.begin() + designatedIndex, tempQueue[i]);
          }
        }
      }
    }
    
    //If there is no process to be executed, or
    //there is process to be executed.
    if ((queue.empty()) && (!hasSkipped) && (executingProcess.getBurstTime() == 0)) {
      ganttTimer.push_back(-1);
      runTime++;
      hasSkipped = false;
    }
    else {
      //If remaining time quantum is more than 0, or
      //there is no more remaining time quantum.
      if (timeLeft > 0) {
        //If there is remaining burst time, or
        //there is no more remaining burst time.
        if (executingProcess.getBurstTime() > 0) {
          executingProcess.decrementBurstTime();
          ganttTimer.push_back(executingProcess.getPID());
          
          timeLeft--;
          totalBurstTime--;
          runTime++;
          hasSkipped = false;
        }
        else {
          if (executingProcess.getPID() != -1) {
            executingProcess.calculateTurnaroundTime(runTime);
            executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
            avgTTRR += executingProcess.getTurnaroundTime();
            avgWTRR += executingProcess.getWaitTime();
          }
          
          executingProcess = queue.at(0);
          queue.erase(queue.begin());
          
          timeLeft = timeQuantum;
          hasSkipped = true;
        }
      }
      else {
        //If there is remaining burst time, or
        //there is no more remaining burst time.
        if (executingProcess.getBurstTime() > 0) {
          queue.push_back(executingProcess);
        }
        else {
          executingProcess.calculateTurnaroundTime(runTime);
          executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
          avgTTRR += executingProcess.getTurnaroundTime();
          avgWTRR += executingProcess.getWaitTime();
        }
        
        executingProcess = queue.at(0);
        queue.erase(queue.begin());
        
        timeLeft = timeQuantum;
        hasSkipped = true;
      }
    }
  }
  
  executingProcess.calculateTurnaroundTime(runTime);
  executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
  avgTTRR += executingProcess.getTurnaroundTime();
  avgWTRR += executingProcess.getWaitTime();
  
  ganttTimerRR = ganttTimer;
  
  avgTTRR /= pList.size();
  avgWTRR /= pList.size();
}

void ThreeLevel(vector<Process> pList, int timeQuantum, double &avgTTTL, double &avgWTTL, vector<int> &ganttTimerTL) {
  vector<Process> queue1;
  vector<Process> queue2;
  vector<Process> queue3;
  vector<int> int_process;
  int quantumTime;
  int sum_burstime = pList[0].getArriveTime();
  
  for (int i = pList.size() - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (pList[j].getArriveTime() > pList[j + 1].getArriveTime()) {
        Process temp_p = pList[j + 1];
        pList[j + 1] = pList[j];
        pList[j] = temp_p;
      }
    }
  }
  
  for (int x = 0; x < pList.size(); x++) {
    sum_burstime = sum_burstime + pList[x].getBurstTime();
  }
  
  for (int i = pList[0].getArriveTime(); i < sum_burstime; i++) {
    for (int y = 0; y < pList.size(); y++) {
      if ((pList[y].getArriveTime() == i) && ((pList[y].getPriority() == 1) || (pList[y].getPriority() == 2))) {
        queue1.push_back(pList[y]);
        for (int i = queue1.size(); i > 0; i--) {
          if (queue1.size() > 1) {
            for (int j = 0; j < i; j++) {
              if (queue1[j].getPriority() > queue1[j + 1].getPriority()) {
                Process temp_p = queue1[j + 1];
                queue1[j + 1] = queue1[j];
                queue1[j] = temp_p;
              }
              
              if (queue1[j].getPriority() == queue1[j + 1].getPriority()) {
                if (queue1[j].getArriveTime() > queue1[j + 1].getArriveTime()) {
                  Process temp_p = queue1[j + 1];
                  queue1[j + 1] = queue1[j];
                  queue1[j] = temp_p;
                }
              }
            }
          }
        }
        quantumTime = queue1[0].getBurstTime();
      }
      
      if ((pList[y].getArriveTime() == i) && ((pList[y].getPriority() == 3) || (pList[y].getPriority() == 4))) {
        
        cout << "Time: " << i << endl;
        cout << "P" << pList[y].getPID() << " Push to Queue Two \n";
        queue2.push_back(pList[y]);
        cout << "Queue 2 Size is: " << queue2.size() << endl;
        for (int i = queue2.size(); i > 0; i--) {
          
          if (queue2.size() > 1) {
            for (int j = 0; j < i; j++) {
              if (queue2[j].getPriority() > queue2[j + 1].getPriority()) {
                Process temp_p = queue2[j + 1];
                queue2[j + 1] = queue2[j];
                queue2[j] = temp_p;
              }
              
              if (queue2[j].getPriority() == queue2[j + 1].getPriority()) {
                if (queue2[j].getArriveTime() > queue2[j + 1].getArriveTime()) {
                  Process temp_p = queue2[j + 1];
                  queue2[j + 1] = queue2[j];
                  queue2[j] = temp_p;
                }
              }
            }
          }
        }
        cout << "P" << pList[y].getPID() << "\n";
      }
      
      if ((pList[y].getArriveTime() == i) && ((pList[y].getPriority() == 5) || (pList[y].getPriority() == 6))) {
        queue3.push_back(pList[y]);
        
        for (int i = queue3.size(); i > 0; i--) {
          
          if (queue3.size() > 1) {
            for (int j = 0; j < i; j++) {
              if (queue3[j].getPriority() > queue3[j + 1].getPriority()) {
                Process temp_p = queue3[j + 1];
                queue3[j + 1] = queue3[j];
                queue3[j] = temp_p;
              }
              
              if (queue3[j].getPriority() == queue3[j + 1].getPriority()) {
                if (queue3[j].getArriveTime() > queue3[j + 1].getArriveTime()) {
                  Process temp_p = queue3[j + 1];
                  queue3[j + 1] = queue3[j];
                  queue3[j] = temp_p;
                }
              }
            }
          }
        }
        
      }
    }
    
    if (queue1.size() == 0 && queue2.size() == 0 && queue3.size() == 0) {
      int_process.push_back(-1);
    }
    
    if (queue1.size() != 0) {
      int_process.push_back((queue1.front()).getPID());
      queue1[0].decrementBurstTime();
      if (queue1[0].getBurstTime() == (quantumTime - timeQuantum)) {
        Process temp_queue = queue1[0];
        queue1.erase(queue1.begin());
        queue1.push_back(temp_queue);
        quantumTime = queue1[0].getBurstTime();
        
      }
      if (queue1[0].getBurstTime() == 0) {
        queue1.erase(queue1.begin());
      }
    }
    
    if (queue1.size() == 0 && queue2.size() != 0) {
      int_process.push_back(queue2[0].getPID());
      
      queue2[0].decrementBurstTime();
      if (queue2[0].getBurstTime() == 0) {
        queue2.erase(queue2.begin());
      }
    }
    
    if (queue1.size() == 0 && queue2.size() == 0 && queue3.size() != 0) {
      int_process.push_back(queue3[0].getPID());
      
      queue3[0].decrementBurstTime();
      if (queue3[0].getBurstTime() == 0) {
        queue3.erase(queue3.begin());
      }
    }
  }
  
  int_process.pop_back();
  ganttTimerTL = int_process;
}

void SJF(vector<Process> pList, double &avgTTSJF, double &avgWTSJF, vector<int> &ganttTimerSJF) {
  for (int i = pList.size() - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (pList[j].getArriveTime() > pList[j + 1].getArriveTime()) {
        Process temp_p = pList[j + 1];
        pList[j + 1] = pList[j];
        pList[j] = temp_p;
      }
    }
  }
  int sum_burstime = pList[0].getArriveTime();
  vector<int> int_process;
  vector<Process> p_schedule;
  int i_time = pList[0].getArriveTime();
  int pro_cess = (pList[0].getArriveTime() - 0);
  for (int i = 0; i < pro_cess; i++) {
    int_process.push_back(-1);
  }
  
  
  for (int x = 0; x < pList.size(); x++) {
    sum_burstime = sum_burstime + pList[x].getBurstTime();
  }
  vector<Process> tem_p;
  
  for (int y = pList[0].getArriveTime(); y < sum_burstime; y++) {
    for (int z = 0; z < pList.size(); z++) {
      if (pList[z].getArriveTime() == y) {
        tem_p.push_back(pList[z]);
        for (int i = tem_p.size() - 1; i > 0; i--) {
          for (int j = 0; j < i; j++) {
            if (tem_p[j].getBurstTime() > tem_p[j + 1].getBurstTime()) {
              Process temp_p = tem_p[j + 1];
              tem_p[j + 1] = tem_p[j];
              tem_p[j] = temp_p;
            }
            
            if (tem_p[j].getBurstTime() == tem_p[j + 1].getBurstTime()) {
              if (tem_p[j].getPriority() > tem_p[j + 1].getPriority()) {
                Process temp_p = tem_p[j + 1];
                tem_p[j + 1] = tem_p[j];
                tem_p[j] = temp_p;
              }
            }
          }
        }
      }
    }
    
    int_process.push_back(tem_p[0].getPID());
    
    
    tem_p[0].decrementBurstTime();
    
    if (tem_p[0].getBurstTime() == 0) {
      for (int counter = 0; counter <= pList.size(); counter++) {
        if (tem_p[0].getPID() == pList[counter].getPID()) {
          pList[counter].calculateTurnaroundTime((y + 1));
          pList[counter].calculateWaitTime(pList[counter].getBurstTime());
          
        }
      }
      tem_p.erase(tem_p.begin());
    }
  }
  
  ganttTimerSJF = int_process;
  
}