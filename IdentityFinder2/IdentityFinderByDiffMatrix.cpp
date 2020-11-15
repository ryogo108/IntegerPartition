#include<vector>
#include"Matrix.cpp"
#include<iostream>
#include<set>

using namespace std;

const int MAX_PARTITION_SIZE = 100;
const int MAX_PART = 100;
const int MAX_FORBIDDEN_PART = 5;
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

// Euler の q - series の因数分解.
// B = (b_0, b_1, b_2, b_3, ..., b_N) -> A = (0, a_1, a_2, a_3, ..., a_N) s.t.
// (1 - q) ^ (-a_1) (1 - q ^ 2) ^ (-a_2) (1 - q ^ 3) ^ (-a_3) ... (1 - q ^ N) ^ (-a_N)
// = 1 + b_1 * q + b_2 * q ^ 2 + b_3 * q ^ 3 + ... + b_N * q ^ N + o(q ^ (N + 1)).
vector<long long> Factor(vector<long long> &  B){
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

// seq で seq[1] から始まる周期列があればそのの長さを返す.
// seq[1] から始めて周期的でなければ 0 を返す.
template<class T> int detectPeriod(const vector<T> & seq){
  int lengthOfSeq = seq.size();
  for(int period = 1; period <= lengthOfSeq / 2; period++){
    bool isPeoridic = true;
    for(int i = 1; i < lengthOfSeq; i++){
      if(seq[i] != seq[i % period == 0 ? period : i % period]){
        isPeoridic = false;
        break;
      }
    }

    if(isPeoridic){
      return period;
    }
  }

  return 0;
}

// seq が seq[1] から始めて周期的なときその周期列を表示する
void printTermOfPeriodicSeq(const vector<long long> & seq){
  int peoriod = detectPeriod(seq);
	vector<long long> term;
	for(int i = 1; i <= peoriod; i++){
		term.push_back(seq[i]);
	}
  cout<<"peoriod = " << term.size() << " : ";
  printVector(term);
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

void dfsForbiddenPartsGenerator(const Mat<int> & diffMatrix, int forbiddenPart, int maxForbiddenPart, vector<int> forbiddenParts){
  if(forbiddenPart == maxForbiddenPart){
    // これ以上 forbiddenPart は考えない.
    vector<long long> numOfPartitions = countPartitionsByDiffMatrix(diffMatrix, forbiddenParts);
    vector<long long> exponents = Factor(numOfPartitions);
    if(detectPeriod(exponents) > 0){
      printTermOfPeriodicSeq(exponents);
      cout << "forbiddenParts : ";
      printVector(forbiddenParts);
      cout << "diffMatrix : " << endl;
      printMatrix(diffMatrix);
    }
  }
  else{
    // forbiddenPart を 採用しない.
    dfsForbiddenPartsGenerator(diffMatrix, forbiddenPart + 1, maxForbiddenPart, forbiddenParts);

    // forbiddenPart を 採用する.
    forbiddenParts.push_back(forbiddenPart);
    dfsForbiddenPartsGenerator(diffMatrix, forbiddenPart + 1, maxForbiddenPart, forbiddenParts);
  }
}
void dfsDiffMatrixGenerator(int matrixSize, int maxDiff, int depth, const Mat<int> & seedMatrix, const Mat<int> & shiftMatrix){
  if(depth == matrixSize * matrixSize){
    Mat<int> diffMatrix = int(seedMatrix.size()) * seedMatrix + shiftMatrix;
    dfsForbiddenPartsGenerator(diffMatrix, 1, MAX_FORBIDDEN_PART, vector<int>());
  }
  else{
    for(int diff = 0; diff <= maxDiff; diff++){
      Mat<int> newSeedMatrix = seedMatrix;
      newSeedMatrix[depth / matrixSize][depth % matrixSize] += diff;
      dfsDiffMatrixGenerator(matrixSize, maxDiff, depth + 1, newSeedMatrix, shiftMatrix);
    }
  }
}

int main(int argc, char *argv[]){
  int matrixSize = atoi(argv[1]), maxDiff = atoi(argv[2]);

  Mat<int> shiftMatrix(matrixSize, vector<int>(matrixSize, 0));
  for(int i = 0; i < matrixSize; i++){
    for(int j = 0; j < matrixSize;j++){
      shiftMatrix[i][j] = i - j;
    }
  }

  Mat<int> seedMatrix(matrixSize, vector<int>(matrixSize, 0));
  for(int i = 0; i < matrixSize; i++){
    for(int j = 0; j < matrixSize;j++){
      seedMatrix[i][j] = j >= i;
    }
  }

  dfsDiffMatrixGenerator(matrixSize, maxDiff, 0, seedMatrix, shiftMatrix);
}
