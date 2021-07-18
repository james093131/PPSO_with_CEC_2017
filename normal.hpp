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
typedef vector<double> d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

// class PPSO : CEC21{
class PPSO : CEC17
{

public:
    d1d Each_Run_Evaluation_Best;
    d1d Each_Run_Result;

public:
    void Run(int run, int MAX_NFE, int pop, int DIM, int FunctionNumber, int FunctionTransform)
    {
        srand((unsigned)time(NULL));
        INI_RUN(run);
        int r = 0;
        double START, END;
        START = clock();
        while (r < run)
        {
            INI(DIM, pop);

            for (int i = 0; i < pop; i++)
            {
                RANDOM_INI(DIM, i, PSO_inf.Particle);
            }
            Evaluation(pop, DIM, FunctionNumber, FunctionTransform);

            while (NFE < MAX_NFE)
            {
                Update_phi(pop, DIM);
                Update_delta(pop, DIM);
                Fuzzy_rules(pop);
                Set_Inertia(pop);
                Set_Social(pop);
                Set_Cognitive(pop);

                Update_Velocity(pop, DIM);
                Update_Position(pop, DIM);
                Evaluation(pop, DIM, FunctionNumber, FunctionTransform);
                // CEC17::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);
                // CEC21::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);
            }

            // CEC17::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);
            // CEC21::CEC_Results_Records(NFE,MAX_NFE,Current_inf.Current_Best_Value,&Each_Run_Evaluation_Best[0]);

            Each_Run_Result[r] = Current_inf.Current_Best_Value;
            r++;
        }
        END = clock();
        OUTPUT(DIM, FunctionNumber, FunctionTransform, MAX_NFE, run, START, END);
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
    struct Current_Inf
    {
        double Current_Best_Value;
        d1d Current_Best_Coordinate;
        double Current_Worst_Value;
        d1d Current_Worst_Coordinate;
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
        d1d Inertia;
        d1d Social;
        d1d Cognitive;
    };
    Current_Inf Current_inf;
    Personal_best Personal_inf;
    PSO_Parameter PSO_inf;
    Fuzzy Fuzzy_coef;
    double max = 100.0;
    double min = -100.0;
    double Delta_MAX;
    int NFE = 0;

private:
    void RANDOM_INI(int DIM, int index, d2d &arr)
    {

        for (int i = 0; i < DIM; i++)
        {
            double a = ((max - min) * randDouble()) + min;

            arr[index][i] = a;
        }
    }
    void INI(int DIM, int pop)
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

        Current_inf.Current_Worst_Coordinate.clear();
        Current_inf.Current_Worst_Coordinate.swap(Current_inf.Current_Worst_Coordinate);

        Fuzzy_coef.Fi_coef.clear();
        Fuzzy_coef.Fi_coef.swap(Fuzzy_coef.Fi_coef);

        Fuzzy_coef.Delta_coef.clear();
        Fuzzy_coef.Delta_coef.swap(Fuzzy_coef.Delta_coef);

        Fuzzy_coef.Inertia.clear();
        Fuzzy_coef.Inertia.swap(Fuzzy_coef.Inertia);

        Fuzzy_coef.Social.clear();
        Fuzzy_coef.Social.swap(Fuzzy_coef.Social);

        Fuzzy_coef.Cognitive.clear();
        Fuzzy_coef.Cognitive.swap(Fuzzy_coef.Cognitive);

        PSO_inf.Particle.assign(pop, d1d(DIM));
        PSO_inf.Velocity.assign(pop, d1d(DIM, 0));
        PSO_inf.Objective.resize(pop, -1);
        PSO_inf.Previous_Particle.assign(pop, d1d(DIM, 0));
        PSO_inf.Previous_Objective.resize(pop, DBL_MAX);
        PSO_inf.delta.resize(pop);
        PSO_inf.phi.resize(pop);

        Current_inf.Current_Best_Coordinate.resize(DIM);
        Current_inf.Current_Best_Value = DBL_MAX;
        Current_inf.Current_Worst_Coordinate.resize(DIM);
        Current_inf.Current_Worst_Value = 0;

        Personal_inf.Personal_Best_Coordinate.assign(pop, d1d(DIM));
        Personal_inf.Personal_Best_Value.resize(pop, DBL_MAX);

        max = 100.0;
        min = -100.0;
        NFE = 0;

        Fuzzy_coef.Fi_coef.assign(pop, d1d(3));
        Fuzzy_coef.Delta_coef.assign(pop, d1d(3));
        Fuzzy_coef.Inertia.resize(pop, 0);
        Fuzzy_coef.Social.resize(pop, 0);
        Fuzzy_coef.Cognitive.resize(pop, 0);

        Delta_MAX = 0;
        for (int i = 0; i < DIM; i++)
        {
            Delta_MAX += pow((max - min), 2);
        }

        Delta_MAX = sqrt(Delta_MAX);
    }
    void INI_RUN(int run)
    {
        Each_Run_Evaluation_Best.resize(14, 0);
        Each_Run_Result.resize(run, DBL_MAX);
    }

