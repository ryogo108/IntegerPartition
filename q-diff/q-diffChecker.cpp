#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"

vector<part> partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = false;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 3;
      if(p[i] % 3 == 0){
        isSuitable &= p[ i ] - p[ i + 1 ] >= 4;
      }
    }
  }
  return isSuitable;
}

unsigned int refineFunction(Par & p){
  unsigned int refineValue = 0;
  for(int i = 0; i < p.size(); i++){
    if(p[i] == 0) break;
    if(p[i] % 3 == 0){
      refineValue += 2;
    }
    else{
      refineValue++;
    }
  }
  return refineValue;
}

void check_qdiff(const Polynomial & p){
	const int order=6;
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
  /*coefs[0]=Polynomial({{1},{0,-1}});
  coefs[1]=Polynomial({{-1},{0,1}});
  coefs[2]=Polynomial({{0},{0,-1}});*/
  coefs[0]=Polynomial({{-1},{0,1}});
  coefs[1]=Polynomial({{0},{0,-1},{0,1}});
  coefs[2]=Polynomial({{0},{0,1},{0,-1}});
  coefs[3]=Polynomial({{1},{0},{0,1}});
  coefs[4]=Polynomial({{0},{0},{0},{0,1}});
  coefs[5]=Polynomial({{0},{0},{0},{0,-1}});
  coefs[6]=Polynomial({{0},{0},{0},{0,1}});
  shifted[0]=p;
  shifted[1]=qShift(p,1);
  shifted[2]=qShift(p,2); 
  shifted[3]=qShift(p,3); 
  shifted[4]=qShift(p,4); 
  shifted[5]=qShift(p,5); 
  shifted[6]=qShift(p,6); 
/*  shifted[0]=p;
  shifted[1]=qShift(p,1);
  shifted[2]=qShift(p,2); */
  
	Polynomial diff;
	for(int i=0;i<=order;i++){
		diff=diff+coefs[i]*shifted[i];
	}
	cout<<"q-diff:"<<endl;
	for(int i=0;i<=order;i++){
		print_Polynomial(coefs[i]);
		cout<<"* ";
		cout<<"term["<<i<<"]"<<endl;
	}
	cout<<"= ";
	print_Polynomial(diff);
}
void test(Polynomial & p1,Polynomial & p2){
  Polynomial diff=p1-p2;
  print_Polynomial(diff);
}

int main(int argc,char *argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // remark : 0 の分割は生成されない.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  //printVector(partitions); // for debug

  // partitions のうちで Suitable な分割を大きさごと, refineFunction の値ごとに数える
  // Option : countWithPrint = true として Suitable な分割を数え上げと同時に表示する.
  Polynomial refinedGeneratingFunction = countSuitableRefinedPartitions( maxPartitionSize, partitions, isSuitablePartition, refineFunction, countWithPrint ) + Polynomial({{1}});

  print_Polynomial(refinedGeneratingFunction);
}

