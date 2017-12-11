#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

int patch_hlt(const char* pixel, const char* output) {
    TFile* f = new TFile(pixel, "read");
    TTree* tp = (TTree*)f->Get("pixel/PixelTree");
    TTree* th = (TTree*)f->Get("hltbitanalysis/HltTree");

    int hlt;
    th->SetBranchStatus("*", 0);
    th->SetBranchStatus("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", 1);
    th->SetBranchAddress("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", &hlt);

    TFile* fout = new TFile(output, "recreate");
    fout->mkdir("pixel");
    fout->cd("pixel");

    TTree* tout = tp->CloneTree();

    TBranch* b = tout->Branch("hlt", &hlt, "hlt/I");

    int64_t nentries = tp->GetEntries();
    for (int64_t i=0; i<nentries; ++i) {
        tp->GetEntry(i);
        th->GetEntry(i);

        b->Fill();
    }

    f->Close();

    tout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int patch_dummy_hlt(const char* pixel) {
    TFile* f = new TFile(pixel, "update");
    TTree* t = (TTree*)f->Get("pixel/PixelTree");

    int hlt = 1;
    TBranch* b = t->Branch("hlt", &hlt, "hlt/I");

    uint64_t nentries = t->GetEntries();
    for (uint64_t i=0; i<nentries; ++i) {
        t->GetEntry(i);

        b->Fill();
    }

    f->cd("pixel");
    t->Write("", TObject::kOverwrite);
    f->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        return patch_dummy_hlt(argv[1]);
    } else if (argc == 3) {
        return patch_hlt(argv[1], argv[2]);
    } else {
        printf("usage: ./patch_pixels [pixel] [output]\n");
        return 1;
    }
}