    inline double randDouble()
    {
        return (double)rand() / (double)RAND_MAX;
    }

    double delta_cal(int index, int DIM)
    {
        double DIS = 0.0;

        for (int i = 0; i < DIM; i++)
        {
            DIS += pow((PSO_inf.Particle[index][i] - PSO_inf.Previous_Particle[index][i]), 2);
        }

        DIS = sqrt(DIS);

        return DIS;
    }
    double delta_cal(int index, int DIM, d1d global)
    {
        double DIS = 0.0;

        for (int i = 0; i < DIM; i++)
        {
            DIS += pow((PSO_inf.Particle[index][i] - global[i]), 2);
        }

        DIS = sqrt(DIS);

        return DIS;
    }
    void Update_phi(int pop, int DIM)
    {
        for (int i = 0; i < pop; i++)
        {
            double f1 = (Current_inf.Current_Worst_Value < PSO_inf.Objective[i]) ? Current_inf.Current_Worst_Value : PSO_inf.Objective[i];
            double f2 = (Current_inf.Current_Worst_Value < PSO_inf.Previous_Objective[i]) ? Current_inf.Current_Worst_Value : PSO_inf.Previous_Objective[i];
            double dis;
            if (f2 == Current_inf.Current_Worst_Value)
            {
                f2 = Current_inf.Current_Worst_Value;
                dis = delta_cal(i, DIM, Current_inf.Current_Worst_Coordinate);
            }
            else
            {
                dis = delta_cal(i, DIM);
            }

            double delta_f = Current_inf.Current_Worst_Value;
            if (delta_f < 0)
                delta_f = -delta_f;

            PSO_inf.phi[i] = ((f1 - f2) / delta_f) * (dis / Delta_MAX);
            // cout<<" PHI " <<PSO_inf.phi[i]<<endl;
        }
    }
    void Update_delta(int pop, int DIM)
    {
        for (int i = 0; i < pop; i++)
        {
            PSO_inf.delta[i] = delta_cal(i, DIM, Current_inf.Current_Best_Coordinate);
            //    cout<<" DEL " <<PSO_inf.delta[i]/Delta_MAX<<endl;
        }
    }
    void Fuzzy_rules(int pop)
    {
        double delta1 = 0.05;
        double delta2 = 0.10;
        double delta3 = 0.15;

        double phi1 = -0.0025;
        double phi2 = 0.0025;
        for (int i = 0; i < pop; i++)
        {
            // phi
            //better
            if (PSO_inf.phi[i] == -1.0)
                Fuzzy_coef.Fi_coef[i][0] = 1.0;
            else if (PSO_inf.phi[i] > -1.0 && PSO_inf.phi[i] < 0.0)
                Fuzzy_coef.Fi_coef[i][0] = -PSO_inf.phi[i];
            else if (PSO_inf.phi[i] >= 0.0 && PSO_inf.phi[i] <= 1.0)
                Fuzzy_coef.Fi_coef[i][0] = 0.0;

            //unvaried
            if (PSO_inf.phi[i] >= -1.0 && PSO_inf.phi[i] < phi1)
                Fuzzy_coef.Fi_coef[i][1] = 0.0;
            else if (PSO_inf.phi[i] >= phi1 && PSO_inf.phi[i] < 0.0)
                Fuzzy_coef.Fi_coef[i][1] = (phi1 - PSO_inf.phi[i]) / phi1;
            else if (PSO_inf.phi[i] >= 0.0 && PSO_inf.phi[i] < phi2)
                Fuzzy_coef.Fi_coef[i][1] = (phi2 - PSO_inf.phi[i]) / phi2;
            else if (PSO_inf.phi[i] >= phi2 && PSO_inf.phi[i] <= 1.0)
                Fuzzy_coef.Fi_coef[i][1] = 0.0;

            //worse
            if (PSO_inf.phi[i] >= -1.0 && PSO_inf.phi[i] < 0.0)
                Fuzzy_coef.Fi_coef[i][2] = 0.0;
            else if (PSO_inf.phi[i] >= 0.0 && PSO_inf.phi[i] < 1)
                Fuzzy_coef.Fi_coef[i][2] = PSO_inf.phi[i];
            else if (PSO_inf.phi[i] == 1.0)
                Fuzzy_coef.Fi_coef[i][2] = 1.0;

            //delta
            //low
            if (PSO_inf.delta[i] / Delta_MAX >= 0.0 && PSO_inf.delta[i] / Delta_MAX < delta1)
                Fuzzy_coef.Delta_coef[i][0] = 1.0;
            else if (PSO_inf.delta[i] / Delta_MAX >= delta1 && PSO_inf.delta[i] / Delta_MAX < delta2)
                Fuzzy_coef.Delta_coef[i][0] = (delta2 - PSO_inf.delta[i] / Delta_MAX) / (delta2 - delta1);
            else if (PSO_inf.delta[i] / Delta_MAX >= delta2 && PSO_inf.delta[i] / Delta_MAX <= 1.0)
                Fuzzy_coef.Delta_coef[i][0] = 0.0;

            //medium
            if (PSO_inf.delta[i] / Delta_MAX >= 0.0 && PSO_inf.delta[i] / Delta_MAX < delta1)
                Fuzzy_coef.Delta_coef[i][1] = 0.0;
            else if (PSO_inf.delta[i] / Delta_MAX >= delta1 && PSO_inf.delta[i] / Delta_MAX < delta2)
                Fuzzy_coef.Delta_coef[i][1] = (PSO_inf.delta[i] / Delta_MAX - delta1) / (delta2 - delta1);
            else if (PSO_inf.delta[i] / Delta_MAX >= delta2 && PSO_inf.delta[i] / Delta_MAX < delta3)
                Fuzzy_coef.Delta_coef[i][1] = (delta3 - PSO_inf.delta[i] / Delta_MAX) / (delta3 - delta2);
            else if (PSO_inf.delta[i] / Delta_MAX >= delta3 && PSO_inf.delta[i] / Delta_MAX <= 1.0)
                Fuzzy_coef.Delta_coef[i][1] = 0.0;
            //high
            if (PSO_inf.delta[i] >= 0.0 && PSO_inf.delta[i] / Delta_MAX < delta2)
                Fuzzy_coef.Delta_coef[i][2] = 0.0;
            else if (PSO_inf.delta[i] / Delta_MAX >= delta2 && PSO_inf.delta[i] / Delta_MAX < delta3)
                Fuzzy_coef.Delta_coef[i][2] = (PSO_inf.delta[i] / Delta_MAX - delta2) / (delta3 - delta2);
            else if (PSO_inf.delta[i] / Delta_MAX >= delta3 && PSO_inf.delta[i] / Delta_MAX <= 1.0)
                Fuzzy_coef.Delta_coef[i][2] = 1.0;
        }
    }

