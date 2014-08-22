//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Jun 14 15:33:00 2011 by ROOT version 5.31/01)
//      from the StreamerInfo in file http://root.cern.ch/files/atlasFlushed.root
//////////////////////////////////////////////////////////


#ifndef EnergySum_ROI_p1_h
#define EnergySum_ROI_p1_h
class EnergySum_ROI_p1;

#include "Riostream.h"
#include <vector>

class EnergySum_ROI_p1 {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int m_roiWord0;    //
   unsigned int m_roiWord1;    //
   unsigned int m_roiWord2;    //
   float        m_energyX;     //
   float        m_energyY;     //
   float        m_energyT;     //
   vector<string> m_thresholds;    //

   EnergySum_ROI_p1();
   EnergySum_ROI_p1(const EnergySum_ROI_p1 & );
   virtual ~EnergySum_ROI_p1();

};
#endif