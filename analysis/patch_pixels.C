#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

int patch_pixels(const char* pixel, const char* output) {
    TFile* f = new TFile(pixel, "read");
    TTree* tp = (TTree*)f->Get("pixel/PixelTree");
    TTree* th = 0;

    f->GetListOfKeys()->Print();
    bool sim = f->GetListOfKeys()->Contains("hltbitanalysis");

    int hlt = 1;

    if (sim) {
        th = (TTree*)f->Get("hltbitanalysis/HltTree");

        th->SetBranchStatus("*", 0);
        th->SetBranchStatus("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", 1);
        th->SetBranchAddress("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", &hlt);
    }

    TFile* fout = new TFile(output, "recreate");
    fout->mkdir("pixel");
    fout->cd("pixel");

    TTree* tout = tp->CloneTree();

    TBranch* b = tout->Branch("hlt", &hlt, "hlt/I");

    int64_t nentries = tout->GetEntries();
    for (int64_t i=0; i<nentries; ++i) {
        tout->GetEntry(i);
        if (sim) { th->GetEntry(i); }

        b->Fill();
    }

    f->Close();

    tout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        return patch_pixels(argv[1], argv[2]);
    } else {
        printf("usage: ./patch_pixels [pixel] [output]\n");
        return 1;
    }
}
