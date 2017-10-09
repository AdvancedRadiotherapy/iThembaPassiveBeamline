// ====================================================================
//   PhantomAnalysisMessenger.hh
//
// ====================================================================
#ifndef PHANTOM_ANALYSIS_MESSENGER_H
#define PHANTOM_ANALYSIS_MESSENGER_H

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class PhantomAnalysis;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;


class PhantomAnalysisMessenger : public G4UImessenger
{
private:
  G4UIdirectory* dir;
  G4UIcmdWithAString*  KillEventCmd;
  PhantomAnalysis* myPhantom;


public:
  PhantomAnalysisMessenger(PhantomAnalysis*);
  ~PhantomAnalysisMessenger(); 

  void SetNewValue(G4UIcommand* command, G4String newValues);
  //G4String GetCurrentValue(G4UIcommand* command);

  
};

#endif
