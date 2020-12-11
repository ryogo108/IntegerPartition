#include<iostream>
#include<vector>
//#include<gmpxx.h>
using namespace std;

//using Q=mpq_class;
//using Z=mpz_class;
template<class T> using Mat=vector<vector<T> >;

template <class T> void printVector(const vector<T>& v);
template <class T> void printMatrix(const Mat<T>&  m);
template <class T> void printMatrixInRow(const Mat<T>&  m);

template<class T> int matrixRank(Mat<T>& m);

//solve Ax=b
template<class T> vector<vector<T> > GaussianElimination(Mat<T>& A);


template <class T> vector<T> operator+(const vector<T>& vl,const vector<T>& vr);
template <class T> vector<T> operator-(const vector<T>& vl,const vector<T>& vr);
template <class T> vector<T> operator*(const vector<T>& vl,const T& r);
template <class T> vector<T> operator*(const T& l,const vector<T>& vr);
template <class T> vector<T> operator-(const vector<T>& v);

template <class T> vector<T> operator*(const Mat<T>& ml,const vector<T>& vr);
template <class T> Mat<T> operator+(const Mat<T>& ml,const Mat<T>& mr);
template <class T> Mat<T> operator-(const Mat<T>& ml,const Mat<T>& mr);
template <class T> Mat<T> operator*(const Mat<T>& ml,const Mat<T>& mr);
template <class T> Mat<T> operator*(const T& l,const Mat<T>& mr);
template <class T> Mat<T> operator*(const Mat<T>& ml,const T& r);
template <class T> Mat<T> operator/(const Mat<T>& ml,const T& r);
template <class T> Mat<T> operator-(const Mat<T>& m);

template <class T> void printVector(const vector<T>& v){
  for(int i=0;i<v.size();i++){
    if(i)cout<<" ";
    cout<<v[i];
  }
  cout<<endl<<endl;
}


template <class T> void printMatrix(const Mat<T>&  m){
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      cout<<m[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}
template <class T> void printMatrixInRow(const Mat<T>&  m){
  if(m.empty()){
    throw invalid_argument("empty matrix cannot be shown");
  }
  else cout<<m.size()<<" "<<m[0].size();
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      cout<<" ";
      cout<<m[i][j]<<" ";
    }
  }
  cout<<endl;
}
template<class T> int matrixRank(Mat<T>& m){
  //行列mのrankを求める
  if(m.empty())return 0;
  int rank=0;//次のピボットが存在する行
  for(int pivot=0;pivot<m[0].size();pivot++){//左から各列をピボットだとして探索する
    //printMatrix(m);
    for(int i=rank;i<m.size();i++){ //pivot列のrank行よりも下にに非零要素があればそれをピボットとして簡約化を行う。なければ、rankはそのまま次の列を探索する。
      if(m[i][pivot]!=0){
        m[rank].swap(m[i]);
        for(int j=m[rank].size()-1;j>=pivot;j--){ //normalize of pivot row
           m[rank][j]/=m[rank][pivot];
        }
        for(int i=0;i<m.size();i++){ //subtraction of every row with pivot row
          if(i==rank)continue;
          for(int j=m[i].size()-1;j>=pivot;j--){
            m[i][j]-=m[i][pivot]*m[rank][j];
          }
        }
        rank++;
        break;
      }
    }
  }
  //printMatrix(m);
  return rank;
}

template<class T> vector< vector<T> > GaussianElimination(Mat<T>& A){
  //Ax=0の解空間の基底を全て求める
  int rank=matrixRank(A);//Aのrankを求める。同時にAは行基本変形により簡約化される。
  vector<T> x(A[0].size(),0);
  vector<vector<T> >re;
  if(rank==A[0].size()){
    re.push_back(x);
    return re;//xが自明な解のみを持つ場合。
  }
  int row=0;//次にピボットとなる要素が存在する行
  vector<int> pick;//ピボットでない列のindex
  re.clear();
  for(int j=0;j<A[0].size();j++){ //左から順にピボットになっていない列を探す
    if(row==rank){//一番下まで探索し切った
      pick.push_back(j);
    }
    else if(A[row][j]!=1){//ピボットでない列が見つかった
      pick.push_back(j);
    }
    else row++;
  }
  for(int i=0;i<pick.size();i++){
    x=vector<T>(A[0].size(),0);
    x[pick[i]]=1;
    row=0;
    for(int j=0;j<A[0].size();j++){//左から順にピボットなっている列を探す。その各列jに対しx[j]はpick列の要素*(-1)。ピボットでもpickでもない列j'はx[j']=0としている。
      if(A[row][j]==1){
        x[j]=-1*A[row][pick[i]];
        row++;
     }
     if(row==rank)break;
    }
    re.push_back(x);
  }
  return re;
}


