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
