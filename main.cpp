#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <bitset>
#include <stdio.h> /* printf, fgets */
#include <stdlib.h>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;

/*
a b 
c d e
f g h

0 1 2
3 4 5
6 7 8

ab-cdefgh
-abcdefgh
bfs

*/

int counter=0; 

void formatPrint(string s){
  for(int j = 0; j < 3; j++){
    int u = j * 3;
    int stop = (j + 1) * 3;
    for(; u < stop; u++)
      cout << setw(2) << s[u];
    cout << endl;
  }
cout << endl;
}

struct Patterns{
  string pattern;
  int heuristics;
  int depth;
};
struct comparePatterns{
  bool operator()(Patterns const& p1, Patterns const& p2){
    return p1.heuristics>p2.heuristics;
  }
};

int heuristics(string input,string output){
  unordered_map<char, int> data;
  for(int i=0;i<(int)input.length();i++){
    data[input.at(i)]=i;
  }
  int sums=0;
  for(int j=0;j<(int)output.length();j++){
    int x1=(int)j/3;
    int y1=(int)j%3;
    int t = data[output.at(j)];
    int x2 =(int)t/3;
    int y2 =(int)t%3;
    sums+=(abs(x2-x1)+abs(y2-y1));
  }
  return sums;
}


int findBlank(string inputString){
  size_t found = inputString.find("-");
  int index = static_cast<int>(found);
  return index;
}

string generateOutputString(string input,int parentBlank,int replaceBlank){
    string copy_input;
     char temp = input[replaceBlank];
     input[replaceBlank]=input[parentBlank];
    input[parentBlank]=temp;
    copy_input=input;
    return copy_input;
}

void printBfs(unordered_map<string, int> data1,unordered_map<string, int> data2,string middle,string input,string output ,int totalNodes1,int totalNodes2){
  string processing=middle;
  vector<string> ans1;
  vector<string> ans2;
  // ans1.push_back(input);
  // cout<<middle << "midde";
  // cout<<"\n"<<goal;
 while(processing!=input){
   int childBlank = findBlank(processing);
   string parent = generateOutputString(processing,data1[processing],childBlank);
  //  cout<<"\n"<<parent;
   ans1.push_back(parent);
   processing=parent;
  }
  
   processing=middle;
  //  cout << middle;
  //  ans2.push_back(middle);
	while(processing!=output){
    
	int childBlank1 = findBlank(processing);
	string parent1 = generateOutputString(processing,data2[processing],childBlank1);
	// cout<<"\n"<<parent1;
	ans2.push_back(parent1);
	processing=parent1;
 }
//  ans2.push_back(output);

  for(int i =ans1.size()-1;i>=0;i--){
  formatPrint(ans1.at(i));
  }
	  
    // cout<<"printed 1";
	for(int i =0 ;i<ans2.size();i++){
	formatPrint(ans2.at(i));
	}
 cout << "Total nodes: " << data1.size()+data2.size()-1 << ", max depth is: " << max(ans1.size(),ans2.size()) << endl;

}





void bfsSearch(string input, string output,vector<vector<int>> &shiftLocations){

  
// cout << "yes";
   
  std::queue<string> qf;
  std::queue<string> qb;
  string processing;
  int found=0;
  int depth=0;
  
  qf.push(input);
  qb.push(output);
  // string middle;
  
// cout << input;
  unordered_map<string, int> data1;
  unordered_map<string, int> data2;
  
  unordered_set<string> frontier1;
  unordered_set<string> frontier2;
  
  data1[input]=-1;
  data2[output]=-1;
  frontier1.insert(input);
  frontier2.insert(output);
  
  vector<string> intersection;
  string middle="";
  bool flag = false;

  int count1=0;
  int count2=0;
  
  //  while(qf.size()!=0 || qb.size()!=0 || flag == false ){

    while(flag == false){
      // for(int i = 0 ; i <  ; i++){
     
  if(qf.size()>0){
      processing=qf.front();
      // cout << processing << " first" << endl;
      qf.pop();
	  frontier1.erase(processing);
      // depth++;
      int parentBlank1=findBlank(processing);
      vector<int> locations1 =  shiftLocations.at(parentBlank1);
      for(int i =0;i<(int)locations1.size();i++){

        string out=generateOutputString(processing,parentBlank1,locations1.at(i));
        
        if (data1.find(out) == data1.end() && find(frontier2.begin(),frontier2.end(),out)==frontier2.end())
            {
              data1[out]=parentBlank1;
              qf.push(out);
			  frontier1.insert(out);
			  
			}else if(data1.find(out) == data1.end() && find(frontier2.begin(),frontier2.end(),out)!=frontier2.end()){
              data1[out]=parentBlank1;
              qf.push(out);
			  frontier1.insert(out);
        middle=out;
        break;        
      }
			  
            // else{
            //   // cout<<"presnt"<<out<<"\n";
            //   // for()
            // }
	  }
        count1+=1;
  }
	// std::set_intersection(frontier1.begin(), frontier1.end(),
  //                        frontier2.begin(), frontier2.end(),
  //                         back_inserter(intersection));
	if(middle.length()!=0){
		 printBfs(data1,data2,middle,input,output,count1,count2);
     flag = true;
    //  cout << "in" ;
		break;
	}
	if(flag == true){
    break;
  }
  
  if(qb.size() > 0){
      processing=qb.front();
      // cout << processing << " second" << endl;
      qb.pop();
	    frontier2.erase(processing);
      // depth++;
      int parentBlank=findBlank(processing);
      vector<int> locations =  shiftLocations.at(parentBlank);
      for(int i =0;i<(int)locations.size();i++){

        string out=generateOutputString(processing,parentBlank,locations.at(i));
        
        if (data2.find(out) == data2.end() && find(frontier1.begin(),frontier1.end(),out)==frontier1.end())
            {
              data2[out]=parentBlank;
              qb.push(out);
			  frontier2.insert(out);		  
			  
            }else if(data2.find(out) == data2.end() && find(frontier1.begin(),frontier1.end(),out)!=frontier1.end()){
              data2[out]=parentBlank;
              qb.push(out);
              frontier2.insert(out);
              middle=out;
              break;
            }
      }
              count2+=1;
  }
	  
	// std::set_intersection(frontier2.begin(), frontier2.end(),
  //                        frontier1.begin(), frontier1.end(),
  //                         back_inserter(intersection));
						  
	if(middle.length()!=0){
		 printBfs(data1,data2,middle,input,output,count1,count2);
     flag = true;
		break;
	
   }
   if(flag){
     break;
   }
	
}
if(!flag){
	cout<<"No solution.";
}
 
}


