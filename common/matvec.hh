#ifndef __MATVEC_HH__
#define __MATVEC_HH__

#include<iostream>
#include<math.h>

#include "misc.hh"
#include "fixedvector.hh"
#include <dune/common/exceptions.hh>

namespace Dune {
/** @defgroup Common Dune Common Module

  This module contains classes for general usage in dune, such as e.g.
  (small) dense matrices and vectors or containers.

  @{
 */


//************************************************************************
/*! Generic class for static rectangular matrices
 */
template<int n, int dim, class T = double>
class Mat {
public:
  enum { m = (dim > 0) ? dim : 1 };

  //! remember the dimension of the matrix 
  enum { dimRow = dim };
  enum { dimCol = n };
  
  //! Constructor making uninitialized matrix
  Mat() {}

  //! Constructor setting all entries to t
  Mat(T t)
  {
    for(int j=0; j<m; j++)
      for (int i=0; i<n; i++) a[j](i) = t;
  }

  //! operator () for read/write access to element in matrix
  T& operator() (int i, int j) {return a[j](i);}
  
  //! operator () for read/write access to element in matrix
  const T& operator() (int i, int j) const {return a[j](i);} 

  //! operator () for read/write access to column vector
  Vec<n,T>& operator() (int j) {return a[j];}

  //! operator [] for read/write access to column vector
  Vec<n,T>& operator[] (int j) {return a[j];}

  //! matrix/vector multiplication
  Vec<n,T> operator* (const Vec<m,T>& x)
  {
    Vec<n,T> z(0.0);
    for (int j=0; j<m; j++)
      for (int i=0; i<n; i++) z(i) += a[j](i) * x[j];
    return z;
  }
  
  //! matrix/vector multiplication with transpose of matrix 
  Vec<m,T> mult_t (const Vec<n,T>& x) const
  {
    Vec<m,T> z(0.0);
    const Mat<n,m,T> &matrix = (*this);
    for (int j=0; j<n; j++)
      for (int i=0; i<m; i++) z(i) += matrix(j,i) * x[j];
    return z;
  }
  
  //! multiplication assignment with scalar
  Mat<n,m,T>& operator*= (T t)
  {
    for(int j=0; j<m; j++) a[j] *= t; 
    return *this;
  }

    //! Print matrix content to an output stream
  void print (std::ostream& s, int indent)
  {
    for (int k=0; k<indent; k++) s << " ";
    s << "Mat [n=" << n << ",m=" << m << "]" << std::endl;
    for (int i=0; i<n; i++)
    {
      for (int k=0; k<indent+2; k++) s << " ";
      s << "row " << i << " [ ";
      for (int j=0; j<m; j++) s << this->operator()(i,j) << " ";
      s << "]" << std::endl;
    }
  }

  //! calculates the determinant of this matrix 
  T determinant () const;
  
  //! calculates the inverse of this matrix and stores it in 
  //! the parameter inverse, return is the determinant
  T invert (Mat<n,m,T>& inverse) const;

  //! calculates the transpose of this matrix and stores it in 
  //! the parameter transpose, return is the determinant
  void transpose (Mat<m,n,T>& transpose) const;

  //! scalar product of two vectors stored in matrixform
  T operator* (const Mat<n,m,T>& b) const
  {
    if (m != 1)
      DUNE_THROW(MathError,
                 "scalar product only defined for (m x 1) matrizes");
    T s=0;
    for (int i=0; i<n; i++) s += this->operator()(i,0) * b(i,0);
    return s;
  }

