#include <iostream>
#include <stdlib.h>
#include <cstdlib> //rand()
#include <ctime> //time()
#include <string.h> //memset()
#include <iomanip>


#define TIMELIMIT 5 //time unit limit
#define MAX_ARR 1001

#define LD_MAX 3//landing max
#define LD_MIN 0 //landing min

#define TO_MAX 3 //takeoff max
#define TO_MIN 0 //takeoff min

#define FL_MAX 10 //fuel level max
#define FL_MIN 1  //fuel level min


#define LANDING 6
#define TAKEOFF 4
#define RUNWAY 4

using namespace std;

int Random(int MAX, int MIN)
{
          return (rand() % (MAX - MIN + 1) + MIN);
}

void Output(int RW[RUNWAY], int LD[LANDING][MAX_ARR][2], int LD_count[LANDING], int TO[TAKEOFF][MAX_ARR], int TO_count[TAKEOFF])
{

          for (int rw = 0; rw < RUNWAY; rw++)
          {
                    cout << endl;
                    cout << "Runway" << rw+1 << " (" << RW[rw] << ")" << endl;
                    for (int l = 1; l <= 2; l++)
                    {
                              cout << "L" << l << ": ";
                              int n;
                              if (rw != 0)
                              {
                                        if (l == 1)
                                        {
                                                  n = rw - 1;
                                        }
                                        else n = rw + 2;
                                        for (int i = 0; i < LD_count[n]; i++)
                                        {
                                                  cout << "(" << LD[n][i][0] << ", " << LD[n][i][1] << "), ";
                                        }
                              }
                              cout << endl;
                    }

                    cout << "T: ";
                    int n;
                    n = rw;
                    for (int i = 0; i < TO_count[n]; i++)
                    {
                              cout << "(" << TO[n][i] << "), ";
                    }
                    cout << endl;
          }
          cout << "________________________________________________" << endl;
}

void Ending(float avgLDwt, float avgTOwt, float avgFLs, int pe, int pc)
{
          cout << std::setprecision(4);
          cout << "How Many Time Unit You Want to Simulate: " << TIMELIMIT << endl;
          cout << "average landing waiting time: " << avgLDwt << "(s)" << endl;
          cout << "average takeoff waiting time: " << avgTOwt << "(s)" << endl;
          cout << "average fuel saved: " << avgFLs << "(s)" << endl;
          cout << "total plane in emergency: " << pe <<endl;
          cout << "total plane crased: " << pc << endl;

}

void FuelLevel(int nld, int WT[MAX_ARR][3], int LD_count[LANDING], int LD[LANDING][MAX_ARR][2], int &ppc)
{
          for (int i = 0; i < nld; i++)
          {
                    WT[i][1]--;
                    if (WT[i][1] < 0)
                    {
                              ppc++;
                    }
          }
          for (int ld = 0; ld < 6; ld++)
          {
                    for (int i = 0; i < LD_count[ld]; i++)
                    {
                              LD[ld][i][1]--;
                    }
          }
}

void WTArr(int index, int nld, int WT[MAX_ARR][3])
{
          for (int i = index+1; i < nld; i++)
          {
                    WT[i-1][0] = WT[i][0];
                    WT[i-1][1] = WT[i][1];
                    WT[i-1][2] = WT[i][2];
          }
}

void LDArr(int index, int ld, int n, int LD[LANDING][MAX_ARR][2])
{
          for (int i = index+1; i < n; i++)
          {
                    LD[ld][i-1][0] = LD[ld][i][0];
                    LD[ld][i-1][1] = LD[ld][i][1];
          }
}

void TOArr(int index, int to, int n, int TO[TAKEOFF][MAX_ARR])
{
          for (int i = index+1; i < n; i++)
          {
                    TO[to][i-1] = TO[to][i];
          }
}

