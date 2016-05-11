#ifndef CABLE_H
#define CABLE_H

#include <vector>
#include <string>
#include <memory>
#include <limits.h>

#include "global_funcs.h"
#include "Property.h"
#include "Ribbon.h"
#include "CablingVisitable.h"


using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;

class Cable : public PropertyObject, public Buildable, public Identifiable<int>, public CablingVisitable {

  typedef PtrVector<Ribbon> Container;
  Container ribbons_;

  Property<int, Default> nRibbonsPerCable;

public:

  Cable() :
            nRibbonsPerCable      ("nRibbonsPerCable"      , parsedAndChecked(), 12)
  {}

  void setup() {
  }


  const Container& ribbons() const { return ribbons_; }
  int nRibbons() const { return ribbons_.size(); }
  
  void check() override;
  void build();


  void accept(CablingVisitor& v) { 
    v.visit(*this); 
    for (auto& r : ribbons_) { r.accept(v); }
  }
  void accept(ConstCablingVisitor& v) const { 
    v.visit(*this); 
    for (const auto& r :ribbons_) { r.accept(v); }
  }

};



#endif
