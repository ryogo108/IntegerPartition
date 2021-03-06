#include<iostream>
#include<vector>
#include<cstdint>
#include<functional>
#include<queue>
#include<gmpxx.h>
#include"countPartition.cpp"
using namespace std;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)

const int PARTITION_LENGTH=100;

typedef /*uint_fast8_t*/ short part; // printVectorで表示するため一時的にpartにshort型を使う.
typedef vector<part> Par;

using ZZ = mpz_class;

part min(part l, part r){
  if(r > l) return l;
  else return r;
}

int lengthOfPartition(const Par & p){
	int length = 0;
	for(int i = 0; i < p.size(); i++){
		if(p[i] == 0) break;
		length++;
	}
	return length;
}

int lengthOfPartitionSp(const Par & p){
	int lengthSp = 0;
	for(int i = 0; i < p.size(); i++){
		if(p[i] == 0) break;
		if(p[i] % 3 == 2) lengthSp += 2;
    else lengthSp += 1;
	}
	return lengthSp;
}

template<class T>
void printVector(vector<T> & vec){
  for(int i = 0; i < vec.size(); i++){
    if(i > 0) cout << " ";
    cout << vec[i];
  }
  cout << endl;
}

void printPartition(Par & p){
	for(int i = 0; i < p.size(); i++){
		if(i > 0 && p[i] == 0) break;
		if(i > 0) cout << " ";
		cout << (short) p[i];
	}
	cout << endl;
}
template<class T>
T sumVector(vector<T> & vec){
  T sum = T(0);
  for(int i = 0; i < vec.size(); i++){
    sum += vec[i];
  }
  return sum;
}
long long numOfPartsOfAllPartition(int n){
  //大きさn以下の分割を一列に列挙するのに十分なpartの個数
  long long sum = 0;
  for(int i = 0; i <= n; i++){
    sum += numOfPartition(i) * (PARTITION_LENGTH);
  }
  return sum; 
}

void generatePartition(int maxSizeOfPartition, vector<part> & destPartitions, bool isStrict = false){
  //大きさn以下の分割を列挙するしてpartitionsに保存
  queue<Par> queOfLeadingPartitions;
  for ( part biggestPart = maxSizeOfPartition; biggestPart >= 1; biggestPart--){
    queOfLeadingPartitions.push( Par( 1, biggestPart ) );
  }
  while( !queOfLeadingPartitions.empty() ){
    Par leadingPartition = queOfLeadingPartitions.front();
    queOfLeadingPartitions.pop();
    if(sumVector( leadingPartition ) <= maxSizeOfPartition){
      destPartitions.insert( destPartitions.end(), leadingPartition.begin(), leadingPartition.end() );
      destPartitions.push_back( part(0) );
      for(part appendingPart = min( leadingPartition.back() - ( isStrict ? 1 : 0 ), maxSizeOfPartition - sumVector( leadingPartition ) ); appendingPart >= 1; appendingPart--){
        Par newPartition(0);
        newPartition.insert( newPartition.end(), leadingPartition.begin(), leadingPartition.end() );
        newPartition.push_back( appendingPart );
        queOfLeadingPartitions.push( newPartition );
      }
    }
  }
}

