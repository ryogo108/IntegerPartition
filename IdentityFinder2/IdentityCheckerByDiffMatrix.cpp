#include<vector>
#include"Matrix.cpp"
#include<iostream>

using namespace std;

const int MAX_PARTITION_SIZE = 100;
const int MAX_PART = 100;
const int MAX_MOD = 20;

int max(int a, int b){
  return a > b ? a : b;
}

template<class T> bool isInVector(T target, const vector<T> & vec) {
  for(int i = 0; i < vec.size(); i++){
    if(target == vec[i]) return true;
  }
  return false;
}

template<class T>void printVector(vector<T> & vec){
  for(int i = 0; i < vec.size(); i++){
    if(i > 0)cout << " ";
    cout << vec[i];
  }
  cout << endl;
}

vector<long long> Factor(vector<long long> &  B){//今はここが律速
  //Eulerのアルゴリズム
  vector<long long> A;
  A.push_back(0);
  for(int i = 1; i < B.size(); i++){
    long long t = i * B[i];
    for(int d = 1; d < i; d++){
      if((i % d) == 0)t -= d * A[d];
    }

    for(int j = 1; j < i; j++){
      long long tmp = 0;
      for(int d = 1; d <= j; d++){
       if((j % d) == 0)tmp += d * A[d];
      }
      t -= tmp * B[i - j];
    }
    A.push_back(t / i);
  }
  return A;
}

int detect(vector<long long> & A){
  //列Aが周期的かどうか調べその周期を返す
  int n = A.size();
  for(int i = 1; i <= n / 2; i++){
    bool f = true;
    for(int j = 1; j < n; j++){
      if(A[j] != A[j % i == 0 ? i : j % i]){
        f = false;
        break;
      }
    }
    if(f)return i;
  }

  return 0;
}

bool printPeriodOfSeq(vector<long long> & Seq){
  //列Seqが周期的なときその1周期分の列を表示する
  int l = detect(Seq);
	vector<long long> v;
	for(int i = 1; i <= l; i++){
		if(Seq[i] != 0) v.push_back(Seq[i] * i);
	}
  if(v.empty()) return false;

  cout << "(mod  " << l << " ): ";
  printVector(v);
  return true;
}

bool checkSeq(vector<long long> & Seq){
  printVector(Seq);
  vector<long long> B = Factor(Seq);
  if(printPeriodOfSeq(B))return true;
  return false;
}

vector<long long> countPartitionsByDiffMatrix(const Mat<int> & diffMatrix, const vector<int> & forbiddenParts){
  vector<long long> numOfPartitions(MAX_PARTITION_SIZE + 1, 0);

  int M = diffMatrix.size();

  // dp[n][N][r] := #{ |λ| = n,  λ_1 <= N, λ_1 ≡r (mod M)}
  long long dp[MAX_PARTITION_SIZE + 1][MAX_PART + 1][MAX_MOD + 1];

  for(int partitionSize = 0; partitionSize <= MAX_PARTITION_SIZE; partitionSize++){
    for(int maximalPart = 0; maximalPart <= MAX_PART; maximalPart++){
      for(int residue = 0; residue <= MAX_MOD; residue++){
        dp[partitionSize][maximalPart][residue] = 0;
      }
    }
  }
  dp[0][0][0] = 1;

  for(int partitionSize = 0; partitionSize <= MAX_PARTITION_SIZE; partitionSize++){
    for(int maximalPart = 1; maximalPart <= MAX_PART; maximalPart++){
      for(int residue = 0; residue < M; residue++){
        dp[partitionSize][maximalPart][residue] = dp[partitionSize][maximalPart - 1][residue];
      }

      if(maximalPart > partitionSize) continue;

      if(isInVector(maximalPart, forbiddenParts)){
        continue;
      }

      for(int residue = 0; residue < M; residue++){
        int diff = diffMatrix[maximalPart % M][residue];
        dp[partitionSize][maximalPart][maximalPart % M] +=
          dp[partitionSize - maximalPart][max(maximalPart - diff, 0)][residue];
      }
    }

    for(int residue = 0; residue < M; residue++){
      numOfPartitions[partitionSize] += dp[partitionSize][partitionSize][residue];
    }
  }

  return numOfPartitions;
}

int main(){
  Mat<int> seed={
    {1, 1, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 2, 2, 2},
    {1, 1, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 2, 2},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {0, 0, 1, 1, 1, 1, 1, 1},
  };

  Mat<int> shift={
    {0, -1, -2, -3, -4, -5, -6, -7},
    {1, 0, -1, -2, -3, -4, -5, -6},
    {2, 1, 0, -1, -2, -3, -4, -5},
    {3, 2, 1, 0, -1, -2, -3, -4},
    {4, 3, 2, 1, 0, -1, -2, -3},
    {5, 4, 3, 2, 1, 0, -1, -2},
    {6, 5, 4, 3, 2, 1, 0, -1},
    {7, 6, 5, 4, 3, 2, 1, 0},
  };

  vector<int> forbiddenParts = {2};

  Mat<int> diffMatrix = int(seed.size()) * seed + shift;
  printMatrix(diffMatrix);

  vector<long long> numOfPartitions = countPartitionsByDiffMatrix(diffMatrix, forbiddenParts);
  checkSeq(numOfPartitions);
}
