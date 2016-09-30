#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void getCofactor(int** A, int** temp, int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}







int determinant(int** A, int n)
{
    int D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
 
   int** temp = new int*[n];  //adj
for(int i = 0; i < n; ++i)
    temp[i] = new int[n];
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}






void adjoint(int** A,int** adj,int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1;

 int** temp = new int*[N];  //adj
for(int i = 0; i < N; ++i)
    temp[i] = new int[N];


    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}
 
// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(int** A, float** inverse,int N)
{
    // Find determinant of A[][]
    int det = determinant(A, N);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    int** adj = new int*[N];  //adj
for(int i = 0; i < N; ++i)
    adj[i] = new int[N];

    adjoint(A, adj,N);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/float(det);
 
    return true;
}












int main()
{

    
    int r1,r2,c1,c2,num;float sum=0.0;
    cout<<"enter the order of matrix X \n";
    cout<<"enter r1\n";
cin>>r1;
cout<<"enter c1\n";
cin>>c1;

int** X = new int*[r1];   //xxxxxxxxxxxxxxxxxxxxxxxx
for(int i = 0; i < r1; ++i)
    X[i] = new int[c1];


int** XT = new int*[c1];  //xxxxxxxxxxxxxxxttttranspoe
for(int i = 0; i < c1; ++i)
    XT[i] = new int[r1];

int** XTX = new int*[r1];  //XTX
for(int i = 0; i < r1; ++i)
    XTX[i] = new int[r1];

int** adj = new int*[r1];  //adj
for(int i = 0; i < r1; ++i)
    adj[i] = new int[r1];

float** inv = new float*[r1];  //inverse
for(int i = 0; i < r1; ++i)
    inv[i] = new float[r1];

float** result = new float*[r1];  //adj
for(int i = 0; i < r1; ++i)
    result[i] = new float[r1];
float** fresult = new float*[r1];  //adj
for(int i = 0; i < r1; ++i)
    fresult[i] = new float[r1];

for(int i=0;i<c1;i++)
    {
        cout<<"enter row :"<<i+1<<" elements\n";
    
    for(int j=0;j<r1;j++)
        {
            cin>>num;
            X[i][j]=num;
        }

    }


cout<<"Enter order of matric Y:\n";

do{
    cout<<"enter r2\n";

cin>>r2;
if(r2!=r1)
    cout<<"Matrices with entered orders can't be multiplied with X transpose enter proper order";
}

while(r2!=r1);

cout<<"enter c2\n";
cin>>c2;

int** Y = new int*[r2]; //Y
for(int i = 0; i < r2; ++i)
    Y[i] = new int[c2];



for(int i=0;i<c1;i++)
    {
        cout<<"enter row :"<<i+1<<" elements\n";
    
    for(int j=0;j<r1;j++)
        {
            cin>>num;
            Y[i][j]=num;
        }

    }

for(int i=0; i<r1; ++i)   //x into xt
    for(int j=0; j<c1; ++j)
    {
       XT[j][i]=X[i][j];
    }

 for (int c = 0; c < r1; c++) {
      for (int d = 0; d < c2; d++) {
        for (int k = 0; k < r2; k++) {
          sum = sum + XT[c][k]*X[k][d];
        }
 
        XTX[c][d] = sum;
        sum = 0;
      }
    }

cout<<"X matrix\n";
for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<X[i][j]<<" ";
        }
 cout<<"\n";
}
cout<<"XT matrix\n";
for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<XT[i][j]<<" ";
        }
 cout<<"\n";
}
cout<<"XTX matrix\n";
for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<XTX[i][j]<<" ";
        }
 cout<<"\n";
}



adjoint(XTX, adj,r1);
 cout << "\nThe Inverse is :\n";
    if (inverse(XTX, inv,r1))
        {

            for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<inv[i][j]<<" ";
        }
 cout<<"\n";
}
        }


sum=0;

 for (int c = 0; c < r1; c++) {
      for (int d = 0; d < c2; d++) {
        for (int k = 0; k < r2; k++) {
          sum = sum + XT[c][k]*Y[k][d];
        }
 
        result[c][d] = sum;
        sum = 0;
      }
    }
  /*  cout<<"XT * Y matrix :\n";
for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<result[i][j]<<" ";
        }
 cout<<"\n";
}*/
sum=0;
for (int c = 0; c < r1; c++) {
      for (int d = 0; d < r1; d++) {
        for (int k = 0; k < r1; k++) {
          sum = sum + inv[c][k]*result[k][d];
        }
 
        fresult[c][d] = sum;
        sum = 0;
      }
    }

cout<<"Theta matrix\n";
for(int i=0;i<r1;i++)
{
    for(int j=0;j<c1;j++)
      {
       
        cout<<fresult[i][j]<<" ";
        }
 cout<<"\n";
}


        }
