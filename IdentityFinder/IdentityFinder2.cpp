#include"common.cpp"
#include"countPartition.cpp"
#include<queue>
#include<functional>

const int PARTITION_LENGTH=60;

vector<part> partitions;

long long sizeOfPartition(int n){ //partition を一列に列挙するのに必要な容量
  long long sum=0;
  for(int i=0;i<=n;i++){
    sum+=numOfPartition(i)*(PARTITION_LENGTH);
  }
  return sum; 
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
      if(sum==i){
        copy(v.begin(),v.end(),partitions.begin()+head+cnt*PARTITION_LENGTH);
        cnt++;
        //print_vector(v);
      }
      else{
        for(int k=min(v.back(),i-sum);k>=1;k--){ 
          vector<part> v_new(v);
          v_new.push_back(k);
          que.push(v_new);
        }
      }
    }
    cout<<i<<" : "<<cnt<<endl;
  }
}

vector<long long>countPartitions(int n,vector<part> & ps,function<bool(Par &)>f){ 
  vector<long long>re;
  long long now=0;
  for(int l=0;l<=n;l++){
    long long cap=sizeOfPartition(l);
    long long cnt=0;
    for(;now<cap;now+=PARTITION_LENGTH){
      vector<part>v;
      v.assign(ps.begin()+now,ps.begin()+now+PARTITION_LENGTH);
      if(f(v))cnt++;
    }
    re.push_back(cnt);
  }
  return re;
}

function<bool(Par&)> generateConditionsKR1(vector<int> & params){
  cout<<"Condition:";
  print_vector(params);
  return [&params](Par & p)->bool{
    bool f=diffAtDist(p,params[0],params[1])&&smallestPart(p,params[2])&&congruenceAtDist(p,params[3],params[4],params[5],params[6]);
    return f;
  };
}
void SearchSp_KR1(int n){
  rep(i,5)rep(j,5)rep(k,10)rep(A,5)rep(B,5)rep(C,5)rep(D,5){
    bool f = (k>=1&&i>=1&&j>=1&&A>=1&&C<D&&D>=2);
    if(!f)continue;
    f=f&&(B>=j*(A/i));
    if(!f)continue;
    vector<int>params={i,j,k,A,B,C,D};
    vector<long long>count=countPartitions(n,partitions,generateConditionsKR1(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  partitions.resize(sizeOfPartition(n));
  generatePartition(n);
  SearchSp_KR1(n);
}
