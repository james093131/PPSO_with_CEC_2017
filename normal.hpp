// #include "CEC21.hpp"
#include "CEC17.hpp"

typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double>d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

// class PPSO : CEC21{
class PPSO : CEC17{

    public:
        d1d Each_Run_Evaluation_Best;
        d1d Each_Run_Result;

    public:
        void Run(int run,int MAX_NFE,int pop,int DIM,int FunctionNumber,int FunctionTransform)
        {   
	        srand((unsigned)time(NULL));
            INI_RUN(run);
            int r = 0;
            double START,END;

            START = clock();
            while(r <run)
            {
                INI(DIM, pop);

                for(int i= 0;i<pop;i++)
                {
                    RANDOM_INI(DIM,i,PSO_inf.Particle,PSO_inf.Objective);
                }
                Evaluation(pop,DIM,FunctionNumber,FunctionTransform);

                while( NFE < MAX_NFE)
                {
                    Update_phi(pop,DIM);
                    Update_delta(pop,DIM);
                    Fuzzy_rules(pop);
                    Set_Inertia(pop);
                    Set_Social(pop);
                    Set_Cognitive(pop);

                    Update_Velocity(pop,DIM);
                    Update_Position(pop,DIM);
                    Find_Boundaries(pop,DIM);
                    Evaluation(pop,DIM,FunctionNumber,FunctionTransform);
                    CEC17::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);
                    // CEC21::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);

                } 
                
                CEC17::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);
                // CEC21::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);

