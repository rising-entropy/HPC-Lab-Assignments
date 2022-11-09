#include<stdio.h>
#include<stdlib.h>
#include<math.h>

__global__ void computeConvolutionValue(int mRows, int mCols, int mWidth, int convRows, int convCols, int *m, int *c, int *output, int outputCols, int outputRows){
    int rowIndex=threadIdx.x, colIndex=blockIdx.x;
    // we need the index of m[rowIndex][colIndex][0]
    int res = 0;
    for(int i=0; i<mWidth; i++){
        for(int j=0; j<convCols; j++){
            for(int k=0; k<convRows; k++){
                //m[rowIndex+k][colIndex+j][i]*c[k][j][i]
                int indexOfC = i*(convCols*convRows) + (j*convRows) + k;
                int indexOfM = i*(mRows*mCols) + ((colIndex+j)*mRows) + (rowIndex+k);
                res += (c[indexOfC] * m[indexOfM]);
            }
        }
    }
    
    int indexToFillInValue = rowIndex + (outputRows*colIndex);
    output[indexToFillInValue] = res;
}

int main(){
    char line[100] = {0};
    // 2D Conv width is 1
    int mRows=512, mCols=512, mWidth=1, convRows=3, convCols=3;
    int outputRows, outputCols;
    int i=0;
    
//     int m[mRows][mCols][mWidth], c[convRows][convCols][mWidth];
    int *m, *c, *output;
    cudaMallocManaged(&m, sizeof(int)*mRows*mCols*mWidth);
    cudaMallocManaged(&c, sizeof(int)*convRows*convCols*mWidth);

    outputRows = mRows - convRows + 1;
    outputCols = mCols - convCols + 1;
//     int output[outputRows][outputCols];
    cudaMallocManaged(&output, sizeof(int)*outputRows*outputCols);
    
    int m_input[mRows][mCols][mWidth], c_input[convRows][convCols][mWidth];
    
    for(int i=0; i<mWidth; i++){
        for(int j=0; j<mCols; j++){
            for(int k=0; k<mRows; k++){
                m_input[k][j][i] = 1;
            }
        }
    }
    for(int i=0; i<mWidth; i++){
        for(int j=0; j<convCols; j++){
            for(int k=0; k<convRows; k++){
                c_input[k][j][i] = 2;
            }
        }
    }
    int val = 0;
    for(int i=0; i<mWidth; i++){
        for(int j=0; j<convCols; j++){
            for(int k=0; k<convRows; k++){
                c[val] = c_input[k][j][i];
                val++;
            }
        }
    }
    
    val = 0;
    for(int i=0; i<mWidth; i++){
        for(int j=0; j<mCols; j++){
            for(int k=0; k<mRows; k++){
                m[val] = m_input[k][j][i];
                val++;
            }
        }
    }
    
    
    int m2[mRows][mCols][mWidth], c2[convRows][convCols][mWidth];
    
    for(int i=0; i<mWidth*convCols*convRows; i++){
        
        int z = i/(convCols*convRows);
        int v = i - z*(convCols*convRows);
        int y = v/convRows;
        v -= y*convRows;
        int x = v;
        c2[x][y][z] = c[i];
    }
    
    for(int i=0; i<mWidth*mCols*mRows; i++){
        
        int z = i/(mCols*mRows);
        int v = i - z*(mCols*mRows);
        int y = v/mRows;
        v -= y*mRows;
        int x = v;
        m2[x][y][z] = m[i];
    }
    
    computeConvolutionValue<<<outputCols, outputRows>>>(mRows, mCols, mWidth, convRows, convCols, m, c, output, outputCols, outputRows);
    cudaDeviceSynchronize();
    
    cudaFree(m);
    cudaFree(c);
    cudaFree(output);
    
    return 0;
}
