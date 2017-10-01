#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Process.hpp"

using namespace std;

void ganttChart(vector<int> ganttTimer);

void setProcess(vector<Process> &pList);

void RoundRobin(vector<Process> pList);

int main() {
  vector<Process> pList;
  
  //Process(int PID, int arriveTime, int burstTime, int priority);
  Process p1(1,  0,  8, 2);
  Process p2(2,  4, 15, 5);
  Process p3(3,  7,  9, 3);
  Process p4(4, 13,  5, 1);
  Process p5(5,  9, 13, 4);
  Process p6(6,  0,  6, 1);
  
  pList.push_back(p1);
  pList.push_back(p2);
  pList.push_back(p3);
  pList.push_back(p4);
  pList.push_back(p5);
  pList.push_back(p6);
  
  cout << "DEBUG: Size of pList = " << pList.size() << endl;
  
  //setProcess(pList);
  RoundRobin(pList);
  
  return 0;
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
  
  //DEBUG CODES
  
  cout << "pList Information" << endl
       << "Size: " << pList.size() << endl << endl;
  
  for (int i = 0; i < pList.size(); i++) {
    cout << "pList[" << i << "] Information " << endl
         << "  - PID: " << pList[i].getPID() << endl
         << "  - AT : " << pList[i].getArriveTime() << endl
         << "  - BT : " << pList[i].getBurstTime() << endl
         << "  - P  : " << pList[i].getPriority() << endl
         << "  - TT : " << pList[i].getTurnaroundTime() << endl
         << "  - WT : " << pList[i].getWaitTime() << endl << endl;
  }
  
  //END OF DEBUG CODES
}

