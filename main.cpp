#include<iostream>
#include<map>
#include<utility>
#include<vector>
#include<cmath>
#include <algorithm>

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
double lineDist(pair<float,float> p1,pair<float,float> p2,pair<float,float> p){
    
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(vector<pair<float,float> > V, int n, pair<float,float> p1, pair<float,float> p2, int side)
{
   
    int ind = -1;
    float max_dist = 0;
    //cout << "side: " << side << endl;
  
    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i < n; i++)
    {
        double temp = lineDist(p1, p2,V[i] );
        //cout << "temp" << temp << endl;
        if (findSide(p1, p2, V[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }
    bool inHull;
    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
       for(int i =0;i<hull.size();i++){
           if(hull[i].first == p1.first && hull[i].second == p1.second){
               inHull=true;
               cout << "inHull " << hull[i].first << endl;
           }
           if(hull[i].first == p2.first && hull[i].second == p2.second){
               inHull=true;
               cout << "inHull " << hull[i].first << endl;
           }

       }
      

       
       if(inHull!= true){
            hull.push_back(p1);
            hull.push_back(p2);

            return;
       }
       return;

    }

        
        
    
  
    // Recur for the two parts divided by a[ind]
    //cout << "recusrivce" << endl;
    quickHull(V, n, V[ind], p1, -findSide(V[ind], p1, p2));
    quickHull(V, n, V[ind], p2, -findSide(V[ind], p2, p1));
}



int main(){

//extract input
int n;
cin >> n;



//if


//map for indexed to coordinates
map<pair<float, float>, int > indexes;
//create vector to hold coordinates
vector<pair<float,float> > cVector;

//variable for pairs of coordinates

for(int i =0; i < n;  i++)
{
    //int d;
    float f;
    char s;
    float c;
   cin  >> f >> s >> c;

   //make each coordinate into pairs
   pair<float,float> coor;
   coor = make_pair(f,c);
   //add coordinates to map, mapping to index
   //indexes[coor]= d;

   // add pairs to vector
   cVector.push_back(coor);
  

}


if(n==1){
    //hull = cVector[0]
}
//if there are only two points, they are the convex hull
if(n == 2){
    hull.push_back(cVector[0]);
    hull.push_back(cVector[1]);
}

if(n==3){
    //see if they are a line, if so take out middle one 
}

//find min and max x coordinates
float max_x, min_x = 0;
for(int i = 1; i < n ; i++){
    if(cVector[i].first < cVector[min_x].first){
        min_x = i;
    }
    if(cVector[i].first > cVector[max_x].first){
        max_x = i;
    }
    
   
   
}

quickHull(cVector, n, cVector[min_x], cVector[max_x], 1);
quickHull(cVector, n, cVector[min_x], cVector[max_x], -1);

cout<< hull.size() << "size" << endl;

for(int i = 0; i < hull.size(); i++){
    cout << hull[i].first << endl;
}








return 0;
}