template<class T> vector<T> operator+(const vector<T>& vl,const vector<T>& vr){
  if(vl.size()!=vr.size())throw invalid_argument("a vector cannot add to a vector which has different size");
  vector<T> v(vl);
  for(int i=0;i<v.size();i++)v[i]=v[i]+vr[i];
  return v;
}
template <class T> vector<T> operator-(const vector<T>& vl,const vector<T>& vr){
  if(vl.size()!=vr.size())throw invalid_argument("a vector cannot  subtract with a vector which has different size");
  vector<T> v(vl);
  for(int i=0;i<v.size();i++)v[i]=v[i]-vr[i];
  return v;
}
template <class T> vector<T> operator*(const vector<T>& vl,const T& r){
  vector<T> v(vl);
  for(int i=0;i<v.size();i++)v[i]=v[i]*r;
  return v;
}
template <class T> vector<T> operator*(const T& l,const vector<T>& vr){
  vector<T> v(vr);
  for(int i=0;i<v.size();i++)v[i]=v[i]*l;
  return v;

}
template <class T> vector<T> operator-(const vector<T>& v){
  vector<T> rev(v);
  for(int i=0;i<rev.size();i++)rev[i]=-v[i];
  return rev;

}
template <class T> vector<T> operator*(const Mat<T>& ml,const vector<T>& vr){ 
  if(ml.empty())throw invalid_argument("empty matrix cannot time to a vector");
  if(ml[0].size()!=vr.size())throw invalid_argument("a matrix cannot time  to a vector which has different size");
  vector<T> v(ml.size(),0);
  for(int i=0;i<v.size();i++){
    T sum=0;
    for(int j=0;j<ml[i].size();j++)sum+=ml[i][j]*vr[j];
    v[i]=sum;
  }
  return v;
}
template <class T> Mat<T> operator+(const Mat<T>& ml,const Mat<T>& mr){
  if(ml.empty() || mr.empty())throw invalid_argument("empty matrix cannto add to a matrix");
  if(ml.size()!=mr.size() || ml[0].size()!=mr[0].size())throw invalid_argument("a matrix cannot add to a matrix which has different shape");
  Mat<T> m(ml.size(),vector<T>(ml[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      m[i][j]=ml[i][j]+mr[i][j];
    }
  }
  return m;
}
template <class T> Mat<T> operator-(const Mat<T>& ml,const Mat<T>& mr){
  if(ml.empty() || mr.empty())throw invalid_argument("empty matrix cannot subtract with a matrix");
  if(ml.size()!=mr.size() || ml[0].size()!=mr[0].size())throw invalid_argument("a matrix cannot subtract with a matrix which has different shape");
  Mat<T> m(ml.size(),vector<T>(ml[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      m[i][j]=ml[i][j]-mr[i][j];
    }
  }
  return m;
  
}
template <class T> Mat<T> operator*(const Mat<T>& ml,const Mat<T>& mr){
  if(ml.empty() || mr.empty())throw invalid_argument("empty matrix cannot time to a matrix");
  if(ml[0].size()!=mr.size())throw invalid_argument("a matrix cannot time to a matrix which has invalid shape");
  Mat<T> m(ml.size(),vector<T>(mr[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      for(int k=0;k<ml[0].size();k++){
        m[i][j]+=ml[i][k]*mr[k][j];
      }
    }
  }
  return m;

}
template <class T> Mat<T> operator*(const T& l,const Mat<T>& mr){
  Mat<T> m(mr.size(),vector<T>(mr[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      m[i][j]=mr[i][j]*l;
    }
  }
  return m;

};
template <class T> Mat<T> operator*(const Mat<T>& ml,const T& r){
  Mat<T> m(ml.size(),vector<T>(ml[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      m[i][j]=ml[i][j]*r;
    }
  }
  return m;

}
template <class T> Mat<T> operator/(const Mat<T>& ml,const T& r){
  Mat<T> m(ml.size(),vector<T>(ml[0].size(),0));
  for(int i=0;i<m.size();i++){
    for(int j=0;j<m[i].size();j++){
      m[i][j]=ml[i][j]/r;
    }
  }
  return m;

}
template <class T> Mat<T> operator-(const Mat<T>& m){
  Mat<T> rem(m.size(),vector<T>(m[0].size(),0));
  for(int i=0;i<rem.size();i++){
    for(int j=0;j<rem[i].size();j++){
      rem[i][j]=-m[i][j];
    }
  }
  return rem;
}