void RoundRobin(vector<Process> pList) {
  bool hasSkipped = false;                //Constraint
  int runTime = 0;                        //Acts as the run time clock.
  int totalBurstTime = 0;                 //Stores the total burst time of all processes.
  int timeQuantum = 0;                    //Stores the time quantum for this algorithm.
  int timeLeft = 0;                       //Acts as expendable time quantum for every run.
  Process executingProcess(-1, 0, 0, 0);  //Acts as the process that gets selected and executed.
  //vector<Process> tempQueue;              //Stores the newly arrived processes that arrived at a particular time unit.
  vector<Process> readyQueue;             //Stores the processes that are ready to be executed.
  vector<int> ganttTimer;                 //Stores the information needed to generate a Gantt chart.
  
  //Gets the total burst time of all processes in the simulation.
  for (int i = 0; i < pList.size(); i++) {
    totalBurstTime += pList[i].getBurstTime();
  }
  cout << "DEBUG: totalBurstTime = " << totalBurstTime << endl;
  
  //Gets and sets the time quantum for this simulation.
  cout << "Enter a time quantum: ";
  cin >> timeQuantum;
  //cout << endl;
  timeLeft = timeQuantum;
  //cout << "DEBUG:timeQuantum = " << timeQuantum << endl;
  //cout << "DEBUG:timeLeft    = " << timeLeft << endl;
  
  while (totalBurstTime > 0) {
    cout << "DEBUG: runTime = " << runTime << endl;
    cout << "DEBUG: totalBurstTime = " << totalBurstTime << endl;
    vector<Process> tempQueue;              //Stores the newly arrived processes that arrived at a particular time unit.
    
    if (!hasSkipped) {
      tempQueue.clear();
      //Checks for newly arrived process at this particular run time.
      for (int i = 0; i < pList.size(); i++) {
        if (pList[i].getArriveTime() == runTime) {
          tempQueue.push_back(pList[i]);
        }
      }
      cout << "DEBUG: Arrived Process" << " = ";
      for(int i = 0; i < tempQueue.size(); i++) {
        cout << "P" << tempQueue[i].getPID() << " ";
      }
      cout << endl;
      
      //If ready queue is empty, add the newly arrived processes to the ready queue by descending priority.
      //Else, check where the newly arrived processes can cut the queue.
      if (readyQueue.empty()) {
        Process tempProcess;
        
        for (int i = tempQueue.size(); i > 0; i--) {
          if (tempQueue.size() > 1) {
            for (int j = 0; j < i; j++) {
              if (tempQueue[i].getPriority() > tempQueue[i + 1].getPriority()) {
                tempProcess = tempQueue[i];
                tempQueue[i] = tempQueue[i + 1];
                tempQueue[i + 1] = tempProcess;
              }
            }
          }
        }
        cout << "DEBUG: Temporary Queue after Buble Sort = ";
        for(int i = 0; i <tempQueue.size(); i++) {
          cout << "P" << tempQueue[i].getPID() << " ";
        }
        cout << endl;
        
        cout << "DEBUG: Size of temporary queue = " << tempQueue.size() << endl;
        
        for (int i = 0; i < tempQueue.size(); i++) {
          readyQueue.push_back(tempQueue[i]);
        }
        //cout << "DEBUG: Size of temporary queue before clear = " << tempQueue.size() << endl;
        //tempQueue.clear();
        //cout << "DEBUG: Size of temporary queue after clear = " << tempQueue.size() << endl;
  
        cout << "DEBUG: Size of ready queue = " << readyQueue.size() << endl;
        cout << "DEBUG: Ready Queue = ";
        for(int i = 0; i < readyQueue.size(); i++) {
          cout << "P" << readyQueue[i].getPID() << " ";
        }
        cout << endl;
      }
      else {
        cout << "DEBUG: hasSkipped > else, ready queue is not empty." << endl;
        cout << "DEBUG: -> Size of ready queue = " << readyQueue.size() << endl;
        
        //Adds the newly arrived process into the ready queue.
        for (int i = 0; i < tempQueue.size(); i++) {
          int checkedPriority = tempQueue[i].getPriority();
          bool isLowerPriority = true;
          int designatedIndex = 0;
          
          //For each newly arrived process, compare its priority with every process in the ready queue.
          //This is to determine how much can the process cut queue.
          for (int j = (readyQueue.size() - 1); j >= 0; j--) {
            isLowerPriority = checkedPriority > readyQueue[j].getPriority();
            cout << "DEBUG: isLowerPriority = " << boolalpha << isLowerPriority << endl;
            
            if (isLowerPriority) {
              designatedIndex = j + 1;
            }
            else {
              if (checkedPriority == readyQueue[j].getPriority()) {
                designatedIndex = j + 1;
                break;
              }
              else {
                designatedIndex = j;
              }
            }
          }
          
          readyQueue.insert(readyQueue.begin() + designatedIndex, tempQueue[i]);
        }
  
        cout << "DEBUG: Ready Queue after priority queueing-ish = ";
        for(int i = 0; i < readyQueue.size(); i++) {
          cout << "P" << readyQueue[i].getPID() << " ";
        }
        cout << endl;
      }
    }
    
    //If readyQueue is empty, records -1, and
    //Else if readyQueue is not empty, records the selected PID.
    if (readyQueue.empty() && !hasSkipped && executingProcess.getBurstTime() == 0) {
      cout << "DEBUG: At " << runTime << ", no process in execution." << endl;
      
      ganttTimer.push_back(-1);
      runTime++;
      hasSkipped = false;
    }
    else {
      //If there is remaining time quantum, and
      //Else if there is no more time quantum.
      if (timeLeft > 0) {
        //If executing process has remaining burst time, and
        //Else if executing process has no more burst time.
        if (executingProcess.getBurstTime() > 0) {
          cout << "DEBUG: IF timeLeft > 0, IF burstTime > 0" << endl;
          cout << "DEBUG: if route is taken." << endl;
          
          //Executes selected process, and
          //Decrements total burst time of simulation.
          executingProcess.decrementBurstTime();
          totalBurstTime--;
          cout << "DEBUG: EXECUTED PROCESS = P" << executingProcess.getPID() << endl;
          
          //Records the gantt chart information.
          //Decrements remaining time quantum left.
          //Increments run time.
          ganttTimer.push_back(executingProcess.getPID());
          timeLeft--;
          runTime++;
          hasSkipped = false;
        }
        else {
          cout << "DEBUG: IF timeLeft > 0, IF burstTime < 0" << endl;
          cout << "DEBUG: else route is taken." << endl;
          
          //If executing process is not empty.
          if (executingProcess.getPID() != -1) {
            //Calculates the turnaround time and wait time.
            executingProcess.calculateTurnaroundTime(runTime);
            executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
          }
          
          //Selects the process in the head of queue.
          //Removes the selected process from the queue.
          executingProcess = readyQueue[0];
          rotate(readyQueue.begin(), readyQueue.begin() + 1, readyQueue.end());
          readyQueue.pop_back();
          
          //Reset the remaining time quantum.
          timeLeft = timeQuantum;
          hasSkipped = true;
        }
      }
      else {
        //If executing process has remaining burst time, and
        //Else if executing process has no more burst time.
        if (executingProcess.getBurstTime() > 0) {
          //If executing process has remaining burst time.
          if (executingProcess.getBurstTime() > 0) {
            readyQueue.push_back(executingProcess);
          }
        }
        else {
          executingProcess.calculateTurnaroundTime(runTime);
          executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
        }
        
        //Selects the process in the head of queue.
        //Removes the selected process from the queue.
        executingProcess = readyQueue[0];
        rotate(readyQueue.begin(), readyQueue.begin() + 1, readyQueue.end());
        readyQueue.pop_back();
        
        //Reset the remaining time quantum.
        timeLeft = timeQuantum;
        hasSkipped = true;
      }
    }
    cout << "DEBUG: Executing Process = P" << executingProcess.getPID() << endl;
    cout << "DEBUG: -> Burst time = " << executingProcess.getBurstTime() << endl;
  
    cout << "DEBUG: Ready Queue = ";
    for(int i = 0; i < readyQueue.size(); i++) {
      cout << "P" << readyQueue[i].getPID() << " ";
    }
    cout << endl;
    
    int nope;
    cout << "End of cycle: ";
    cin >> nope;
    
  }
  
  cout << endl;
  for (int i = 0; i < ganttTimer.size(); i++) {
    cout << ganttTimer[i];
  }
  cout << endl;
  
  cout << "Round Robin, quantum = " << timeQuantum << endl;
  ganttChart(ganttTimer);
}