    double Ternary_operation(double a, double b, double c)
    {

        double R = (a > b ? a : b) > (b > c ? b : c) ? (a > b ? a : b) : (b > c ? b : c);
        return R;
    }
    void Set_Inertia(int pop)
    {
        for (int i = 0; i < pop; i++)
        {
            double temp1 = 0.0;
            double temp2 = 0.0;

            //rule 1
            // double r1 = Ternary_operation(Fuzzy_coef.Fi_coef[i][2], Fuzzy_coef.Delta_coef[i][1], Fuzzy_coef.Delta_coef[i][2]);
            // temp1 += r1 * 0.3;
            // temp2 += r1;

            temp1 += Fuzzy_coef.Fi_coef[i][2] * 0.3;
            temp2 += Fuzzy_coef.Fi_coef[i][2];

            temp1 += Fuzzy_coef.Delta_coef[i][1] * 0.3;
            temp2 += Fuzzy_coef.Delta_coef[i][1];

            temp1 += Fuzzy_coef.Delta_coef[i][2] * 0.3;
            temp2 += Fuzzy_coef.Delta_coef[i][2];

            //rule2
            // double r2 = (Fuzzy_coef.Fi_coef[i][1] > Fuzzy_coef.Delta_coef[i][0]) ? Fuzzy_coef.Fi_coef[i][1] : Fuzzy_coef.Delta_coef[i][0];
            // temp1 += r2 * 0.5;
            // temp2 += r2;

            temp1 += Fuzzy_coef.Fi_coef[i][1] * 0.5;
            temp2 += Fuzzy_coef.Fi_coef[i][1];

            temp1 += Fuzzy_coef.Delta_coef[i][0] * 0.5;
            temp2 += Fuzzy_coef.Delta_coef[i][0];

            //rule3
            // double r3 = Fuzzy_coef.Fi_coef[i][0];
            // temp1 += r3 * 1.0;
            // temp2 += r3;

            temp1 += Fuzzy_coef.Fi_coef[i][0] * 1.0;
            temp2 += Fuzzy_coef.Fi_coef[i][0];

            // cout<<"WEIGHT "<<temp2<<endl;
            Fuzzy_coef.Inertia[i] = temp1 / temp2;

            // cout<<PSO_inf.phi[i]<<' '<<PSO_inf.delta[i]/Delta_MAX<<' '<<Fuzzy_coef.Inertia[i]<<endl;
        }
    }
    void Set_Social(int pop)
    {
        for (int i = 0; i < pop; i++)
        {
            double temp1 = 0.0;
            double temp2 = 0.0;
            //rule 1

            // double s1 = (Fuzzy_coef.Fi_coef[i][0] > Fuzzy_coef.Delta_coef[i][1]) ? Fuzzy_coef.Fi_coef[i][0] : Fuzzy_coef.Delta_coef[i][1];
            // temp1 += s1 * 0.1;
            // temp2 += s1;

            temp1 += Fuzzy_coef.Fi_coef[i][0] * 0.1;
            temp2 += Fuzzy_coef.Fi_coef[i][0];

            temp1 += Fuzzy_coef.Delta_coef[i][1] * 0.1;
            temp2 += Fuzzy_coef.Delta_coef[i][1];

            //rule2
            // double s2 = Fuzzy_coef.Fi_coef[i][1];
            // temp1 += s2 * 1.5;
            // temp2 += s2;
            temp1 += Fuzzy_coef.Fi_coef[i][1] * 1.5;
            temp2 += Fuzzy_coef.Fi_coef[i][1];

            //rule3
            // double s3 = Ternary_operation(Fuzzy_coef.Fi_coef[i][2], Fuzzy_coef.Delta_coef[i][0], Fuzzy_coef.Delta_coef[i][2]);
            // temp1 += s3 * 3.0;
            // temp2 += s3;

            temp1 += Fuzzy_coef.Fi_coef[i][2] * 3.0;
            temp2 += Fuzzy_coef.Fi_coef[i][2];

            temp1 += Fuzzy_coef.Delta_coef[i][0] * 3.0;
            temp2 += Fuzzy_coef.Delta_coef[i][0];

            temp1 += Fuzzy_coef.Delta_coef[i][2] * 3.0;
            temp2 += Fuzzy_coef.Delta_coef[i][2];

            Fuzzy_coef.Social[i] = temp1 / temp2;
            // cout<<" SOCIAL "<<Fuzzy_coef.Social[i]<<endl;
        }
    }

