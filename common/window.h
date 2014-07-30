#pragma once

#include <thread>
#include <memory>
#include <ncurses.h>

namespace nova {

class window
{
public:
    window(int x, int y, int length, int width)
        :m_x(x),m_y(y),m_length(length),m_width(width)
    {
        m_update_interval = 1000;

        m_handler = newwin(width,length,y,x);
        if(m_handler == NULL)
        {
            throw(0);
        }

        m_close = false;

        m_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(&window::thread_func, this)));
    }

    virtual void refresh()
    {
        on_refresh();
        wrefresh(m_handler);
    }

    virtual void on_refresh() {}

    virtual ~window()
    {
        m_close = true;

        m_thread->join();

        wclear(m_handler);

        wrefresh(m_handler);

        delwin(m_handler);
    }

    virtual void addstring(const char* str)
    {
        waddstr(m_handler,str);
    }

    virtual void mvaddstring(const int x, const int y, const char* str)
    {
        mvwaddstr(m_handler, y, x, str);
    }

    virtual void getstring(char* str, size_t size)
    {
        wgetnstr(m_handler, str, size);
    }

    void clear()
    {
        wclear(m_handler);
    }

    void enable_scrollable(bool val)
    {
        scrollok(m_handler, TRUE);
    }

    void set_bkgd_color(unsigned int val)
    {
        wbkgd(m_handler,val);
    }

    void set_font_color(unsigned int val)
    {
        wattrset(m_handler,val);
    }

    void set_refresh_interval(size_t msec)
    {
        m_update_interval = msec;
    }

    void stop_refresh()
    {
        m_close = true;
        m_thread->join();
    }

    bool is_refreshing()
    {
        return !m_close;
    }

    void resume_refresh()
    {
        m_close = false;
        m_thread.reset(new std::thread(std::bind(&window::thread_func, this)));
    }
protected:
    int m_x;
    int m_y;
    int m_length;
    int m_width;
    WINDOW* m_handler;
private:
    void thread_func()
    {
        timespec time_val;
        while (!m_close)
        {
            time_val.tv_sec = m_update_interval / 1000;
            time_val.tv_nsec = (m_update_interval % 1000) * 1000 * 1000;
            nanosleep(&time_val,NULL);
            refresh();
        }
    }
private:
    std::shared_ptr<std::thread> m_thread;
    bool m_close;
    int m_font_color;
    size_t m_update_interval;
};

} //namespace nova
