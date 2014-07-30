#ifndef ZENIT_TASK_MANAGER_H
#define ZENIT_TASK_MANAGER_H

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>

#include "boost/thread.hpp"
#include "tools.h"

namespace zenit{
	enum TaskStatus{
		TaskStatus_Active,
		TaskStatus_Inactive
	};

	class Task{
	public:
		Task():m_Priority(0),m_Status(TaskStatus_Active){}
		//Setter
		virtual void SetPriority(const int val){
			m_Priority=val;
		}
		virtual void SetName(const std::string &val){
			m_Name = val;
		}
		virtual void SetStatus(const TaskStatus &val){
			m_Status=val;
		}
		virtual void SetCheckPeriod(const int val){//In seconds
			m_Period = val;
		}

		//Getter
		virtual TaskStatus GetStatus() const{
			return m_Status;
		}
		virtual std::string GetName() const{
			return m_Name;
		}
		virtual int GetPriority() const{
			return m_Priority;
		}
		virtual int GetCheckPeriod() const{
			return m_Period;
		}

		//Invoke function
		virtual int operator()() = 0;
	protected:
		int m_Priority;
		std::string m_Name;
		TaskStatus m_Status;
		int m_Period;
	};

	class TimeCountDownTask:public Task{
	public:
		TimeCountDownTask()
			:m_CountDownTime(-1),m_IsCountingDown(false){}
		TimeCountDownTask(const int CountDownTime)
			:m_CountDownTime(CountDownTime),m_IsCountingDown(false){}
		virtual void StartCountDown(){
			m_Timer.reset();
			m_IsCountingDown= true;
		}

		virtual void SetCountDownTime(const int val){
			m_CountDownTime=val;
		}

		virtual int operator()(){
			if(m_IsCountingDown){
				double temp_time;
				m_Timer.get_time_in_s(temp_time);
				if(temp_time >= m_CountDownTime){
					Run();
					m_IsCountingDown = false;
				}
			}
			return 0;
		}
	private:
		virtual void Run() = 0;
	private:
		int m_CountDownTime;
		local_timer m_Timer;
		bool m_IsCountingDown;
	};

	class LocalTimeTask:public Task{
	public:
		LocalTimeTask(const time_t TriggerTime)
			:m_TriggerTime(TriggerTime){}
		LocalTimeTask()
			:m_TriggerTime(-1){}
		void SetTriggerTime(const time_t val){
			m_TriggerTime = val;
		}
		virtual int operator()(){
			if(m_TriggerTime > 0){
				//Get the current time
				time_t temp_time;
				time ( &temp_time );
				if(temp_time >= m_TriggerTime){
					Run();
					//After running the task, set the task status to inactive
					m_TriggerTime=-1;
				}
			}
			return 0;
		}
	private:
		virtual void Run() = 0;
	private:
		time_t m_TriggerTime;
	};

	struct Time_Period{
		int day;
		int week;
		int hour;
		int min;
		int sec;
	};

	class LocalTimeRepeatTask : public Task{
	public:
		LocalTimeRepeatTask(const time_t TriggerTime, const Time_Period &Period)
			:m_Period(Period),m_TriggerTime(TriggerTime){}
		LocalTimeRepeatTask()
			:m_TriggerTime(-1){
				m_Period.week   = 0;
				m_Period.day	= 1;
				m_Period.hour	= 0;
				m_Period.min	= 0;
				m_Period.sec	= 0;
		}
		void SetTriggerTime(const time_t val){
			time_t temp_time;
			time ( &temp_time );
			if(temp_time > val){
				m_TriggerTime = val+PeroidToTime(m_Period);
			}
			else{
				m_TriggerTime = val;
			}
		}
		void SetPeriod(const Time_Period &val){
			m_Period = val;
		}
		virtual int operator()(){
			if(m_TriggerTime >0 ){
				//Get the current time
				time_t temp_time;
				time ( &temp_time );
				if(temp_time >= m_TriggerTime){
					Run();
					m_TriggerTime += PeroidToTime(m_Period);
				}
			}
			return 0;
		}
	private:
		virtual void Run() = 0;
		time_t PeroidToTime(Time_Period &Period){
			return time_t(Period.week*7*86400+Period.day*86400+Period.hour*3600+Period.min*60+Period.sec);
		}
	private:
		Time_Period m_Period;
		time_t m_TriggerTime;
	};

