    // **************************************************************************************
    //
    // HADRONTHERAPY:  a Geant4-based application for proton/ion-therapy studies
    // _________________________________________________________________________
    //
    // This is the FULL version of the Hadrontherapy application.
    // It is based on the Geant4 toolkit classes and released under the GPL3 license.
    //
    // Its basic version is released and maintained inside the Geant4 code
    // as Advanced Example.
    //
	// To compile and run Hadrontherapy you only require the installation of Geant4 and,
	// if you wish, the ROOT ananlysis program.
    //
    // For more information see the documentation at http://sites.google.com/site/hadrontherapy/
    // or contact cirrone@lns.infn.it
    //
    // **************************************************************************************

#include "DetectorHit.hh"

G4Allocator<DetectorHit> DetectorHitAllocator;

//*************************************************************************************************
DetectorHit::DetectorHit()
//-------------------------------------------------------------------------------------------------
{
 energyDeposit = 0;
}
//*************************************************************************************************
DetectorHit::~DetectorHit()
//-------------------------------------------------------------------------------------------------
{
}
//*************************************************************************************************
DetectorHit::DetectorHit(const DetectorHit &right): G4VHit()
//-------------------------------------------------------------------------------------------------
{
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
}
//*************************************************************************************************
const DetectorHit& DetectorHit::operator=(const DetectorHit &right)
//-------------------------------------------------------------------------------------------------
{
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
 return *this;
}
//*************************************************************************************************
int DetectorHit::operator==(const DetectorHit &right) const
//-------------------------------------------------------------------------------------------------
{
 return((xHitID==right.xHitID)&&(zHitID==right.zHitID)&&(yHitID==right.yHitID));
}
//*************************************************************************************************


