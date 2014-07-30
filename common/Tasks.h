#ifndef TASKS_H_INCLUDED
#define TASKS_H_INCLUDED

#include <TaskManager.h>
#include <BaseLib.h>
#include <Window.h>
#include <fstream>
#include "ProgramTraderServer.h"

typedef void (*GetLogFileNameCallBack) (char*, const char*);

namespace zenit{
    typedef IProgramTrader* (*CreateProgramTraderCallBack) (const char*, IApp*, char*);

    class OrderLoginTask : public LocalTimeRepeatTask{
    public:
        OrderLoginTask(IOrderConnection *pOrderConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        IOrderConnection* m_pOrderConnection;
        window *m_pLogWindow;
    };

    class MultiOrderLoginTask : public LocalTimeRepeatTask{
    public:
        MultiOrderLoginTask(std::vector<IOrderConnection*> & vecOrderConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        std::vector<zenit::IOrderConnection*> m_vecOrderConnection;
        window *m_pLogWindow;
    };

    class DataLoginTask : public LocalTimeRepeatTask{
    public:
        DataLoginTask(IDataConnection *pDataConnection);
    private:
        virtual void Run();
    private:
        IDataConnection* m_pDataConnection;
    };

    class MultiDataLoginTask : public LocalTimeRepeatTask{
    public:
        MultiDataLoginTask(std::vector<IDataConnection*> & vecDataConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        std::vector<IDataConnection*> m_vecDataConnection;
        window *m_pLogWindow;
    };

    class OrderLogoutTask : public LocalTimeRepeatTask{
    public:
        OrderLogoutTask(IOrderConnection *pOrderConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        IOrderConnection* m_pOrderConnection;
        window *m_pLogWindow;
    };

    class MultiOrderLogoutTask : public LocalTimeRepeatTask{
    public:
        MultiOrderLogoutTask(std::vector<IOrderConnection*> & vecOrderConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        std::vector<IOrderConnection*>  m_vecOrderConnection;
        window *m_pLogWindow;
    };

    class DataLogoutTask : public LocalTimeRepeatTask{
    public:
        DataLogoutTask(IDataConnection *pDataConnection);
    private:
        virtual void Run();
    private:
        IDataConnection* m_pDataConnection;
    };

    class MultiDataLogoutTask : public LocalTimeRepeatTask{
    public:
        MultiDataLogoutTask(std::vector<IDataConnection*> & vecDataConnection,window *pLogWindow);
    private:
        virtual void Run();
    private:
        std::vector<IDataConnection*> m_vecDataConnection;
        window *m_pLogWindow;
    };

    class OrderResetTask : public LocalTimeRepeatTask{
    public:
        OrderResetTask(IOrderConnection *pOrderConnection, GetLogFileNameCallBack CallBack,window *pLogWindow);
        void SetLogFile(const char * strLogFile);
    private:
        virtual void Run();
    private:
        IOrderConnection* m_pOrderConnection;
        GetLogFileNameCallBack m_GetLogFileNameCallBack;
        window *m_pLogWindow;
    };

    class MultiOrderResetTask : public LocalTimeRepeatTask{
    public:
        MultiOrderResetTask(std::vector<IOrderConnection*> & vecOrderConnection, IAccountMgr* pAccountMgr, GetLogFileNameCallBack CallBack,window *pLogWindow);
        void SetLogFile(const char * strLogFile);
    private:
        virtual void Run();
        static bool EnumPrintAccount(account_no_t accountNo, const ACCOUNT_SUMMARY * pAccountSummary, void* nUserData);
    private:
        std::vector<IOrderConnection*> m_vecOrderConnection;
        IAccountMgr *m_pAccountMgr;
        GetLogFileNameCallBack m_GetLogFileNameCallBack;
        window *m_pLogWindow;
        std::ofstream m_stmLog;
    };

    class DataResetTask : public LocalTimeRepeatTask{
    public:
        DataResetTask(IDataConnection *pDataConnection, GetLogFileNameCallBack CallBack);
        void SetLogFile(const char * strLogFile);
    private:
        virtual void Run();
    private:
        IDataConnection* m_pDataConnection;
        GetLogFileNameCallBack m_GetLogFileNameCallBack;
    };

    class MultiDataResetTask : public LocalTimeRepeatTask{
    public:
        MultiDataResetTask(std::vector<IDataConnection*> & vecDataConnection,window *pLogWindow, IApp *pApp);
    private:
        virtual void Run();
    private:
        std::vector<IDataConnection*> m_vecDataConnection;
        window *m_pLogWindow;
        IApp    *m_pApp;
    };

    class LocalTimeStartTradeTask : public LocalTimeRepeatTask{
    public:
        LocalTimeStartTradeTask(const char* name, IApp *pApp, window *pLogWindow, CreateProgramTraderCallBack callback);
    private:
        virtual void Run();
    private:
        char            m_name[256];
        IApp		    * m_pApp;
        window          * m_pLogWindow;
        CreateProgramTraderCallBack m_callback;
    };

    class LocalTimeStopTradeBeginTask : public LocalTimeRepeatTask{
    public:
        LocalTimeStopTradeBeginTask(const char* name, IApp *pApp, window *pLogWindow);
    private:
        virtual void Run();
    private:
        char            m_name[256];
        IApp		    * m_pApp;
        window          *m_pLogWindow;
    };

    class LocalTimeStopTradeFinishTask : public LocalTimeRepeatTask{
    public:
        LocalTimeStopTradeFinishTask(const char* name, IApp *pApp, window *pLogWindow);
    private:
        virtual void Run();
    private:
        char            m_name[256];
        IApp		    * m_pApp;
        window          *m_pLogWindow;
    };

    class StartRemoteServerTask : public LocalTimeRepeatTask{
    public:
        StartRemoteServerTask(IRemoteServer *pRemoteServer, window *pLogWindow);
    private:
        virtual void Run();
    private:
        IRemoteServer* m_pRemoteServer;
        window *m_pLogWindow;
    };

    class StopRemoteServerTask : public LocalTimeRepeatTask{
    public:
        StopRemoteServerTask(IRemoteServer *pRemoteServer, window *pLogWindow);
    private:
        virtual void Run();
    private:
        IRemoteServer* m_pRemoteServer;
        window *m_pLogWindow;
    };

    class StartProgramTraderServerTask : public LocalTimeRepeatTask{
    public:
        StartProgramTraderServerTask(ProgramTraderServer *pRemoteServer, window *pLogWindow);
    private:
        virtual void Run();
    private:
        ProgramTraderServer* m_pRemoteServer;
        window *m_pLogWindow;
    };

    class StopProgramTraderServerTask : public LocalTimeRepeatTask{
    public:
        StopProgramTraderServerTask(ProgramTraderServer *pRemoteServer, window *pLogWindow);
    private:
        virtual void Run();
    private:
        ProgramTraderServer* m_pRemoteServer;
        window *m_pLogWindow;
    };
}

#endif // TASKS_H_INCLUDED
