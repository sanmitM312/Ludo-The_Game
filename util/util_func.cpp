#include "util_func.hpp"

#ifdef __linux__
    #include<sys/ioctl.h>
    #include<unistd.h>
#elif __MINGW32
    #include<windows.h>
#elif __CYGWIN32
    #include<windows.h>
#endif

#ifndef _GLIBCXX_IOSTREAM
    #include<iostream>
#endif
#ifndef _GLIBCXX_ALGORITHM
    #include<algorithm>
#endif

intTuple getTerminalDimen(){
  intTuple retTuple(0,0);
  #ifdef __linux__
    winsize windowsSize;
    ioctl (STDOUT_FILENO, TIOCGWINSZ, &windowsSize);
      retTuple[0] = windowsSize.ws_row;
      retTuple[1] = windowsSize.ws_col;

  #else //Windows API
    {
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
        retTuple[0] = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        retTuple[1] = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

  #endif

  return retTuple;
}

inline bool align_text_center(int max_length,const std::string& str){    //@returns bool indicating, if max_len is enough or not
    if(max_length < str.size()){
        return false;
    }
    else
    {
        for (size_t i = 0; i < (max_length-str.size())/2; i++)  std::cout<<' ';
        std::cout<<str;
        for (size_t i = 0; i < (max_length-str.size()) - (max_length-str.size())/2; i++)  std::cout<<' ';
    }
    
}

inline std::string trimString(const std::string &s){
    std::string str_out(s);
    str_out.erase(std::find_if(str_out.rbegin(),str_out.rend(),[](char ch){
        return ! isspace(ch);
    }).base(), str_out.end());

    str_out.erase(std::find_if(str_out.begin(),str_out.end(),[](char ch){
        return ! isspace(ch);
    }), str_out.rend().base());
    
}

//LEARNT+QUESTIONS BELOW//
//ERROR - [in getTerminalDimen()] Replace intTuple with simpleTuple<int,int> gives error : conversion from ‘simpleTuple<int, int>’ to non-scalar type ‘intTuple {aka homoTuple<int>}’ requested
/*LEARNT - ASCII value of integers 0-9 are actually 48-57*/
    /*Learnt - In case of only 1 argument passed to std::string::erase()...
                1. If we provide an index number, ALL including and after it are erased
                2. If we provide an iterator,    ONLY that position is removed*/

    //LEARNT - algorithm -> find_if - Keep finding, until the predicate is true
    //LEARNT - Using .base() on a reverse_iterator returns us the normal_iterator, BUT CAUTION- This isn't advisable, and might cause SEGFAULT, (for eg. accessing .rbegin().base())

/*LEARNT - stringify() can turn any name into text, BUT remember, it ignores trailing and front spaces, for eg. in stringify( Hello World ), first and last space ignored*(Verified)/
*/

/*LEARNT - The component type of STL containers like vectors must be 'asignable'.
			References are NOT assignable, ie. we can only initialise them once, and,
			you can't make them reference something else later (you can't assign it to reference any other vairable, and even after equating 2 references, only the values of variable they reference is changed, not the addresses they both refer to)
			Due to same reason, other non-assignable types are also not allowed as components of containers, for eg. vector<const int> not allowed
*/