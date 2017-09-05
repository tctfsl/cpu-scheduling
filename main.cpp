#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Process.hpp"
using namespace std;

void ganttChart(vector<int> ganttTimer);
void setProcess(vector<Process> &pList);
void RoundRobin(vector<Process> pList);

int main()
{
  vector<Process> pList;
  
  setProcess(pList);
  RoundRobin(pList);
  
  return 0;
}

void ganttChart(vector<int> ganttTimer)
{
  vector<int> vList;
  vector<int> dList;
  bool hasCheckedGanttTimer = false;
  int checkedVectorIndex = 0;
  int duration = 0;
  int timer = 0;
  
  //LABEL 1 OF 2: SORTING THE VECTOR
  while (!(hasCheckedGanttTimer))
  {
	if(checkedVectorIndex == 0)
	{
	  vList.push_back(ganttTimer.front());
	  duration++;
	}
	else
	{
	  if(checkedVectorIndex == ganttTimer.size())
	    dList.push_back(duration);
	  else
	  {
	    if(ganttTimer[checkedVectorIndex] == ganttTimer[checkedVectorIndex - 1])
	      duration++;
	    else
	    {
  		  dList.push_back(duration);
		  duration = 0;
		  
		  vList.push_back(ganttTimer[checkedVectorIndex]);
	      duration++;
	    }
	  }
	}
	checkedVectorIndex++;
	
	if(checkedVectorIndex > ganttTimer.size())
	  hasCheckedGanttTimer = true;
  }
  
  //LABEL 2 OF 2: SHOWING THE GANTT CHART
  for(int i = 0; i < vList.size(); i++)			//For-Loop 1
    cout << "+---";
  cout << "+" << endl;
  
  for(int j = 0; j < vList.size(); j++)			//For-Loop 1
  {
    if (vList[j] < 10)
	  cout << "| P" << vList[j];
	else
	  cout << "|P" << vList[j];
  }
  cout << "|" << endl;
  
  for(int k = 0; k < dList.size(); k++)			//For-Loop 1
    cout << "+---";
  cout << "+" << endl;
  
  for(int l = 0; l < vList.size(); l++)			//For-Loop 1
  {
	if(l == 0)
      cout << left << setw(4) << timer;
	else
	  cout << left << setw(4) << (timer += dList[l - 1]);
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

void setProcess(vector<Process> &pList)
{
  /*
  bool inRange = false;
  int numberOfProcess = (-1);
  
  for(int i = 0; !inrange; i++)
  {
	if(i != 0)
	  cout << "invalid input, please enter a number in range [3, 21]" << endl;
    
	cout << "enter a number of process for this simulation: ";
	cin >> numberofprocess;
	
	if ((numberofprocess > 2) && (numberofprocess < 21))
	  inrange = true;
  }
  
  for(int j = 0; j < numberOfProcess; j ++)
  {
	Process temp;
	
	cout << "Enter the 
  }
  */
  
  Process p1(1, 0, 21, 1);
  Process p2(2, 1, 19, 2);
  Process p3(3, 2, 20, 1);
  Process p4(4, 3, 20, 1);
  Process p5(5, 4, 20, 1);
  
  pList.push_back(p1);
  pList.push_back(p2);
  pList.push_back(p3);
  pList.push_back(p4);
  pList.push_back(p5);
  
  //DEBUG CODES
  
  cout << "pList Information" << endl
	   << "Size: " << pList.size() << endl << endl;
  
  for(int i = 0; i < pList.size(); i++)
  {
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

/*
Current Problem:
If a process with a higher priority arrives, it goes to the head of the queue.
What if a priority with a higher priority than the last half of the queue but lower priority than first half of the queue, does it go to the middle of the queue or just back of the queue.
*/
void RoundRobin(vector<Process> pList)
{
  bool skipped = false;
  int runTime = 0;
  int totalBurstTime = 0;
  int timeQuantum = 0;
  int timeLeft = 0;
  Process executingProcess(-1, 0, 0, 0);
  vector<int> ganttTimer;
  vector<Process> finishedPList;
  vector<Process> queue;
  
  for(int i = 0; i < pList.size(); i++)
    totalBurstTime += pList[i].getBurstTime();
  
  cout << "Enter a time quantum: ";
  cin >> timeQuantum;
  cout << endl;
  timeLeft = timeQuantum;
  
  while (totalBurstTime > 0)
  {
	if (!(skipped))
	{
	  for(int j = 0; j < pList.size(); j++)
	  {
	    if (pList[j].getArriveTime() == runTime)
	      queue.push_back(pList[j]);
	  }
	}
	
	if (timeLeft > 0)
	{
	  if (executingProcess.getBurstTime() > 0)
	  {
		executingProcess.decrementBurstTime();
		totalBurstTime--;
		
		ganttTimer.push_back(executingProcess.getPID());
		timeLeft--;
		runTime++;
		skipped = false;
	  }
	  else
	  {
		if (executingProcess.getPID() != -1)
		{
		  executingProcess.calculateTurnaroundTime(runTime);
		  executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
		  finishedPList.push_back(executingProcess);
		}
		
		executingProcess = queue[0];
		rotate(queue.begin(), queue.begin() + 1, queue.end());
		queue.pop_back();
		timeLeft = timeQuantum;
		skipped = true;
	  }
	}
	else
	{
	  if (executingProcess.getBurstTime())
	    queue.push_back(executingProcess);
	  
	  executingProcess.calculateTurnaroundTime(runTime);
	  executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
	  finishedPList.push_back(executingProcess);
      
	  executingProcess = queue[0];
	  rotate(queue.begin(), queue.begin() + 1, queue.end());
	  queue.pop_back();
	  timeLeft = timeQuantum;
	  skipped = true;
	}
  }
  cout << "Round Robin, quantum = " << timeQuantum << endl;
  ganttChart(ganttTimer);  
}