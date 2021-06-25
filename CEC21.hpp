#include<stdio.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include<vector>
#include <algorithm>
#include<math.h>
#include<float.h>
#include <sys/stat.h>
#include <iomanip>
#include "cec21_test_func.cpp"
using namespace std;


class CEC21{

    public:
        void cec21_cal(double *P,double &Obj,int DIM,int F,int F_T)
        {
            if(F_T == 1)
            {
                cec21_basic_func(&P[0],&Obj,DIM,1,F);   
            }
            else if(F_T==2)
            {
                cec21_bias_func(&P[0],&Obj,DIM,1,F);
                // cec21_fitness_error(Obj,F);
            }
            else if(F_T==3)
            {
                cec21_shift_func(&P[0],&Obj,DIM,1,F);
            }
            else if(F_T==4)
            {
                cec21_rot_func(&P[0],&Obj,DIM,1,F);
            }
            else if(F_T==5)
            {
                cec21_bias_shift_func(&P[0],&Obj,DIM,1,F);
                // cec21_fitness_error(Obj,F);
            }
            else if(F_T==6)
            {
            cec21_bias_rot_func(&P[0],&Obj,DIM,1,F);
                // cec21_fitness_error(Obj,F);
            }
            else if(F_T==7)
            {
                cec21_shift_rot_func(&P[0],&Obj,DIM,1,F);   
            }
            else if(F_T==8)
            {
                cec21_bias_shift_rot_func(&P[0],&Obj,DIM,1,F);
                // cec21_fitness_error(Obj,F);
            }
                
        }
    double cec21_fitness_error(int F,double K)
            {
                switch(F)
                {
                    case 1:	
                        K-=100.0;
                        return K;
                        break;
                    case 2:	
                        K-=1100.0;
                        return K;
                        break;
                    case 3:
                        K-=700.0;
                        return K;
                        break;
                    case 4: 
                        K-=1900.0;
                        return K;
                        break;
                    case 5:
                        K-=1700.0;
                        return K;
                        break;
                    case 6:
                        K-=1600.0;
                        return K;
                        break;
                    case 7:
                        K-=2100.0;
                        return K;
                        break;
                    case 8:
                        K-=2200.0;
                        return K;
                        break;
                    case 9:
                        K-=2400.0;
                        return K;
                        break;
                    case 10:
                        K-=2500.0;
                        return K;
                        break;
                }
            }
            void CEC_Classify(int F,int F_T,double START,double END,double RUN_STD,double RUN_AVG,int DIM)
            {
                fstream file;           
                string A = "PPSO_2021_CEC_Classify"+to_string(DIM)+".txt";
                file.open(A,ios::app);
                file << scientific << setprecision(2);
                file<<F<<' '<<F_T<<' '<<RUN_AVG<<' '<<RUN_STD<<' '<<(END - START) / CLOCKS_PER_SEC<<endl;
            }
            void Run_Classify(double *Run_Result,int F,int F_T,int run,int DIM)
            {
                fstream file; 
                string DIR = "./RUN_RESULT/";        
                string A = DIR+to_string(DIM)+"D/"+to_string(F)+"_"+to_string(F_T)+"_Run_Classify.txt";
                file.open(A,ios::out);
                file << scientific << setprecision(2);
                for(int i=0;i<run;i++)
                {
                    file<<Run_Result[i]<<endl;

                }
            }
};