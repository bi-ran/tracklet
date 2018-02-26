#ifndef HF_H
#define HF_H

/* CentralityTable_HFtowers200_DataXeXe_eff95_run2v941x02_offline */
static const float hfofficial[21] = {
        0.00, 13.2348, 18.7674, 27.4916, 40.5531,
     59.3048, 85.5337, 121.442,   169.9, 233.563,
     314.095,  414.83, 538.815, 686.084, 862.823,
     1071.18, 1317.78, 1610.02, 1961.63, 2394.33,
    10000.00
};

/* CentralityTable_HFtowers200_DataXeXe_eff100_run2v941x01_offline */
// static const float hfofficial[21] = {
//         0.00,  18.715, 26.8853, 38.8775,  55.839,
//       79.171, 110.752, 153.039, 208.026, 277.951,
//      364.262, 470.097, 596.901, 747.509, 924.333,
//      1132.31, 1375.09, 1661.39, 2003.11, 2419.56,
//     10000.00
// };

/* CentralityTable_HFtowers200_XeXe5p44TeVEPOSLHC_v941x01_mc */
// static const float hfofficial[21] = {
//         0.00, 12.4995, 17.3889, 25.2556, 37.7678,
//      54.8032, 77.9654, 109.395, 152.187, 205.717,
//        272.2, 356.406, 459.404, 582.857, 731.719,
//      906.561, 1128.65, 1406.31,  1733.3, 2184.99,
//     10000.00
// };

/* CentralityTable_HFtowers200_DataXeXe_eff942_run2v9313x02_offline */
// static const float hfofficial[21] = {
//         0.00,    0.00,  16.104, 22.5195, 33.3297,
//      49.7959, 72.9208, 104.563, 149.178,   208.7,
//      285.911, 383.223, 504.114, 651.325, 829.723,
//      1036.22, 1275.67, 1565.72, 1912.75, 2341.83,
//     10000.00
// };

int hfbin(float hft) {
    for (int i=0; i<20; ++i) {
        if (hft < hfofficial[i+1])
            return i;
    }

    __builtin_unreachable();
}

#endif  /* HF_H */
