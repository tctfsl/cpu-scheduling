//
// Created by DELL on 28-Sep-17.
//

#include "Process.hpp"

Process::Process()
{
  this->PID = 0;
  this->arriveTime = 0;
  this->burstTime = 0;
  this->priority = 0;
  this->turnaroundTime = 0;
  this->waitTime = 0;
}

Process::Process(int PID, int arriveTime, int burstTime, int priority)
{
  this->PID = PID;
  this->arriveTime = arriveTime;
  this->burstTime = burstTime;
  this->priority = priority;
  this->turnaroundTime = 0;
  this->waitTime = 0;
}

int Process::getPID()
{
  return PID;
}

int Process::getArriveTime()
{
  return arriveTime;
}

int Process::getBurstTime()
{
  return burstTime;
}

int Process::getPriority()
{
  return priority;
}

int Process::getTurnaroundTime()
{
  return turnaroundTime;
}

int Process::getWaitTime()
{
  return waitTime;
}

void Process::decrementBurstTime()
{
  burstTime--;
}

void Process::calculateTurnaroundTime(int endTime)
{
  this->turnaroundTime = endTime - this->arriveTime;
}

void Process::calculateWaitTime(int burstTime)
{
  this->waitTime = this->turnaroundTime - burstTime;
}