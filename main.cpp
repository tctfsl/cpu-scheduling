#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Process.hpp"
using namespace std;

void setProcess(vector<Process> &pList);
void RR(vector<Process> pList);
void SJF(vector<Process> pList);
void ganttChart(vector<int> ganttTimer);

vector<Process> processList(vector<Process> pList)
{
    vector<Process> p_List = pList;
    return p_List;
}

int main()
{
    vector<Process> pList;

    setProcess(pList);
    SJF(pList);
      setProcess(pList);

  return 0;
}

void setProcess(vector<Process> &pList)
{
  Process p1(1,10,10,1);
  Process p2(2,0,12,2);
  Process p3(3,3,8,3);
  Process p4(4,5,4,4);
  Process p5(5,12,6,5);
  //Process p6(6,4,2,6);
  //Process p7(7,3,5,7);


  pList.push_back(p1);
  pList.push_back(p2);
  pList.push_back(p3);
  pList.push_back(p4);
  pList.push_back(p5);
  //pList.push_back(p6);
  //pList.push_back(p7);

}

void ganttChart(vector<int> ganttTimer)
{
  vector<int> vList;
  vector<int> dList;
  bool hasCheckedGanttTimer = false;
  int checkedVectorIndex = 0;
  int duration = 0;
  int timer = 0;

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
	if(l == 0)
      cout << left << setw(4) << timer;
	else
	  cout << left << setw(4) << (timer += dList[l - 1]);
  }
  cout << (timer += dList.back()) << endl;

}

void SJF(vector<Process> pList)
{
    for(int i = pList.size()-1; i>0; i--)
    {
        for(int j =0; j<i; j++)
        {
            if(pList[j].getArriveTime()>pList[j+1].getArriveTime())
            {
                Process temp_p = pList[j+1];
                pList[j+1] = pList[j];
                pList[j] = temp_p;
            }
        }
    }
    int sum_burstime=pList[0].getArriveTime();
    vector<int>int_process;
    vector<Process> p_schedule;
    int i_time = pList[0].getArriveTime();
    int pro_cess = (pList[0].getArriveTime()-0);
    for(int i = 0; i < pro_cess; i++)
    {
        int_process.push_back(-1);
    }


    for(int x =0; x< pList.size(); x++)
    {
        sum_burstime = sum_burstime + pList[x].getBurstTime();
    }
    vector<Process> tem_p;

    for(int y = pList[0].getArriveTime(); y <sum_burstime; y++)
    {

           for(int z = 0; z <pList.size(); z++)
            {
                if(pList[z].getArriveTime()==y)
                {
                    tem_p.push_back(pList[z]);
                    for(int i = tem_p.size()-1; i>0; i--)
                    {
                        for(int j =0; j<i; j++)
                        {
                            if(tem_p[j].getBurstTime()>tem_p[j+1].getBurstTime())
                            {
                                Process temp_p = tem_p[j+1];
                                tem_p[j+1] = tem_p[j];
                                tem_p[j] = temp_p;
                            }

                            if(tem_p[j].getBurstTime()==tem_p[j+1].getBurstTime())
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

            int_process.push_back(tem_p[0].getPID());


            tem_p[0].decrementBurstTime();

            if(tem_p[0].getBurstTime()==0)
            {
                for(int counter = 0; counter <= pList.size(); counter++)
                {
                    if(tem_p[0].getPID() == pList[counter].getPID())
                    {
                        pList[counter].calculateTurnaroundTime((y+1));
                        pList[counter].calculateWaitTime(pList[counter].getBurstTime());

                    }
                }
                tem_p.erase(tem_p.begin());
            }
    }

    cout<<endl;
    for(int i = 0; i < int_process.size(); i++)
    {
        cout<<int_process[i]<<" ";
    }
    cout<<endl;
    ganttChart(int_process);
    cout<<endl;

}


void multiSchedule (vector<Process> pList)
{
    vector<Process> queue1;
    vector<Process> queue2;
    vector<Process> queue3;
    vector<int> int_process;
    int sum_burstime=pList[0].getArriveTime();


    for(int i = pList.size()-1; i>0; i--)
    {
        for(int j =0; j<i; j++)
        {
            if(pList[j].getArriveTime()>pList[j+1].getArriveTime())
            {
                Process temp_p = pList[j+1];
                pList[j+1] = pList[j];
                pList[j] = temp_p;
            }
        }
    }

    for(int x =0; x< pList.size(); x++)
    {
        sum_burstime = sum_burstime + pList[x].getBurstTime();
    }

    for(int i = pList[0].getArriveTime(); i<sum_burstime ; i++)
    {
        for(int y = 0; y<pList.size(); i++)
        {
            if((pList[y].getArriveTime()==i)&&((pList[y].getPriority()==1)||(pList[y].getPriority()==2)))
            {
                queue1.push_back(pList[y]);
                   for(int i = tem_p.size()-1; i>0; i--)
                    {
                        for(int j =0; j<i; j++)
                        {
                            if(tem_p[j].getBurstTime()>tem_p[j+1].getBurstTime())
                            {
                                Process temp_p = tem_p[j+1];
                                tem_p[j+1] = tem_p[j];
                                tem_p[j] = temp_p;
                            }

                            if(tem_p[j].getBurstTime()==tem_p[j+1].getBurstTime())
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

        //
            if(queue1.size()!=0)
            {
                int_process.push_back(queue1[0].getPID());
                queue1[0].decrementBurstTime();
                if(tem_p[0].getBurstTime()==0)
                {
                tem_p.erase(tem_p.begin());
                }
            }



}

