#include "normal.hpp"

int main(int argc,const char *argv[])
{
    int run = atoi(argv[1]);
    int pop = atoi(argv[2]);
    int DIM = atoi(argv[3]);
    int Function_Number = atoi(argv[4]);
    int MAX_NFE = atoi(argv[5]);


    
    if( argc > 1 )
    {
        PPSO ppso;
        ppso.Run(run, MAX_NFE,pop,DIM,Function_Number);
    }
      
    else 
    {
        PPSO ppso;
        ppso.Run(1,100000,200,10,1);

    }
   
    return 0;
}