    void Set_Cognitive(int pop)
    {
        for (int i = 0; i < pop; i++)
        {
            double temp1 = 0.0;
            double temp2 = 0.0;
            //rule 1

            // double c1 = Fuzzy_coef.Delta_coef[i][2];
            // temp1 += c1 * 0.1;
            // temp2 += c1;

            temp1 += Fuzzy_coef.Delta_coef[i][2] * 0.1;
            temp2 += Fuzzy_coef.Delta_coef[i][2];

            //rule2
            // double c2 = Ternary_operation(Fuzzy_coef.Fi_coef[i][1], Fuzzy_coef.Fi_coef[i][2], Fuzzy_coef.Delta_coef[i][0]);
            // c2 = (c2 > Fuzzy_coef.Delta_coef[i][1]) ? c2 : Fuzzy_coef.Delta_coef[i][1];
            // temp1 += c2 * 1.5;
            // temp2 += c2;

            temp1 += Fuzzy_coef.Fi_coef[i][1] * 1.5;
            temp2 += Fuzzy_coef.Fi_coef[i][1];

            temp1 += Fuzzy_coef.Fi_coef[i][2] * 1.5;
            temp2 += Fuzzy_coef.Fi_coef[i][2];

            temp1 += Fuzzy_coef.Delta_coef[i][0] * 1.5;
            temp2 += Fuzzy_coef.Delta_coef[i][0];

            temp1 += Fuzzy_coef.Delta_coef[i][1] * 1.5;
            temp2 += Fuzzy_coef.Delta_coef[i][1];

            //rule3
            // double c3 = Fuzzy_coef.Fi_coef[i][0];
            // temp1 += c3 * 3.0;
            // temp2 += c3;
            temp1 += Fuzzy_coef.Fi_coef[i][0] * 3.0;
            temp2 += Fuzzy_coef.Fi_coef[i][0];

            Fuzzy_coef.Cognitive[i] = temp1 / temp2;

            // cout<<"CONG "<<Fuzzy_coef.Cognitive[i]<<endl;
        }
    }

