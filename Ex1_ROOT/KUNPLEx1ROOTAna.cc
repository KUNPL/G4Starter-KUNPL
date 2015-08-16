#include "KUNPLEx1ROOTAna.hh"

KUNPLEx1ROOTAna* KUNPLEx1ROOTAna::fInstance = 0;
KUNPLEx1ROOTAna* KUNPLEx1ROOTAna::GetInstance() { return fInstance; }

KUNPLEx1ROOTAna::KUNPLEx1ROOTAna()
{
  fName = "KUNPLEx1Data";
  fInstance = this;

  Init();
}

KUNPLEx1ROOTAna::KUNPLEx1ROOTAna(TString name)
{
  fName = name;
  fInstance = this;

  Init();
}

KUNPLEx1ROOTAna::~KUNPLEx1ROOTAna()
{
}

void KUNPLEx1ROOTAna::Init()
{
  TString fileName = fName + ".root";

  fFile = new TFile(fileName,"recreate");
  fTree = new TTree("data",fName);

  fTree -> Branch("eventID",         &fEventID);
  fTree -> Branch("trackID",         &fTrackID);
  fTree -> Branch("parentID",        &fParentID);
  fTree -> Branch("pdg",             &fPdg);
  fTree -> Branch("totalEdep",       &fTotalEdep);
  fTree -> Branch("nonIonizingEdep", &fNonIonizingEdep);

  fTree -> Branch("preVolumeIdx",    &fPreVolumeIdx);
  fTree -> Branch("preX",            &fPreX);
  fTree -> Branch("preY",            &fPreY);
  fTree -> Branch("preZ",            &fPreZ);
  fTree -> Branch("preTime",         &fPreTime);

  fTree -> Branch("pstVolumeIdx",    &fPstVolumeIdx);
  fTree -> Branch("pstX",            &fPstX);
  fTree -> Branch("pstY",            &fPstY);
  fTree -> Branch("pstZ",            &fPstZ);
  fTree -> Branch("pstTime",         &fPstTime);
}

void KUNPLEx1ROOTAna::Fill(
  Int_t    parentID,
  Int_t    pdg,
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
  Double_t pstTime)
{
  fParentID        = parentID;
  fPdg             = pdg;
  fTotalEdep       = totalEdep;
  fNonIonizingEdep = nonIonizingEdep; 

  fPreVolumeIdx    = preVolumeIdx;
  fPreX            = preX;
  fPreY            = preY;
  fPreZ            = preZ;
  fPreTime         = preTime; 
 
  fPstVolumeIdx    = pstVolumeIdx;
  fPstX            = pstX;
  fPstY            = pstY;
  fPstZ            = pstZ;
  fPstTime         = pstTime;

  fTree -> Fill();
}

void KUNPLEx1ROOTAna::SetEventID(Int_t id) { fEventID = id; }
void KUNPLEx1ROOTAna::SetTrackID(Int_t id) { fTrackID = id; }
void KUNPLEx1ROOTAna::EndOfRun() { fTree -> Write(); }
