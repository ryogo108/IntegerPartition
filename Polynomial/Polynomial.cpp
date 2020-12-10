#include<iostream>
#include<vector>
#include<string>
using namespace std;

// Polynomial は ZZ[x, q] / (x ^ (MAX_X_INDEX + 1), q ^ (MAX_Q_INDEX + 1)) の上の元.
typedef vector<vector<long long> > Polynomial;
const int MAX_Q_INDEX = 30;
const int MAX_X_INDEX = 30;

int max(int a, int b){
  return a > b ? a : b;
}

int min(int a, int b){
  return a < b ? a : b;
}

Polynomial operator + (const Polynomial & l, const Polynomial & r){
  Polynomial result(MAX_Q_INDEX + 1, vector<long long>(MAX_X_INDEX + 1, 0));
  for(int qIndex = 0; qIndex < min(l.size(), MAX_Q_INDEX + 1); qIndex++){
    for(int xIndex = 0; xIndex < min(l[qIndex].size(), MAX_X_INDEX + 1); xIndex++){
      result[qIndex][xIndex] += l[qIndex][xIndex];
    }
  }

  for(int qIndex = 0; qIndex < min(r.size(),  MAX_Q_INDEX + 1); qIndex++){
    for(int xIndex = 0; xIndex < min(r[qIndex].size(), MAX_X_INDEX + 1); xIndex++){
      result[qIndex][xIndex] += r[qIndex][xIndex];
    }
 }
  return result;
}

Polynomial operator - (const Polynomial & r){
  Polynomial result(MAX_Q_INDEX + 1, vector<long long>(MAX_X_INDEX + 1, 0));
  for(int qIndex = 0; qIndex < min(r.size(), MAX_Q_INDEX + 1); qIndex++){
    for(int xIndex = 0; xIndex < min(r[qIndex].size(), MAX_X_INDEX + 1); xIndex++){
      result[qIndex][xIndex] = -r[qIndex][xIndex];
    }
  }
  return result;
}

Polynomial operator - (const Polynomial & l, const Polynomial & r){
  Polynomial result(MAX_Q_INDEX + 1, vector<long long>(MAX_X_INDEX + 1, 0));
  for(int qIndex = 0; qIndex < min(l.size(), MAX_Q_INDEX + 1); qIndex++){
    for(int xIndex = 0; xIndex < min(l[qIndex].size(), MAX_X_INDEX + 1); xIndex++){
      result[qIndex][xIndex] += l[qIndex][xIndex];
    }
  }

  for(int qIndex = 0; qIndex < min(r.size(),  MAX_Q_INDEX + 1); qIndex++){
    for(int xIndex = 0; xIndex < min(r[qIndex].size(), MAX_X_INDEX + 1); xIndex++){
      result[qIndex][xIndex] -= r[qIndex][xIndex];
    }
  }
  return result;
}

Polynomial operator * (const Polynomial & l, const Polynomial & r){
  Polynomial result(MAX_Q_INDEX + 1, vector<long long>(MAX_X_INDEX + 1, 0));
  for(int lQIndex = 0; lQIndex < min(l.size(), MAX_Q_INDEX + 1); lQIndex++){
    for(int lXIndex = 0; lXIndex < min(l[lQIndex].size(), MAX_X_INDEX + 1); lXIndex++){
      for(int rQIndex = 0; rQIndex < min(r.size(), MAX_Q_INDEX + 1); rQIndex++){
        for(int rXIndex = 0; rXIndex < min(r[rQIndex].size(), MAX_X_INDEX + 1); rXIndex++){
          if(lQIndex + rQIndex > MAX_Q_INDEX) continue;
          if(lXIndex + rXIndex > MAX_X_INDEX) continue;
          result[lQIndex + rQIndex][lXIndex + rXIndex] += l[lQIndex][lXIndex] * r[rQIndex][rXIndex];
        }
      }
    }
  }
  return result;
}

// f(x) -> f(x * q ^ s)
Polynomial qShift(const Polynomial & p, int s){
  int ms = 0;
  for(int i = 0;i < p.size(); i++) ms = max(ms, p[i].size());

  Polynomial re(p.size() + (ms - 1) * s, vector<long long>(ms, 0));
  for(int i = 0; i < p.size(); i++){
    for(int j = 0; j < p[i].size(); j++){
      re[i + j * s][j] = p[i][j];
    }
  }
  return re;
}

Polynomial xInv(const Polynomial & p){
  //x <- (-x)
  Polynomial re = p;
  for(int i = 0; i < re.size(); i++){
    for(int j = 0;j < re[i].size(); j++){
      if(j % 2) re[i][j] = -re[i][j];
    }
  }
  return re;
}

void print_Polynomial(Polynomial & p){
  int terms = 0;
  for(int i = 0; i < p.size(); i++){
    for(int j = 0; j < p[i].size(); j++){
      if(p[i][j] == 0)continue;
      if(terms > 0){
        if(p[i][j] > 0) cout << " + ";
        if(p[i][j] < 0) cout << " ";
      }
      cout << p[i][j];
      if(j > 0) cout << " * x^" << j;
      if(i > 0) cout << " * q^" << i;
      terms++;
    }
  }
  cout<<endl;
}

int main(){
  Polynomial p1 = Polynomial({{1, 1, 100, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1}});
  Polynomial p2 = Polynomial({{1}, {1, 1}});
  Polynomial x={{1,1,1,1,1,1},{1,2,3,4}};

  Polynomial q = Polynomial({{1}, {0, 1}});

  Polynomial r = q * p2;
  print_Polynomial(r);
  //print_Polynomial(r);
}