  //! scalar product of two vectors; one of them stored in matrixform
  T operator* (const Vec<n,T>& b) const
  {
    if (m != 1)
      DUNE_THROW(MathError,
                 "scalar product only defined for (m x 1) matrizes");
    T s=0;
    for (int i=0; i<n; i++) s += this->operator()(i,0) * b[i];
    return s;
  }

private:
  //! built-in array to hold the data
  Vec<n,T> a[m];
};

namespace HelpMat {

// calculation of determinat of matrix   
template <int row,int col, typename T>
static inline T determinantMatrix (const Mat<row,col,T> &matrix)
{
  std::cerr << "No default implementation of determinantMatrix for Mat<" << row << "," << col << "> !\n";
  abort();
  return 0.0;
}

template <typename T>
static inline T determinantMatrix (const Mat<1,1,T> &matrix)
{
  return matrix(0,0);
}

template <typename T>
static inline T determinantMatrix (const Mat<2,2,T> &matrix)
{
  T det = (matrix(0,0)*matrix(1,1) - matrix(0,1)*matrix(1,0));      
  return det;
}
template <typename T>
static inline T determinantMatrix (const Mat<3,3,T> &matrix)
{
  // code generated by maple 
  T t4  = matrix(0,0) * matrix(1,1);
  T t6  = matrix(0,0) * matrix(1,2);
  T t8  = matrix(0,1) * matrix(1,0);
  T t10 = matrix(0,2) * matrix(1,0);
  T t12 = matrix(0,1) * matrix(2,0);
  T t14 = matrix(0,2) * matrix(2,0);

  T det = (t4*matrix(2,2)-t6*matrix(2,1)-t8*matrix(2,2)+
           t10*matrix(2,1)+t12*matrix(1,2)-t14*matrix(1,1));
  return det;
}
// calculation of inverse of matrix 
template <int row,int col, typename T>
static inline T invertMatrix (const Mat<row,col,T> &matrix, Mat<row,col,T> &inverse)
{
  std::cerr << "No default implementation of invertMatrix for Mat<" << row << "," << col << "> !\n";
  abort();
  return 0.0;
}

// invert scalar 
template <typename T>
static inline T invertMatrix (const Mat<1,1,T> &matrix, Mat<1,1,T> &inverse)
{
  inverse(0,0) = 1.0/matrix(0,0);
  return (matrix(0,0));
}


// invert 2x2 Matrix 
template <typename T>
static inline T invertMatrix (const Mat<2,2,T> &matrix, Mat<2,2,T> &inverse)
{
  // code generated by maple 
  T det = (matrix(0,0)*matrix(1,1) - matrix(0,1)*matrix(1,0));      
  T det_1 = 1.0/det;
  inverse(0,0) =   matrix(1,1) * det_1;
  inverse(0,1) = - matrix(0,1) * det_1;
  inverse(1,0) = - matrix(1,0) * det_1;
  inverse(1,1) =   matrix(0,0) * det_1;
  return det;
}

// invert 3x3 Matrix 
template <typename T>
static inline T invertMatrix (const Mat<3,3,T> &matrix, Mat<3,3,T> &inverse)
{
  // code generated by maple 
  T t4  = matrix(0,0) * matrix(1,1);
  T t6  = matrix(0,0) * matrix(1,2);
  T t8  = matrix(0,1) * matrix(1,0);
  T t10 = matrix(0,2) * matrix(1,0);
  T t12 = matrix(0,1) * matrix(2,0);
  T t14 = matrix(0,2) * matrix(2,0);

  T det = (t4*matrix(2,2)-t6*matrix(2,1)-t8*matrix(2,2)+
           t10*matrix(2,1)+t12*matrix(1,2)-t14*matrix(1,1));
  T t17 = 1.0/det;

  inverse(0,0) =  (matrix(1,1) * matrix(2,2) - matrix(1,2) * matrix(2,1))*t17;
  inverse(0,1) = -(matrix(0,1) * matrix(2,2) - matrix(0,2) * matrix(2,1))*t17;
  inverse(0,2) =  (matrix(0,1) * matrix(1,2) - matrix(0,2) * matrix(1,1))*t17;
  inverse(1,0) = -(matrix(1,0) * matrix(2,2) - matrix(1,2) * matrix(2,0))*t17;
  inverse(1,1) =  (matrix(0,0) * matrix(2,2) - t14) * t17;
  inverse(1,2) = -(t6-t10) * t17;
  inverse(2,0) =  (matrix(1,0) * matrix(2,1) - matrix(1,1) * matrix(2,0)) * t17;
  inverse(2,1) = -(matrix(0,0) * matrix(2,1) - t12) * t17;
  inverse(2,2) =  (t4-t8) * t17;

  return det;
}
  
} // end namespace HelpMat 
template <int n, int m, class T>
inline std::ostream& operator<< (std::ostream& s, Mat<n,m,T>& A)
{
  A.print(s,0);
  return s;
}

// implementation od determinant 
template <int n, int m, class T>
inline T Mat<n,m,T>::determinant () const
{
  return HelpMat::determinantMatrix(*this);
}

// implementation of invert 
template <int n, int m, class T>
inline T Mat<n,m,T>::invert (Mat<n,m,T>& inverse) const
{
  return HelpMat::invertMatrix( *this , inverse);
}

// implementation of transpose 
template <int n, int m, class T>
inline void Mat<n,m,T>::transpose (Mat<m,n,T>& transpose) const
{
  const Mat<n,m,T> & matrix = (*this);
  for(int i=0; i<n; i++)
    for(int k=0; k<m; k++)
      transpose(i,k) = matrix(k,i);
}


/** @} */

}// end namespace Dune 


#endif










