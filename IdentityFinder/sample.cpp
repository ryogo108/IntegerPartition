#include<iostream>

using namespace std;

void imp(int (*po)(int,int)){
  cout<<(*po)(10,3)<<endl;
}
void (*func())(){
  auto hello=[](){cout<<"Hello"<<endl;};
  return hello;
}

int main(){
  auto plus=[](int a,int b){return a+b;};
  imp(plus);
  void (*po)()=func();
  (*po)();
}