void filterSuitablePartitions(int maxSizeOfPartition, vector<part> & rawPartitions, vector<part> & destPartitions, function<bool(Par &)> isSuitable){
  // Init destPartitions.
  destPartitions.clear();

  // isSuitable を満たす分割を destPartition に保存する.
  Par examinedPartition;
  examinedPartition.reserve(maxSizeOfPartition + 1);
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      if( isSuitable( examinedPartition ) ){
        destPartitions.reserve( destPartitions.size() + examinedPartition.size() );
        destPartitions.insert( destPartitions.end(), examinedPartition.begin(), examinedPartition.end());
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
}

vector<long long> countSuitablePartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  //条件fを満たす分割の数を数える
  vector<long long> numOfSuitablePartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      if( isSuitable( examinedPartition ) ){
        numOfSuitablePartitionsBySize[ sumVector(examinedPartition) ]++;
        if( withPrint ) printPartition( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOfSuitablePartitionsBySize;
}

// countSuitableRefinedPartitions は 条件を満たす分割を分割の大きさ, refineFunction の値ごとに数える.
vector<vector<ZZ> > countSuitableRefinedPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, function<unsigned int(Par &)> refineFunction, bool withPrint = false){
  vector<vector<ZZ> > numOfSuitableRefinedPartitionsBySize( maxSizeOfPartition + 1, vector<ZZ> (maxSizeOfPartition + 1, ZZ(0) ) );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      if( isSuitable( examinedPartition ) ){
        numOfSuitableRefinedPartitionsBySize[ sumVector(examinedPartition) ][ refineFunction(examinedPartition) ]++;
        if( withPrint ) printPartition( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOfSuitableRefinedPartitionsBySize;
}

void printSuitablePartitionsBySize(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable){
  // 条件 isSuitable を満たす分割を 大きさ ごとに表示する.

  // 条件 isSuitable を満たす分割を列挙する.
  vector< part > suitablePartitions;
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      if( isSuitable( examinedPartition ) ){
        suitablePartitions.reserve( suitablePartitions.size() + examinedPartition.size() );
        suitablePartitions.insert( suitablePartitions.end(), examinedPartition.begin(), examinedPartition.end());
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }

  // 列挙した分割を大きさ毎に表示する.
  for(part i = 0 ; i <= maxSizeOfPartition; i++){

    if( i > 0)cout<<endl;

    cout<<"Size : "<< i <<endl;

    Par examinedPartition;
    examinedPartition.reserve( maxSizeOfPartition + 1 );

    for(auto itr = suitablePartitions.begin(); itr != suitablePartitions.end(); itr++){
      if(*itr == part(0)){
        if(sumVector(examinedPartition) == i)printPartition(examinedPartition);
        examinedPartition.clear();
      }
      else {
        examinedPartition.push_back( *itr );
      }
    }
  }
}

vector<long long> Factor(vector<long long> &  B){
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
      t -= tmp * B[ i - j ];
    }
    A.push_back( t / i );
  }
  return A;
}

//列Aが周期的であれば一周期の長さ,
//周期的でなければ 0 を返す.
int detectLengthOfPeriodOfSeq(vector<long long> & A){
  int n = A.size();
  for(int i = 1; i <= n / 2; i++){
    bool f = true;
    for(int j = 1; j < n; j++){
      if(A[j] != A[ j % i == 0 ? i : j % i]){
        f = false;
        break;
      }
    }
    if( f )return i;
  }
  return 0;
}
void printPeriodOfSeq(vector<long long> & Seq){
  //列Seqが周期的なときその1周期分の列を表示する
  int l = detectLengthOfPeriodOfSeq( Seq );
	vector<long long> v;
	for(int i = 1; i <= l; i++){
		if( Seq[i] != 0 ) v.push_back( Seq[i] *( i ) );
	}
  if( v.empty() ) return;
  cout << "(mod  " << l << " ): ";
  printVector( v );
}

//まだ結果を整理していない分割の条件
function<bool(Par &)> generateConditions_GeneralGollnitz2(vector<int> & params){
  cout<<"Condition(M,r1,r2,r3):";
  printVector(params);
	const int M=params[0];
	const int r1=params[1];
	const int r2=params[2];
	const int r3=params[3];
  return [=](Par & p)->bool{
		bool f=true;
		for(int i=0;i<p.size();i++){
      bool tmp=false;
			if(p[i]==0)break;
			else{
        if(p[i]>=r1+r2)tmp=tmp||(p[i]%M==(r1+r2)%M);
        if(p[i]>=r2+r3)tmp=tmp||(p[i]%M==(r2+r3)%M);
        if(p[i]>=r1+r3)tmp=tmp||(p[i]%M==(r1+r3)%M);
				f=f&&(p[i]%M==r1 || p[i]%M==r2 || p[i]%M==r3 || tmp);
			}
			if(p[i+1]!=0){
				f=f&&(p[i]-p[i+1]>=M);
        if(tmp)f=f&&(p[i]-p[i+1]>M);
			}
		}
		return f;
  };
}

//論文中の結果を得た分割の条件
function<bool(Par &)> generateConditionsGeneralGollnitz(vector<int> & params){
  cout<<"Condition(no appear(bit),dist,diff,residue(bit)):";
  printVector(params);
	const int np=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int residue=params[3];
  return [=](Par & p)->bool{
		if(diff==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&((np>>(p[i]-1)&1)!=1);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
				if(p[i]-p[i+dist]==diff){
					bool tmp=false;
					for(int j=0;j<=diff;j++){
						if((residue>>(j))&1)tmp=tmp||(p[i]%(diff)==j);
					}
					f=f&&tmp;
        }
			}
		}
		return f;
  };
}
function<bool(Par &)> generateConditionsGeneralSchur(vector<int> & params){
  cout<<"Condition(no appear(residue),no appear MOD,dist,diff,residue(bit)):";
  printVector(params);
	const int np=params[0];
	const int D=params[1];
	const int dist=params[2];
	const int diff=params[3];
	const int residue=params[4];
  return [=](Par & p)->bool{
		if(D==0 || diff==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&((np>>((p[i]%D))&1)!=1);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
				if(p[i]-p[i+dist]==diff){
					bool tmp=false;
					for(int j=0;j<=diff;j++){
						if((residue>>(j))&1)tmp=tmp||(p[i]%(diff)==j);
					}
					f=f&&tmp;
				}
			}
		}
		return f;
  };
}
function<bool(Par &)> generateConditionsGeneralSchur2(vector<int> & params){
  cout<<"Condition(GeneralSchur2) k:";
  printVector(params);
	const int k=params[0];
	const int D=2*k;
	const int ap=(1<<1)|(1<<((1+k)%D))|(1<<((2+k)%D));
	const int dist=1;
	const int diff=D;
	const int residue=(1<<1)|(1<<((1+k)%D));
  return [=](Par & p)->bool{
		if(D==0 || diff==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&((ap>>((p[i]%D))&1)==1);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
				if(p[i]-p[i+dist]==diff){
					bool tmp=false;
					for(int j=0;j<=diff;j++){
						if((residue>>(j))&1)tmp=tmp||(p[i]%(diff)==j);
					}
					f=f&&tmp;
				}
			}
		}
		return f;
  };
}

