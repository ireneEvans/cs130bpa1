#include<iostream>
#include<map>
#include<utility>
#include<vector>
#include<cmath>
#include <algorithm>
#include<set>
#include<iterator>
#include"cmath"

using namespace std;



set<pair<float,float> > hull;

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
  
  
    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i < n; i++)
    {
        double temp = lineDist(p1, p2,V[i] );
        
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
      

       
       //if(inHull!= true){
            //hull.push_back(p1);
            //hull.push_back(p2);
            hull.insert(p1);
            hull.insert(p2);

            return;
      // }
       

    }

        
        
    
  
    // Recur for the two parts divided by a[ind]
  
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
  indexes[cVector[i]]=i;

}


bool oneLineX =false;


int X = 0;
//variable shows 1 if x coordinates are in one line and -1 if y

for(int i = 1; i < cVector.size(); i++){
    if(cVector[i-1].first==cVector[i].first){
         X++;
    }
}
if((X+1) == cVector.size()){
    oneLineX = true;
}


cout << oneLineX << endl;


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


vector<pair<float,float> > s(hull.size());
copy(hull.begin(),hull.end(),s.begin());




//find minimum y coordinate
float minx = 0;
float min_y = 0;
bool min_x_used= false;
float min =0;

//find minimum y coordinate and minimum x coordinate, 
//if there exists two equal min y coordinates then use min x 
for(int i = 1; i < s.size() ; i++){
    if(s[i].second < s[min].second){
        min = i;
    }
    if(s[i].first < s[minx].first){
        minx = i;
    }

}
for(int i = 0; i < s.size() ; i++){
    if(i!=min){
    if(s[i].second==s[min].second){
        min = minx;
        min_x_used = true;
    }
    }
}

//check if we are using min y or min x
//variable min will be used for whichever lowest x or y coordinate we end up using
if(min_x_used==true){
    min = minx;
}



//create map for angles that correspond to points and vector to hold angle values
map<float,pair<float, float> > angles;
vector<float> ang;

//find angle with respect to y
//s is my vector of points on the hull
for(int i =0;i < s.size();i++){
    float angle;

    //make sure not comparing the minimum y coordiante with itself
    if(i != min){
        if(s[i].second==s[min].second){
             angle = 90;
             
        }
        else{
           
            float diff = (s[min].second-s[i].second)/(s[min].first-s[i].first);
        
             angle = atan(diff);
            
            angle = angle * (180/M_PI);
            
            if(angle<0){
                angle = angle + 180;
            }
            
        }
       

    //add angle to mao and vector
    
    angles[angle]=s[i];
    ang.push_back(angle);
    }
   
    
}
//sort vector of angles
sort(ang.begin(),ang.end());



cout << s.size() << endl;
cout << indexes[s[min]] << ", " << s[min].first << ", " << s[min].second << endl;

//go through sorted angle vector and use map to find cooresponding points and print in order
for(int i = 0; i< s.size()-1;i++){
    float a = ang[i];
  
   cout<< indexes[angles[a]] << ", " << angles[a].first << ", " << angles[a].second << endl;
}

//final cout











return 0;
}


