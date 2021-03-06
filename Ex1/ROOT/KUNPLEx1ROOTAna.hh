#pragma once

#include "TFile.h"
#include "TTree.h"

class KUNPLEx1ROOTAna
{
  public:
    static KUNPLEx1ROOTAna* GetInstance();

    KUNPLEx1ROOTAna();
    KUNPLEx1ROOTAna(TString name);

    ~KUNPLEx1ROOTAna();

    void Fill(
      Int_t    parentID,
      Int_t    pdg,
      Double_t pX,
      Double_t pY,
      Double_t pZ);

    void Fill(
      Int_t    parentID,
      Int_t    pdg,
      TString  process,
      Double_t totalEdep,
      Double_t nonIonizingEdep, 
      Int_t    preVolumeIdx,
      Double_t preX,
      Double_t preY,
      Double_t preZ,
      Double_t preTime, 
      Int_t    pstVolumeIdx,
      Double_t pstX,
      Double_t pstY,
      Double_t pstZ,
      Double_t pstTime);

    void SetEventID(Int_t id);
    void SetTrackID(Int_t id);
    void EndOfRun();

  private:
    void Init();

    TString fName;

    TFile* fFile;
    TTree* fTree;
    TTree* fTree2;

    Int_t    fEventID;
    Int_t    fTrackID;
    Int_t    fParentID;
    Int_t    fPdg;
    TString  fProcess;
    Double_t fTotalEdep;
    Double_t fNonIonizingEdep;
    Int_t    fPreVolumeIdx;
    Double_t fPreX;
    Double_t fPreY;
    Double_t fPreZ;
    Double_t fPreTime;
    Int_t    fPstVolumeIdx;
    Double_t fPstX;
    Double_t fPstY;
    Double_t fPstZ;
    Double_t fPstTime;

    Double_t fPX;
    Double_t fPY;
    Double_t fPZ;

    static KUNPLEx1ROOTAna* fInstance;
};
