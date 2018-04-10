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

/* CentralityTable_HFtowers200_DataXeXe_effstep98a25_run2v941x01_offline */
static const float hfeffup[21] = {
        0.00, 17.6382, 23.7497, 34.2277, 49.7004,
     71.2325, 100.793, 140.552, 193.142, 260.808,
     345.225,     449, 574.858, 724.443, 900.748,
      1109.4, 1353.88, 1641.79, 1987.47, 2410.48,
    10000.00
};

/* CentralityTable_HFtowers200_DataXeXe_effstep92a25_run2v941x01_offline */
static const float hfeffdown[21] = {
        0.00,  15.929, 19.4426, 23.7154,  33.661,
     50.1023, 73.4304, 106.172, 150.959, 210.843,
     288.199, 385.384, 506.484, 652.586, 828.802,
     1037.42, 1285.74, 1581.93, 1938.88, 2380.16,
    10000.00
};

/* CentralityTable_HFtowers200_XeXe5p44TeVEPOSLHC_v941x01_mc */
static const float hfepos[21] = {
        0.00, 12.4995, 17.3889, 25.2556, 37.7678,
     54.8032, 77.9654, 109.395, 152.187, 205.717,
       272.2, 356.406, 459.404, 582.857, 731.719,
     906.561, 1128.65, 1406.31,  1733.3, 2184.99,
    10000.00
};

/* CentralityTable_HFtowers200_XeXe5p44TeVHYDJET_v941x01_mc */
static const float hfhydjet[21] = {
        0.00, 11.7854,  14.634, 18.5804, 25.2036,
     38.0423, 58.1654,  83.794, 119.777, 169.254,
     235.553,  322.45, 436.102, 578.494, 754.796,
     973.746, 1245.74, 1581.32,  2006.6, 2551.86,
    10000.00
};

/* AMPT (default) */
static const float hfamptnm[21] = {
        0.00, 19.5809, 27.2536, 38.8990, 56.0056,
     80.7715, 115.848, 164.708, 230.328, 318.081,
     430.881, 576.298, 759.515, 988.671, 1266.27,
     1603.48, 2005.61, 2498.42, 3103.36, 3866.94,
    10000.00
};

/* AMPT (string melting) */
static const float hfamptsm[21] = {
        0.00, 19.4531, 27.0190, 38.6896, 55.8400,
     80.2462, 114.488, 162.446, 228.975, 317.726,
    433.3286, 578.349, 763.574, 992.350, 1278.27,
     1622.72, 2039.56, 2542.28, 3157.37, 3933.34,
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

const float* hftables[7] = {
    hfofficial, hfeffup, hfeffdown,
    hfepos, hfhydjet, hfamptnm, hfamptsm
};

float hftval(int hfb, int sample) {
    return hftables[sample][hfb];
}

#endif  /* HF_H */
