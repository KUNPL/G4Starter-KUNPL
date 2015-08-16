#include "KUNPLEx1ROOTEventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

KUNPLEx1ROOTEventAction::KUNPLEx1ROOTEventAction()
: G4UserEventAction()
{
  ana = KUNPLEx1ROOTAna::GetInstance();
}

KUNPLEx1ROOTEventAction::~KUNPLEx1ROOTEventAction()
{
}

void KUNPLEx1ROOTEventAction::BeginOfEventAction(const G4Event* event)
{
  ana -> SetEventID(event -> GetEventID());
}

void KUNPLEx1ROOTEventAction::EndOfEventAction(const G4Event* event)
{
}
