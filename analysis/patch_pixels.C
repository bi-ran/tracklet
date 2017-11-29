#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "include/matchmaker.h"
#include "include/hf.h"

int patch_hlt(const char* fpixel, const char* fhlt) {
    TFile* fh = new TFile(fhlt, "read");
    TTree* th = (TTree*)fh->Get("hltbitanalysis/HltTree");

    int run, lumi; ULong64_t event;
    th->SetBranchStatus("*", 0);
    th->SetBranchStatus("Run", 1);
    th->SetBranchAddress("Run", &run);
    th->SetBranchStatus("LumiBlock", 1);
    th->SetBranchAddress("LumiBlock", &lumi);
    th->SetBranchStatus("Event", 1);
    th->SetBranchAddress("Event", &event);

    matchmaker* mm = new matchmaker();

    int64_t nentries;
    nentries = th->GetEntries();
    for (int64_t i=0; i<nentries; ++i) {
        th->GetEntry(i);
        mm->set(run, lumi, event, i);
    }

    TFile* fp = new TFile(fpixel, "update");
    TTree* tp = (TTree*)fp->Get("pixel/PixelTree");

    int prun, plumi, pevent;
    tp->SetBranchAddress("run", &prun);
    tp->SetBranchAddress("lumi", &plumi);
    tp->SetBranchAddress("event", &pevent);

    int hlt;
    th->SetBranchStatus("*", 0);
    th->SetBranchStatus("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", 1);
    th->SetBranchAddress("HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_v1", &hlt);

    TBranch* b = tp->Branch("hlt", &hlt, "hlt/I");

    nentries = tp->GetEntries();
    for (int64_t i=0; i<nentries; ++i) {
        tp->GetEntry(i);

        int64_t j = mm->get(prun, plumi, pevent);
        if (j == -1) {
            printf("run: %i, lumi: %i, event: %i not found!\n", prun, plumi, pevent);
            return 1;
        }

        th->GetEntry(j);
        b->Fill();
    }

    fp->cd("pixel");
    tp->Write("", TObject::kOverwrite);
    fp->Close();
    fh->Close();

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
        patch_dummy_hlt(argv[1]);
        return 0;
    } else if (argc == 3) {
        patch_hlt(argv[1], argv[2]);
    } else {
        printf("usage: ./patch_pixels [pixel] {hlt}\n");
        return 1;
    }
}
