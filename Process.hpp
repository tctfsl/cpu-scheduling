//
// Created by DELL on 28-Sep-17.
//

#ifndef V9_PROCESS_HPP
#define V9_PROCESS_HPP

class Process
{
  private:
  int PID;
  int arriveTime;
  int burstTime;
  int priority;
  int turnaroundTime;
  int waitTime;
  public:
  Process();
  Process(int PID, int arriveTime, int burstTime, int priority);
  int getPID();
  int getArriveTime();
  int getBurstTime();
  int getPriority();
  int getTurnaroundTime();
  int getWaitTime();
  void decrementBurstTime();
  void calculateTurnaroundTime(int endTime);
  void calculateWaitTime(int burstTime);
};

#endif //V9_PROCESS_HPP
