#include "TH1.h"
#include "TGraphErrors.h"

static const double alice_trunc_etabins[25] = {
    -3.0, -2.75, -2.5, -2.25, -2.0, -1.75, -1.5, -1.25, -1.0, -0.75, -0.5, -0.25, 0.0,
    0.25,   0.5, 0.75,   1.0, 1.25,   1.5, 1.75,   2.0, 2.25,   2.5, 2.75,   3.0
};

TH1F* halice_pbpb_5p02_eta_trunc_c0t5() {
   TH1F* halice_pbpb_5p02_eta_trunc_c0t5 = new TH1F("halice_pbpb_5p02_eta_trunc_c0t5", "", 24, alice_trunc_etabins);

   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(1, 1718.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(1, 77.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(2, 1787.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(2, 81.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(3, 1835.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(3, 83.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(4, 1912.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(4, 86.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(5, 1968.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(5, 64.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(6, 2001.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(6, 80.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(7, 2021.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(7, 71.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(8, 2017.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(8, 64.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(9, 1995.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(9, 56.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(10, 1970.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(10, 52.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(11, 1943.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(11, 47.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(12, 1929.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(12, 46.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(13, 1929.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(13, 46.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(14, 1943.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(14, 47.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(15, 1970.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(15, 52.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(16, 1995.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(16, 56.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(17, 2017.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(17, 64.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(18, 2021.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(18, 71.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(19, 2001.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(19, 80.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(20, 1968.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(20, 64.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(21, 1912.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(21, 86.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(22, 1835.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(22, 83.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(23, 1787.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(23, 81.0);
   halice_pbpb_5p02_eta_trunc_c0t5->SetBinContent(24, 1718.0); halice_pbpb_5p02_eta_trunc_c0t5->SetBinError(24, 77.0);

   return halice_pbpb_5p02_eta_trunc_c0t5;
}

static const double alice_etabins[35] = {
   -3.50, -3.25,  -3.0, -2.75, -2.5, -2.25, -2.0, -1.75, -1.5, -1.25, -1.0,
   -0.75,  -0.5, -0.25,   0.0, 0.25,   0.5, 0.75,   1.0, 1.25,   1.5, 1.75, 2.0,
    2.25,   2.5,  2.75,   3.0, 3.25,   3.5, 3.75,   4.0, 4.25,   4.5, 4.75, 5.0
};

TH1F* halice_pbpb_5p02_eta_c0t5() {
   TH1F* halice_pbpb_5p02_eta_c0t5 = new TH1F("halice_pbpb_5p02_eta_c0t5", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c0t5->SetBinContent(1, 1643.0); halice_pbpb_5p02_eta_c0t5->SetBinError(1, 74.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(2, 1670.0); halice_pbpb_5p02_eta_c0t5->SetBinError(2, 75.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(3, 1718.0); halice_pbpb_5p02_eta_c0t5->SetBinError(3, 77.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(4, 1787.0); halice_pbpb_5p02_eta_c0t5->SetBinError(4, 81.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(5, 1835.0); halice_pbpb_5p02_eta_c0t5->SetBinError(5, 83.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(6, 1912.0); halice_pbpb_5p02_eta_c0t5->SetBinError(6, 86.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(7, 1968.0); halice_pbpb_5p02_eta_c0t5->SetBinError(7, 64.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(8, 2001.0); halice_pbpb_5p02_eta_c0t5->SetBinError(8, 80.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(9, 2021.0); halice_pbpb_5p02_eta_c0t5->SetBinError(9, 71.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(10, 2017.0); halice_pbpb_5p02_eta_c0t5->SetBinError(10, 64.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(11, 1995.0); halice_pbpb_5p02_eta_c0t5->SetBinError(11, 56.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(12, 1970.0); halice_pbpb_5p02_eta_c0t5->SetBinError(12, 52.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(13, 1943.0); halice_pbpb_5p02_eta_c0t5->SetBinError(13, 47.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(14, 1929.0); halice_pbpb_5p02_eta_c0t5->SetBinError(14, 46.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(15, 1929.0); halice_pbpb_5p02_eta_c0t5->SetBinError(15, 46.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(16, 1943.0); halice_pbpb_5p02_eta_c0t5->SetBinError(16, 47.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(17, 1970.0); halice_pbpb_5p02_eta_c0t5->SetBinError(17, 52.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(18, 1995.0); halice_pbpb_5p02_eta_c0t5->SetBinError(18, 56.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(19, 2017.0); halice_pbpb_5p02_eta_c0t5->SetBinError(19, 64.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(20, 2021.0); halice_pbpb_5p02_eta_c0t5->SetBinError(20, 71.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(21, 2001.0); halice_pbpb_5p02_eta_c0t5->SetBinError(21, 80.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(22, 1968.0); halice_pbpb_5p02_eta_c0t5->SetBinError(22, 64.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(23, 1912.0); halice_pbpb_5p02_eta_c0t5->SetBinError(23, 86.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(24, 1835.0); halice_pbpb_5p02_eta_c0t5->SetBinError(24, 83.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(25, 1787.0); halice_pbpb_5p02_eta_c0t5->SetBinError(25, 81.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(26, 1718.0); halice_pbpb_5p02_eta_c0t5->SetBinError(26, 77.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(27, 1670.0); halice_pbpb_5p02_eta_c0t5->SetBinError(27, 75.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(28, 1643.0); halice_pbpb_5p02_eta_c0t5->SetBinError(28, 74.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(29, 1563.0); halice_pbpb_5p02_eta_c0t5->SetBinError(29, 106.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(30, 1474.0); halice_pbpb_5p02_eta_c0t5->SetBinError(30, 100.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(31, 1370.0); halice_pbpb_5p02_eta_c0t5->SetBinError(31, 93.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(32, 1324.0); halice_pbpb_5p02_eta_c0t5->SetBinError(32, 90.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(33, 1281.0); halice_pbpb_5p02_eta_c0t5->SetBinError(33, 87.0);
   halice_pbpb_5p02_eta_c0t5->SetBinContent(34, 1244.0); halice_pbpb_5p02_eta_c0t5->SetBinError(34, 85.0);

   return halice_pbpb_5p02_eta_c0t5;
}

TH1F* halice_pbpb_5p02_eta_c5t10() {
   TH1F* halice_pbpb_5p02_eta_c5t10 = new TH1F("halice_pbpb_5p02_eta_c5t10", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c5t10->SetBinContent(1, 1364.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(1, 62.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(2, 1391.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(2, 63.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(3, 1424.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(3, 64.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(4, 1474.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(4, 67.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(5, 1507.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(5, 68.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(6, 1569.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(6, 71.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(7, 1644.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(7, 53.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(8, 1679.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(8, 67.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(9, 1682.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(9, 59.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(10, 1672.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(10, 52.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(11, 1646.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(11, 47.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(12, 1621.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(12, 42.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(13, 1597.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(13, 39.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(14, 1583.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(14, 37.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(15, 1583.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(15, 37.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(16, 1597.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(16, 39.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(17, 1621.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(17, 42.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(18, 1646.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(18, 47.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(19, 1672.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(19, 52.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(20, 1682.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(20, 59.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(21, 1679.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(21, 67.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(22, 1644.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(22, 53.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(23, 1569.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(23, 71.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(24, 1507.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(24, 68.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(25, 1474.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(25, 67.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(26, 1424.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(26, 64.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(27, 1391.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(27, 63.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(28, 1364.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(28, 62.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(29, 1292.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(29, 88.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(30, 1218.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(30, 83.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(31, 1132.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(31, 77.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(32, 1093.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(32, 74.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(33, 1062.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(33, 72.0);
   halice_pbpb_5p02_eta_c5t10->SetBinContent(34, 1032.0); halice_pbpb_5p02_eta_c5t10->SetBinContent(34, 70.0);

   return halice_pbpb_5p02_eta_c5t10;
}

TH1F* halice_pbpb_5p02_eta_c10t20() {
   TH1F* halice_pbpb_5p02_eta_c10t20 = new TH1F("halice_pbpb_5p02_eta_c10t20", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c10t20->SetBinContent(1, 1038.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(1, 47.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(2, 1061.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(2, 48.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(3, 1080.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(3, 49.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(4, 1114.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(4, 50.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(5, 1136.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(5, 51.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(6, 1178.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(6, 53.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(7, 1229.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(7, 39.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(8, 1253.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(8, 49.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(9, 1256.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(9, 43.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(10, 1247.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(10, 38.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(11, 1229.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(11, 34.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(12, 1210.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(12, 31.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(13, 1191.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(13, 28.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(14, 1181.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(14, 28.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(15, 1181.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(15, 28.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(16, 1191.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(16, 28.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(17, 1210.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(17, 31.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(18, 1229.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(18, 34.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(19, 1247.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(19, 38.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(20, 1256.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(20, 43.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(21, 1253.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(21, 49.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(22, 1229.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(22, 39.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(23, 1178.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(23, 53.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(24, 1136.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(24, 51.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(25, 1114.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(25, 50.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(26, 1080.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(26, 49.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(27, 1061.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(27, 48.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(28, 1038.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(28, 47.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(29, 977.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(29, 66.0);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(30, 921.3); halice_pbpb_5p02_eta_c10t20->SetBinContent(30, 62.6);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(31, 857.7); halice_pbpb_5p02_eta_c10t20->SetBinContent(31, 58.3);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(32, 829.6); halice_pbpb_5p02_eta_c10t20->SetBinContent(32, 56.4);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(33, 807.4); halice_pbpb_5p02_eta_c10t20->SetBinContent(33, 54.9);
   halice_pbpb_5p02_eta_c10t20->SetBinContent(34, 787.0); halice_pbpb_5p02_eta_c10t20->SetBinContent(34, 53.0);

   return halice_pbpb_5p02_eta_c10t20;
}

TH1F* halice_pbpb_5p02_eta_c20_30() {
   TH1F* halice_pbpb_5p02_eta_c20_30 = new TH1F("halice_pbpb_5p02_eta_c20_30", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c20_30->SetBinContent(1, 714.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(1, 32.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(2, 726.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(2, 33.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(3, 738.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(3, 33.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(4, 759.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(4, 34.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(5, 772.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(5, 35.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(6, 797.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(6, 36.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(7, 827.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(7, 26.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(8, 842.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(8, 31.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(9, 844.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(9, 28.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(10, 838.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(10, 25.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(11, 826.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(11, 22.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(12, 811.9); halice_pbpb_5p02_eta_c20_30->SetBinContent(12, 20.1);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(13, 799.2); halice_pbpb_5p02_eta_c20_30->SetBinContent(13, 18.7);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(14, 792.4); halice_pbpb_5p02_eta_c20_30->SetBinContent(14, 17.9);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(15, 792.4); halice_pbpb_5p02_eta_c20_30->SetBinContent(15, 17.9);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(16, 799.2); halice_pbpb_5p02_eta_c20_30->SetBinContent(16, 18.7);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(17, 811.9); halice_pbpb_5p02_eta_c20_30->SetBinContent(17, 20.1);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(18, 826.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(18, 22.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(19, 838.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(19, 25.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(20, 844.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(20, 28.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(21, 842.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(21, 31.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(22, 827.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(22, 26.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(23, 797.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(23, 36.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(24, 772.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(24, 35.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(25, 759.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(25, 34.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(26, 738.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(26, 33.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(27, 726.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(27, 33.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(28, 714.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(28, 32.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(29, 665.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(29, 45.0);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(30, 625.4); halice_pbpb_5p02_eta_c20_30->SetBinContent(30, 42.5);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(31, 582.6); halice_pbpb_5p02_eta_c20_30->SetBinContent(31, 39.6);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(32, 565.5); halice_pbpb_5p02_eta_c20_30->SetBinContent(32, 38.4);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(33, 551.4); halice_pbpb_5p02_eta_c20_30->SetBinContent(33, 37.5);
   halice_pbpb_5p02_eta_c20_30->SetBinContent(34, 538.0); halice_pbpb_5p02_eta_c20_30->SetBinContent(34, 37.0);

   return halice_pbpb_5p02_eta_c20_30;
}

TH1F* halice_pbpb_5p02_eta_c30_40() {
   TH1F* halice_pbpb_5p02_eta_c30_40 = new TH1F("halice_pbpb_5p02_eta_c30_40", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c30_40->SetBinContent(1, 475.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(1, 21.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(2, 482.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(2, 21.8);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(3, 489.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(3, 22.1);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(4, 502.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(4, 22.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(5, 510.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(5, 23.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(6, 522.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(6, 23.5);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(7, 539.9); halice_pbpb_5p02_eta_c30_40->SetBinContent(7, 15.9);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(8, 549.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(8, 19.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(9, 549.3);  halice_pbpb_5p02_eta_c30_40->SetBinContent(9, 16.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(10, 545.5); halice_pbpb_5p02_eta_c30_40->SetBinContent(10, 15.1);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(11, 537.5); halice_pbpb_5p02_eta_c30_40->SetBinContent(11, 13.6);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(12, 527.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(12, 12.6);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(13, 519.3); halice_pbpb_5p02_eta_c30_40->SetBinContent(13, 11.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(14, 514.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(14, 11.4);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(15, 514.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(15, 11.4);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(16, 519.3); halice_pbpb_5p02_eta_c30_40->SetBinContent(16, 11.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(17, 527.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(17, 12.6);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(18, 537.5); halice_pbpb_5p02_eta_c30_40->SetBinContent(18, 13.6);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(19, 545.5); halice_pbpb_5p02_eta_c30_40->SetBinContent(19, 15.1);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(20, 549.3); halice_pbpb_5p02_eta_c30_40->SetBinContent(20, 16.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(21, 549.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(21, 19.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(22, 539.9); halice_pbpb_5p02_eta_c30_40->SetBinContent(22, 15.9);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(23, 522.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(23, 23.5);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(24, 510.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(24, 23.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(25, 502.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(25, 22.7);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(26, 489.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(26, 22.1);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(27, 482.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(27, 21.8);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(28, 475.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(28, 21.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(29, 440.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(29, 30.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(30, 413.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(30, 28.1);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(31, 386.7); halice_pbpb_5p02_eta_c30_40->SetBinContent(31, 26.3);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(32, 375.6); halice_pbpb_5p02_eta_c30_40->SetBinContent(32, 25.5);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(33, 368.0); halice_pbpb_5p02_eta_c30_40->SetBinContent(33, 25.0);
   halice_pbpb_5p02_eta_c30_40->SetBinContent(34, 359.9); halice_pbpb_5p02_eta_c30_40->SetBinContent(34, 24.5);

   return halice_pbpb_5p02_eta_c30_40;
}

TH1F* halice_pbpb_5p02_eta_c40_50() {
   TH1F* halice_pbpb_5p02_eta_c40_50 = new TH1F("halice_pbpb_5p02_eta_c40_50", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c40_50->SetBinContent(1, 302.0); halice_pbpb_5p02_eta_c40_50->SetBinContent(1, 14.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(2, 306.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(2, 13.8);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(3, 310.1); halice_pbpb_5p02_eta_c40_50->SetBinContent(3, 14.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(4, 317.9); halice_pbpb_5p02_eta_c40_50->SetBinContent(4, 14.3);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(5, 322.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(5, 14.5);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(6, 327.6); halice_pbpb_5p02_eta_c40_50->SetBinContent(6, 14.8);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(7, 335.1); halice_pbpb_5p02_eta_c40_50->SetBinContent(7, 9.3);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(8, 340.0); halice_pbpb_5p02_eta_c40_50->SetBinContent(8, 11.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(9, 340.2); halice_pbpb_5p02_eta_c40_50->SetBinContent(9, 9.6);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(10, 337.7); halice_pbpb_5p02_eta_c40_50->SetBinContent(10, 8.7);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(11, 332.5); halice_pbpb_5p02_eta_c40_50->SetBinContent(11, 7.9);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(12, 326.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(12, 7.4);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(13, 320.7); halice_pbpb_5p02_eta_c40_50->SetBinContent(13, 7.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(14, 317.5); halice_pbpb_5p02_eta_c40_50->SetBinContent(14, 6.7);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(15, 317.5); halice_pbpb_5p02_eta_c40_50->SetBinContent(15, 6.7);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(16, 320.7); halice_pbpb_5p02_eta_c40_50->SetBinContent(16, 7.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(17, 326.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(17, 7.4);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(18, 332.5); halice_pbpb_5p02_eta_c40_50->SetBinContent(18, 7.9);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(19, 337.7); halice_pbpb_5p02_eta_c40_50->SetBinContent(19, 8.7);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(20, 340.2); halice_pbpb_5p02_eta_c40_50->SetBinContent(20, 9.6);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(21, 340.0); halice_pbpb_5p02_eta_c40_50->SetBinContent(21, 11.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(22, 335.1); halice_pbpb_5p02_eta_c40_50->SetBinContent(22, 9.3);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(23, 327.6); halice_pbpb_5p02_eta_c40_50->SetBinContent(23, 14.8);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(24, 322.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(24, 14.5);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(25, 317.9); halice_pbpb_5p02_eta_c40_50->SetBinContent(25, 14.3);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(26, 310.1); halice_pbpb_5p02_eta_c40_50->SetBinContent(26, 14.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(27, 306.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(27, 13.8);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(28, 302.0); halice_pbpb_5p02_eta_c40_50->SetBinContent(28, 14.0);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(29, 277.5); halice_pbpb_5p02_eta_c40_50->SetBinContent(29, 18.9);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(30, 261.3); halice_pbpb_5p02_eta_c40_50->SetBinContent(30, 17.8);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(31, 244.7); halice_pbpb_5p02_eta_c40_50->SetBinContent(31, 16.6);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(32, 238.4); halice_pbpb_5p02_eta_c40_50->SetBinContent(32, 16.2);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(33, 233.8); halice_pbpb_5p02_eta_c40_50->SetBinContent(33, 15.9);
   halice_pbpb_5p02_eta_c40_50->SetBinContent(34, 229.4); halice_pbpb_5p02_eta_c40_50->SetBinContent(34, 15.6);

   return halice_pbpb_5p02_eta_c40_50;
}

TH1F* halice_pbpb_5p02_eta_c50_60() {
   TH1F* halice_pbpb_5p02_eta_c50_60 = new TH1F("halice_pbpb_5p02_eta_c50_60", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c50_60->SetBinContent(1, 178.0); halice_pbpb_5p02_eta_c50_60->SetBinContent(1, 8.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(2, 179.9); halice_pbpb_5p02_eta_c50_60->SetBinContent(2, 8.1);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(3, 181.7); halice_pbpb_5p02_eta_c50_60->SetBinContent(3, 8.2);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(4, 186.0); halice_pbpb_5p02_eta_c50_60->SetBinContent(4, 8.4);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(5, 188.2); halice_pbpb_5p02_eta_c50_60->SetBinContent(5, 8.5);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(6, 189.8); halice_pbpb_5p02_eta_c50_60->SetBinContent(6, 8.6);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(7, 193.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(7, 4.9);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(8, 196.4); halice_pbpb_5p02_eta_c50_60->SetBinContent(8, 5.5);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(9, 196.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(9, 5.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(10, 194.8); halice_pbpb_5p02_eta_c50_60->SetBinContent(10, 4.6);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(11, 191.4); halice_pbpb_5p02_eta_c50_60->SetBinContent(11, 4.3);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(12, 187.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(12, 4.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(13, 184.3); halice_pbpb_5p02_eta_c50_60->SetBinContent(13, 3.8);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(14, 182.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(14, 3.7);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(15, 182.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(15, 3.7);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(16, 184.3); halice_pbpb_5p02_eta_c50_60->SetBinContent(16, 3.8);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(17, 187.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(17, 4.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(18, 191.4); halice_pbpb_5p02_eta_c50_60->SetBinContent(18, 4.3);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(19, 194.8); halice_pbpb_5p02_eta_c50_60->SetBinContent(19, 4.6);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(20, 196.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(20, 5.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(21, 196.4); halice_pbpb_5p02_eta_c50_60->SetBinContent(21, 5.5);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(22, 193.5); halice_pbpb_5p02_eta_c50_60->SetBinContent(22, 4.9);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(23, 189.8); halice_pbpb_5p02_eta_c50_60->SetBinContent(23, 8.6);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(24, 188.2); halice_pbpb_5p02_eta_c50_60->SetBinContent(24, 8.5);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(25, 186.0); halice_pbpb_5p02_eta_c50_60->SetBinContent(25, 8.4);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(26, 181.7); halice_pbpb_5p02_eta_c50_60->SetBinContent(26, 8.2);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(27, 179.9); halice_pbpb_5p02_eta_c50_60->SetBinContent(27, 8.1);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(28, 178.0); halice_pbpb_5p02_eta_c50_60->SetBinContent(28, 8.0);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(29, 163.2); halice_pbpb_5p02_eta_c50_60->SetBinContent(29, 11.1);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(30, 153.4); halice_pbpb_5p02_eta_c50_60->SetBinContent(30, 10.4);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(31, 143.8); halice_pbpb_5p02_eta_c50_60->SetBinContent(31, 9.8);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(32, 140.3); halice_pbpb_5p02_eta_c50_60->SetBinContent(32, 9.5);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(33, 138.7); halice_pbpb_5p02_eta_c50_60->SetBinContent(33, 9.4);
   halice_pbpb_5p02_eta_c50_60->SetBinContent(34, 136.0); halice_pbpb_5p02_eta_c50_60->SetBinContent(34, 9.2);

   return halice_pbpb_5p02_eta_c50_60;
}

TH1F* halice_pbpb_5p02_eta_c60_70() {
   TH1F* halice_pbpb_5p02_eta_c60_70 = new TH1F("halice_pbpb_5p02_eta_c60_70", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c60_70->SetBinContent(1, 94.9); halice_pbpb_5p02_eta_c60_70->SetBinContent(1, 4.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(2, 96.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(2, 4.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(3, 96.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(3, 4.4);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(4, 98.3); halice_pbpb_5p02_eta_c60_70->SetBinContent(4, 4.4);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(5, 98.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(5, 4.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(6, 99.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(6, 4.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(7, 101.2); halice_pbpb_5p02_eta_c60_70->SetBinContent(7, 2.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(8, 102.7); halice_pbpb_5p02_eta_c60_70->SetBinContent(8, 2.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(9, 103.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(9, 2.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(10, 102.0); halice_pbpb_5p02_eta_c60_70->SetBinContent(10, 2.2);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(11, 100.3); halice_pbpb_5p02_eta_c60_70->SetBinContent(11, 2.1);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(12, 98.0); halice_pbpb_5p02_eta_c60_70->SetBinContent(12, 2.0);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(13, 96.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(13, 1.9);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(14, 95.2); halice_pbpb_5p02_eta_c60_70->SetBinContent(14, 1.9);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(15, 95.2); halice_pbpb_5p02_eta_c60_70->SetBinContent(15, 1.9);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(16, 96.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(16, 1.9);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(17, 98.0); halice_pbpb_5p02_eta_c60_70->SetBinContent(17, 2.0);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(18, 100.3); halice_pbpb_5p02_eta_c60_70->SetBinContent(18, 2.1);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(19, 102.0); halice_pbpb_5p02_eta_c60_70->SetBinContent(19, 2.2);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(20, 103.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(20, 2.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(21, 102.7); halice_pbpb_5p02_eta_c60_70->SetBinContent(21, 2.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(22, 101.2); halice_pbpb_5p02_eta_c60_70->SetBinContent(22, 2.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(23, 99.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(23, 4.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(24, 98.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(24, 4.5);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(25, 98.3); halice_pbpb_5p02_eta_c60_70->SetBinContent(25, 4.4);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(26, 96.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(26, 4.4);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(27, 96.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(27, 4.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(28, 94.9); halice_pbpb_5p02_eta_c60_70->SetBinContent(28, 4.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(29, 86.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(29, 5.9);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(30, 81.9); halice_pbpb_5p02_eta_c60_70->SetBinContent(30, 5.6);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(31, 77.3); halice_pbpb_5p02_eta_c60_70->SetBinContent(31, 5.3);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(32, 75.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(32, 5.2);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(33, 75.1); halice_pbpb_5p02_eta_c60_70->SetBinContent(33, 5.1);
   halice_pbpb_5p02_eta_c60_70->SetBinContent(34, 73.8); halice_pbpb_5p02_eta_c60_70->SetBinContent(34, 5.0);

   return halice_pbpb_5p02_eta_c60_70;
}

TH1F* halice_pbpb_5p02_eta_c70_80() {
   TH1F* halice_pbpb_5p02_eta_c70_80 = new TH1F("halice_pbpb_5p02_eta_c70_80", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c70_80->SetBinContent(1, 45.4); halice_pbpb_5p02_eta_c70_80->SetBinContent(1, 2.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(2, 46.0); halice_pbpb_5p02_eta_c70_80->SetBinContent(2, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(3, 46.0); halice_pbpb_5p02_eta_c70_80->SetBinContent(3, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(4, 46.5); halice_pbpb_5p02_eta_c70_80->SetBinContent(4, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(5, 46.8); halice_pbpb_5p02_eta_c70_80->SetBinContent(5, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(6, 46.7); halice_pbpb_5p02_eta_c70_80->SetBinContent(6, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(7, 47.3); halice_pbpb_5p02_eta_c70_80->SetBinContent(7, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(8, 47.9); halice_pbpb_5p02_eta_c70_80->SetBinContent(8, 1.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(9, 48.2); halice_pbpb_5p02_eta_c70_80->SetBinContent(9, 1.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(10, 47.6); halice_pbpb_5p02_eta_c70_80->SetBinContent(10, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(11, 46.7); halice_pbpb_5p02_eta_c70_80->SetBinContent(11, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(12, 45.5); halice_pbpb_5p02_eta_c70_80->SetBinContent(12, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(13, 44.6); halice_pbpb_5p02_eta_c70_80->SetBinContent(13, 0.8);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(14, 44.1); halice_pbpb_5p02_eta_c70_80->SetBinContent(14, 0.8);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(15, 44.1); halice_pbpb_5p02_eta_c70_80->SetBinContent(15, 0.8);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(16, 44.6); halice_pbpb_5p02_eta_c70_80->SetBinContent(16, 0.8);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(17, 45.5); halice_pbpb_5p02_eta_c70_80->SetBinContent(17, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(18, 46.7); halice_pbpb_5p02_eta_c70_80->SetBinContent(18, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(19, 47.6); halice_pbpb_5p02_eta_c70_80->SetBinContent(19, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(20, 48.2); halice_pbpb_5p02_eta_c70_80->SetBinContent(20, 1.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(21, 47.9); halice_pbpb_5p02_eta_c70_80->SetBinContent(21, 1.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(22, 47.3); halice_pbpb_5p02_eta_c70_80->SetBinContent(22, 0.9);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(23, 46.7); halice_pbpb_5p02_eta_c70_80->SetBinContent(23, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(24, 46.8); halice_pbpb_5p02_eta_c70_80->SetBinContent(24, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(25, 46.5); halice_pbpb_5p02_eta_c70_80->SetBinContent(25, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(26, 46.0); halice_pbpb_5p02_eta_c70_80->SetBinContent(26, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(27, 46.0); halice_pbpb_5p02_eta_c70_80->SetBinContent(27, 2.1);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(28, 45.4); halice_pbpb_5p02_eta_c70_80->SetBinContent(28, 2.0);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(29, 41.4); halice_pbpb_5p02_eta_c70_80->SetBinContent(29, 2.8);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(30, 39.3); halice_pbpb_5p02_eta_c70_80->SetBinContent(30, 2.7);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(31, 37.4); halice_pbpb_5p02_eta_c70_80->SetBinContent(31, 2.5);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(32, 36.8); halice_pbpb_5p02_eta_c70_80->SetBinContent(32, 2.5);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(33, 36.6); halice_pbpb_5p02_eta_c70_80->SetBinContent(33, 2.5);
   halice_pbpb_5p02_eta_c70_80->SetBinContent(34, 35.7); halice_pbpb_5p02_eta_c70_80->SetBinContent(34, 2.4);

   return halice_pbpb_5p02_eta_c70_80;
}

TH1F* halice_pbpb_5p02_eta_c80_90() {
   TH1F* halice_pbpb_5p02_eta_c80_90 = new TH1F("halice_pbpb_5p02_eta_c80_90", "", 34, alice_etabins);

   halice_pbpb_5p02_eta_c80_90->SetBinContent(1, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(1, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(2, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(2, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(3, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(3, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(4, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(4, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(5, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(5, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(6, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(6, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(7, 19.2); halice_pbpb_5p02_eta_c80_90->SetBinContent(7, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(8, 19.1); halice_pbpb_5p02_eta_c80_90->SetBinContent(8, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(9, 19.2); halice_pbpb_5p02_eta_c80_90->SetBinContent(9, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(10, 18.9); halice_pbpb_5p02_eta_c80_90->SetBinContent(10, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(11, 18.5); halice_pbpb_5p02_eta_c80_90->SetBinContent(11, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(12, 18.0); halice_pbpb_5p02_eta_c80_90->SetBinContent(12, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(13, 17.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(13, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(14, 17.4); halice_pbpb_5p02_eta_c80_90->SetBinContent(14, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(15, 17.4); halice_pbpb_5p02_eta_c80_90->SetBinContent(15, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(16, 17.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(16, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(17, 18.0); halice_pbpb_5p02_eta_c80_90->SetBinContent(17, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(18, 18.5); halice_pbpb_5p02_eta_c80_90->SetBinContent(18, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(19, 18.9); halice_pbpb_5p02_eta_c80_90->SetBinContent(19, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(20, 19.2); halice_pbpb_5p02_eta_c80_90->SetBinContent(20, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(21, 19.1); halice_pbpb_5p02_eta_c80_90->SetBinContent(21, 0.4);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(22, 19.2); halice_pbpb_5p02_eta_c80_90->SetBinContent(22, 0.3);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(23, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(23, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(24, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(24, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(25, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(25, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(26, 18.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(26, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(27, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(27, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(28, 18.7); halice_pbpb_5p02_eta_c80_90->SetBinContent(28, 0.8);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(29, 17.1); halice_pbpb_5p02_eta_c80_90->SetBinContent(29, 1.2);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(30, 16.27); halice_pbpb_5p02_eta_c80_90->SetBinContent(30, 1.11);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(31, 15.46); halice_pbpb_5p02_eta_c80_90->SetBinContent(31, 1.05);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(32, 15.47); halice_pbpb_5p02_eta_c80_90->SetBinContent(32, 1.05);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(33, 15.6); halice_pbpb_5p02_eta_c80_90->SetBinContent(33, 1.1);
   halice_pbpb_5p02_eta_c80_90->SetBinContent(34, 15.4); halice_pbpb_5p02_eta_c80_90->SetBinContent(34, 1.0);

   return halice_pbpb_5p02_eta_c80_90;
}

TGraphErrors* alice_pbpb_2p76_y_c0t5() {
   TGraphErrors* galice_pbpb_2p76_y_c0t5 = new TGraphErrors(42);
   galice_pbpb_2p76_y_c0t5->SetName("galice_pbpb_2p76_y_c0t5");

   galice_pbpb_2p76_y_c0t5->SetPoint(0, (-4.492 + (-4.896)) / 2, 887.0); galice_pbpb_2p76_y_c0t5->SetPointError(0, 0, 39.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(1, (-4.25 + (-4.638)) / 2, 978.0); galice_pbpb_2p76_y_c0t5->SetPointError(1, 0, 41.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(2, (-4.007 + (-4.381)) / 2, 1047.0); galice_pbpb_2p76_y_c0t5->SetPointError(2, 0, 44.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(3, (-3.764 + (-4.126)) / 2, 1132.0); galice_pbpb_2p76_y_c0t5->SetPointError(3, 0, 46.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(4, (-3.521 + (-3.869)) / 2, 1212.0); galice_pbpb_2p76_y_c0t5->SetPointError(4, 0, 50.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(5, (-3.277 + (-3.613)) / 2, 1307.0); galice_pbpb_2p76_y_c0t5->SetPointError(5, 0, 54.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(6, (-3.033 + (-3.359)) / 2, 1393.0); galice_pbpb_2p76_y_c0t5->SetPointError(6, 0, 58.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(7, (-2.789 + (-3.103)) / 2, 1455.0); galice_pbpb_2p76_y_c0t5->SetPointError(7, 0, 60.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(8, (-2.546 + (-2.85)) / 2, 1514.0); galice_pbpb_2p76_y_c0t5->SetPointError(8, 0, 59.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(9, (-2.303 + (-2.597)) / 2, 1594.0); galice_pbpb_2p76_y_c0t5->SetPointError(9, 0, 62.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(10, (-2.062 + (-2.342)) / 2, 1653.0); galice_pbpb_2p76_y_c0t5->SetPointError(10, 0, 64.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(11, (-1.823 + (-2.089)) / 2, 1708.0); galice_pbpb_2p76_y_c0t5->SetPointError(11, 0, 65.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(12, (-1.585 + (-1.839)) / 2, 1761.0); galice_pbpb_2p76_y_c0t5->SetPointError(12, 0, 71.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(13, (-1.349 + (-1.593)) / 2, 1813.0); galice_pbpb_2p76_y_c0t5->SetPointError(13, 0, 71.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(14, (-1.115 + (-1.349)) / 2, 1843.0); galice_pbpb_2p76_y_c0t5->SetPointError(14, 0, 75.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(15, (-0.884 + (-1.112)) / 2, 1831.0); galice_pbpb_2p76_y_c0t5->SetPointError(15, 0, 80.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(16, (-0.658 + (-0.88) ) / 2, 1844.0); galice_pbpb_2p76_y_c0t5->SetPointError(16, 0, 61.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(17, (-0.435 + (-0.653)) / 2, 1867.0); galice_pbpb_2p76_y_c0t5->SetPointError(17, 0, 57.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(18, (-0.216 + (-0.432)) / 2, 1866.0); galice_pbpb_2p76_y_c0t5->SetPointError(18, 0, 56.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(19, (0.0 + (-0.216)) / 2, 1873.0); galice_pbpb_2p76_y_c0t5->SetPointError(19, 0, 54.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(20, (0.216 + 0.0) / 2, 1873.0); galice_pbpb_2p76_y_c0t5->SetPointError(20, 0, 54.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(21, (0.432 + 0.216) / 2, 1866.0); galice_pbpb_2p76_y_c0t5->SetPointError(21, 0, 56.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(22, (0.653 + 0.435) / 2, 1867.0); galice_pbpb_2p76_y_c0t5->SetPointError(22, 0, 57.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(23, (0.88 + 0.658) / 2, 1844.0); galice_pbpb_2p76_y_c0t5->SetPointError(23, 0, 61.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(24, (1.112 + 0.884) / 2, 1831.0); galice_pbpb_2p76_y_c0t5->SetPointError(24, 0, 80.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(25, (1.349 + 1.115) / 2, 1843.0); galice_pbpb_2p76_y_c0t5->SetPointError(25, 0, 75.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(26, (1.593 + 1.349) / 2, 1813.0); galice_pbpb_2p76_y_c0t5->SetPointError(26, 0, 71.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(27, (1.839 + 1.585) / 2, 1761.0); galice_pbpb_2p76_y_c0t5->SetPointError(27, 0, 71.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(28, (2.089 + 1.823) / 2, 1708.0); galice_pbpb_2p76_y_c0t5->SetPointError(28, 0, 65.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(29, (2.342 + 2.062) / 2, 1653.0); galice_pbpb_2p76_y_c0t5->SetPointError(29, 0, 64.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(30, (2.597 + 2.303) / 2, 1594.0); galice_pbpb_2p76_y_c0t5->SetPointError(30, 0, 62.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(31, (2.85 + 2.546) / 2, 1514.0); galice_pbpb_2p76_y_c0t5->SetPointError(31, 0, 59.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(32, (3.103 + 2.789) / 2, 1455.0); galice_pbpb_2p76_y_c0t5->SetPointError(32, 0, 60.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(33, (3.359 + 3.033) / 2, 1393.0); galice_pbpb_2p76_y_c0t5->SetPointError(33, 0, 58.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(34, (3.613 + 3.277) / 2, 1307.0); galice_pbpb_2p76_y_c0t5->SetPointError(34, 0, 54.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(35, (3.869 + 3.521) / 2, 1212.0); galice_pbpb_2p76_y_c0t5->SetPointError(35, 0, 50.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(36, (4.126 + 3.764) / 2, 1132.0); galice_pbpb_2p76_y_c0t5->SetPointError(36, 0, 46.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(37, (4.381 + 4.007) / 2, 1047.0); galice_pbpb_2p76_y_c0t5->SetPointError(37, 0, 44.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(38, (4.638 + 4.25) / 2, 978.0); galice_pbpb_2p76_y_c0t5->SetPointError(38, 0, 41.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(39, (4.896 + 4.492) / 2, 887.0); galice_pbpb_2p76_y_c0t5->SetPointError(39, 0, 39.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(40, (5.154 + 4.734) / 2, 770.0); galice_pbpb_2p76_y_c0t5->SetPointError(40, 0, 42.0);
   galice_pbpb_2p76_y_c0t5->SetPoint(41, (5.412 + 4.976) / 2, 667.0); galice_pbpb_2p76_y_c0t5->SetPointError(41, 0, 39.0);

   return galice_pbpb_2p76_y_c0t5;
}

TGraphErrors* alice_pbpb_5p02_y_c0t5() {
   TGraphErrors* galice_pbpb_5p02_y_c0t5 = new TGraphErrors(34);
   galice_pbpb_5p02_y_c0t5->SetName("galice_pbpb_5p02_y_c0t5");

   galice_pbpb_5p02_y_c0t5->SetPoint(0, (-3.05 + (-3.29)) / 2, 1650.0); galice_pbpb_5p02_y_c0t5->SetPointError(0, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(1, (-2.85 + (-3.09)) / 2, 1680.0); galice_pbpb_5p02_y_c0t5->SetPointError(1, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(2, (-2.57 + (-2.79)) / 2, 1730.0); galice_pbpb_5p02_y_c0t5->SetPointError(2, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(3, (-2.36 + (-2.59)) / 2, 1800.0); galice_pbpb_5p02_y_c0t5->SetPointError(3, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(4, (-2.06 + (-2.29)) / 2, 1860.0); galice_pbpb_5p02_y_c0t5->SetPointError(4, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(5, (-1.86 + (-2.1)) / 2, 1950.0); galice_pbpb_5p02_y_c0t5->SetPointError(5, 0, 90.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(6, (-1.57 + (-1.82)) / 2, 2030.0); galice_pbpb_5p02_y_c0t5->SetPointError(6, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(7, (-1.38 + (-1.61)) / 2, 2080.0); galice_pbpb_5p02_y_c0t5->SetPointError(7, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(8, (-1.1 + (-1.32)) / 2, 2140.0); galice_pbpb_5p02_y_c0t5->SetPointError(8, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(9, (-0.91 + (-1.13)) / 2, 2170.0); galice_pbpb_5p02_y_c0t5->SetPointError(9, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(10, (-0.64 + (-0.85)) / 2, 2200.0); galice_pbpb_5p02_y_c0t5->SetPointError(10, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(11, (-0.45 + (-0.68)) / 2, 2210.0); galice_pbpb_5p02_y_c0t5->SetPointError(11, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(12, (-0.2 + (-0.4)) / 2, 2230.0); galice_pbpb_5p02_y_c0t5->SetPointError(12, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(13, (-0.0 + (-0.2)) / 2, 2240.0); galice_pbpb_5p02_y_c0t5->SetPointError(13, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(14, (0.2 + (0.0)) / 2, 2240.0); galice_pbpb_5p02_y_c0t5->SetPointError(14, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(15, (0.4 + (0.2)) / 2, 2230.0); galice_pbpb_5p02_y_c0t5->SetPointError(15, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(16, (0.68 + (0.45)) / 2, 2210.0); galice_pbpb_5p02_y_c0t5->SetPointError(16, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(17, (0.85 + (0.64)) / 2, 2200.0); galice_pbpb_5p02_y_c0t5->SetPointError(17, 0, 60.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(18, (1.13 + (0.91)) / 2, 2170.0); galice_pbpb_5p02_y_c0t5->SetPointError(18, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(19, (1.32 + (1.1)) / 2, 2140.0); galice_pbpb_5p02_y_c0t5->SetPointError(19, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(20, (1.61 + (1.38)) / 2, 2080.0); galice_pbpb_5p02_y_c0t5->SetPointError(20, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(21, (1.82 + (1.57)) / 2, 2030.0); galice_pbpb_5p02_y_c0t5->SetPointError(21, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(22, (2.1 + (1.86)) / 2, 1950.0); galice_pbpb_5p02_y_c0t5->SetPointError(22, 0, 90.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(23, (2.29 + (2.06)) / 2, 1860.0); galice_pbpb_5p02_y_c0t5->SetPointError(23, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(24, (2.59 + (2.36)) / 2, 1800.0); galice_pbpb_5p02_y_c0t5->SetPointError(24, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(25, (2.79 + (2.57)) / 2, 1730.0); galice_pbpb_5p02_y_c0t5->SetPointError(25, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(26, (3.09 + (2.85)) / 2, 1680.0); galice_pbpb_5p02_y_c0t5->SetPointError(26, 0, 80.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(27, (3.29 + (3.05)) / 2, 1650.0); galice_pbpb_5p02_y_c0t5->SetPointError(27, 0, 70.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(28, (3.59 + (3.35)) / 2, 1600.0); galice_pbpb_5p02_y_c0t5->SetPointError(28, 0, 100.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(29, (3.79 + (3.55)) / 2, 1500.0); galice_pbpb_5p02_y_c0t5->SetPointError(29, 0, 100.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(30, (4.09 + (3.85)) / 2, 1370.0); galice_pbpb_5p02_y_c0t5->SetPointError(30, 0, 90.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(31, (4.29 + (4.05)) / 2, 1320.0); galice_pbpb_5p02_y_c0t5->SetPointError(31, 0, 90.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(32, (4.59 + (4.35)) / 2, 1280.0); galice_pbpb_5p02_y_c0t5->SetPointError(32, 0, 90.0);
   galice_pbpb_5p02_y_c0t5->SetPoint(33, (4.79 + (4.55)) / 2, 1240.0); galice_pbpb_5p02_y_c0t5->SetPointError(33, 0, 80.0);

   return galice_pbpb_5p02_y_c0t5;
}

static const double cms_0p5_etabins[11] = {
   -2.5, -2.0, -1.5, -1.0, -0.5, 0.0,
    0.5,  1.0,  1.5,  2.0,  2.5
};

TH1F* hcms_pbpb_2p76_eta_c0t5() {
   TH1F* hcms_pbpb_2p76_eta_c0t5 = new TH1F("hcms_pbpb_2p76_eta_c0t5", "", 10, cms_0p5_etabins);

   hcms_pbpb_2p76_eta_c0t5->SetBinContent(1, 8.74 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(1, 0.3 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(2, 8.88 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(2, 0.31 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(3, 8.92 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(3, 0.31 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(4, 8.71 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(4, 0.3 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(5, 8.47 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(5, 0.29 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(6, 8.45 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(6, 0.29 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(7, 8.74 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(7, 0.3 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(8, 8.88 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(8, 0.31 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(9, 8.97 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(9, 0.31 * 381 / 2);
   hcms_pbpb_2p76_eta_c0t5->SetBinContent(10, 8.74 * 381 / 2); hcms_pbpb_2p76_eta_c0t5->SetBinError(10, 0.3 * 381 / 2);

   return hcms_pbpb_2p76_eta_c0t5;
}

TH1F* hcms_pbpb_2p76_eta_c0t90() {
   TH1F* hcms_pbpb_2p76_eta_c0t90 = new TH1F("hcms_pbpb_2p76_eta_c0t90", "", 10, cms_0p5_etabins);

   hcms_pbpb_2p76_eta_c0t90->SetBinContent(1, 7.63 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(1, 0.59 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(2, 7.77 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(2, 0.6 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(3, 7.71 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(3, 0.59 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(4, 7.51 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(4, 0.58 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(5, 7.28 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(5, 0.56 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(6, 7.27 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(6, 0.56 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(7, 7.49 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(7, 0.58 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(8, 7.69 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(8, 0.59 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(9, 7.79 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(9, 0.6 * 103.97 / 2);
   hcms_pbpb_2p76_eta_c0t90->SetBinContent(10, 7.63 * 103.97 / 2); hcms_pbpb_2p76_eta_c0t90->SetBinError(10, 0.59 * 103.97 / 2);

   return hcms_pbpb_2p76_eta_c0t90;
}

TH1F* hcms_pp_2p36_eta() {
   TH1F* hcms_pp_2p36_eta = new TH1F("hcms_pp_2p36_eta", "", 10, cms_0p5_etabins);

   hcms_pp_2p36_eta->SetBinContent(1, 3.6); hcms_pp_2p36_eta->SetBinError(1, 0.13);
   hcms_pp_2p36_eta->SetBinContent(2, 3.73); hcms_pp_2p36_eta->SetBinError(2, 0.14);
   hcms_pp_2p36_eta->SetBinContent(3, 3.62); hcms_pp_2p36_eta->SetBinError(3, 0.13);
   hcms_pp_2p36_eta->SetBinContent(4, 3.54); hcms_pp_2p36_eta->SetBinError(4, 0.13);
   hcms_pp_2p36_eta->SetBinContent(5, 3.48); hcms_pp_2p36_eta->SetBinError(5, 0.13);
   hcms_pp_2p36_eta->SetBinContent(6, 3.48); hcms_pp_2p36_eta->SetBinError(6, 0.13);
   hcms_pp_2p36_eta->SetBinContent(7, 3.54); hcms_pp_2p36_eta->SetBinError(7, 0.13);
   hcms_pp_2p36_eta->SetBinContent(8, 3.62); hcms_pp_2p36_eta->SetBinError(8, 0.13);
   hcms_pp_2p36_eta->SetBinContent(9, 3.73); hcms_pp_2p36_eta->SetBinError(9, 0.14);
   hcms_pp_2p36_eta->SetBinContent(10, 3.6); hcms_pp_2p36_eta->SetBinError(10, 0.13);

   return hcms_pp_2p36_eta;
}

TH1F* hcms_pp_7p0_eta() {
   TH1F* hcms_pp_7p0_eta = new TH1F("hcms_pp_7p0_eta", "", 10, cms_0p5_etabins);

   hcms_pp_7p0_eta->SetBinContent(1, 6.18); hcms_pp_7p0_eta->SetBinError(1, 0.25);
   hcms_pp_7p0_eta->SetBinContent(2, 6.26); hcms_pp_7p0_eta->SetBinError(2, 0.25);
   hcms_pp_7p0_eta->SetBinContent(3, 6.14); hcms_pp_7p0_eta->SetBinError(3, 0.24);
   hcms_pp_7p0_eta->SetBinContent(4, 6.01); hcms_pp_7p0_eta->SetBinError(4, 0.24);
   hcms_pp_7p0_eta->SetBinContent(5, 5.78); hcms_pp_7p0_eta->SetBinError(5, 0.23);
   hcms_pp_7p0_eta->SetBinContent(6, 5.78); hcms_pp_7p0_eta->SetBinError(6, 0.23);
   hcms_pp_7p0_eta->SetBinContent(7, 6.01); hcms_pp_7p0_eta->SetBinError(7, 0.24);
   hcms_pp_7p0_eta->SetBinContent(8, 6.14); hcms_pp_7p0_eta->SetBinError(8, 0.24);
   hcms_pp_7p0_eta->SetBinContent(9, 6.26); hcms_pp_7p0_eta->SetBinError(9, 0.25);
   hcms_pp_7p0_eta->SetBinContent(10, 6.18); hcms_pp_7p0_eta->SetBinError(10, 0.25);

   return hcms_pp_7p0_eta;
}

TH1F* hcms_pp_13p0_eta() {
#define INCLUDE_ETA_BINS
#include "bins.h"
   TH1F* hcms_pp_13p0_eta = new TH1F("hcms_pp_13p0_eta", "", neta, etab);

   hcms_pp_13p0_eta->SetBinContent(9, 6.25); hcms_pp_13p0_eta->SetBinError(9, 0.226);
   hcms_pp_13p0_eta->SetBinContent(10, 6.138); hcms_pp_13p0_eta->SetBinError(10, 0.199);
   hcms_pp_13p0_eta->SetBinContent(11, 6.091); hcms_pp_13p0_eta->SetBinError(11, 0.196);
   hcms_pp_13p0_eta->SetBinContent(12, 6.074); hcms_pp_13p0_eta->SetBinError(12, 0.192);
   hcms_pp_13p0_eta->SetBinContent(13, 5.966); hcms_pp_13p0_eta->SetBinError(13, 0.185);
   hcms_pp_13p0_eta->SetBinContent(14, 5.825); hcms_pp_13p0_eta->SetBinError(14, 0.179);
   hcms_pp_13p0_eta->SetBinContent(15, 5.743); hcms_pp_13p0_eta->SetBinError(15, 0.177);
   hcms_pp_13p0_eta->SetBinContent(16, 5.606); hcms_pp_13p0_eta->SetBinError(16, 0.172);
   hcms_pp_13p0_eta->SetBinContent(17, 5.495); hcms_pp_13p0_eta->SetBinError(17, 0.168);
   hcms_pp_13p0_eta->SetBinContent(18, 5.412); hcms_pp_13p0_eta->SetBinError(18, 0.169);
   hcms_pp_13p0_eta->SetBinContent(19, 5.412); hcms_pp_13p0_eta->SetBinError(19, 0.169);
   hcms_pp_13p0_eta->SetBinContent(20, 5.495); hcms_pp_13p0_eta->SetBinError(20, 0.168);
   hcms_pp_13p0_eta->SetBinContent(21, 5.606); hcms_pp_13p0_eta->SetBinError(21, 0.172);
   hcms_pp_13p0_eta->SetBinContent(22, 5.743); hcms_pp_13p0_eta->SetBinError(22, 0.177);
   hcms_pp_13p0_eta->SetBinContent(23, 5.825); hcms_pp_13p0_eta->SetBinError(23, 0.179);
   hcms_pp_13p0_eta->SetBinContent(24, 5.966); hcms_pp_13p0_eta->SetBinError(24, 0.185);
   hcms_pp_13p0_eta->SetBinContent(25, 6.074); hcms_pp_13p0_eta->SetBinError(25, 0.192);
   hcms_pp_13p0_eta->SetBinContent(26, 6.091); hcms_pp_13p0_eta->SetBinError(26, 0.196);
   hcms_pp_13p0_eta->SetBinContent(27, 6.138); hcms_pp_13p0_eta->SetBinError(27, 0.199);
   hcms_pp_13p0_eta->SetBinContent(28, 6.25); hcms_pp_13p0_eta->SetBinError(28, 0.226);

   return hcms_pp_13p0_eta;
}

static const double phobos_etabins[55] = {
   -5.4, -5.2, -5.0, -4.8, -4.6, -4.4, -4.2, -4.0, -3.8, -3.6,
   -3.4, -3.2, -3.0, -2.8, -2.6, -2.4, -2.2, -2.0, -1.8, -1.6,
   -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2,  0.0,  0.2,  0.4,
    0.6,  0.8,  1.0,  1.2,  1.4,  1.6,  1.8,  2.0,  2.2,  2.4,
    2.6,  2.8,  3.0,  3.2,  3.4,  3.6,  3.8,  4.0,  4.2,  4.4,
    4.6,  4.8,  5.0,  5.2,  5.4
};

TH1F* hphobos_pp_0p2_eta() {
   TH1F* hphobos_pp_0p2_eta = new TH1F("hphobos_pp_0p2_eta", "", 54, phobos_etabins);

   hphobos_pp_0p2_eta->SetBinContent(1, 0.4197); hphobos_pp_0p2_eta->SetBinError(1, 0.2114);
   hphobos_pp_0p2_eta->SetBinContent(2, 0.5389); hphobos_pp_0p2_eta->SetBinError(2, 0.2047);
   hphobos_pp_0p2_eta->SetBinContent(3, 0.5448); hphobos_pp_0p2_eta->SetBinError(3, 0.3225);
   hphobos_pp_0p2_eta->SetBinContent(4, 0.6034); hphobos_pp_0p2_eta->SetBinError(4, 0.3981);
   hphobos_pp_0p2_eta->SetBinContent(5, 0.9493); hphobos_pp_0p2_eta->SetBinError(5, 0.1958);
   hphobos_pp_0p2_eta->SetBinContent(6, 1.0945); hphobos_pp_0p2_eta->SetBinError(6, 0.2019);
   hphobos_pp_0p2_eta->SetBinContent(7, 1.2286); hphobos_pp_0p2_eta->SetBinError(7, 0.2248);
   hphobos_pp_0p2_eta->SetBinContent(8, 1.3915); hphobos_pp_0p2_eta->SetBinError(8, 0.2222);
   hphobos_pp_0p2_eta->SetBinContent(9, 1.5117); hphobos_pp_0p2_eta->SetBinError(9, 0.2631);
   hphobos_pp_0p2_eta->SetBinContent(10, 1.6755); hphobos_pp_0p2_eta->SetBinError(10, 0.2583);
   hphobos_pp_0p2_eta->SetBinContent(11, 1.8018); hphobos_pp_0p2_eta->SetBinError(11, 0.2858);
   hphobos_pp_0p2_eta->SetBinContent(12, 1.9779); hphobos_pp_0p2_eta->SetBinError(12, 0.2558);
   hphobos_pp_0p2_eta->SetBinContent(13, 2.0333); hphobos_pp_0p2_eta->SetBinError(13, 0.3360);
   hphobos_pp_0p2_eta->SetBinContent(14, 2.1300); hphobos_pp_0p2_eta->SetBinError(14, 0.3622);
   hphobos_pp_0p2_eta->SetBinContent(15, 2.2300); hphobos_pp_0p2_eta->SetBinError(15, 0.3706);
   hphobos_pp_0p2_eta->SetBinContent(16, 2.3037); hphobos_pp_0p2_eta->SetBinError(16, 0.3890);
   hphobos_pp_0p2_eta->SetBinContent(17, 2.4071); hphobos_pp_0p2_eta->SetBinError(17, 0.3603);
   hphobos_pp_0p2_eta->SetBinContent(18, 2.4430); hphobos_pp_0p2_eta->SetBinError(18, 0.3803);
   hphobos_pp_0p2_eta->SetBinContent(19, 2.4125); hphobos_pp_0p2_eta->SetBinError(19, 0.4462);
   hphobos_pp_0p2_eta->SetBinContent(20, 2.4691); hphobos_pp_0p2_eta->SetBinError(20, 0.4025);
   hphobos_pp_0p2_eta->SetBinContent(21, 2.5033); hphobos_pp_0p2_eta->SetBinError(21, 0.3569);
   hphobos_pp_0p2_eta->SetBinContent(22, 2.4502); hphobos_pp_0p2_eta->SetBinError(22, 0.3737);
   hphobos_pp_0p2_eta->SetBinContent(23, 2.3038); hphobos_pp_0p2_eta->SetBinError(23, 0.4617);
   hphobos_pp_0p2_eta->SetBinContent(24, 2.2266); hphobos_pp_0p2_eta->SetBinError(24, 0.4654);
   hphobos_pp_0p2_eta->SetBinContent(25, 2.2254); hphobos_pp_0p2_eta->SetBinError(25, 0.3908);
   hphobos_pp_0p2_eta->SetBinContent(26, 2.2390); hphobos_pp_0p2_eta->SetBinError(26, 0.3141);
   hphobos_pp_0p2_eta->SetBinContent(27, 2.2096); hphobos_pp_0p2_eta->SetBinError(27, 0.3076);
   hphobos_pp_0p2_eta->SetBinContent(28, 2.2644); hphobos_pp_0p2_eta->SetBinError(28, 0.2527);
   hphobos_pp_0p2_eta->SetBinContent(29, 2.2526); hphobos_pp_0p2_eta->SetBinError(29, 0.3004);
   hphobos_pp_0p2_eta->SetBinContent(30, 2.2318); hphobos_pp_0p2_eta->SetBinError(30, 0.3843);
   hphobos_pp_0p2_eta->SetBinContent(31, 2.2559); hphobos_pp_0p2_eta->SetBinError(31, 0.4362);
   hphobos_pp_0p2_eta->SetBinContent(32, 2.3299); hphobos_pp_0p2_eta->SetBinError(32, 0.4355);
   hphobos_pp_0p2_eta->SetBinContent(33, 2.4606); hphobos_pp_0p2_eta->SetBinError(33, 0.3633);
   hphobos_pp_0p2_eta->SetBinContent(34, 2.4947); hphobos_pp_0p2_eta->SetBinError(34, 0.3655);
   hphobos_pp_0p2_eta->SetBinContent(35, 2.5480); hphobos_pp_0p2_eta->SetBinError(35, 0.3236);
   hphobos_pp_0p2_eta->SetBinContent(36, 2.4996); hphobos_pp_0p2_eta->SetBinError(36, 0.3591);
   hphobos_pp_0p2_eta->SetBinContent(37, 2.5075); hphobos_pp_0p2_eta->SetBinError(37, 0.3158);
   hphobos_pp_0p2_eta->SetBinContent(38, 2.4436); hphobos_pp_0p2_eta->SetBinError(38, 0.3238);
   hphobos_pp_0p2_eta->SetBinContent(39, 2.3223); hphobos_pp_0p2_eta->SetBinError(39, 0.3704);
   hphobos_pp_0p2_eta->SetBinContent(40, 2.2673); hphobos_pp_0p2_eta->SetBinError(40, 0.3332);
   hphobos_pp_0p2_eta->SetBinContent(41, 2.1105); hphobos_pp_0p2_eta->SetBinError(41, 0.3817);
   hphobos_pp_0p2_eta->SetBinContent(42, 2.0041); hphobos_pp_0p2_eta->SetBinError(42, 0.3652);
   hphobos_pp_0p2_eta->SetBinContent(43, 1.9361); hphobos_pp_0p2_eta->SetBinError(43, 0.2975);
   hphobos_pp_0p2_eta->SetBinContent(44, 1.7353); hphobos_pp_0p2_eta->SetBinError(44, 0.3523);
   hphobos_pp_0p2_eta->SetBinContent(45, 1.6879); hphobos_pp_0p2_eta->SetBinError(45, 0.2458);
   hphobos_pp_0p2_eta->SetBinContent(46, 1.5785); hphobos_pp_0p2_eta->SetBinError(46, 0.1963);
   hphobos_pp_0p2_eta->SetBinContent(47, 1.2767); hphobos_pp_0p2_eta->SetBinError(47, 0.3371);
   hphobos_pp_0p2_eta->SetBinContent(48, 1.1797); hphobos_pp_0p2_eta->SetBinError(48, 0.2737);
   hphobos_pp_0p2_eta->SetBinContent(49, 1.0612); hphobos_pp_0p2_eta->SetBinError(49, 0.2352);
   hphobos_pp_0p2_eta->SetBinContent(50, 0.9580); hphobos_pp_0p2_eta->SetBinError(50, 0.1871);
   hphobos_pp_0p2_eta->SetBinContent(51, 0.7445); hphobos_pp_0p2_eta->SetBinError(51, 0.2570);
   hphobos_pp_0p2_eta->SetBinContent(52, 0.6122); hphobos_pp_0p2_eta->SetBinError(52, 0.2551);
   hphobos_pp_0p2_eta->SetBinContent(53, 0.5636); hphobos_pp_0p2_eta->SetBinError(53, 0.1800);
   hphobos_pp_0p2_eta->SetBinContent(54, 0.4608); hphobos_pp_0p2_eta->SetBinError(54, 0.1703);

   return hphobos_pp_0p2_eta;
}

TH1F* hphobos_cucu_0p2_eta() {
   TH1F* hphobos_cucu_0p2_eta = new TH1F("hphobos_cucu_0p2_eta", "", 54, phobos_etabins);

   hphobos_cucu_0p2_eta->SetBinContent(1, 24.379385); hphobos_cucu_0p2_eta->SetBinError(1, 8.962027);
   hphobos_cucu_0p2_eta->SetBinContent(2, 30.176258); hphobos_cucu_0p2_eta->SetBinError(2, 11.101170);
   hphobos_cucu_0p2_eta->SetBinContent(3, 38.267990); hphobos_cucu_0p2_eta->SetBinError(3, 12.285854);
   hphobos_cucu_0p2_eta->SetBinContent(4, 46.675228); hphobos_cucu_0p2_eta->SetBinError(4, 14.472263);
   hphobos_cucu_0p2_eta->SetBinContent(5, 60.128609); hphobos_cucu_0p2_eta->SetBinError(5, 12.799446);
   hphobos_cucu_0p2_eta->SetBinContent(6, 70.254242); hphobos_cucu_0p2_eta->SetBinError(6, 15.392792);
   hphobos_cucu_0p2_eta->SetBinContent(7, 82.831604); hphobos_cucu_0p2_eta->SetBinError(7, 16.115997);
   hphobos_cucu_0p2_eta->SetBinContent(8, 94.446022); hphobos_cucu_0p2_eta->SetBinError(8, 17.952393);
   hphobos_cucu_0p2_eta->SetBinContent(9, 107.081223); hphobos_cucu_0p2_eta->SetBinError(9, 18.465080);
   hphobos_cucu_0p2_eta->SetBinContent(10, 120.271469); hphobos_cucu_0p2_eta->SetBinError(10, 17.703064);
   hphobos_cucu_0p2_eta->SetBinContent(11, 132.030731); hphobos_cucu_0p2_eta->SetBinError(11, 17.320450);
   hphobos_cucu_0p2_eta->SetBinContent(12, 134.127335); hphobos_cucu_0p2_eta->SetBinError(12, 25.329330);
   hphobos_cucu_0p2_eta->SetBinContent(13, 147.000381); hphobos_cucu_0p2_eta->SetBinError(13, 21.186737);
   hphobos_cucu_0p2_eta->SetBinContent(14, 154.990021); hphobos_cucu_0p2_eta->SetBinError(14, 20.548584);
   hphobos_cucu_0p2_eta->SetBinContent(15, 161.189713); hphobos_cucu_0p2_eta->SetBinError(15, 20.391144);
   hphobos_cucu_0p2_eta->SetBinContent(16, 170.396317); hphobos_cucu_0p2_eta->SetBinError(16, 16.032501);
   hphobos_cucu_0p2_eta->SetBinContent(17, 174.753235); hphobos_cucu_0p2_eta->SetBinError(17, 15.464951);
   hphobos_cucu_0p2_eta->SetBinContent(18, 180.856552); hphobos_cucu_0p2_eta->SetBinError(18, 12.230835);
   hphobos_cucu_0p2_eta->SetBinContent(19, 183.806976); hphobos_cucu_0p2_eta->SetBinError(19, 11.359756);
   hphobos_cucu_0p2_eta->SetBinContent(20, 186.008026); hphobos_cucu_0p2_eta->SetBinError(20, 10.566040);
   hphobos_cucu_0p2_eta->SetBinContent(21, 187.171173); hphobos_cucu_0p2_eta->SetBinError(21, 10.244843);
   hphobos_cucu_0p2_eta->SetBinContent(22, 185.606094); hphobos_cucu_0p2_eta->SetBinError(22, 12.187927);
   hphobos_cucu_0p2_eta->SetBinContent(23, 185.841324); hphobos_cucu_0p2_eta->SetBinError(23, 11.972778);
   hphobos_cucu_0p2_eta->SetBinContent(24, 183.168472); hphobos_cucu_0p2_eta->SetBinError(24, 14.429077);
   hphobos_cucu_0p2_eta->SetBinContent(25, 181.652359); hphobos_cucu_0p2_eta->SetBinError(25, 15.634750);
   hphobos_cucu_0p2_eta->SetBinContent(26, 179.552185); hphobos_cucu_0p2_eta->SetBinError(26, 17.488083);
   hphobos_cucu_0p2_eta->SetBinContent(27, 181.015442); hphobos_cucu_0p2_eta->SetBinError(27, 15.988327);
   hphobos_cucu_0p2_eta->SetBinContent(28, 178.787140); hphobos_cucu_0p2_eta->SetBinError(28, 18.216629);
   hphobos_cucu_0p2_eta->SetBinContent(29, 180.017761); hphobos_cucu_0p2_eta->SetBinError(29, 17.022507);
   hphobos_cucu_0p2_eta->SetBinContent(30, 180.435165); hphobos_cucu_0p2_eta->SetBinError(30, 16.851944);
   hphobos_cucu_0p2_eta->SetBinContent(31, 183.092102); hphobos_cucu_0p2_eta->SetBinError(31, 14.505447);
   hphobos_cucu_0p2_eta->SetBinContent(32, 184.128784); hphobos_cucu_0p2_eta->SetBinError(32, 13.685318);
   hphobos_cucu_0p2_eta->SetBinContent(33, 184.961655); hphobos_cucu_0p2_eta->SetBinError(33, 12.832367);
   hphobos_cucu_0p2_eta->SetBinContent(34, 185.473038); hphobos_cucu_0p2_eta->SetBinError(34, 11.942978);
   hphobos_cucu_0p2_eta->SetBinContent(35, 184.833832); hphobos_cucu_0p2_eta->SetBinError(35, 11.740234);
   hphobos_cucu_0p2_eta->SetBinContent(36, 183.310120); hphobos_cucu_0p2_eta->SetBinError(36, 11.856613);
   hphobos_cucu_0p2_eta->SetBinContent(37, 179.333206); hphobos_cucu_0p2_eta->SetBinError(37, 13.754181);
   hphobos_cucu_0p2_eta->SetBinContent(38, 175.620987); hphobos_cucu_0p2_eta->SetBinError(38, 14.597198);
   hphobos_cucu_0p2_eta->SetBinContent(39, 170.214859); hphobos_cucu_0p2_eta->SetBinError(39, 16.213959);
   hphobos_cucu_0p2_eta->SetBinContent(40, 163.751419); hphobos_cucu_0p2_eta->SetBinError(40, 17.829422);
   hphobos_cucu_0p2_eta->SetBinContent(41, 156.375198); hphobos_cucu_0p2_eta->SetBinError(41, 19.163406);
   hphobos_cucu_0p2_eta->SetBinContent(42, 149.111435); hphobos_cucu_0p2_eta->SetBinError(42, 19.075684);
   hphobos_cucu_0p2_eta->SetBinContent(43, 145.059875); hphobos_cucu_0p2_eta->SetBinError(43, 14.396790);
   hphobos_cucu_0p2_eta->SetBinContent(44, 136.883072); hphobos_cucu_0p2_eta->SetBinError(44, 12.468109);
   hphobos_cucu_0p2_eta->SetBinContent(45, 126.255379); hphobos_cucu_0p2_eta->SetBinError(45, 11.719139);
   hphobos_cucu_0p2_eta->SetBinContent(46, 114.817757); hphobos_cucu_0p2_eta->SetBinError(46, 10.728546);
   hphobos_cucu_0p2_eta->SetBinContent(47, 92.280182); hphobos_cucu_0p2_eta->SetBinError(47, 20.118217);
   hphobos_cucu_0p2_eta->SetBinContent(48, 79.906502); hphobos_cucu_0p2_eta->SetBinError(48, 19.041069);
   hphobos_cucu_0p2_eta->SetBinContent(49, 69.002914); hphobos_cucu_0p2_eta->SetBinError(49, 16.644119);
   hphobos_cucu_0p2_eta->SetBinContent(50, 59.664650); hphobos_cucu_0p2_eta->SetBinError(50, 13.263405);
   hphobos_cucu_0p2_eta->SetBinContent(51, 47.732155); hphobos_cucu_0p2_eta->SetBinError(51, 13.415310);
   hphobos_cucu_0p2_eta->SetBinContent(52, 39.450710); hphobos_cucu_0p2_eta->SetBinError(52, 11.103134);
   hphobos_cucu_0p2_eta->SetBinContent(53, 31.027746); hphobos_cucu_0p2_eta->SetBinError(53, 10.249662);
   hphobos_cucu_0p2_eta->SetBinContent(54, 24.524733); hphobos_cucu_0p2_eta->SetBinError(54, 8.816679);

   return hphobos_cucu_0p2_eta;
}

TH1F* hphobos_cucu_0p2_eta_c35t45() {
   TH1F* hphobos_cucu_0p2_eta_c35t45 = new TH1F("hphobos_cucu_0p2_eta_c35t45", "", 54, phobos_etabins);

   hphobos_cucu_0p2_eta_c35t45->SetBinContent(1, 10.713883); hphobos_cucu_0p2_eta_c35t45->SetBinError(1, 2.559818);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(2, 11.863523); hphobos_cucu_0p2_eta_c35t45->SetBinError(2, 3.624869);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(3, 14.237708); hphobos_cucu_0p2_eta_c35t45->SetBinError(3, 3.678662);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(4, 16.138020); hphobos_cucu_0p2_eta_c35t45->SetBinError(4, 4.392117);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(5, 18.141741); hphobos_cucu_0p2_eta_c35t45->SetBinError(5, 5.147337);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(6, 21.092979); hphobos_cucu_0p2_eta_c35t45->SetBinError(6, 5.048157);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(7, 24.192680); hphobos_cucu_0p2_eta_c35t45->SetBinError(7, 4.833424);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(8, 26.717342); hphobos_cucu_0p2_eta_c35t45->SetBinError(8, 5.162884);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(9, 29.210012); hphobos_cucu_0p2_eta_c35t45->SetBinError(9, 5.431414);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(10, 32.001163); hphobos_cucu_0p2_eta_c35t45->SetBinError(10, 5.252953);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(11, 34.848530); hphobos_cucu_0p2_eta_c35t45->SetBinError(11, 4.824337);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(12, 35.129944); hphobos_cucu_0p2_eta_c35t45->SetBinError(12, 6.734463);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(13, 38.495369); hphobos_cucu_0p2_eta_c35t45->SetBinError(13, 5.312531);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(14, 40.238113); hphobos_cucu_0p2_eta_c35t45->SetBinError(14, 5.255653);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(15, 41.771786); hphobos_cucu_0p2_eta_c35t45->SetBinError(15, 5.149727);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(16, 43.755245); hphobos_cucu_0p2_eta_c35t45->SetBinError(16, 4.341953);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(17, 45.013794); hphobos_cucu_0p2_eta_c35t45->SetBinError(17, 4.017170);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(18, 46.338566); hphobos_cucu_0p2_eta_c35t45->SetBinError(18, 3.396496);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(19, 47.126366); hphobos_cucu_0p2_eta_c35t45->SetBinError(19, 3.096298);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(20, 47.231361); hphobos_cucu_0p2_eta_c35t45->SetBinError(20, 3.276474);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(21, 47.368591); hphobos_cucu_0p2_eta_c35t45->SetBinError(21, 3.238373);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(22, 47.485168); hphobos_cucu_0p2_eta_c35t45->SetBinError(22, 3.056816);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(23, 46.468193); hphobos_cucu_0p2_eta_c35t45->SetBinError(23, 3.877213);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(24, 45.886757); hphobos_cucu_0p2_eta_c35t45->SetBinError(24, 4.179333);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(25, 46.108749); hphobos_cucu_0p2_eta_c35t45->SetBinError(25, 3.663780);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(26, 45.732285); hphobos_cucu_0p2_eta_c35t45->SetBinError(26, 3.816013);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(27, 45.606201); hphobos_cucu_0p2_eta_c35t45->SetBinError(27, 3.869148);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(28, 45.321159); hphobos_cucu_0p2_eta_c35t45->SetBinError(28, 4.154190);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(29, 45.919102); hphobos_cucu_0p2_eta_c35t45->SetBinError(29, 3.629196);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(30, 45.778915); hphobos_cucu_0p2_eta_c35t45->SetBinError(30, 3.993614);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(31, 46.054806); hphobos_cucu_0p2_eta_c35t45->SetBinError(31, 4.011284);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(32, 46.454231); hphobos_cucu_0p2_eta_c35t45->SetBinError(32, 3.891174);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(33, 46.937347); hphobos_cucu_0p2_eta_c35t45->SetBinError(33, 3.604637);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(34, 47.191952); hphobos_cucu_0p2_eta_c35t45->SetBinError(34, 3.415012);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(35, 47.227406); hphobos_cucu_0p2_eta_c35t45->SetBinError(35, 3.280430);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(36, 46.747669); hphobos_cucu_0p2_eta_c35t45->SetBinError(36, 3.474995);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(37, 45.966244); hphobos_cucu_0p2_eta_c35t45->SetBinError(37, 3.768818);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(38, 45.487816); hphobos_cucu_0p2_eta_c35t45->SetBinError(38, 3.543148);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(39, 44.068298); hphobos_cucu_0p2_eta_c35t45->SetBinError(39, 4.028896);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(40, 42.552265); hphobos_cucu_0p2_eta_c35t45->SetBinError(40, 4.369244);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(41, 40.868225); hphobos_cucu_0p2_eta_c35t45->SetBinError(41, 4.625542);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(42, 39.006367); hphobos_cucu_0p2_eta_c35t45->SetBinError(42, 4.801533);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(43, 38.795532); hphobos_cucu_0p2_eta_c35t45->SetBinError(43, 3.068871);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(44, 36.594158); hphobos_cucu_0p2_eta_c35t45->SetBinError(44, 3.078705);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(45, 33.703438); hphobos_cucu_0p2_eta_c35t45->SetBinError(45, 3.550674);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(46, 30.659842); hphobos_cucu_0p2_eta_c35t45->SetBinError(46, 3.981585);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(47, 26.453003); hphobos_cucu_0p2_eta_c35t45->SetBinError(47, 5.427221);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(48, 23.129271); hphobos_cucu_0p2_eta_c35t45->SetBinError(48, 5.896826);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(49, 20.601303); hphobos_cucu_0p2_eta_c35t45->SetBinError(49, 5.539833);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(50, 18.462830); hphobos_cucu_0p2_eta_c35t45->SetBinError(50, 4.826248);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(51, 16.385647); hphobos_cucu_0p2_eta_c35t45->SetBinError(51, 4.144484);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(52, 13.890127); hphobos_cucu_0p2_eta_c35t45->SetBinError(52, 4.026243);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(53, 11.789232); hphobos_cucu_0p2_eta_c35t45->SetBinError(53, 3.699155);
   hphobos_cucu_0p2_eta_c35t45->SetBinContent(54, 10.114573); hphobos_cucu_0p2_eta_c35t45->SetBinError(54, 3.159129);

   return hphobos_cucu_0p2_eta_c35t45;
}

TH1F* hphobos_cucu_0p0624_eta_c0t6() {
   TH1F* hphobos_cucu_0p0624_eta_c0t6 = new TH1F("hphobos_cucu_0p0624_eta_c0t6", "", 54, phobos_etabins);

   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(1, 5.494038); hphobos_cucu_0p0624_eta_c0t6->SetBinError(1, 4.073462);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(2, 6.983626); hphobos_cucu_0p0624_eta_c0t6->SetBinError(2, 5.029666);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(3, 9.294306); hphobos_cucu_0p0624_eta_c0t6->SetBinError(3, 5.702373);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(4, 11.555000); hphobos_cucu_0p0624_eta_c0t6->SetBinError(4, 7.032448);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(5, 15.397482); hphobos_cucu_0p0624_eta_c0t6->SetBinError(5, 7.440840);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(6, 19.832870); hphobos_cucu_0p0624_eta_c0t6->SetBinError(6, 8.619917);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(7, 25.369761); hphobos_cucu_0p0624_eta_c0t6->SetBinError(7, 9.665434);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(8, 33.923515); hphobos_cucu_0p0624_eta_c0t6->SetBinError(8, 8.635803);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(9, 39.360306); hphobos_cucu_0p0624_eta_c0t6->SetBinError(9, 11.553825);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(10, 48.114353); hphobos_cucu_0p0624_eta_c0t6->SetBinError(10, 11.782337);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(11, 58.738029); hphobos_cucu_0p0624_eta_c0t6->SetBinError(11, 10.485085);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(12, 64.471703); hphobos_cucu_0p0624_eta_c0t6->SetBinError(12, 14.087410);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(13, 74.432838); hphobos_cucu_0p0624_eta_c0t6->SetBinError(13, 13.131165);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(14, 82.587112); hphobos_cucu_0p0624_eta_c0t6->SetBinError(14, 13.349190);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(15, 91.629501); hphobos_cucu_0p0624_eta_c0t6->SetBinError(15, 11.818680);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(16, 99.657646); hphobos_cucu_0p0624_eta_c0t6->SetBinError(16, 10.303444);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(17, 106.715179); hphobos_cucu_0p0624_eta_c0t6->SetBinError(17, 8.707382);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(18, 112.472328); hphobos_cucu_0p0624_eta_c0t6->SetBinError(18, 7.377655);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(19, 117.470818); hphobos_cucu_0p0624_eta_c0t6->SetBinError(19, 5.838371);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(20, 118.897888); hphobos_cucu_0p0624_eta_c0t6->SetBinError(20, 6.996941);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(21, 121.087418); hphobos_cucu_0p0624_eta_c0t6->SetBinError(21, 6.629227);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(22, 121.900505); hphobos_cucu_0p0624_eta_c0t6->SetBinError(22, 6.992958);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(23, 121.455688); hphobos_cucu_0p0624_eta_c0t6->SetBinError(23, 8.098648);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(24, 120.222260); hphobos_cucu_0p0624_eta_c0t6->SetBinError(24, 9.621704);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(25, 119.137665); hphobos_cucu_0p0624_eta_c0t6->SetBinError(25, 10.788651);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(26, 119.610321); hphobos_cucu_0p0624_eta_c0t6->SetBinError(26, 10.366913);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(27, 119.593559); hphobos_cucu_0p0624_eta_c0t6->SetBinError(27, 10.565773);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(28, 120.174385); hphobos_cucu_0p0624_eta_c0t6->SetBinError(28, 9.984947);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(29, 120.590843); hphobos_cucu_0p0624_eta_c0t6->SetBinError(29, 9.386391);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(30, 120.131210); hphobos_cucu_0p0624_eta_c0t6->SetBinError(30, 9.795105);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(31, 121.247765); hphobos_cucu_0p0624_eta_c0t6->SetBinError(31, 8.596199);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(32, 121.938728); hphobos_cucu_0p0624_eta_c0t6->SetBinError(32, 7.615608);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(33, 120.563179); hphobos_cucu_0p0624_eta_c0t6->SetBinError(33, 8.330284);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(34, 120.804970); hphobos_cucu_0p0624_eta_c0t6->SetBinError(34, 6.911674);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(35, 119.731316); hphobos_cucu_0p0624_eta_c0t6->SetBinError(35, 6.163506);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(36, 116.786774); hphobos_cucu_0p0624_eta_c0t6->SetBinError(36, 6.522408);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(37, 112.715271); hphobos_cucu_0p0624_eta_c0t6->SetBinError(37, 7.134712);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(38, 107.690964); hphobos_cucu_0p0624_eta_c0t6->SetBinError(38, 7.731590);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(39, 100.897964); hphobos_cucu_0p0624_eta_c0t6->SetBinError(39, 9.063118);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(40, 93.805611); hphobos_cucu_0p0624_eta_c0t6->SetBinError(40, 9.642563);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(41, 85.205536); hphobos_cucu_0p0624_eta_c0t6->SetBinError(41, 10.730766);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(42, 76.127274); hphobos_cucu_0p0624_eta_c0t6->SetBinError(42, 11.436722);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(43, 66.799805); hphobos_cucu_0p0624_eta_c0t6->SetBinError(43, 11.759293);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(44, 61.199184); hphobos_cucu_0p0624_eta_c0t6->SetBinError(44, 8.023922);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(45, 52.212872); hphobos_cucu_0p0624_eta_c0t6->SetBinError(45, 7.683807);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(46, 43.527973); hphobos_cucu_0p0624_eta_c0t6->SetBinError(46, 7.386158);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(47, 29.682739); hphobos_cucu_0p0624_eta_c0t6->SetBinError(47, 12.876572);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(48, 23.521372); hphobos_cucu_0p0624_eta_c0t6->SetBinError(48, 11.513803);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(49, 19.048742); hphobos_cucu_0p0624_eta_c0t6->SetBinError(49, 9.404045);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(50, 14.957639); hphobos_cucu_0p0624_eta_c0t6->SetBinError(50, 7.880683);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(51, 11.993420); hphobos_cucu_0p0624_eta_c0t6->SetBinError(51, 6.594019);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(52, 9.144915); hphobos_cucu_0p0624_eta_c0t6->SetBinError(52, 5.851764);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(53, 7.090699); hphobos_cucu_0p0624_eta_c0t6->SetBinError(53, 4.922585);
   hphobos_cucu_0p0624_eta_c0t6->SetBinContent(54, 5.306877); hphobos_cucu_0p0624_eta_c0t6->SetBinError(54, 4.260623);

   return hphobos_cucu_0p0624_eta_c0t6;
}

TH1F* hphobos_auau_0p2_eta() {
   TH1F* hphobos_auau_0p2_eta = new TH1F("hphobos_auau_0p2_eta", "", 54, phobos_etabins);

   hphobos_auau_0p2_eta->SetBinContent(1, 72.292084 ); hphobos_auau_0p2_eta->SetBinError(1, 19.991364);
   hphobos_auau_0p2_eta->SetBinContent(2, 88.964233 ); hphobos_auau_0p2_eta->SetBinError(2, 25.744209);
   hphobos_auau_0p2_eta->SetBinContent(3, 116.828552); hphobos_auau_0p2_eta->SetBinError(3, 24.647537);
   hphobos_auau_0p2_eta->SetBinContent(4, 147.454895); hphobos_auau_0p2_eta->SetBinError(4, 25.432419);
   hphobos_auau_0p2_eta->SetBinContent(5, 173.092545); hphobos_auau_0p2_eta->SetBinError(5, 35.924500);
   hphobos_auau_0p2_eta->SetBinContent(6, 223.513947); hphobos_auau_0p2_eta->SetBinError(6, 26.113495);
   hphobos_auau_0p2_eta->SetBinContent(7, 262.477631); hphobos_auau_0p2_eta->SetBinError(7, 31.627045);
   hphobos_auau_0p2_eta->SetBinContent(8, 297.870361); hphobos_auau_0p2_eta->SetBinError(8, 43.575928);
   hphobos_auau_0p2_eta->SetBinContent(9, 345.325348); hphobos_auau_0p2_eta->SetBinError(9, 44.994019);
   hphobos_auau_0p2_eta->SetBinContent(10, 387.878998); hphobos_auau_0p2_eta->SetBinError(10, 51.310272);
   hphobos_auau_0p2_eta->SetBinContent(11, 420.483612); hphobos_auau_0p2_eta->SetBinError(11, 66.011414);
   hphobos_auau_0p2_eta->SetBinContent(12, 472.000549); hphobos_auau_0p2_eta->SetBinError(12, 58.829651);
   hphobos_auau_0p2_eta->SetBinContent(13, 519.498962); hphobos_auau_0p2_eta->SetBinError(13, 51.585144);
   hphobos_auau_0p2_eta->SetBinContent(14, 546.577637); hphobos_auau_0p2_eta->SetBinError(14, 59.937073);
   hphobos_auau_0p2_eta->SetBinContent(15, 572.937805); hphobos_auau_0p2_eta->SetBinError(15, 63.811768);
   hphobos_auau_0p2_eta->SetBinContent(16, 600.294067); hphobos_auau_0p2_eta->SetBinError(16, 61.436646);
   hphobos_auau_0p2_eta->SetBinContent(17, 617.312805); hphobos_auau_0p2_eta->SetBinError(17, 64.318481);
   hphobos_auau_0p2_eta->SetBinContent(18, 641.832458); hphobos_auau_0p2_eta->SetBinError(18, 54.936462);
   hphobos_auau_0p2_eta->SetBinContent(19, 653.074951); hphobos_auau_0p2_eta->SetBinError(19, 54.461182);
   hphobos_auau_0p2_eta->SetBinContent(20, 652.291443); hphobos_auau_0p2_eta->SetBinError(20, 62.066895);
   hphobos_auau_0p2_eta->SetBinContent(21, 655.508728); hphobos_auau_0p2_eta->SetBinError(21, 62.178040);
   hphobos_auau_0p2_eta->SetBinContent(22, 653.151123); hphobos_auau_0p2_eta->SetBinError(22, 64.878052);
   hphobos_auau_0p2_eta->SetBinContent(23, 652.749634); hphobos_auau_0p2_eta->SetBinError(23, 63.265015);
   hphobos_auau_0p2_eta->SetBinContent(24, 647.516052); hphobos_auau_0p2_eta->SetBinError(24, 64.957825);
   hphobos_auau_0p2_eta->SetBinContent(25, 637.687866); hphobos_auau_0p2_eta->SetBinError(25, 70.800415);
   hphobos_auau_0p2_eta->SetBinContent(26, 649.766052); hphobos_auau_0p2_eta->SetBinError(26, 55.562012);
   hphobos_auau_0p2_eta->SetBinContent(27, 642.598267); hphobos_auau_0p2_eta->SetBinError(27, 61.619446);
   hphobos_auau_0p2_eta->SetBinContent(28, 640.510803); hphobos_auau_0p2_eta->SetBinError(28, 63.706909);
   hphobos_auau_0p2_eta->SetBinContent(29, 647.693481); hphobos_auau_0p2_eta->SetBinError(29, 57.634583);
   hphobos_auau_0p2_eta->SetBinContent(30, 634.537720); hphobos_auau_0p2_eta->SetBinError(30, 73.950562);
   hphobos_auau_0p2_eta->SetBinContent(31, 641.307983); hphobos_auau_0p2_eta->SetBinError(31, 71.165955);
   hphobos_auau_0p2_eta->SetBinContent(32, 644.122070); hphobos_auau_0p2_eta->SetBinError(32, 71.892578);
   hphobos_auau_0p2_eta->SetBinContent(33, 645.974487); hphobos_auau_0p2_eta->SetBinError(33, 72.054688);
   hphobos_auau_0p2_eta->SetBinContent(34, 653.934570); hphobos_auau_0p2_eta->SetBinError(34, 63.752197);
   hphobos_auau_0p2_eta->SetBinContent(35, 656.526672); hphobos_auau_0p2_eta->SetBinError(35, 57.831604);
   hphobos_auau_0p2_eta->SetBinContent(36, 652.849121); hphobos_auau_0p2_eta->SetBinError(36, 54.687012);
   hphobos_auau_0p2_eta->SetBinContent(37, 640.414246); hphobos_auau_0p2_eta->SetBinError(37, 56.354675);
   hphobos_auau_0p2_eta->SetBinContent(38, 630.086121); hphobos_auau_0p2_eta->SetBinError(38, 51.545105);
   hphobos_auau_0p2_eta->SetBinContent(39, 607.745605); hphobos_auau_0p2_eta->SetBinError(39, 53.985107);
   hphobos_auau_0p2_eta->SetBinContent(40, 577.862122); hphobos_auau_0p2_eta->SetBinError(40, 58.887451);
   hphobos_auau_0p2_eta->SetBinContent(41, 560.939148); hphobos_auau_0p2_eta->SetBinError(41, 45.575562);
   hphobos_auau_0p2_eta->SetBinContent(42, 516.956177); hphobos_auau_0p2_eta->SetBinError(42, 54.127930);
   hphobos_auau_0p2_eta->SetBinContent(43, 480.390808); hphobos_auau_0p2_eta->SetBinError(43, 50.439392);
   hphobos_auau_0p2_eta->SetBinContent(44, 435.675659); hphobos_auau_0p2_eta->SetBinError(44, 50.819305);
   hphobos_auau_0p2_eta->SetBinContent(45, 402.111511); hphobos_auau_0p2_eta->SetBinError(45, 37.077698);
   hphobos_auau_0p2_eta->SetBinContent(46, 349.748199); hphobos_auau_0p2_eta->SetBinError(46, 40.571167);
   hphobos_auau_0p2_eta->SetBinContent(47, 305.843170); hphobos_auau_0p2_eta->SetBinError(47, 35.603058);
   hphobos_auau_0p2_eta->SetBinContent(48, 262.543976); hphobos_auau_0p2_eta->SetBinError(48, 31.560577);
   hphobos_auau_0p2_eta->SetBinContent(49, 225.120712); hphobos_auau_0p2_eta->SetBinError(49, 24.506729);
   hphobos_auau_0p2_eta->SetBinContent(50, 182.782562); hphobos_auau_0p2_eta->SetBinError(50, 26.234482);
   hphobos_auau_0p2_eta->SetBinContent(51, 147.906143); hphobos_auau_0p2_eta->SetBinError(51, 24.981094);
   hphobos_auau_0p2_eta->SetBinContent(52, 117.969063); hphobos_auau_0p2_eta->SetBinError(52, 23.507027);
   hphobos_auau_0p2_eta->SetBinContent(53, 93.337891 ); hphobos_auau_0p2_eta->SetBinError(53, 21.370491);
   hphobos_auau_0p2_eta->SetBinContent(54, 72.882820 ); hphobos_auau_0p2_eta->SetBinError(54, 19.400627);

   return hphobos_auau_0p2_eta;
}

TH1F* hphobos_auau_0p2_eta_c35t45() {
   TH1F* hphobos_auau_0p2_eta_c35t45 = new TH1F("hphobos_auau_0p2_eta_c35t45", "", 54, phobos_etabins);

   hphobos_auau_0p2_eta_c35t45->SetBinContent(1, 29.877424); hphobos_auau_0p2_eta_c35t45->SetBinError(1, 5.348680);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(2, 33.691338); hphobos_auau_0p2_eta_c35t45->SetBinError(2, 7.959045);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(3, 40.900539); hphobos_auau_0p2_eta_c35t45->SetBinError(3, 7.971889);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(4, 49.878662); hphobos_auau_0p2_eta_c35t45->SetBinError(4, 6.982246);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(5, 53.220970); hphobos_auau_0p2_eta_c35t45->SetBinError(5, 12.318939);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(6, 64.484451); hphobos_auau_0p2_eta_c35t45->SetBinError(6, 10.301918);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(7, 74.361710); hphobos_auau_0p2_eta_c35t45->SetBinError(7, 10.071373);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(8, 82.292580); hphobos_auau_0p2_eta_c35t45->SetBinError(8, 11.985306);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(9, 90.220284); hphobos_auau_0p2_eta_c35t45->SetBinError(9, 13.878357);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(10, 98.831459); hphobos_auau_0p2_eta_c35t45->SetBinError(10, 14.839905);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(11, 108.680870); hphobos_auau_0p2_eta_c35t45->SetBinError(11, 14.107506);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(12, 121.947540); hphobos_auau_0p2_eta_c35t45->SetBinError(12, 9.325851);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(13, 125.489777); hphobos_auau_0p2_eta_c35t45->SetBinError(13, 13.501251);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(14, 131.561279); hphobos_auau_0p2_eta_c35t45->SetBinError(14, 14.288742);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(15, 135.853836); hphobos_auau_0p2_eta_c35t45->SetBinError(15, 15.946838);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(16, 141.713898); hphobos_auau_0p2_eta_c35t45->SetBinError(16, 15.114304);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(17, 145.558090); hphobos_auau_0p2_eta_c35t45->SetBinError(17, 15.386185);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(18, 149.144577); hphobos_auau_0p2_eta_c35t45->SetBinError(18, 15.034088);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(19, 152.068558); hphobos_auau_0p2_eta_c35t45->SetBinError(19, 14.504333);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(20, 153.668945); hphobos_auau_0p2_eta_c35t45->SetBinError(20, 14.508682);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(21, 154.095886); hphobos_auau_0p2_eta_c35t45->SetBinError(21, 14.959457);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(22, 154.842575); hphobos_auau_0p2_eta_c35t45->SetBinError(22, 14.446823);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(23, 154.531250); hphobos_auau_0p2_eta_c35t45->SetBinError(23, 14.468674);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(24, 154.135880); hphobos_auau_0p2_eta_c35t45->SetBinError(24, 14.226517);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(25, 155.645096); hphobos_auau_0p2_eta_c35t45->SetBinError(25, 11.973297);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(26, 152.999252); hphobos_auau_0p2_eta_c35t45->SetBinError(26, 14.060837);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(27, 152.972809); hphobos_auau_0p2_eta_c35t45->SetBinError(27, 14.000763);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(28, 149.794601); hphobos_auau_0p2_eta_c35t45->SetBinError(28, 17.178970);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(29, 151.782593); hphobos_auau_0p2_eta_c35t45->SetBinError(29, 15.277496);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(30, 153.495148); hphobos_auau_0p2_eta_c35t45->SetBinError(30, 14.123245);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(31, 153.097916); hphobos_auau_0p2_eta_c35t45->SetBinError(31, 15.264481);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(32, 151.989822); hphobos_auau_0p2_eta_c35t45->SetBinError(32, 17.010101);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(33, 151.420715); hphobos_auau_0p2_eta_c35t45->SetBinError(33, 17.868683);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(34, 152.737732); hphobos_auau_0p2_eta_c35t45->SetBinError(34, 16.317596);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(35, 153.199066); hphobos_auau_0p2_eta_c35t45->SetBinError(35, 14.978561);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(36, 150.983475); hphobos_auau_0p2_eta_c35t45->SetBinError(36, 15.589417);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(37, 148.733597); hphobos_auau_0p2_eta_c35t45->SetBinError(37, 15.445068);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(38, 147.036407); hphobos_auau_0p2_eta_c35t45->SetBinError(38, 13.907867);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(39, 141.784958); hphobos_auau_0p2_eta_c35t45->SetBinError(39, 15.043243);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(40, 139.299301); hphobos_auau_0p2_eta_c35t45->SetBinError(40, 12.501373);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(41, 133.309647); hphobos_auau_0p2_eta_c35t45->SetBinError(41, 12.540375);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(42, 124.384232); hphobos_auau_0p2_eta_c35t45->SetBinError(42, 14.606781);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(43, 121.207779); hphobos_auau_0p2_eta_c35t45->SetBinError(43, 10.065598);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(44, 113.969757); hphobos_auau_0p2_eta_c35t45->SetBinError(44, 8.818611);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(45, 102.340714); hphobos_auau_0p2_eta_c35t45->SetBinError(45, 11.330643);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(46, 92.809639); hphobos_auau_0p2_eta_c35t45->SetBinError(46, 11.289001);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(47, 84.118805); hphobos_auau_0p2_eta_c35t45->SetBinError(47, 10.159065);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(48, 72.661690); hphobos_auau_0p2_eta_c35t45->SetBinError(48, 11.771370);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(49, 63.864304); hphobos_auau_0p2_eta_c35t45->SetBinError(49, 10.922066);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(50, 55.003082); hphobos_auau_0p2_eta_c35t45->SetBinError(50, 10.536827);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(51, 48.912209); hphobos_auau_0p2_eta_c35t45->SetBinError(51, 7.948681);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(52, 40.961990); hphobos_auau_0p2_eta_c35t45->SetBinError(52, 7.910439);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(53, 34.000664); hphobos_auau_0p2_eta_c35t45->SetBinError(53, 7.649704);
   hphobos_auau_0p2_eta_c35t45->SetBinContent(54, 29.296186); hphobos_auau_0p2_eta_c35t45->SetBinError(54, 5.929918);

   return hphobos_auau_0p2_eta_c35t45;
}

TH1F* hcms_xexe_5p44_eta_c0t90() {
#define INCLUDE_ETA_BINS
#include "bins.h"
   TH1F *hcms_xexe_5p44_eta_c0t90 = new TH1F("hcms_xexe_5p44_eta_c0t90", "", neta, etab);

   hcms_xexe_5p44_eta_c0t90->SetBinContent(3, 344.453); hcms_xexe_5p44_eta_c0t90->SetBinError(3, 0.394508);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(4, 359.817); hcms_xexe_5p44_eta_c0t90->SetBinError(4, 0.234074);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(5, 370.873); hcms_xexe_5p44_eta_c0t90->SetBinError(5, 0.160529);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(6, 378.507); hcms_xexe_5p44_eta_c0t90->SetBinError(6, 0.136289);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(7, 383.299); hcms_xexe_5p44_eta_c0t90->SetBinError(7, 0.138374);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(8, 380.62); hcms_xexe_5p44_eta_c0t90->SetBinError(8, 0.129599);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(9, 377.127); hcms_xexe_5p44_eta_c0t90->SetBinError(9, 0.124363);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(10, 371.255); hcms_xexe_5p44_eta_c0t90->SetBinError(10, 0.124545);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(11, 366.758); hcms_xexe_5p44_eta_c0t90->SetBinError(11, 0.125546);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(12, 361.566); hcms_xexe_5p44_eta_c0t90->SetBinError(12, 0.104539);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(13, 355.715); hcms_xexe_5p44_eta_c0t90->SetBinError(13, 0.0980333);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(14, 349.492); hcms_xexe_5p44_eta_c0t90->SetBinError(14, 0.0969413);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(15, 342.916); hcms_xexe_5p44_eta_c0t90->SetBinError(15, 0.0966607);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(16, 337.01); hcms_xexe_5p44_eta_c0t90->SetBinError(16, 0.096332);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(17, 332.102); hcms_xexe_5p44_eta_c0t90->SetBinError(17, 0.0958821);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(18, 327.469); hcms_xexe_5p44_eta_c0t90->SetBinError(18, 0.0950725);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(19, 327.469); hcms_xexe_5p44_eta_c0t90->SetBinError(19, 0.0950725);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(20, 332.102); hcms_xexe_5p44_eta_c0t90->SetBinError(20, 0.0958821);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(21, 337.01); hcms_xexe_5p44_eta_c0t90->SetBinError(21, 0.096332);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(22, 342.916); hcms_xexe_5p44_eta_c0t90->SetBinError(22, 0.0966607);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(23, 349.492); hcms_xexe_5p44_eta_c0t90->SetBinError(23, 0.0969413);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(24, 355.715); hcms_xexe_5p44_eta_c0t90->SetBinError(24, 0.0980333);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(25, 361.566); hcms_xexe_5p44_eta_c0t90->SetBinError(25, 0.104539);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(26, 366.758); hcms_xexe_5p44_eta_c0t90->SetBinError(26, 0.125546);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(27, 371.255); hcms_xexe_5p44_eta_c0t90->SetBinError(27, 0.124545);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(28, 377.127); hcms_xexe_5p44_eta_c0t90->SetBinError(28, 0.124363);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(29, 380.62); hcms_xexe_5p44_eta_c0t90->SetBinError(29, 0.129599);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(30, 383.299); hcms_xexe_5p44_eta_c0t90->SetBinError(30, 0.138374);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(31, 378.507); hcms_xexe_5p44_eta_c0t90->SetBinError(31, 0.136289);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(32, 370.873); hcms_xexe_5p44_eta_c0t90->SetBinError(32, 0.160529);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(33, 359.817); hcms_xexe_5p44_eta_c0t90->SetBinError(33, 0.234074);
   hcms_xexe_5p44_eta_c0t90->SetBinContent(34, 344.453); hcms_xexe_5p44_eta_c0t90->SetBinError(34, 0.394508);

   return hcms_xexe_5p44_eta_c0t90;
}

TH1F* hcms_xexe_5p44_eta_c0t5() {
#define INCLUDE_ETA_BINS
#include "bins.h"
   TH1F *hcms_xexe_5p44_eta_c0t5 = new TH1F("hcms_xexe_5p44_eta_c0t5","",36, etab);

   hcms_xexe_5p44_eta_c0t5->SetBinContent(3,1205.07);   hcms_xexe_5p44_eta_c0t5->SetBinError(3,3.67789);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(4,1261.74);   hcms_xexe_5p44_eta_c0t5->SetBinError(4,2.17985);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(5,1306.27);   hcms_xexe_5p44_eta_c0t5->SetBinError(5,1.50188);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(6,1334.04);   hcms_xexe_5p44_eta_c0t5->SetBinError(6,1.27621);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(7,1347.97);   hcms_xexe_5p44_eta_c0t5->SetBinError(7,1.29392);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(8,1342.74);   hcms_xexe_5p44_eta_c0t5->SetBinError(8,1.21209);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(9,1334.83);   hcms_xexe_5p44_eta_c0t5->SetBinError(9,1.16685);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(10,1317.51);  hcms_xexe_5p44_eta_c0t5->SetBinError(10,1.16409);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(11,1306.83);  hcms_xexe_5p44_eta_c0t5->SetBinError(11,1.18136);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(12,1292.37);  hcms_xexe_5p44_eta_c0t5->SetBinError(12,0.982696);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(13,1276.24);  hcms_xexe_5p44_eta_c0t5->SetBinError(13,0.928481);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(14,1257.59);  hcms_xexe_5p44_eta_c0t5->SetBinError(14,0.921091);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(15,1237.16);  hcms_xexe_5p44_eta_c0t5->SetBinError(15,0.921866);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(16,1218.52);  hcms_xexe_5p44_eta_c0t5->SetBinError(16,0.919874);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(17,1203.23);  hcms_xexe_5p44_eta_c0t5->SetBinError(17,0.917166);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(18,1187.14);  hcms_xexe_5p44_eta_c0t5->SetBinError(18,0.910276);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(19,1187.14);  hcms_xexe_5p44_eta_c0t5->SetBinError(19,0.910276);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(20,1203.23);  hcms_xexe_5p44_eta_c0t5->SetBinError(20,0.917166);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(21,1218.52);  hcms_xexe_5p44_eta_c0t5->SetBinError(21,0.919874);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(22,1237.16);  hcms_xexe_5p44_eta_c0t5->SetBinError(22,0.921866);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(23,1257.59);  hcms_xexe_5p44_eta_c0t5->SetBinError(23,0.921091);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(24,1276.24);  hcms_xexe_5p44_eta_c0t5->SetBinError(24,0.928481);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(25,1292.37);  hcms_xexe_5p44_eta_c0t5->SetBinError(25,0.982696);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(26,1306.83);  hcms_xexe_5p44_eta_c0t5->SetBinError(26,1.18136);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(27,1317.51);  hcms_xexe_5p44_eta_c0t5->SetBinError(27,1.16409);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(28,1334.83);  hcms_xexe_5p44_eta_c0t5->SetBinError(28,1.16685);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(29,1342.74);  hcms_xexe_5p44_eta_c0t5->SetBinError(29,1.21209);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(30,1347.97);  hcms_xexe_5p44_eta_c0t5->SetBinError(30,1.29392);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(31,1334.04);  hcms_xexe_5p44_eta_c0t5->SetBinError(31,1.27621);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(32,1306.27);  hcms_xexe_5p44_eta_c0t5->SetBinError(32,1.50188);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(33,1261.74);  hcms_xexe_5p44_eta_c0t5->SetBinError(33,2.17985);
   hcms_xexe_5p44_eta_c0t5->SetBinContent(34,1205.07);  hcms_xexe_5p44_eta_c0t5->SetBinError(34,3.67789);

   return hcms_xexe_5p44_eta_c0t5;
}
