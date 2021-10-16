#include<iostream>
#include<map>
#include<utility>
#include<vector>
#include<cmath>
#include"Quickhull.h"
using namespace std;


vector<pair<float,float> > hull;

//this will take the points on the current line and a point and determine which side of the line it is on
// PRECONDITION: input P1 and P2 are points that create the line, P is the farthest point from P1 and P2
//POST CONDITION: returns 1 if it is above the line or -1 if it is below 
int findSide(pair<float,float> P1,pair<float,float> P2,pair<float,float> P){
    float val;
    val = (P.second - P1.second) * (P2.first - P1.first) -
              (P2.second - P1.second) * (P.first - P1.first);
    if (val > 0)
        return 1;
    if(val < 0)
        return -1;
    return 0; 
    
}

//this will find the distance of a point from the line
float lineDist(pair<float,float> P1,pair<float,float> P2,pair<float,float> P){
    return abs((P.second - P1.second) * (P2.first - P1.first) -
               (P2.second - P1.second) * (P.first - P1.first));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(vector<pair<float,float> > V, int n, pair<float,float> p1, pair<float,float> p2, int side)
{
    int ind = -1;
    int max_dist = 0;
  
    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2,V[i] );
        if (findSide(p1, p2, V[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }
  
    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.push_back(p1);
        hull.push_back(p2);
        return;
    }
  
    // Recur for the two parts divided by a[ind]
    quickHull(V, n, V[ind], p1, -findSide(V[ind], p1, p2));
    quickHull(V, n, V[ind], p2, -findSide(V[ind], p2, p1));
}