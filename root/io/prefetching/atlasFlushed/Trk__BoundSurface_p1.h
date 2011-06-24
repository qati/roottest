//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Jun 14 15:33:00 2011 by ROOT version 5.31/01)
//      from the StreamerInfo in file http://root.cern.ch/files/atlasFlushed.root
//////////////////////////////////////////////////////////


#ifndef Trk__BoundSurface_p1_h
#define Trk__BoundSurface_p1_h
namespace Trk {
class BoundSurface_p1;
} // end of namespace.

#include "Trk__Surface_p1.h"
#include "TPObjRef.h"

namespace Trk {
class BoundSurface_p1 : public Trk::Surface_p1 {

public:
// Nested classes declaration.

public:
// Data Members.
   TPObjRef    m_bounds;    //

   BoundSurface_p1();
   BoundSurface_p1(const BoundSurface_p1 & );
   virtual ~BoundSurface_p1();

};
} // namespace
#endif