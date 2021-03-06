/*LAB 2 PAUL KUBALA
Used Collaboration with Chris Yarish To Complete
Assignment
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include <cstring>
#include <cassert>
#include <hdf5.h>
#include<algorithm>

namespace util
{

  void read_hdf(const std::string &filename, double* &data, int &m_rows, int &m_cols){

    hid_t file_id, dataset_id, space_id, property_id;
    herr_t status;

    //Create a new file using the default properties.
    file_id = H5Fopen (filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    dataset_id = H5Dopen(file_id, "x", H5P_DEFAULT);
    space_id = H5Dget_space(dataset_id);
    int length = H5Sget_simple_extent_npoints(space_id);
    hsize_t dims[2];
    hsize_t mdims[2];
    status = H5Sget_simple_extent_dims(space_id,dims,mdims);
    m_rows = dims[0];
    m_cols = dims[1];
    
    data = new double[length];
    status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL,
		     H5P_DEFAULT, data);

    status = H5Sclose(space_id);
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);

  }

  void write_hdf(const std::string &filename, double* &data, int &m_rows, int &m_cols){

    hid_t file_id, dataset_id, space_id, property_id;
    herr_t status;

    hsize_t dims[2] = {m_rows,m_cols};
   
    
    //Create a new file using the default properties.
    file_id = H5Fcreate (filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    //Create dataspace. Setting maximum size to NULL sets the maximum
    //size to be the current size.
    space_id = H5Screate_simple (2, dims, NULL);

    //Create the dataset creation property list, set the layout to compact.
    property_id = H5Pcreate (H5P_DATASET_CREATE);
    status = H5Pset_layout (property_id, H5D_CONTIGUOUS);

    // Create the dataset.
    dataset_id = H5Dcreate (file_id, "x", H5T_NATIVE_DOUBLE, space_id, H5P_DEFAULT, property_id, H5P_DEFAULT);
   
    //Write the data to the dataset.
    status = H5Dwrite (dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    status = H5Sclose(space_id);
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);
    status = H5Pclose(property_id);

  }

};


int main(int argc,char* argv[]){
  // Take Input Of First File or Matrix
  std::string matrixA=argv[1];
 std::string matrixB=argv[2];
 std::string matrixC=argv[3];
 double* input_1=0;
  double* input_2=0;
  

  int row = 0;
  int column = 0;



  //  std::ifstream  input_file(filename.c_str());
 
  std::cout.precision(8);
  
  //  input_file >> row;
  //input_file >> column;

  // Testing to see if we are getting column in correctly 
  //  std::cout << col << '\n';
 
  // Take the matrix and put into single array
 
 input_1 = new double[row*column];
 util::read_hdf(matrixA, input_1,row,column); 
/*
  for(int i=0; i<row; i++){
    for(int j=0;j<column; j++){
      int index = i*column + j;
      input_file >> input_1[index];
      // std::cout << "index = "  << input_1[index] << '\n';
    }
  }
 */

  // Do the Same Procedure as above with the second
  // Matrix
  int row2=0;
  int column2=0;
  // filename=argv[2];
  // std::cout << filename << '\n';
  // std::ifstream  input_file2(filename.c_str());
  // input_file2 >> row2;
  // input_file2 >> column2;
  //  Test to see if the row and col are correct
  //  std::cout << row2 << " " << column2 << '\n';
 
input_2 = new double[row2*column2];
 util::read_hdf(matrixB, input_2,row2,column2);
/* for(int i=0; i<row2; ++i){
    for(int j=0;j<column2;++j){
      int index = i*column2 + j;
      input_file2 >> input_2[index];
      //  std::cout << "index = "  << input_2[index] << '\n';
      //      Test to see if input_2[]is correct
      //      std::cout << input_2[index] << "  " << '\n';
    }
    }*/
  //std::cout << "\n\n\n\n\n\n\n\n\n\n";
  // test: matrix1 = 10x5, matrix2 = 5x7, solnmatrix= 10x7
  // row = 10, col = 5, row2 = 5, col2 = 7

  double* end_matrix=0;
  end_matrix = new double[row*column2];
  //  memset(end_matrix, 0, row*column2*sizeof(double));
  // Array Multiple Function
  //int blocksize = 4;

  int mm, m, nn, n, k, kk, M, N, K;
  M = row;
  N = column2;
  K = column;
  int block_size = 40;
  //  assert(M%block_size == 0);
  //  assert(N%block_size == 0);
  //  assert(K%block_size == 0);


  //#pragma omp parallel for collapse(3) default(none) private(M,N,K,block_size,mm,nn,kk) shared(input_1,input_2, end_matrix) 
  for(m = 0; m < M; m+=block_size){  
    for(n = 0; n < N; n+=block_size){  
      for(k = 0; k < K; k+=block_size){  

	for(mm = m; mm < std::min(m+block_size, M); mm++){
	  for(nn = n; nn < std::min(n+block_size, N); nn++){
	    int index3 = mm*N + nn;
	    for(kk = k; kk < std::min(k+block_size,K); kk++){
	      int index1 = mm*K + kk;
	      int index2 = kk*N + nn;
	      
	      end_matrix[index3] += input_1[index1]*input_2[index2];
	      //	      asm("nop");
		  }}}
      }
    }
  }


  util::write_hdf(matrixC, end_matrix,row,column2);
  // Print Matrix
  /*
  std::cout << row << " " << column2 << '\n';
  k = 0;
  int counter;
  for(counter = 0; counter<row*column2; counter++){
    if(k <= column2-1){
    std::cout << end_matrix[counter] << " ";
    k++;
    }
    else{
      std::cout << '\n';
      k=0;
      counter-=1;
    }  
  }
  */
  // Testing for loop to see if 
  // enough iterations are being done
  // std::cout << counter;

  // Delete all input data and array
  // for next use of the code
  delete[] input_1;
  delete[] input_2;
  delete[] end_matrix;
  return 0;
}
