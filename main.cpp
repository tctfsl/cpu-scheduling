#include <algorithm>
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
  vector<int> vList; //= {1, 2, 3, 1, 4, 5, 3, 1, 5, 1, 5, 1};
  vector<int> dList; //= {2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2};
  
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
	  {
		dList.push_back(duration);
	  }
	  else
	  {
	    if(ganttTimer[checkedVectorIndex] == ganttTimer[checkedVectorIndex - 1])
	    {
		  duration++;
	    }
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
  
  for(int i = 0; i < vList.size(); i++)
    cout << "+---";
  cout << "+" << endl;
  
  for(int j = 0; j < vList.size(); j++)
  {
    if (vList[j] < 10)
	  cout << "| P" << vList[j];
	else
	  cout << "|P" << vList[j];
  }
  cout << "|" << endl;
  
  for(int k = 0; k < dList.size(); k++)
    cout << "+---";
  cout << "+" << endl;
  
  for(int l = 0; l < vList.size(); l++)
  {
	if (l == 0)
	  cout << timer << "   ";
    else
	{
	  if (timer < 9)
	    cout << (timer += dList[l - 1]) << "   ";
	  else
		cout << (timer += dList[l - 1]) << "  ";
	}
  }
  cout << (timer += dList.back()) << endl;
  
  cout << endl << "HELLO WORLD!" << endl << endl;
}

void setProcess(vector<Process> &pList)
{
  Process p1(1, 0, 10, 1);
  Process p2(2, 1, 2, 2);
  Process p3(3, 2, 3, 1);
  Process p4(4, 3, 1, 1);
  Process p5(5, 4, 5, 1);
  
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

void RoundRobin(vector<Process> pList)
{
  bool skipped = false;
  int totalBurstTime = 0;
  int timeQuantum = 0;
  int timeLeft = 0;
  Process executingProcess(-1, 0, 0, 0);
  vector<int> ganttTimer;
  vector<Process> finishedPList;
  vector<Process> queue;
  
  //DEBUG CODES
  
  cout << "Initial Variables' initial Information" << endl
	   << "totalBurstTime  : " << totalBurstTime << endl
	   << "timeQuantum     : " << timeQuantum << endl
	   << "executingProcess: " << endl
	   << "  - PID: " << executingProcess.getPID() << endl
	   << "  - AT : " << executingProcess.getArriveTime() << endl
	   << "  - BT : " << executingProcess.getBurstTime() << endl
	   << "  - P  : " << executingProcess.getPriority() << endl
	   << "  - TT : " << executingProcess.getTurnaroundTime() << endl
	   << "  - WT : " << executingProcess.getWaitTime() << endl
	   << "ganttTimer size : " << ganttTimer.size() << endl
	   << "queue size      : " << queue.size() << endl << endl;
	   
  //END OF DEBUG CODES
  
  for(int i = 0; i < pList.size(); i++)
  {
	totalBurstTime += pList[i].getBurstTime();
	
	//DEBUG CODE
	
	cout << "Getting Total Burst Time Information" << endl
	     << "totalBurstTime: " << totalBurstTime << endl << endl;
	
	//END OF DEBUG CODE
  }
  
  cout << "Enter a time quantum: ";
  cin >> timeQuantum;
  timeLeft = timeQuantum;
  
  //DEBUG CODES
  
  cout << endl
       << "Getting Time Quantum Information" << endl
       << "timeQuantum: " << timeQuantum << endl
	   << "timeLeft   : " << timeLeft << endl << endl;
  
  //END OF DEBUG CODES
  
  //Variables on trial
  int runTime = 0;

  while (totalBurstTime > 0)
  {
	//DEBUG CODE
	cout << "runTime: " << runTime << endl
		 << "PreTBT : " << totalBurstTime << endl << endl;
	
	
	
	if (!(skipped))
	{
	  
	  for(int j = 0; j < pList.size(); j++)
	  {
	    if (pList[j].getArriveTime() == runTime)
	    {
		  //DEBUG CODE
		  cout << "p" << j << " has arrived, goes into the queue." << endl;
		  
		  queue.push_back(pList[j]);
	    }
	  }
	  
	}
	
	cout << "==================================================" << endl
		 << "Before | queue: ";
	
	for(int l = 0; l < queue.size(); l++)
	{
	  cout << "p" << queue[l].getPID() - 1 << " ";
	}
	cout << endl;
	
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
		
		cout << "Decremented the burst time of executing process" << endl
			 << "Decremented the total burst time" << endl
			 << "Added p" << executingProcess.getPID() << " to gantt chart" << endl
			 << "Decremented time quantum left" << endl
			 << "Incremented run time/End of a cycle" << endl 
			 << "IF > IF" << endl << endl;
	  }
	  else
	  {
		if (executingProcess.getPID() != -1)
		{
		  executingProcess.calculateTurnaroundTime(runTime);
		  executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
		  finishedPList.push_back(executingProcess);
		  
		  cout << "Calculated the turnaround time for the executing process" << endl
			   << "Calculated the waiting time for the executing process" << endl
			   << "Added the executing process into the new process list" << endl;
		}
		
		executingProcess = queue[0];
		rotate(queue.begin(), queue.begin() + 1, queue.end());
		queue.pop_back();
		timeLeft = timeQuantum;
		skipped = true;
		
		cout << "Selected a new process for execution" << endl
			 << "p" << executingProcess.getPID() - 1 << " was choosen" << endl
			 << "Removed selected process from the queue" << endl
			 << "Reset the time quantum" << endl 
			 << "IF > ELSE" << endl << endl;
	  }
	}
	else
	{
	  if (executingProcess.getBurstTime())
	  {
		queue.push_back(executingProcess);
		
		cout << "Added back the executing process to the queue" << endl;
	  }
	  
	  executingProcess.calculateTurnaroundTime(runTime);
	  executingProcess.calculateWaitTime(pList[executingProcess.getPID() - 1].getBurstTime());
	  finishedPList.push_back(executingProcess);
      	  
	  executingProcess = queue[0];
	  rotate(queue.begin(), queue.begin() + 1, queue.end());
	  queue.pop_back();
	  timeLeft = timeQuantum;
	  skipped = true;
	  
	  cout << "Calculated the turnaround time for the executing process" << endl
		   << "Calculated the waiting time for the executing process" << endl
		   << "Added the executing process into the new process list" << endl
		   << "Selected a new process for execution" << endl
		   << "Removed selected process from the queue" << endl
		   << "Reset the time quantum" << endl 
		   << "ELSE" << endl << endl;
	}
	
	cout << "After | queue: ";
	
	for(int l = 0; l < queue.size(); l++)
	{
	  cout << "p" << queue[l].getPID() - 1 << " ";
	}
	cout << endl;
  }
	
  //DEBUG CODE
  cout << "PostTBT: " << totalBurstTime << endl << endl;
  
  cout << "Gantt Chart, size: " << ganttTimer.size() << endl;
  for(int k = 0; k < ganttTimer.size(); k ++)
    cout << " " << ganttTimer[k];
  cout << endl << endl;
  
  //END OF DEBUG CODES

  ganttChart(ganttTimer);  
}