    void Update_Velocity(int pop, int DIM)
    {
        for (int i = 0; i < pop; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                double r1 = randDouble();
                double r2 = randDouble();
                PSO_inf.Velocity[i][j] = Fuzzy_coef.Inertia[i] * PSO_inf.Velocity[i][j] + Fuzzy_coef.Social[i] * r1 * (Current_inf.Current_Best_Coordinate[j] - PSO_inf.Particle[i][j]) + Fuzzy_coef.Cognitive[i] * r2 * (Personal_inf.Personal_Best_Coordinate[i][j] - PSO_inf.Particle[i][j]);

                if (PSO_inf.Velocity[i][j] > 0.2 * (max - min))
                    PSO_inf.Velocity[i][j] = 0.2 * (max - min);
                else if (PSO_inf.Velocity[i][j] < -0.2 * (max - min))
                    PSO_inf.Velocity[i][j] = -0.2 * (max - min);
            }
        }
    }
    void boundary_damping(int Particle_index, int DIM, int out_dim)
    {
        double r1 = randDouble();
        for (int i = out_dim; i < DIM; i++)
        {
            if (i != out_dim)
            {
                PSO_inf.Particle[Particle_index][i] += PSO_inf.Velocity[Particle_index][i];

                if (PSO_inf.Particle[Particle_index][i] > max)
                {
                    PSO_inf.Particle[Particle_index][i] = max;
                    boundary_damping(Particle_index, DIM, i);
                    break;
                }
                else if (PSO_inf.Particle[Particle_index][i] < min)
                {
                    PSO_inf.Particle[Particle_index][i] = min;
                    boundary_damping(Particle_index, DIM, i);
                    break;
                }
            }
            else
            {
                PSO_inf.Velocity[Particle_index][i] = -r1 * (PSO_inf.Velocity[Particle_index][i]);
                PSO_inf.Particle[Particle_index][i] += PSO_inf.Velocity[Particle_index][i];
                if (PSO_inf.Particle[Particle_index][i] > max)
                {
                    PSO_inf.Particle[Particle_index][i] = max;
                    boundary_damping(Particle_index, DIM, i);
                    break;
                }
                else if (PSO_inf.Particle[Particle_index][i] < min)
                {
                    PSO_inf.Particle[Particle_index][i] = min;
                    boundary_damping(Particle_index, DIM, i);
                    break;
                }
            }
        }
    }
    void Record_previous_position(int pop, int DIM)
    {
        for (int i = 0; i < pop; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                PSO_inf.Previous_Particle[i][j] = PSO_inf.Particle[i][j];
            }
        }
    }
    void Update_Position(int pop, int DIM)
    {
        Record_previous_position(pop, DIM);
        for (int i = 0; i < pop; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                PSO_inf.Particle[i][j] += PSO_inf.Velocity[i][j];

                if (PSO_inf.Particle[i][j] > max)
                {
                    PSO_inf.Particle[i][j] = max;
                    boundary_damping(i, DIM, j);
                    break;
                }
                else if (PSO_inf.Particle[i][j] < min)
                {
                    PSO_inf.Particle[i][j] = min;
                    boundary_damping(i, DIM, j);
                    break;
                }
            }
        }
    }
    void Evaluation(int pop, int DIM, int F, int F_T)
    {
        for (int i = 0; i < pop; i++)
        {
            if (PSO_inf.Objective[i] != -1) //first run previous objective is empty
                PSO_inf.Previous_Objective[i] = PSO_inf.Objective[i];
            // CEC21::cec21_cal(&PSO_inf.Particle[i][0], PSO_inf.Objective[i], DIM,F,F_T);
            CEC17::cec17_cal(&PSO_inf.Particle[i][0], &PSO_inf.Objective[i], DIM, F);
            NFE++;

            if (PSO_inf.Objective[i] <= Personal_inf.Personal_Best_Value[i])
            {
                Personal_inf.Personal_Best_Value[i] = PSO_inf.Objective[i];
                Personal_inf.Personal_Best_Coordinate[i].assign(PSO_inf.Particle[i].begin(), PSO_inf.Particle[i].end());

                if (PSO_inf.Objective[i] <= Current_inf.Current_Best_Value)
                {
                    Current_inf.Current_Best_Value = PSO_inf.Objective[i];
                    Current_inf.Current_Best_Coordinate.assign(PSO_inf.Particle[i].begin(), PSO_inf.Particle[i].end());
                }
            }

            if (PSO_inf.Objective[i] > Current_inf.Current_Worst_Value)
            {
                Current_inf.Current_Worst_Value = PSO_inf.Objective[i];
                Current_inf.Current_Worst_Coordinate = PSO_inf.Particle[i];
            }
        }
    }

    void OUTPUT(int DIM, int Function, int F_T, int MAX_NFE, int run, double START, double END)
    {

        double STD = 0;
        double AVG = 0;
        for (int i = 0; i < run; i++)
        {
            AVG += Each_Run_Result[i];
        }
        AVG /= run;

        for (int i = 0; i < run; i++)
        {
            STD += pow(Each_Run_Result[i] - AVG, 2);
            STD /= run;
            STD = sqrt(STD);
        }

        cout << "# CEC Testing Function : " << Function << endl;
        cout << "# CEC Transform : " << F_T << endl;
        cout << "# Run : " << run << endl;
        cout << "# Evaluation : " << MAX_NFE << endl;
        cout << "# Dimension : " << DIM << endl;
        cout << "# Average Objective Value :" << endl
             << AVG << endl;
        cout << "# Std :" << endl
             << STD << endl;
        cout << "# Execution Time :" << endl
             << (END - START) / CLOCKS_PER_SEC << "(s)" << endl;
        // CEC21::CEC_Classify(Function,F_T,START,END,STD,AVG,DIM);
        CEC17::CEC_Classify(Function, START, END, STD, AVG, DIM);
        // CEC21::Run_Classify(&Each_Run_Result[0],Function,F_T,run,DIM);
        CEC17::Run_Classify(&Each_Run_Result[0], Function, run, DIM);
    }
};
