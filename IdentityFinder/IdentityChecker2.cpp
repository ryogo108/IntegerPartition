#include"common.cpp"
#include<vector>
vector<part> partitions;
bool checkConditions(Par & p){	
  bool f=true;
  bool tmp=false;
  int pool;
  int l=lengthOfPartition(p);
  vector<int> sub;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
//    f=f&&(p[i]%12==4 || p[i]%12==8 || p[i]%12==10 || p[i]%12==11);
    f=f&&(p[i]%12!=1 && p[i]%12!=5);
    f=f&&(p[i]!=2 &&p[i]!=3 && p[i]!=6 && p[i]!=7 && p[i]!=9);
    if(p[i+1]!=0){
      bool tmp=p[i]-p[i+1]>12;
      if(p[i]-p[i+1]==9){
       tmp=(((p[i]%12==3 || p[i]%12==9)&&(p[i+2]==0 || p[i]-p[i+2]>=24))||(p[i]==27 && p[i+1]==18 && p[i+2]==4 && p[i+3]==0));
      }
      if(p[i]-p[i+1]==12)tmp=(p[i]%12==4||p[i]%12==8||p[i]%12==10||p[i]%12==11);
      f=f&&tmp;
    }
 /*   if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>0);
    }*/
  }
/*  if(!f)return f;
  for(int i=0;i<l;i++){
    if(p[i]>0)sub.push_back(p[i]-(l-(i+1))*3);
  }*/
  //printVector(sub);
/*  for(int i=0;i<p.size();i++){ 
    if(p[i]==0)break;
    if(sub[i]%3==2){
      tmp=true;
      pool=sub[i]/3;
    }
    if(tmp){
      if(sub[i]==pool*3-2){
        f=false;
        break;
      }
      if(sub[i]!=pool*3+2&&sub[i]!=(pool+1)*3)tmp=false;
    }
  }*/
  return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	//vector<long long>v(countPartitions(n,partitions,checkConditions));
	vector<long long>v(countPartitionsWithPirnt(n,partitions,checkConditions));
	printVector(v);
	vector<long long>A(Factor(v));
	printVector(A);
	printPeriodOfSeq(A);
}
