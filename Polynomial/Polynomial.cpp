#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef vector<vector<long long> > Polynomial;

int max(int a,int b){
  return a>b?a:b;
}

Polynomial operator+(const Polynomial & l,const Polynomial & r){
  Polynomial re(max(l.size(),r.size()));
  for(int i=0;i<re.size();i++){
    int ls=0,rs=0;
    if(i<l.size())ls=l[i].size();
    if(i<r.size())rs=r[i].size();
    re[i].resize(max(ls,rs));
  } for(int i=0;i<l.size();i++){
    for(int j=0;j<l[i].size();j++){
      re[i][j]+=l[i][j];
    }
  }
  for(int i=0;i<r.size();i++){
    for(int j=0;j<r[i].size();j++){
      re[i][j]+=r[i][j];
    }
  }
  return re;
}
Polynomial operator-(const Polynomial & l,const Polynomial & r){
  Polynomial re(max(l.size(),r.size()));
  for(int i=0;i<re.size();i++){
    int ls=0,rs=0; 
    if(i<l.size())ls=l[i].size();
    if(i<r.size())rs=r[i].size();
    re[i].resize(max(ls,rs));
  }
  for(int i=0;i<l.size();i++){
    for(int j=0;j<l[i].size();j++){
      re[i][j]+=l[i][j];
    }
  }
  for(int i=0;i<r.size();i++){
    for(int j=0;j<r[i].size();j++){
      re[i][j]-=r[i][j];
    }
  }
  return re;
}
Polynomial operator*(const Polynomial & l,const Polynomial & r){
  int mls=0,mrs=0;
  for(int i=0;i<l.size();i++)mls=max(mls,l[i].size());
  for(int i=0;i<r.size();i++)mrs=max(mrs,r[i].size());
  Polynomial re(l.size()+r.size()-1,vector<long long>(mls+mrs-1,0));
  for(int il=0;il<l.size();il++){
    for(int jl=0;jl<l[il].size();jl++){
      for(int ir=0;ir<r.size();ir++){
        for(int jr=0;jr<r[ir].size();jr++){
          re[il+ir][jl+jr]+=l[il][jl]*r[ir][jr];
        }
      }
    }
  }
  return re;
}

Polynomial qShift(const Polynomial & p,int s){
  int ms=0;
  for(int i=0;i<p.size();i++)ms=max(ms,p[i].size());
  Polynomial re(p.size()+(ms-1)*s,vector<long long>(ms,0));
  for(int i=0;i<p.size();i++){
    for(int j=0;j<p[i].size();j++){
      re[i+j*s][j]=p[i][j];
    }
  }
  return re;
}

void print_Polynomial(Polynomial & p){
  int terms=0;
  for(int i=0;i<p.size();i++){
    int cnt=0;
    for(int j=0;j<p[i].size();j++){
      if(p[i][j]==0)continue;
      else cnt++;
      if((cnt>1 || terms!=0)&&p[i][j]>0)cout<<"+";
      if(p[i][j]!=1 || (i==0 && j==0) )cout<<p[i][j];
      if(j==1)cout<<"x";
      else if(j)cout<<"x^"<<j;
      if(i==1)cout<<"q";
      else if(i)cout<<"q^"<<i;
    }
    terms+=cnt;
    if(cnt>0)cout<<endl;
  }
}

/*int main(){
  Polynomial p={{1,1}};
  Polynomial x={{0,1}};

  Polynomial r=p-x*qShift(p,2);
  print_Polynomial(p);
  print_Polynomial(r);
}*/