bool recurrsiveDfs(string input,string output,vector<string> &stack,vector<vector<int>> &shiftLocations,int &total,int level,int iteration){
  
  //cout<<level<<"comparing "<<iteration;
    total+=1;
  
  if(input==output){
    return true;
  }
  
  if(iteration==level){
    // cout<<"reached "<<iteration<<" "<<level<<endl;
	  return false;
  }



  //cout << "in" << endl;
  

 int parentBlank = findBlank(input);

  vector<int> locations = shiftLocations.at(parentBlank);

  for(int i=0;i<(int)locations.size();i++){
    string out=generateOutputString(input,parentBlank,locations.at(i));
	//extern int counter;

    //change to stack instead of data
      // data++;
    if ((std::find(stack.begin(), stack.end(), out))== stack.end()){
      stack.push_back(out);
		//counter+=1;
      if(recurrsiveDfs(out,output,stack,shiftLocations,total,level,iteration+1)){
          return true;
      }
      else{
        stack.pop_back();
      }


    }else{
      continue;
    }

    

  }

  return false;
}

void dfsSearch(string input,string output,vector<vector<int>> &shiftLocations,int it){
vector<string> stack;
//stack.push_back(input);
unordered_set <string> data ;
//int level=0;

int total=0;

bool ans=false;
int k=0;
int depth=0;
int iteration=0;
//extern int counter;
for(k=1;k<=it;k++){
	// data.insert(input);
// total++;

// int iteration=0;
	stack.push_back(input);
	//cout<<"restarting"<<endl;
	ans=recurrsiveDfs(input,output,stack,shiftLocations,total,k,iteration);
  iteration=0;
	//cout<<data.size()<< endl;
  // cout<<"Total: "<<total;
	//cout << k << " total" << endl;
	// data.clear();
	//counter=0;
	if(ans){
		depth=k;
		break;
	}else{
		stack.clear();
	}
	

}
// cout<<ans;
if(ans){
  for(int i=0;i<(int)stack.size();i++){
    formatPrint(stack.at(i));
}
cout << "Total nodes: " << total << ", max depth is: " << depth << endl;
}else{
  cout<<"No solution."<<endl;
}
}






using namespace std;
int main() {
  string input;
  string goal;
  string method;
  vector<vector<int>> shiftLocations;

  // vector<int> first =  new vector<int, typename _Alloc>
  shiftLocations.push_back(vector<int>{ 1, 3 });
  shiftLocations.push_back(vector<int>{0, 2, 4 });
  shiftLocations.push_back(vector<int>{ 1, 5 });
  shiftLocations.push_back(vector<int>{ 0, 4, 6 });
  shiftLocations.push_back(vector<int>{ 1, 3, 5, 7 });
  shiftLocations.push_back(vector<int>{ 2, 4, 8 });
  shiftLocations.push_back(vector<int>{ 3, 7 });
  shiftLocations.push_back(vector<int>{ 4, 6, 8 });
  shiftLocations.push_back(vector<int>{ 5, 7 });


// cout << "hi";
  // getline(cin, input);
  // getline(cin, goal);
  // getline(cin, method);

  cin >> input;
  cin >> goal;
  cin >> method;
  // input="ab-cdefgh";  
  // goal="-abcdefgh"; 
  // method="bfs";

  // cout<<findBlank(input);
// cout << "why";
 if(method.compare("bidirect") == 0){
  //  cout << "in";
   bfsSearch(input, goal, shiftLocations);
 }else if(method=="id"){
	 int it;
	cin >> it;
   dfsSearch(input,goal,shiftLocations,it);
 }
 
    
  return 0;
  
}