#include"../common.cpp"
#include<vector>
#include<string>
#include<sstream>

using namespace std;

const int MAX_LENGTH=30;

vector<string> split(const string &s, char delim){
  vector<string> elems;
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim)){
    if(!item.empty()){
      elems.push_back(item);
    }
  }
  return elems;
}

int strToPar(const string &str, Par &par){
  vector<string> spl = split(str, ' ');
  for(int i=0;i<spl.size();i++){
    par[i]=part(stoi(spl[i]));
  }
  return 0;
}
int strToIntVector(const string &str, vector<int> &A){
  A.clear();
  vector<string> spl = split(str, ' ');
  for(int i=0;i<spl.size();i++){
    A.push_back(stoi(spl[i]));
  }
  return 0;
}

vector<int> A;

int main(){
  string s;
  getline(cin,s);
  strToIntVector(s,A);
  for(int i=0;i<A.size();i++){
    for(int j=0;j<A[i];j++){
      string str;
      getline(cin,str);
      cout<<str<<endl;
      Par p(MAX_LENGTH);
      strToPar(str,p);
      printPartition(p);
    }
  }
}
