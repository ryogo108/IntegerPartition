#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef vector<vector<int> > Polynomial;

Polynomial operator+(const Polynomial & l,const Polynomial & r){
  Polynomial re(max(l.size(),r.size()),vector<int>(max(l[0].size(),r[0].size()),0));
  for(int i=0;i<re.size();i++){
    for(int j=0;j<re[i].size();j++){
      re[i][j]=r[i][j]+l[i][j];
    }
  }
  return re;
}
Polynomial operator-(const Polynomial & l,const Polynomial & r){
  Polynomial re(max(l.size(),r.size()),vector<int>(max(l[0].size(),r[0].size()),0));
  for(int i=0;i<re.size();i++){
    for(int j=0;j<re[i].size();j++){
      re[i][j]=r[i][j]+l[i][j];
    }
  }
  return re;
}
Polynomial operator*(const Polynomial & l,const Polynomial & r){
  Polynomial re(l.size()+r.size()-1,vector<int>(l[0].size()+r[0].size()-1,0));
  for(int il=0;il<l.size();il++){
    for(int jl=0;jl<l[0].size();jl++){
      for(int ir=0;ir<r.size();ir++){
        for(int jr=0;jr<r[0].size();jr++){
          re[il+ir][jl+jr]+=l[il][jl]*r[ir][jr];
        }
      }
    }
  }
  return re;
}

void print_Polynomial(Polynomial & p){
  for(int i=0;i<p.size();i++){
    for(int j=0;j<p[i].size();j++){
      if(j)cout<<" ";
      cout<<p[i][j]<<"x^"<<j<<"q^"<<i;
    }
    cout<<endl;
  }
}

int main(){
  Polynomial p={{1,2,3},{1,2,3}};
  Polynomial q={{3,2,1},{1,2,3}};
  Polynomial r=p*q;
  print_Polynomial(r);
}
