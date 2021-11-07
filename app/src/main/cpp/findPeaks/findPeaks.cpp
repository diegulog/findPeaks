//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// findPeaks.cpp
//
// Code generation for function 'findPeaks'
//

// Include files
#include "findPeaks.h"
#include "blockedSummation.h"
#include "eml_setop.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "coder_array.h"
#include "findPeaks_terminate.h"
#include <cmath>
#include <jni.h>

// Function Definitions
/*
void findPeaks(const coder::array<double, 1U> &mag, double minPeakDistance,
               coder::array<double, 1U> &indexStep)
{
*/

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_diegulog_findpeaksinf_MainActivity_findPeaksFromJNI(JNIEnv *env, jobject thiz, jdoubleArray magEntrys,
                                                             jint minPeakDistance) {
    // TODO: implement findPeaksFromJNI()
    int len = env->GetArrayLength(magEntrys);
    double *entry = env->GetDoubleArrayElements(magEntrys, JNI_FALSE);
    coder::array<double, 1U> mag;
    // Set the size of the array.
    // Change this size to the value that the application requires.
    mag.set_size(len);
    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < mag.size(0); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        mag[idx0] = entry[idx0];
    }


    coder::array<double, 1U> absdiff;
    coder::array<double, 1U> locs_temp;
    coder::array<double, 1U> magNoG;
    coder::array<int, 2U> b_y;
    coder::array<unsigned int, 2U> y;
    coder::array<int, 1U> c;
    coder::array<int, 1U> iFinite;
    coder::array<int, 1U> iInfinite;
    coder::array<int, 1U> iPk;
    coder::array<int, 1U> idx;
    coder::array<int, 1U> iwork;
    coder::array<int, 1U> r;
    coder::array<int, 1U> sortIdx;
    coder::array<bool, 1U> idelete;
    coder::array<bool, 1U> r1;
    double scale;
    double t;
    double xbar;
    int i;
    int k;
    int kend;
    int kfirst;
    int n;
    int nInf;
    int nPk;
    int qEnd;
    char dir;
    bool isinfykfirst;
    xbar = coder::blockedSummation(mag, mag.size(0)) /
           static_cast<double>(mag.size(0));
    magNoG.set_size(mag.size(0));
    kend = mag.size(0);
    for (i = 0; i < kend; i++) {
        magNoG[i] = mag[i] - xbar;
    }
    n = magNoG.size(0);
    if (magNoG.size(0) == 0) {
        t = rtNaN;
    } else if (magNoG.size(0) == 1) {
        if ((!std::isinf(magNoG[0])) && (!std::isnan(magNoG[0]))) {
            t = 0.0;
        } else {
            t = rtNaN;
        }
    } else {
        xbar = coder::blockedSummation(magNoG, magNoG.size(0)) /
               static_cast<double>(magNoG.size(0));
        absdiff.set_size(magNoG.size(0));
        for (k = 0; k < n; k++) {
            absdiff[k] = std::abs(magNoG[k] - xbar);
        }
        xbar = 0.0;
        scale = 3.3121686421112381E-170;
        kend = magNoG.size(0);
        for (k = 0; k < kend; k++) {
            if (absdiff[k] > scale) {
                t = scale / absdiff[k];
                xbar = xbar * t * t + 1.0;
                scale = absdiff[k];
            } else {
                t = absdiff[k] / scale;
                xbar += t * t;
            }
        }
        xbar = scale * std::sqrt(xbar);
        t = xbar / std::sqrt(static_cast<double>(magNoG.size(0)) - 1.0);
    }
    y.set_size(1, magNoG.size(0));
    kend = magNoG.size(0) - 1;
    for (i = 0; i <= kend; i++) {
        y[i] = i + 1U;
    }
    absdiff.set_size(y.size(1));
    kend = y.size(1);
    for (i = 0; i < kend; i++) {
        absdiff[i] = y[i];
    }
    iFinite.set_size(magNoG.size(0));
    iInfinite.set_size(magNoG.size(0));
    kend = magNoG.size(0);
    nPk = 0;
    nInf = 0;
    dir = 'n';
    kfirst = 0;
    xbar = rtInf;
    isinfykfirst = true;
    for (k = 1; k <= kend; k++) {
        bool isinfyk;
        scale = magNoG[k - 1];
        if (std::isnan(scale)) {
            scale = rtInf;
            isinfyk = true;
        } else if (std::isinf(scale) && (scale > 0.0)) {
            isinfyk = true;
            nInf++;
            iInfinite[nInf - 1] = k;
        } else {
            isinfyk = false;
        }
        if (scale != xbar) {
            char previousdir;
            previousdir = dir;
            if (isinfyk || isinfykfirst) {
                dir = 'n';
            } else if (scale < xbar) {
                dir = 'd';
                if (('d' != previousdir) && (previousdir == 'i')) {
                    nPk++;
                    iFinite[nPk - 1] = kfirst;
                }
            } else {
                dir = 'i';
            }
            xbar = scale;
            kfirst = k;
            isinfykfirst = isinfyk;
        }
    }
    if (1 > nPk) {
        i = 0;
    } else {
        i = nPk;
    }
    iFinite.set_size(i);
    if (1 > nInf) {
        nInf = 0;
    }
    iInfinite.set_size(nInf);
    iPk.set_size(i);
    nPk = 0;
    for (k = 0; k < i; k++) {
        xbar = magNoG[iFinite[k] - 1];
        if ((xbar > t) &&
            (xbar - std::fmax(magNoG[iFinite[k] - 2], magNoG[iFinite[k]]) >= 0.0)) {
            nPk++;
            iPk[nPk - 1] = iFinite[k];
        }
    }
    if (1 > nPk) {
        nPk = 0;
    }
    iPk.set_size(nPk);
    coder::do_vectors(iPk, iInfinite, c, idx, iFinite);
    if ((c.size(0) == 0) || (minPeakDistance == 0.0)) {
        if (c.size(0) < 1) {
            n = 0;
        } else {
            n = c.size(0);
        }
        b_y.set_size(1, n);
        if (n > 0) {
            b_y[0] = 1;
            kend = 1;
            for (k = 2; k <= n; k++) {
                kend++;
                b_y[k - 1] = kend;
            }
        }
        idx.set_size(b_y.size(1));
        kend = b_y.size(1);
        for (i = 0; i < kend; i++) {
            idx[i] = b_y[i];
        }
    } else {
        int b_i;
        n = c.size(0) + 1;
        sortIdx.set_size(c.size(0));
        kend = c.size(0);
        for (i = 0; i < kend; i++) {
            sortIdx[i] = 0;
        }
        iwork.set_size(c.size(0));
        i = c.size(0) - 1;
        for (k = 1; k <= i; k += 2) {
            xbar = magNoG[c[k - 1] - 1];
            if ((xbar >= magNoG[c[k] - 1]) || std::isnan(xbar)) {
                sortIdx[k - 1] = k;
                sortIdx[k] = k + 1;
            } else {
                sortIdx[k - 1] = k + 1;
                sortIdx[k] = k;
            }
        }
        if ((c.size(0) & 1) != 0) {
            sortIdx[c.size(0) - 1] = c.size(0);
        }
        b_i = 2;
        while (b_i < n - 1) {
            kend = b_i << 1;
            kfirst = 1;
            for (nPk = b_i + 1; nPk < n; nPk = qEnd + b_i) {
                int kEnd;
                int q;
                nInf = kfirst - 1;
                q = nPk;
                qEnd = kfirst + kend;
                if (qEnd > n) {
                    qEnd = n;
                }
                k = 0;
                kEnd = qEnd - kfirst;
                while (k + 1 <= kEnd) {
                    xbar = magNoG[c[sortIdx[nInf] - 1] - 1];
                    i = sortIdx[q - 1];
                    if ((xbar >= magNoG[c[i - 1] - 1]) || std::isnan(xbar)) {
                        iwork[k] = sortIdx[nInf];
                        nInf++;
                        if (nInf + 1 == nPk) {
                            while (q < qEnd) {
                                k++;
                                iwork[k] = sortIdx[q - 1];
                                q++;
                            }
                        }
                    } else {
                        iwork[k] = i;
                        q++;
                        if (q == qEnd) {
                            while (nInf + 1 < nPk) {
                                k++;
                                iwork[k] = sortIdx[nInf];
                                nInf++;
                            }
                        }
                    }
                    k++;
                }
                for (k = 0; k < kEnd; k++) {
                    sortIdx[(kfirst + k) - 1] = iwork[k];
                }
                kfirst = qEnd;
            }
            b_i = kend;
        }
        locs_temp.set_size(sortIdx.size(0));
        kend = sortIdx.size(0);
        for (i = 0; i < kend; i++) {
            locs_temp[i] = absdiff[c[sortIdx[i] - 1] - 1];
        }
        idelete.set_size(sortIdx.size(0));
        kend = sortIdx.size(0);
        for (i = 0; i < kend; i++) {
            idelete[i] = false;
        }
        i = sortIdx.size(0);
        for (b_i = 0; b_i < i; b_i++) {
            if (!idelete[b_i]) {
                xbar = absdiff[c[sortIdx[b_i] - 1] - 1];
                scale = xbar - minPeakDistance;
                xbar += minPeakDistance;
                kend = locs_temp.size(0);
                r1.set_size(locs_temp.size(0));
                for (kfirst = 0; kfirst < kend; kfirst++) {
                    r1[kfirst] =
                            ((locs_temp[kfirst] >= scale) && (locs_temp[kfirst] <= xbar));
                }
                kend = idelete.size(0);
                for (kfirst = 0; kfirst < kend; kfirst++) {
                    idelete[kfirst] = (idelete[kfirst] || r1[kfirst]);
                }
                idelete[b_i] = false;
            }
        }
        kfirst = idelete.size(0) - 1;
        kend = 0;
        for (b_i = 0; b_i <= kfirst; b_i++) {
            if (!idelete[b_i]) {
                kend++;
            }
        }
        r.set_size(kend);
        kend = 0;
        for (b_i = 0; b_i <= kfirst; b_i++) {
            if (!idelete[b_i]) {
                r[kend] = b_i + 1;
                kend++;
            }
        }
        idx.set_size(r.size(0));
        kend = r.size(0);
        for (i = 0; i < kend; i++) {
            idx[i] = sortIdx[r[i] - 1];
        }
        coder::internal::sort(idx);
    }
    if (idx.size(0) > magNoG.size(0)) {
        idx.set_size(magNoG.size(0));
    }

    iPk.set_size(idx.size(0));
    kend = idx.size(0);
    for (i = 0; i < kend; i++) {
        iPk[i] = c[idx[i] - 1];
    }
    jdoubleArray result = env->NewDoubleArray(iPk.size(0));
    double *indexStep_data = env->GetDoubleArrayElements(result, JNI_FALSE); // Get C++ pointer to array data

    kend = iPk.size(0);
    for (i = 0; i < kend; i++) {
        indexStep_data[i] = absdiff[iPk[i] - 1];
    }
    env->ReleaseDoubleArrayElements(result, indexStep_data, 0);
    findPeaks_terminate();

    return result;
}

// End of code generation (findPeaks.cpp)
