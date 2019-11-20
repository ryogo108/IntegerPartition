#include"common.cpp"
#include"countPartition.cpp"
#include<queue>

const int PARTITION_LENGTH=33;

vector<part> partitions;

long long sizeOfPartition(int n){ //partition を一列に列挙するのに必要な容量
  long long sum=0;
  for(int i=0;i<=n;i++){
    sum+=numOfPartition(i)*(PARTITION_LENGTH);
  }
  return sum; 
}
bool checkConditions(Par & p){
  return smallestPart(p,4)&&diffAtDist(p,2,4)&&congruenceAtDist(p,1,1,0,4);
}
void generatePartition(int n){
  for(int i=1;i<=n;i++){
    int head=sizeOfPartition(i-1);
    int num=0;
    long long cnt=0;
    queue<vector<part> > que;
    for(int j=i;j>=1;j--)que.push(vector<part>(1,j));
    while(!que.empty()){
      vector<part> v=que.front();
      que.pop();
      int sum=sum_vector(v);
      if(sum==i && checkConditions(v)){
        copy(v.begin(),v.end(),partitions.begin()+head+cnt*PARTITION_LENGTH);
        cnt++;
        print_vector(v);
      }
      else{
        for(int k=min(v.back(),i-sum);k>=1;k--){ 
          vector<part> v_new(v);
          v_new.push_back(k);
          que.push(v_new);
        }
      }
    }
    cout<<"cnt : "<<cnt<<endl;
  }
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  partitions.resize(sizeOfPartition(n));
  generatePartition(n);
/*  for(long long i=0;i<partitions.size();i+=PARTITION_LENGTH){
    vector<part>v;
    v.assign(partitions.begin()+i,partitions.begin()+i+PARTITION_LENGTH);
    print_vector(v);
  }*/
}
