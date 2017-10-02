#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Process.hpp"
using namespace std;

void ganttChart(vector<int> ganttTimer);
void setProcess(vector<Process> &pList);
void RoundRobin(vector<Process> pList);
void FCFS_PREMP(vector<Process> pList);

int main() {
  vector<Process> pList;

  setProcess(pList);
  RoundRobin(pList);
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

void RoundRobin(vector<Process> pList) {
  bool hasSkipped = false;
  int runTime = 0;
  int timeLeft = 0;
  int timeQuantum = 0;
  int totalBurstTime = 0;
  Process executingProcess(-1, 0, 0, 0);
  vector<int> ganttTimer;
  vector<Process> queue;

  for(int i = 0; i < pList.size(); i++) {
    totalBurstTime += pList[i].getBurstTime();
  }

  cout << "Enter a time quantum: ";
  cin >> timeQuantum;
  timeLeft = timeQuantum;

  while (totalBurstTime > 0) {
    vector<Process> tempQueue;

    //If have completed a cycle.
    if (!hasSkipped) {
      for(int i = 0; i < pList.size(); i++) {
        if (pList[i].getArriveTime() == runTime) {
          Process tempProcess;
          tempProcess = pList[i];
          tempQueue.push_back(tempProcess);
        }
      }

      if (tempQueue.size() > 1) {
        for(int i = 0; i < (tempQueue.size() - 1); i++) {
          for(int j = 0; j < ((tempQueue.size() - i) - 1); j++) {
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
        for(int i = 0; i < tempQueue.size(); i++) {
          queue.push_back(tempQueue[i]);
        }
      }
      else {
        for(int i = 0; i < tempQueue.size(); i++) {
          int addingMode = -1;
          int checkedPriority = tempQueue[i].getPriority();
          int designatedIndex = (queue.size() - 1);

          for(int j = (queue.size() - 1); j > -1; j--) {
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
         ;
        }

        executingProcess = queue.at(0);
        queue.erase(queue.begin());

        timeLeft = timeQuantum;
        hasSkipped = true;
      }
    }
  }

  ganttChart(ganttTimer);
}

void FCFS_PREMP(vector<Process> pList)
{
    //Vector to keep track of which process are running at each increment.
    vector<int>int_process;
    //Store all processes.
    vector<Process> tem_p;
    int basePriority = 1;
    int sum_burstime = 0;
    int pro_cess = pList[0].getArriveTime();

    //Bubble Sort based on priority based on ascending order.
    for(int i = pList.size()-1; i>0; i--)
    {
        for(int j =0; j<i; j++)
        {
            if(pList[j].getPriority()>pList[j+1].getPriority())
            {
                Process temp_p = pList[j+1];
                pList[j+1] = pList[j];
                pList[j] = temp_p;
            }
        }
    }

    for(int i = 0; i < pro_cess; i++)
    {
        int_process.push_back(-1);
    }
    //Calculate total burst time.
    for(int x =0; x< pList.size(); x++)
    {
        sum_burstime = sum_burstime + pList[x].getBurstTime();
    }


    for(int tick = 0; tick < sum_burstime; tick++)
    {
        for(int i = 0; i < pList.size(); i++)
        {
            if (pList[i].getArriveTime() == tick)
            {
                tem_p.push_back(pList[i]);
                //If 1'st tick, set base priority, and resort vector with bubble sort.
                if (i == 1)
                {
                    basePriority = pList[0].getPriority();
                    for(int j = 0; j < tem_p.size()-1 ; j++)
                    {
                        if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                        {
                            Process temp_p = tem_p[j];
                            tem_p[j] = tem_p[j+1];
                            tem_p[j+1] = temp_p;
                        }

                        if(tem_p[j].getPriority() == tem_p[j+1].getPriority())
                        {
                            if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                            {
                                Process temp_p = tem_p[j+1];
                                tem_p[j+1] = tem_p[j];
                                tem_p[j] = temp_p;
                            }
                        }
                    }
                }
                //Bubble sort vector based on priority in ascending order.
                for(int j = 0; j < tem_p.size()-1 ; j++)
                {
                    if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                    {
                        Process temp_p = tem_p[j];
                        tem_p[j] = tem_p[j+1];
                        tem_p[j+1] = temp_p;
                    }

                    if(tem_p[j].getPriority() == tem_p[j+1].getPriority())
                        {
                            if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                            {
                                Process temp_p = tem_p[j+1];
                                tem_p[j+1] = tem_p[j];
                                tem_p[j] = temp_p;
                            }
                        }
                }

                //If current process has a higher priority than base priority, and then bubble sort vector.
                if (pList[i].getPriority() <= basePriority)
                {
                    basePriority = pList[i].getPriority();

                    for(int j = 0; j < tem_p.size()-1 ; j++)
                    {
                        if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                        {
                            Process temp_p = tem_p[j];
                            tem_p[j] = tem_p[j+1];
                            tem_p[j+1] = temp_p;
                        }

                        if(tem_p[j].getPriority() == tem_p[j+1].getPriority())
                        {
                            if(tem_p[j].getPriority() > tem_p[j+1].getPriority())
                            {
                                Process temp_p = tem_p[j+1];
                                tem_p[j+1] = tem_p[j];
                                tem_p[j] = temp_p;
                            }
                        }
                    }
                }
            }
        }

        //Push current working process into vector
        int_process.push_back(tem_p[0].getPID());
        tem_p[0].decrementBurstTime();


        //If a process is finished. Calculate its turnaround time, wait time, and remove it from list of processes.
        if(tem_p[0].getBurstTime() == 0)
        {
            for(int counter = 0; counter <= pList.size(); counter++)
            {
                if(tem_p[0].getPID() == pList[counter].getPID())
                {
                    pList[counter].calculateTurnaroundTime((tick+1));
                    pList[counter].calculateWaitTime(pList[counter].getBurstTime());
                }
            }
            tem_p.erase(tem_p.begin());
        }

    }
    ganttChart(int_process);
}
