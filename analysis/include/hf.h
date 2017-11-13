#ifndef HF_H
#define HF_H

static const float hfofficial[21] = {
        0.00,    0.00,  16.104, 22.5195, 33.3297,
     49.7959, 72.9208, 104.563, 149.178,   208.7,
     285.911, 383.223, 504.114, 651.325, 829.723,
     1036.22, 1275.67, 1565.72, 1912.75, 2341.83,
    10000.00
};

int hfbin(float hft) {
    for (int i=0; i<20; ++i) {
        if (hft < hfofficial[i+1])
            return i;
    }

    __builtin_unreachable();
}

#endif  /* HF_H */