//論文中の結果とは関係ないが他に試した分割の条件
function<bool(Par &)> generateConditionsKR1(vector<int> & params){
  cout<<"Condition(sp,dist,diff,A,B,C,D):";
  printVector(params);
	const int sp=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int A=params[3];
	const int B=params[4];
	const int C=params[5];
	const int D=params[6];
  return [=](Par & p)->bool{
		if(D==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&(p[i]>=sp);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			}
			if(p[i+A]!=0){
				if(p[i]-p[i+A]<=B){
					unsigned short sum=0;
					for(int j=0;j<=A;j++)sum+=p[i+j];
					f=f&&(sum%D==C);
				}
			}
		}
		return f;
  };
}


function<bool(Par &)>generateConditionsSchur(vector<int> & params){
	cout<<"Condition(schur)(f1,f2,a,b,c,d):";
	printVector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int f1=params[0];
		int f2=params[1];
		int a=params[2];
		int b=params[3];
		int c=params[4];
		int d=params[5];
		if(d==0)return true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			f=f&&(p[i]!=f1)&&(p[i]!=f2);
			if(p[i+1]!=0){
				if(p[i]%d==c)f=f&&((p[i]-p[i+1])>=b);
				else f=f&&((p[i]-p[i+1])>=a);
			}
		}
		return f;
	};
}
function<bool(Par &)>generateConditionsOriginal1(vector<int> & params){
	cout<<"Condition(Origin1):";
	printVector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int k=params[0];
		int a=params[1];
		int b=params[2];
		if(b==0||k==0)return true;
		for(int i=0;i+k<p.size();i++){
			if((p[i]-p[i+k-1])==0)f=f&&((p[i]%b)==a);
			if(p[i+k]==0)break;
			f=f&&((p[i]-p[i+k])>=1);
		}
		return f;
	};
}

function<bool(Par &)>generateConditionOriginal4(vector<int> & params){
	//all product has x twos.
	cout<<" Condition(sp,s,t,x,sw): ";
	printVector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int sp=params[0];
		int s=params[1];
		int t=params[2];
		int x=params[3];
		int sw=params[4];
		int cnt=0;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			f=f&&(p[i]>=sp);
			if(p[i+s]!=0){
				f=f&&((p[i]-p[i+s])>=t);
			}
			int tmp=p[i];
			while(tmp%2==0){
				tmp/=2;
				cnt++;
			}
		}
		if(sw==0)f=f&&(cnt<=x);
		else f=f&&(cnt>=x);
		return f;
	};
}

