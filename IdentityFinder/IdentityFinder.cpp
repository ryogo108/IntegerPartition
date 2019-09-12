#include<iostream>
#include<list>
#include<vector>
using namespace std;

template<class T> void print_list(list<T> lst){
  for(typename list<T>::iterator itr=lst.begin();itr!=lst.end();itr++){
    if(itr!=lst.begin())cout<<" ";
    cout<<*itr;
  }
  cout<<endl;
}
template<class T>void print_vector(vector<T> vec){
  for(int i=0;i<vec.size();i++){
    if(i>0)cout<<" ";
    cout<<vec[i];
  }
  cout<<endl;
}



bool strict(list<int> lst){
  if(lst.empty())return true;
  for(list<int>::iterator itr=lst.begin();next(itr)!=lst.end();itr++){
    if((*itr)==*next(itr))return false;
  }
  return true;
}
bool hyperStrict(list<int> lst){
  if(lst.empty())return true;
  for(list<int>::iterator itr=lst.begin();next(itr)!=lst.end();itr++){
    if((*itr)-*next(itr)<2)return false;
  }
  return true;
}
bool diffAtDist(list<int> lst,int dist,int diff){
  if(lst.size()<dist)return true;
  for(list<int>::iterator itr=lst.begin();next(itr,dist)!=lst.end();itr++){
    if((*itr)-*next(itr,dist)<diff)return false;
  }
  return true;
  
}
bool congruenceAtDist(list<int> lst,int A,int B,int C,int D){
  // diff of lamda_j and lamda_{j+A} is less than or equal to B only if sum from lamda_j to lamda_{j+A} is congruence to C (mod D)
  if(lst.size()<A)return true;
  for(list<int>::iterator itr=lst.begin();next(itr,A)!=lst.end();itr++){
    if((*itr)-*next(itr,A)<=B){
      int sum=0;
      for(list<int>::iterator jtr=itr;jtr!=next(itr,A+1);jtr++){
        sum+=*(jtr);
      }
      if(sum%D!=C)return false;
    }
  }
  return true;
}
bool smallestPart(list<int> lst,int n){
  if(lst.empty())return true;
  return *prev(lst.end())>=n;
}

bool I1(list<int> lst){
  return diffAtDist(lst,2,3)&&congruenceAtDist(lst,1,1,0,3)&&smallestPart(lst,1);
}
bool I2(list<int> lst){
  return diffAtDist(lst,2,3)&&congruenceAtDist(lst,1,1,0,3)&&smallestPart(lst,2);
}
bool I3(list<int> lst){
  return diffAtDist(lst,2,3)&&congruenceAtDist(lst,1,1,0,3)&&smallestPart(lst,3);
}
bool I4(list<int> lst){
  return diffAtDist(lst,2,3)&&congruenceAtDist(lst,1,1,2,3)&&smallestPart(lst,2);
}
bool I5(list<int> lst){
  list<int> tmpLst(lst);
  if(!tmpLst.empty())tmpLst.pop_back();
  return diffAtDist(lst,3,3)&&congruenceAtDist(lst,2,1,1,3)&&smallestPart(tmpLst,2);
}
bool I6(list<int> lst){
  list<int> tmpLst(lst);
  if(!tmpLst.empty())tmpLst.pop_back();
  return diffAtDist(lst,3,3)&&congruenceAtDist(lst,2,1,2,3)&&smallestPart(tmpLst,3)&&smallestPart(lst,2);
}

bool euler(list<int> lst){
  return diffAtDist(lst,1,1);
}
bool RogersRamanujan(list<int> lst){
  return diffAtDist(lst,1,2);
}

bool checkConditions(list<int> lst){
  return diffAtDist(lst,1,2);
}

int generatePartition(int n,int tail,int sum,list<int> prev){
  if(sum!=0)prev.push_back(tail);
  list<int> now(prev);
  if(n<sum)return 0;
  if(n==sum){
    if(checkConditions(now)){
      print_list(now);
      return 1;
    }
    return 0;
  }
  int re=0;
  for(int i=tail;i>=1;i--){
     re+=generatePartition(n,i,sum+i,now);
  }
  return re;
}

void partition(int n){
  list<int> lst;
  generatePartition(n,n,0,lst);
}
int countPartition(int n){
  list<int> lst;
  return generatePartition(n,n,0,lst);
}

vector<int> Factor(vector<int> B){
  vector<int> A;
  A.push_back(0);
  for(int i=1;i<B.size();i++){
    int t=i*B[i];
    for(int d=1;d<i;d++){
      if((i%d)==0)t-=d*A[d];
    }
    for(int j=1;j<i;j++){
      int tmp=0;
      for(int d=1;d<=j;d++){
       if((j%d)==0)tmp+=d*A[d];
      }
      t-=tmp*B[i-j];
    }
    A.push_back(t/i);
  }
  return A;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  vector<int> B;
  for(int i=0;i<=n;i++)B.push_back(countPartition(i));
  print_vector(Factor(B));
}