int main()
{
          srand(time(NULL)); //use for rand()

          int RW[RUNWAY];
          int nld = 0, WT[MAX_ARR][3], N_LD = -1, LD[LANDING][MAX_ARR][2], LD_count[LANDING];
          int nto = 0, N_TO = -1, TO[TAKEOFF][MAX_ARR], TO_count[TAKEOFF];
          int LDwtt = 0, TOwtt = 0, FLs = 0;
          int pe = 0, pc = 0;
          //Fill Array
          memset(LD_count, 0, sizeof(LD_count));
          memset(TO_count, 0, sizeof(TO_count));

          //Run
          for (int time_unit = 1; time_unit <= TIMELIMIT; time_unit++) //5
          {
                    cout <<"Simulation Time: " << time_unit << endl;

                    memset(RW,-1,sizeof(RW)); //Fill Array RW
                    int t = 0; //use in step 3 choose runway
                    Output(RW, LD, LD_count, TO, TO_count);

                    for (int step = 1; step <= 4; step++) //4 step
                    {
                              cout << "Step " << step <<":" << endl;
                              if (step == 1) //STEP 1
                              {
                                        cout << "landing plane: ";
                                        int LD_random = Random(LD_MAX, LD_MIN);
                                        for (int i = 0; i < LD_random; i++)
                                        {
                                                  N_LD++;
                                                  int id = 2*N_LD+1; //odd
                                                  int fl = Random(FL_MAX, FL_MIN);
                                                  cout << "(" << id << "," << fl << "), "; //(id, fl)

                                                  int index = 0;
                                                  for (int k = 0; k < 6; k++) //choose landing queue
                                                  {
                                                            if (LD_count[index] > LD_count[k])
                                                            {
                                                                      index = k;
                                                            }
                                                  }
                                                  LD[index][LD_count[index]][0] = id;
                                                  LD[index][LD_count[index]][1] = fl;
                                                  LD_count[index]++;

                                                  WT[nld][0] = id;
                                                  WT[nld][1] = fl;
                                                  WT[nld][2] = index; //landing queue
                                                  nld++;
                                        }
                                        cout << endl;
                              }
                              else if (step == 2) //STEP 2
                              {
                                        cout << "takeoff plane: ";
                                        int TO_random = Random(TO_MAX, TO_MIN);
                                        for (int i = 0; i < TO_random; i++)
                                        {
                                                  N_TO++;
                                                  cout << "(" << 2*N_TO << "), ";
                                                  int index = 0;
                                                  for (int k = 0; k < 4; k++) //choose takeoff queue
                                                  {
                                                            if (TO_count[index] > TO_count[k])
                                                            {
                                                                      index = k;
                                                            }
                                                  }
                                                  TO[index][TO_count[index]] = 2*N_TO;
                                                  TO_count[index]++; //takeoff queue
                                                  nto++;
                                        }
                                        cout << endl;
                              }
                              else if (step == 3) //STEP 3
                              {
                                        cout << "emergency plane: ";
                                        int index = 0;
                                        while (index < nld)
                                        {
                                                  int id = WT[index][0];
                                                  int fl = WT[index][1];
                                                  int ld = WT[index][2];
                                                  if (fl == 0)
                                                  {
                                                            while (RW[t] != -1) //choose runway
                                                            {
                                                                      t++;
                                                            }
                                                            if  (t <= 3)
                                                            {
                                                                      RW[t] = id;
                                                            }
                                                            cout << "(" << id << "), ";
                                                            pe++;
                                                            for (int i = 0; i < LD_count[ld]; i++)
                                                            {
                                                                      if (LD[ld][i][0] == id)
                                                                      {
                                                                                LDArr(i, ld, LD_count[ld], LD);
                                                                                LD_count[ld]--;
                                                                                break;
                                                                      }
                                                            }
                                                            WTArr(index, nld, WT);
                                                            nld--;
                                                  }
                                                  else
                                                  {
                                                            index++;
                                                  }
                                        }
                                        cout << endl;
                              }
                              else if (step == 4)
                              {
                                        for (int rw = 0; rw < RUNWAY; rw++)
                                        {
                                                  if (RW[rw] != -1)
                                                  {
                                                            continue;
                                                  }

                                                  int minFL = FL_MAX+1;
                                                  int minLD;
                                                  int minIndex;

                                                  if (rw == 0 && TO_count[rw] != 0)
                                                  {
                                                            RW[rw] = TO[rw][0];
                                                            TOArr(0, rw, TO_count[rw], TO);
                                                            TO_count[rw]--;
                                                            nto--;
                                                            continue;
                                                  }
                                                  else if (rw != 0)
                                                  {
                                                            int ld;
                                                            for (int l = 1; l <= 2; l++) //find airplane in landing queue
                                                            {
                                                                      if (l == 1)
                                                                      {
                                                                                ld = rw - 1;
                                                                      }
                                                                      else ld = rw+2;
                                                                      for (int i = 0; i < LD_count[ld]; i++)
                                                                      {
                                                                                if (LD[ld][i][1] < minFL)
                                                                                {
                                                                                          RW[rw] = LD[ld][i][0];
                                                                                          minFL = LD[ld][i][1];
                                                                                          minLD = ld;
                                                                                          minIndex = i;
                                                                                }
                                                                      }
                                                            }

                                                            if ((minFL < LD_count[rw-1]+LD_count[rw+2] || nld >= nto || TO_count[rw] == 0) && RW[rw] != -1)
                                                            {
                                                                      int index;
                                                                      FLs+=minFL;
                                                                      LDArr(minIndex, minLD, LD_count[minLD], LD);
                                                                      LD_count[minLD]--;
                                                                      for (int i = 0; i < nld; i++)
                                                                      {
                                                                                if (WT[i][0] == RW[rw])
                                                                                {
                                                                                          index = i;
                                                                                          break;
                                                                                }
                                                                      }
                                                                      WTArr(index, nld, WT);
                                                                      nld--;
                                                            }
                                                            else if (TO_count[rw] > 0)
                                                            {
                                                                      RW[rw] = TO[rw][0];
                                                                      TOArr(0, rw, TO_count[rw], TO);
                                                                      TO_count[rw]--;
                                                                      nto--;
                                                            }
                                                  }
                                        }
                              }
                              Output(RW, LD, LD_count, TO, TO_count);
                    }
                    FuelLevel(nld, WT, LD_count, LD,pc);
                    LDwtt+=nld;
                    TOwtt+=nto;
                    cout << "############################################" << endl << endl;
          }
          //Ending
          float avgLDwt, avgTOwt, avgFLs;
          avgLDwt = (float)LDwtt/(N_LD-nld+1);
          avgTOwt = (float)TOwtt/(N_TO-nto+1);
          avgFLs = (float)FLs/(N_LD-nld+1);
          Ending(avgLDwt, avgTOwt, avgFLs, pe, pc);
          return 0;
}
