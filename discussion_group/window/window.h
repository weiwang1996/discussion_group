#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <ncurses.h>

class window{
public:
    //创建window 句柄
    window();
    void wrefreshMyWindow(WINDOW* win);//清屏
    void putStringToWin(WINDOW* win);//给window上输出字符串
    void putStringToWin(WINDOW* win,int start_y,int start_x,std::string &msg);//
    void getStringFromWin(WINDOW* win,std::string &outString);//从window上拿到消息下来
    void clrNumsLines(WINDOW* win,int begin,int nums);//清理一行内容
    void createHeader();
    void createoutput();
    void createfriendList();
    void createinput();
    ~window();
public:
    //管理四个窗口
    WINDOW* header;
    WINDOW* output;
    WINDOW* friend_list;
    WINDOW* input;
};


#endif