function<bool(Par &)>generateConditionOriginal5(vector<int> & params){
	cout<<"Condition(sp,dist,diff,a) :";
	printVector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int sp=params[0];
		int dist=params[1];
		int diff=params[2];
		int a=params[3];
		int b=params[4];
		for(int i=0;i<p.size();i++){
			if(p[i]==0 || !f)break;
			f=f&&(p[i]>=sp);
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			if(p[i]%a==0)f=f&&(p[i]-p[i+dist]>=diff+b);
			}
		}	
		return f;
	};
}
function<bool(Par &)> generateConditionsOriginal6(vector<int> & params){
  cout<<"Condition(sp,dist,diff,A1,B1,C1,D1,A2,B2,C2,D2):";
  printVector(params);
	const int sp=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int A1=params[3];
	const int B1=params[4];
	const int C1=params[5];
	const int D1=params[6];
	const int A2=params[7];
	const int B2=params[8];
	const int C2=params[9];
	const int D2=params[10];
  return [=](Par & p)->bool{
		if(D1==0||D2==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&(p[i]>=sp);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			}
			if(p[i+A1]!=0){
				if(p[i]-p[i+A1]<=B1){
					unsigned short sum=0;
					for(int j=0;j<=A1;j++)sum+=p[i+j];
					f=f&&(sum%D1==C1);
				}
			}
			if(p[i+A2]!=0){
				if(p[i]-p[i+A2]<=B2){
					unsigned short sum=0;
					for(int j=0;j<=A2;j++)sum+=p[i+j];
					f=f&&(sum%D2==C2);
				}
			}
		}
		return f;
  };
}

function<bool(Par &)>generateConditionsGeneralMacMahon(vector<int> & params){
	cout<<"Conditions(sp,k):";
	printVector(params);
	const int sp=params[0];
	const int k=params[1];
	return [=](Par & p)->bool{
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			f=f&&(p[i]>=sp);
			if(p[i+k]!=0){
				for(int j=1;j<=k;j++){
					f=f&&(p[i]-p[i+j]==0 || p[i]-p[i+j]>k);
				}
			}
		}
		return f;
	};
}

function<bool(Par &)> generateConditionsOriginal6_1(vector<int> & params){
  cout<<"Condition(sp,dist,diff,A1,B1,C1,D1,2,0,0,4,1,0,4,5):";
  printVector(params);
	const int sp=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int A1=params[3];
	const int B1=params[4];
	const int C1=params[6];
	const int D1=params[7];
  return [=](Par & p)->bool{
		if(D1==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&(p[i]>=sp);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			}
			if(p[i+A1]!=0){
				if(p[i]-p[i+A1]<=B1){
					unsigned short sum=0;
					for(int j=0;j<=A1;j++)sum+=p[i+j];
					f=f&&(sum%D1==C1);
				}
			}
			if(p[i+2]!=0){
				if(p[i]-p[i+2]<=0){
					unsigned short sum=0;
					for(int j=0;j<=2;j++)sum+=j*p[i+j];
					f=f&&(sum%4==0);
				}
			}
			if(p[i+1]!=0){
				if(p[i]-p[i+1]<=0){
					unsigned short sum=0;
					for(int j=0;j<=1;j++)sum+=j*p[i+j];
					f=f&&(sum%5==4);
				}
			}
		}
		return f;
  };
}
function<bool(Par &)> generateConditionsOriginal7(vector<int> & params){
  cout<<"Condition(sp,dist,diff,A1,B1,C1,D1,A2,B2,C2,D2):";
  printVector(params);
	const int sp=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int A1=params[3];
	const int B1=params[4];
	const int C1=params[5];
	const int D1=params[6];
	const int A2=params[7];
	const int B2=params[8];
	const int C2=params[9];
	const int D2=params[10];
  return [=](Par & p)->bool{
		if(D1==0||D2==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&(p[i]>=sp);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			}
			if(p[i+A1]!=0){
				if(p[i]-p[i+A1]<=B1){
					unsigned short sum=0;
					for(int j=0;j<=A1;j++)sum+=(j+1)*p[i+j];
					f=f&&(sum%D1==C1);
				}
			}
			if(p[i+A2]!=0){
				if(p[i]-p[i+A2]<=B2){
					unsigned short sum=0;
					for(int j=0;j<=A2;j++)sum+=(j+1)*p[i+j];
					f=f&&(sum%D2==C2);
				}
			}
		}
		return f;
  };
}

function<bool(Par &)> generateConditionsOriginal8(vector<int> & params){
  cout<<"Condition(no appear(bit),dist,diff,residue(bit) , equal Mod):";
  printVector(params);
	const int np=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int residue=params[3];
	const int D=params[4];
  return [=](Par & p)->bool{
		if(D==0 || diff==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&((np>>(p[i]-1)&1)!=1);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
				if(p[i]-p[i+dist]==diff){
					bool tmp=false;
					f=f&&(p[i]%D==1);
				}
			}
		}
		return f;
  };
}
