//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sort.cpp
//
// Code generation for function 'sort'
//

// Include files
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
namespace internal {
void sort(::coder::array<int, 1U> &x)
{
  array<int, 1U> b_iwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  array<int, 1U> vwork;
  array<int, 1U> xwork;
  int b_xwork[256];
  int c_iwork[256];
  int idx4[4];
  int x4[4];
  int dim;
  int i;
  int k;
  int vlen;
  int vstride;
  signed char perm[4];
  dim = 0;
  if (x.size(0) != 1) {
    dim = -1;
  }
  if (dim + 2 <= 1) {
    i = x.size(0);
  } else {
    i = 1;
  }
  vlen = i - 1;
  vwork.set_size(i);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x.size(0);
  }
  for (int j{0}; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork[k] = x[j + k * vstride];
    }
    iidx.set_size(vwork.size(0));
    dim = vwork.size(0);
    for (i = 0; i < dim; i++) {
      iidx[i] = 0;
    }
    i = vwork.size(0);
    if (vwork.size(0) != 0) {
      int b_i;
      int b_j;
      int i1;
      int i2;
      int i4;
      int nBlocks;
      int nLeft;
      int nQuartets;
      x4[0] = 0;
      idx4[0] = 0;
      x4[1] = 0;
      idx4[1] = 0;
      x4[2] = 0;
      idx4[2] = 0;
      x4[3] = 0;
      idx4[3] = 0;
      iwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (nBlocks = 0; nBlocks < dim; nBlocks++) {
        iwork[nBlocks] = 0;
      }
      xwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (nBlocks = 0; nBlocks < dim; nBlocks++) {
        xwork[nBlocks] = 0;
      }
      nQuartets = vwork.size(0) >> 2;
      for (b_j = 0; b_j < nQuartets; b_j++) {
        b_i = b_j << 2;
        idx4[0] = b_i + 1;
        idx4[1] = b_i + 2;
        idx4[2] = b_i + 3;
        idx4[3] = b_i + 4;
        x4[0] = vwork[b_i];
        dim = vwork[b_i + 1];
        x4[1] = dim;
        i4 = vwork[b_i + 2];
        x4[2] = i4;
        nLeft = vwork[b_i + 3];
        x4[3] = nLeft;
        if (vwork[b_i] <= dim) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (i4 <= nLeft) {
          dim = 3;
          i4 = 4;
        } else {
          dim = 4;
          i4 = 3;
        }
        nBlocks = x4[i1 - 1];
        nLeft = x4[dim - 1];
        if (nBlocks <= nLeft) {
          nBlocks = x4[i2 - 1];
          if (nBlocks <= nLeft) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(dim);
            perm[3] = static_cast<signed char>(i4);
          } else if (nBlocks <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(dim);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(dim);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          nLeft = x4[i4 - 1];
          if (nBlocks <= nLeft) {
            if (x4[i2 - 1] <= nLeft) {
              perm[0] = static_cast<signed char>(dim);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(dim);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(dim);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        iidx[b_i] = idx4[perm[0] - 1];
        iidx[b_i + 1] = idx4[perm[1] - 1];
        iidx[b_i + 2] = idx4[perm[2] - 1];
        iidx[b_i + 3] = idx4[perm[3] - 1];
        vwork[b_i] = x4[perm[0] - 1];
        vwork[b_i + 1] = x4[perm[1] - 1];
        vwork[b_i + 2] = x4[perm[2] - 1];
        vwork[b_i + 3] = x4[perm[3] - 1];
      }
      i4 = nQuartets << 2;
      nLeft = (i - i4) - 1;
      if (nLeft + 1 > 0) {
        for (k = 0; k <= nLeft; k++) {
          dim = i4 + k;
          idx4[k] = dim + 1;
          x4[k] = vwork[dim];
        }
        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (nLeft + 1 == 1) {
          perm[0] = 1;
        } else if (nLeft + 1 == 2) {
          if (x4[0] <= x4[1]) {
            perm[0] = 1;
            perm[1] = 2;
          } else {
            perm[0] = 2;
            perm[1] = 1;
          }
        } else if (x4[0] <= x4[1]) {
          if (x4[1] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 2;
            perm[2] = 3;
          } else if (x4[0] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 2;
          } else {
            perm[0] = 3;
            perm[1] = 1;
            perm[2] = 2;
          }
        } else if (x4[0] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 1;
          perm[2] = 3;
        } else if (x4[1] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 3;
          perm[2] = 1;
        } else {
          perm[0] = 3;
          perm[1] = 2;
          perm[2] = 1;
        }
        for (k = 0; k <= nLeft; k++) {
          i1 = perm[k] - 1;
          dim = i4 + k;
          iidx[dim] = idx4[i1];
          vwork[dim] = x4[i1];
        }
      }
      i4 = 2;
      if (i > 1) {
        if (i >= 256) {
          nBlocks = i >> 8;
          for (int b{0}; b < nBlocks; b++) {
            nQuartets = (b << 8) - 1;
            for (int b_b{0}; b_b < 6; b_b++) {
              int bLen2;
              int nPairs;
              b_i = 1 << (b_b + 2);
              bLen2 = b_i << 1;
              nPairs = 256 >> (b_b + 3);
              for (k = 0; k < nPairs; k++) {
                i4 = (nQuartets + k * bLen2) + 1;
                for (b_j = 0; b_j < bLen2; b_j++) {
                  dim = i4 + b_j;
                  c_iwork[b_j] = iidx[dim];
                  b_xwork[b_j] = vwork[dim];
                }
                i2 = 0;
                nLeft = b_i;
                dim = i4 - 1;
                int exitg1;
                do {
                  exitg1 = 0;
                  dim++;
                  if (b_xwork[i2] <= b_xwork[nLeft]) {
                    iidx[dim] = c_iwork[i2];
                    vwork[dim] = b_xwork[i2];
                    if (i2 + 1 < b_i) {
                      i2++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    iidx[dim] = c_iwork[nLeft];
                    vwork[dim] = b_xwork[nLeft];
                    if (nLeft + 1 < bLen2) {
                      nLeft++;
                    } else {
                      dim -= i2;
                      for (b_j = i2 + 1; b_j <= b_i; b_j++) {
                        i1 = dim + b_j;
                        iidx[i1] = c_iwork[b_j - 1];
                        vwork[i1] = b_xwork[b_j - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          dim = nBlocks << 8;
          i4 = i - dim;
          if (i4 > 0) {
            merge_block(iidx, vwork, dim, i4, 2, iwork, xwork);
          }
          i4 = 8;
        }
        dim = iwork.size(0);
        b_iwork.set_size(iwork.size(0));
        for (nBlocks = 0; nBlocks < dim; nBlocks++) {
          b_iwork[nBlocks] = iwork[nBlocks];
        }
        dim = xwork.size(0);
        iwork.set_size(xwork.size(0));
        for (nBlocks = 0; nBlocks < dim; nBlocks++) {
          iwork[nBlocks] = xwork[nBlocks];
        }
        merge_block(iidx, vwork, 0, i, i4, b_iwork, iwork);
      }
    }
    for (k = 0; k <= vlen; k++) {
      x[j + k * vstride] = vwork[k];
    }
  }
}

} // namespace internal
} // namespace coder

// End of code generation (sort.cpp)