    class AutoRepeatTask : public Task{
	public:
		AutoRepeatTask(const Time_Period &Period)
			:m_Period(Period),m_LastTriggerTime(0){}
		AutoRepeatTask(){
            m_Period.week   = 0;
            m_Period.day	= 0;
            m_Period.hour	= 0;
            m_Period.min	= 0;
            m_Period.sec	= 1;
		}
		void SetPeriod(const Time_Period &val){
			m_Period = val;
		}
		virtual int operator()(){
            //Get the current time
            time_t temp_time;
            time ( &temp_time );
            if(temp_time >= m_LastTriggerTime + PeroidToTime(m_Period)){
                Run();
                time(&m_LastTriggerTime);
            }

			return 0;
		}
	private:
		virtual void Run() = 0;
		time_t PeroidToTime(Time_Period &Period){
			return time_t(Period.week*7*86400+Period.day*86400+Period.hour*3600+Period.min*60+Period.sec);
		}
	private:
		Time_Period m_Period;
		time_t m_LastTriggerTime;
	};

	template<class T>
	class ChangeAlarmTask : public Task{
	public:
		ChangeAlarmTask(const T *t)
			:m_t(t),m_last(*t){}
		virtual int operator()(){
			if(m_t != NULL ){
				if(m_last != (*m_t)){
					Run();
					m_last = (*m_t);
				}
			}
			return 0;
		}
	private:
		virtual void Run() = 0;
	private:
		T	*m_t;
		T	m_last;
	};

	class TaskManager{
	public:
		TaskManager()
			:m_IsRunning(false),m_Period(1000){}
		void AddTask(Task *pTask){
			boost::mutex::scoped_lock lock(m_mutex);
			if(std::find(m_TaskList.begin(),m_TaskList.end(),pTask) == m_TaskList.end()){
				m_TaskList.push_back(pTask);
			}
		}
		void RemoveTask(Task *pTask){
			boost::mutex::scoped_lock lock(m_mutex);
			std::list<Task*>::iterator iter;
			iter = std::find(m_TaskList.begin(),m_TaskList.end(),pTask);
			if(iter != m_TaskList.end()){
				m_TaskList.erase(iter);
			}
		}
		void Reset();
		void Start(){
			if(!m_IsRunning){
				//Start a thread
				m_Thread = new boost::thread(boost::bind(&TaskManager::ThreadFunction, this));
				m_Stop = false;
				m_IsRunning = true;
			}
		}
		void Stop(){
			boost::mutex::scoped_lock lock(m_mutex);
			//Stop a thread
			if(m_IsRunning){
				m_Stop = true;
				m_Thread->join();
				delete m_Thread;
				m_IsRunning = false;
			}
		}
		void SetPeriod(const int Period){
			boost::mutex::scoped_lock lock(m_mutex);
			m_Period = Period;
		}
		void CheckAll(){
			boost::mutex::scoped_lock lock(m_mutex);
			_CheckAll();
		}
		~TaskManager(){
			Stop();
		}
	private:
		bool			m_Stop;
		bool			m_IsRunning;
		boost::thread	*m_Thread;
		std::list<Task*> m_TaskList;
		boost::mutex	m_mutex;
		int				m_Period;
	private:
		void _CheckAll(){
			for(std::list<Task*>::iterator iter = m_TaskList.begin();iter != m_TaskList.end();iter++){
				if((*iter)->GetStatus() == TaskStatus_Active) (*(*iter))();
			}
		}
		void ThreadFunction(){
			while(true){
			    {
                    boost::mutex::scoped_lock lock(m_mutex);
                    if(m_Stop) break;
                    _CheckAll();
			    }
                timespec spec;
                spec.tv_sec = m_Period/1000;
                spec.tv_nsec = (m_Period%1000)*1000*1000;
			    nanosleep(&spec,NULL);
			}
		}
	};
}

#endif