                Each_Run_Result[r] = Current_inf.Current_Best_Value;
                r++;
            }
            END = clock();
            OUTPUT(DIM,FunctionNumber,FunctionTransform,MAX_NFE,run,START,END);

            

        }
        private:
            struct PSO_Parameter
            {
                d2d Particle;
                d1d Objective;
                d2d Velocity;
                d2d Previous_Particle;
                d1d Previous_Objective;
                d1d phi;
                d1d delta;
                
            };
            struct Current_best
            {
                double Current_Best_Value;
                d1d Current_Best_Coordinate;        
            };
            struct Personal_best
            {
                d1d Personal_Best_Value;
                d2d Personal_Best_Coordinate;        
            };
            struct Fuzzy
            {
                d2d Fi_coef;
                d2d Delta_coef;
                d1d Inerlia;
                d1d Social;
                d1d Cognitive;
            };
            struct Boundaries
            {
                d1d min;
                d1d max;
            };
            Current_best Current_inf;
            Personal_best Personal_inf;
            PSO_Parameter PSO_inf;
            Fuzzy Fuzzy_coef;
            Boundaries boundaries;
            double max = 100.0;
            double min = -100.0;
            double Current_Worst_Value;
            double Delta_MAX;
            int NFE = 0 ;
      

        private:
        void RANDOM_INI(int DIM,int index,d2d &arr,d1d &objective)
        {
            
      
            for(int i=0;i<DIM;i++)
            {
                double a = (max - min) * rand() / (RAND_MAX + 1.0) + min;

                arr[index][i] = a;
            }

        }
        void INI(int DIM,int pop)
            {
                cout << scientific << setprecision(8);
                PSO_inf.Particle.clear();
                PSO_inf.Particle.swap(PSO_inf.Particle);

                PSO_inf.Velocity.clear();
                PSO_inf.Velocity.swap(PSO_inf.Velocity);

                PSO_inf.Objective.clear();
                PSO_inf.Objective.swap(PSO_inf.Objective);

                PSO_inf.Previous_Particle.clear();
                PSO_inf.Previous_Particle.swap(PSO_inf.Previous_Particle);

                PSO_inf.Previous_Objective.clear();
                PSO_inf.Previous_Objective.swap(PSO_inf.Previous_Objective);

                PSO_inf.phi.clear();
                PSO_inf.phi.swap(PSO_inf.phi);

                PSO_inf.delta.clear();
                PSO_inf.delta.swap(PSO_inf.delta);

                Personal_inf.Personal_Best_Coordinate.clear();
                Personal_inf.Personal_Best_Coordinate.swap(Personal_inf.Personal_Best_Coordinate);

                Personal_inf.Personal_Best_Value.clear();
                Personal_inf.Personal_Best_Value.swap(Personal_inf.Personal_Best_Value);
           
                Current_inf.Current_Best_Coordinate.clear();
                Current_inf.Current_Best_Coordinate.swap(Current_inf.Current_Best_Coordinate);

                
                Fuzzy_coef.Fi_coef.clear();
                Fuzzy_coef.Fi_coef.swap(Fuzzy_coef.Fi_coef);
                
                Fuzzy_coef.Delta_coef.clear();
                Fuzzy_coef.Delta_coef.swap( Fuzzy_coef.Delta_coef);

                Fuzzy_coef.Inerlia.clear();
                Fuzzy_coef.Inerlia.swap(Fuzzy_coef.Inerlia);

                Fuzzy_coef.Social.clear();
                Fuzzy_coef.Social.swap(Fuzzy_coef.Social);

                Fuzzy_coef.Cognitive.clear();
                Fuzzy_coef.Cognitive.swap(Fuzzy_coef.Cognitive);

                boundaries.max.clear();
                boundaries.max.swap( boundaries.max);
                boundaries.min.clear();
                boundaries.max.swap( boundaries.min);

                PSO_inf.Particle.assign(pop,d1d(DIM));
                PSO_inf.Velocity.assign(pop,d1d(DIM,0));
                PSO_inf.Objective.resize(pop);
                PSO_inf.Previous_Particle.assign(pop,d1d(DIM,DBL_MAX));
                PSO_inf.Previous_Objective.resize(pop,0);
                PSO_inf.delta.resize(pop);
                PSO_inf.phi.resize(pop);


                Current_inf.Current_Best_Coordinate.resize(DIM);
                Current_inf.Current_Best_Value = DBL_MAX;

                Personal_inf.Personal_Best_Coordinate.assign(pop,d1d(DIM));
                Personal_inf.Personal_Best_Value.resize(pop,DBL_MAX);


                max = 100;
                min = -100;
                NFE = 0;
                Current_Worst_Value = 0;
                
                Fuzzy_coef.Fi_coef.assign(pop,d1d(3)) ;
                Fuzzy_coef.Delta_coef.resize(pop,d1d(3)) ;
                Fuzzy_coef.Inerlia.resize(pop,0);
                Fuzzy_coef.Social.resize(pop,0);
                Fuzzy_coef.Cognitive.resize(pop,0);

                boundaries.max.resize(DIM,max);
                boundaries.min.resize(DIM,min);

                Delta_MAX = 0;
                for(int i=0;i<DIM;i++)
                {
                    Delta_MAX += pow( (max-min), 2 );
                }
            
                Delta_MAX = sqrt(Delta_MAX);

            }   
            void INI_RUN(int run)
            {
                Each_Run_Evaluation_Best.resize(14,0);
                Each_Run_Result.resize(run,DBL_MAX);
            }


            double  delta_cal(int index,int DIM)
            {
                double DIS = 0.0;

                for(int i=0;i<DIM;i++)
                {
                   DIS += pow( (PSO_inf.Particle[index][i]-PSO_inf.Previous_Particle[index][i]) ,2);
                }

                DIS =sqrt(DIS);

                DIS /= Delta_MAX;

                return DIS;
            }
            double  delta_cal(int index,int DIM,d1d global)
            {
                double DIS = 0.0;

                for(int i=0;i<DIM;i++)
                {
                   DIS += pow( (PSO_inf.Particle[index][i]-global[i]) ,2);
                }

                DIS = sqrt(DIS);

                DIS /= Delta_MAX;

                return DIS;
            }
            void Update_phi(int pop,int DIM)
            {
                for(int i= 0;i<pop;i++)
                {
                    double f1  = (Current_Worst_Value < PSO_inf.Objective[i] ) ? Current_Worst_Value  : PSO_inf.Objective[i];
                    double f2  = (Current_Worst_Value < PSO_inf.Previous_Objective[i] ) ? Current_Worst_Value  : PSO_inf.Previous_Objective[i];


                    double dis = delta_cal(i,DIM);

                    double delta_f = Current_Worst_Value;
                    if (delta_f < 0)
                        delta_f = -delta_f;

                    PSO_inf.phi[i] = ( (f1-f2)/delta_f ) * dis; 
                }
            }
            void Update_delta(int pop,int DIM)
            {
                for(int i=0;i<pop;i++)
                {
                   PSO_inf.delta[i] =  delta_cal(i,DIM,Current_inf.Current_Best_Coordinate);
                }
            }
            void Fuzzy_rules(int pop)
            {
                for(int i=0;i<pop;i++)
                {
                    // phi 
                    //better
                    if(PSO_inf.phi[i] == -1 )
                        Fuzzy_coef.Fi_coef[i][0] = 1;
                    else if(PSO_inf.phi[i] > -1  && PSO_inf.phi[i] < 0 )  
                        Fuzzy_coef.Fi_coef[i][0] = -PSO_inf.phi[i];
                    else if(PSO_inf.phi[i] >= 0  && PSO_inf.phi[i] <= 1 )
                        Fuzzy_coef.Fi_coef[i][0] = 0;

                    //unvaried
                    if(PSO_inf.phi[i] >= -1 && PSO_inf.phi[i] < (-0.0025) )
                        Fuzzy_coef.Fi_coef[i][1] = 0;
                    else if(PSO_inf.phi[i] >= -0.025  && PSO_inf.phi[i] < 0 )  
                        Fuzzy_coef.Fi_coef[i][1] = (-0.025-PSO_inf.phi[i])/-0.025;
                    else if(PSO_inf.phi[i] >= 0  && PSO_inf.phi[i] < 0.025 )
                        Fuzzy_coef.Fi_coef[i][1] = (0.025-PSO_inf.phi[i])/0.025;
                    else if(PSO_inf.phi[i] >= 0.025  && PSO_inf.phi[i] <= 1)
                        Fuzzy_coef.Fi_coef[i][1] = 0;

                    //worse
                    if(PSO_inf.phi[i] >= -1 && PSO_inf.phi[i] < 0 )
                        Fuzzy_coef.Fi_coef[i][2] = 0;
                    else if(PSO_inf.phi[i] >= 0  && PSO_inf.phi[i] < 1 )
                        Fuzzy_coef.Fi_coef[i][2] = PSO_inf.phi[i] ;
                    else if(PSO_inf.phi[i] == 1 )
                        Fuzzy_coef.Fi_coef[i][2] = 1;  


                    //delta
                    //low
                    if( PSO_inf.delta[i] >= 0 && PSO_inf.delta[i] < 0.05*Delta_MAX )  
                        Fuzzy_coef.Delta_coef[i][0] = 1;
                    else if(PSO_inf.delta[i] >= 0.05*Delta_MAX  && PSO_inf.delta[i] < 0.10*Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][0] = (0.10*Delta_MAX - PSO_inf.delta[i])/(0.10*Delta_MAX - 0.05*Delta_MAX);
                    else if(PSO_inf.delta[i] >= 0.10*Delta_MAX  && PSO_inf.delta[i] <= Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][0] = 0;

                    //medium
                    if( PSO_inf.delta[i] >= 0 && PSO_inf.delta[i] < 0.05*Delta_MAX )  
                        Fuzzy_coef.Delta_coef[i][1] = 0;
                    else if(PSO_inf.delta[i] >= 0.05*Delta_MAX  && PSO_inf.delta[i] < 0.10*Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][1] = (PSO_inf.delta[i] - 0.05*Delta_MAX )/(0.10*Delta_MAX - 0.05*Delta_MAX  );
                    else if(PSO_inf.delta[i] >= 0.10*Delta_MAX  && PSO_inf.delta[i] < 0.15*Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][1] = ( 0.15*Delta_MAX - PSO_inf.delta[i] )/(0.15*Delta_MAX - 0.10*Delta_MAX  );
                    else if(PSO_inf.delta[i] >= 0.15*Delta_MAX  && PSO_inf.delta[i] <=  Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][1] = 0;
                    //high
                    if( PSO_inf.delta[i] >= 0 && PSO_inf.delta[i] < 0.10*Delta_MAX )  
                        Fuzzy_coef.Delta_coef[i][2] = 0;
                    else if(PSO_inf.delta[i] >= 0.10*Delta_MAX  && PSO_inf.delta[i] < 0.15 * Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][2] = (PSO_inf.delta[i] - 0.10*Delta_MAX )/( 0.15*Delta_MAX- 0.10*Delta_MAX) ;
                    else if(PSO_inf.delta[i] >= 0.15*Delta_MAX  && PSO_inf.delta[i] <= Delta_MAX  )
                        Fuzzy_coef.Delta_coef[i][2] = 1;
                }
            }
            void Set_Inertia(int pop)
            {
                for(int i=0;i<pop;i++)
                {
                    double temp1 = 0.0;
                    double temp2 = 0.0;
                    //rule 1
                    if(Fuzzy_coef.Fi_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][2]*0.3;
                        temp2 += Fuzzy_coef.Fi_coef[i][2];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][1]*0.3;
                        temp2 += Fuzzy_coef.Delta_coef[i][1];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][2]*0.3;
                        temp2 += Fuzzy_coef.Delta_coef[i][2];
                    }

                    //rule2
                    if(Fuzzy_coef.Fi_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][1]*0.5;
                        temp2 += Fuzzy_coef.Fi_coef[i][1];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][0]*0.5;
                        temp2 += Fuzzy_coef.Delta_coef[i][0];
                    }

                    //rule3
                    else if(Fuzzy_coef.Fi_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][0]*1.0;
                        temp2 += Fuzzy_coef.Fi_coef[i][0];
                    }

                    if(temp2 == 0)
                        Fuzzy_coef.Inerlia[i] = 0.0;
                    else
                        Fuzzy_coef.Inerlia[i] = temp1/temp2;
                }
            }
            void Set_Social(int pop)
            {
                for(int i=0;i<pop;i++)
                {
                    double temp1 = 0.0;
                    double temp2 = 0.0;
                    //rule 1
                    if(Fuzzy_coef.Fi_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][0]*0.1;
                        temp2 += Fuzzy_coef.Fi_coef[i][0];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][1]*0.1;
                        temp2 += Fuzzy_coef.Delta_coef[i][1];
                    }
                    

                    //rule2
                    if(Fuzzy_coef.Fi_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][1]*1.5;
                        temp2 += Fuzzy_coef.Fi_coef[i][1];
                    }
                  

                    //rule3
                    if(Fuzzy_coef.Fi_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][2]*3.0;
                        temp2 += Fuzzy_coef.Fi_coef[i][2];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][0]*3.0;
                        temp2 += Fuzzy_coef.Delta_coef[i][0];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][2]*3.0;
                        temp2 += Fuzzy_coef.Delta_coef[i][2];
                    }

                    if(temp2 == 0.0)
                        Fuzzy_coef.Social[i] = 0.0;
                    else
                        Fuzzy_coef.Social[i] = temp1/temp2;
                }
            }
             void Set_Cognitive(int pop)
            {
                for(int i=0;i<pop;i++)
                {
                    double temp1 = 0.0;
                    double temp2 = 0.0;
                    //rule 1
                    if(Fuzzy_coef.Delta_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][2]*0.1;
                        temp2 += Fuzzy_coef.Delta_coef[i][2];
                    }
                    

                    //rule2
                    if(Fuzzy_coef.Fi_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][1]*1.5;
                        temp2 += Fuzzy_coef.Fi_coef[i][1];
                    }
                    else if(Fuzzy_coef.Fi_coef[i][2] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][2]*1.5;
                        temp2 += Fuzzy_coef.Fi_coef[i][2];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][0]*1.5;
                        temp2 += Fuzzy_coef.Delta_coef[i][0];
                    }
                    else if(Fuzzy_coef.Delta_coef[i][1] != 0 )
                    {
                        temp1 += Fuzzy_coef.Delta_coef[i][1]*1.5;
                        temp2 += Fuzzy_coef.Delta_coef[i][1];
                    }
                    //rule3
                    if(Fuzzy_coef.Fi_coef[i][0] != 0 )
                    {
                        temp1 += Fuzzy_coef.Fi_coef[i][0]*3.0;
                        temp2 += Fuzzy_coef.Fi_coef[i][0];
                    }
                    
                    if(temp2 == 0.0)
                        Fuzzy_coef.Cognitive[i] = 0.0;
                    else
                        Fuzzy_coef.Cognitive[i] = temp1/temp2;
                }
            }

            void Update_Velocity(int pop,int DIM)
            {
                for(int i=0;i<pop;i++)
                {
                    
                    for(int j=0;j<DIM;j++)
                    {
                        double r1 = (1.0 - 0.0) * rand() / (RAND_MAX + 1.0) + 0.0;
                        double r2 = (1.0 - 0.0) * rand() / (RAND_MAX + 1.0) + 0.0;

                        PSO_inf.Velocity[i][j] = Fuzzy_coef.Inerlia[i] * PSO_inf.Velocity[i][j]\
                        +Fuzzy_coef.Cognitive[i] * r1 *(Personal_inf.Personal_Best_Coordinate[i][j] - PSO_inf.Particle[i][j] )\
                        +Fuzzy_coef.Social[i] * r2 *(Current_inf.Current_Best_Coordinate[j] - PSO_inf.Particle[i][j] );

                        // if(PSO_inf.Velocity[i][j] > 0.2*(boundaries.max[j]-boundaries.min[j]))
                        //     PSO_inf.Velocity[i][j] = 0.2*(boundaries.max[j]-boundaries.min[j]);
                        // else if(PSO_inf.Velocity[i][j] < -0.2*(boundaries.max[j]-boundaries.min[j]))
                        //     PSO_inf.Velocity[i][j] = -0.2*(boundaries.max[j]-boundaries.min[j]);
                        if(PSO_inf.Velocity[i][j] > 0.2*(max - min))
                            PSO_inf.Velocity[i][j] = 0.2*(max - min);
                        else if(PSO_inf.Velocity[i][j] < -0.2*(max - min))
                            PSO_inf.Velocity[i][j] = -0.2*(max - min);
                    }
                }
            }
            void Update_Position(int pop,int DIM)
            {
                 for(int i=0;i<pop;i++)
                {
                    for(int j=0;j<DIM;j++)
                    {
                       PSO_inf.Previous_Particle[i][j] =  PSO_inf.Particle[i][j];
                       PSO_inf.Particle[i][j] += PSO_inf.Velocity[i][j] ;

                        if(PSO_inf.Particle[i][j] > max)
                            PSO_inf.Particle[i][j] = boundaries.max[j];
                        else if(PSO_inf.Particle[i][j] < min)
                            PSO_inf.Particle[i][j] = boundaries.min[j];
                    }
                }
            }
            void Find_Boundaries(int pop,int DIM)
            {
                d1d temp_min(DIM,max);
                d1d temp_max(DIM,min);
                for(int i=0;i<pop;i++)
                {
                    for(int j=0;j<DIM;j++)
                    {
                       if(Personal_inf.Personal_Best_Coordinate[i][j] < temp_min[j])
                            temp_min[j] = Personal_inf.Personal_Best_Coordinate[i][j];
 
                      
                        else if(Personal_inf.Personal_Best_Coordinate[i][j] > temp_max[j])
                            temp_max[j] = Personal_inf.Personal_Best_Coordinate[i][j];
                    }
                }
                boundaries.max = temp_max;
                boundaries.min = temp_min;

            }
            void Evaluation(int pop,int DIM,int F,int F_T)
            {
                for(int i=0;i<pop;i++)
                {   
                    
                    PSO_inf.Previous_Objective[i] = PSO_inf.Objective[i];
                    // CEC21::cec21_cal(&PSO_inf.Particle[i][0], PSO_inf.Objective[i], DIM,F,F_T);
                    CEC17::cec17_cal(&PSO_inf.Particle[i][0],&PSO_inf.Objective[i], DIM,F);
                    NFE++;

                    if(PSO_inf.Objective[i] < Personal_inf.Personal_Best_Value[i])
                    {
                        Personal_inf.Personal_Best_Value[i] = PSO_inf.Objective[i];
                        Personal_inf.Personal_Best_Coordinate[i].assign(PSO_inf.Particle[i].begin(),PSO_inf.Particle[i].end());

                        if(PSO_inf.Objective[i] < Current_inf.Current_Best_Value)
                        {
                            Current_inf.Current_Best_Value = PSO_inf.Objective[i];
                            Current_inf.Current_Best_Coordinate.assign(PSO_inf.Particle[i].begin(),PSO_inf.Particle[i].end());
                        }
                    }


                    if ( PSO_inf.Objective[i] > Current_Worst_Value )
                    {
                        Current_Worst_Value = PSO_inf.Objective[i];
                    }
                    
                    
                }
            }
     
        void OUTPUT(int DIM,int Function,int F_T,int MAX_NFE,int run,double START,double END)
        {
           
            double STD = 0;
            double AVG = 0;
            for(int i=0;i<run;i++)
            {
                AVG+= Each_Run_Result[i];

               
            }
            AVG /= run;
   
            for(int i=0;i<run;i++)
            {
                STD += pow(Each_Run_Result[i]-AVG,2);
                STD /= run;
                STD = sqrt(STD);
            }
            
            cout<<"# CEC Testing Function : "<<Function<<endl;
            cout<<"# CEC Transform : "<<F_T<<endl;
            cout<<"# Run : "<<run<<endl;
            cout<<"# Evaluation : "<<MAX_NFE<<endl;
            cout<<"# Dimension : "<<DIM<<endl;
            cout<<"# Average Objective Value :"<<endl<<AVG<<endl;
            cout<<"# Std :"<<endl<<STD<<endl;
            cout<<"# Execution Time :"<<endl<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
            // CEC21::CEC_Classify(Function,F_T,START,END,STD,AVG,DIM);
            CEC17::CEC_Classify(Function,START,END,STD,AVG,DIM);
            // CEC21::Run_Classify(&Each_Run_Result[0],Function,F_T,run,DIM);
            CEC17::Run_Classify(&Each_Run_Result[0],Function,run,DIM);
        }
    
};


