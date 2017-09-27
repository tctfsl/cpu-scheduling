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
void multiSchedule (vector<Process> pList);

vector<Process> processList(vector<Process> pList)
{
    vector<Process> p_List = pList;
    return p_List;
}

int main()
{
    cout << "Start \n";
    vector<Process> pList;

    setProcess(pList);
    multiSchedule(pList);

    cout << "End \n";

  return 0;
}

void setProcess(vector<Process> &pList)
{
    Process p1(1,0,2,2);
    Process p2(2,4,4,4);
    Process p3(3,6,6,4);
    Process p4(4,5,8,1);
    Process p5(5,4,9,5);
    Process p6(6,6,10,6);
//    Process p5(5,12,6,5);
  //Process p6(6,4,2,6);
  //Process p7(7,3,5,7);


    pList.push_back(p1);
    pList.push_back(p2);
    pList.push_back(p3);
    pList.push_back(p4);
 pList.push_back(p5);
  pList.push_back(p6);
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


void multiSchedule(vector<Process> pList)
{
    cout << "Start Multi Schedule \n";
    vector<Process> queue1;
    vector<Process> queue2;
    vector<Process> queue3;
    vector<int> int_process;
    int sum_burstime = pList[0].getArriveTime();


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
        for(int y = 0; y<pList.size(); y++)
        {
            if( (pList[y].getArriveTime() == i) && ((pList[y].getPriority() == 1) || (pList[y].getPriority() == 2) ))
            {
                cout << "Push to Queue One \n";
                queue1.push_back(pList[y]);
                cout << "Queue 1 Size is: " << queue1.size() << endl;
                for(int i = queue1.size(); i>0; i--)
                {
                    if (queue1.size() > 1){
                        for(int j = 0; j<i; j++)
                        {
                            cout << "Bubble Sort \n";
                            if(queue1[j].getBurstTime()>queue1[j+1].getBurstTime())
                            {
                                Process temp_p = queue1[j+1];
                                queue1[j+1] = queue1[j];
                                queue1[j] = temp_p;
                            }

                            if(queue1[j].getBurstTime()==queue1[j+1].getBurstTime())
                            {
                                if(queue1[j].getPriority() > queue1[j+1].getPriority())
                                {
                                    Process temp_p = queue1[j+1];
                                    queue1[j+1] = queue1[j];
                                    queue1[j] = temp_p;
                                }
                            }
                        }
                    }
                }
            }

            if((pList[y].getArriveTime() == i)&&((pList[y].getPriority() == 3)||(pList[y].getPriority() == 4)))
            {
                cout << "Push to Queue Two \n";
                queue2.push_back(pList[y]);
                cout << "Queue 2 Size is: " << queue2.size() << endl;
                for (int i = queue2.size(); i > 0; i--)
                {
                    cout << "--------------------- START OF TICK ---------------------" << endl;
                    if (queue2.size() > 1)
                    {
                        for(int j = 0; j<i; j++)
                        {
                            if(queue2[j].getPriority()>queue2[j+1].getPriority())
                            {
                                Process temp_p = queue2[j+1];
                                queue2[j+1] = queue2[j];
                                queue2[j] = temp_p;
                            }

                            if(queue2[j].getPriority()==queue2[j+1].getPriority())
                            {
                                if(queue2[j].getArriveTime() > queue2[j+1].getArriveTime())
                                {
                                    Process temp_p = queue2[j+1];
                                    queue2[j+1] = queue2[j];
                                    queue2[j] = temp_p;
                                }
                            }
                        }
                    }
                    cout << "Debug 3\n";
                }
            }

            if((pList[y].getArriveTime() == i)&&((pList[y].getPriority() == 5)||(pList[y].getPriority() == 6)))
            {
                cout << "Push to Queue Three \n";
                queue3.push_back(pList[y]);
                cout << "Queue 3 Size is: " << queue3.size() << endl;
                for (int i = queue3.size(); i > 0; i--)
                {
                    cout << "--------------------- START OF TICK ---------------------" << endl;
                    if (queue3.size() > 1)
                    {
                        for(int j = 0; j<i; j++)
                        {
                            if(queue3[j].getPriority()>queue3[j+1].getPriority())
                            {
                                Process temp_p = queue3[j+1];
                                queue3[j+1] = queue3[j];
                                queue3[j] = temp_p;
                            }

                            if(queue3[j].getPriority()==queue3[j+1].getPriority())
                            {
                                if(queue3[j].getArriveTime() > queue3[j+1].getArriveTime())
                                {
                                    Process temp_p = queue3[j+1];
                                    queue3[j+1] = queue3[j];
                                    queue3[j] = temp_p;
                                }
                            }
                        }
                    }
                }
            }
        }

        if(queue1.size()==0 && queue2.size()==0 && queue3.size()==0)
        {
            int_process.push_back(-1);
        }

        if(queue1.size()!=0)
        {
            int_process.push_back(queue1[0].getPID());
            cout<<"\nint_process "<<queue1[0].getPID();
            queue1[0].decrementBurstTime();
            if(queue1[0].getBurstTime()==0)
            {
            queue1.erase(queue1.begin());
            }
        }

        if(queue1.size()==0 && queue2.size()!=0)
        {
            int_process.push_back(queue2[0].getPID());
                   cout<<"\nint_process "<<queue2[0].getPID();
            queue2[0].decrementBurstTime();
            if(queue2[0].getBurstTime()==0)
            {
            queue2.erase(queue2.begin());
            }
        }

        if(queue1.size()==0 && queue2.size()==0 && queue3.size()!=0)
        {
            int_process.push_back(queue3[0].getPID());
                   cout<<"\nint_process "<<queue3[0].getPID();
            queue3[0].decrementBurstTime();
            if(queue3[0].getBurstTime()==0)
            {
            queue3.erase(queue3.begin());
            }
        }


    }

    ganttChart(int_process);
}
