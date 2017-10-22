#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include<unistd.h>

#define PW_LEN 256
#define NAME_LEN 256

int main(){

 char name[NAME_LEN];
 char password[PW_LEN];
 const char* real_password ="dota2";
 int i;

 initscr();
 move(5,10);
 printw("%s","please login:");

 move(7,10);
 printw("%s","User name:");
 getstr(name);

 move(8,10);
 printw("%s","password:");
 refresh();

 cbreak();//键盘只要输入就会传递到程序里，不缓存
 noecho(); //关闭回显功能，键盘上输入屏幕看不见
 memset(password,'\0',sizeof(password));
 while(i<PW_LEN){
     password[i]= getch();
     if(password[i]=='\n') break;
     move(8,20+i);
     addch('*');
     refresh();
     i++;
  }

 echo();
 nocbreak();

 move(11,10);
 if(strncmp(real_password,password,strlen(real_password))==0)
   printw("%s","right");
 else
   printw("%s","wrong");
 printw("%s","password");
 refresh();
 sleep(10);

 endwin();
 exit(EXIT_SUCCESS);
}
