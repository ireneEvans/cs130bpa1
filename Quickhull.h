#include<iostream>
using namespace std;



int findSide(pair<float,float> P1,pair<float,float> P2,pair<float,float> P);
float lineDist(pair<float,float> P1,pair<float,float> P2,pair<float,float> P);
void quickHull(vector<pair<float,float> > V, int n, pair<float,float> p1, pair<float,float> p2, int side);
