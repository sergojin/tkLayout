#ifndef RIBBON_H
#define RIBBON_H

#include <vector>
#include <string>
#include <memory>
#include <limits.h>

#include "global_funcs.h"
#include "Property.h"
#include "Module.h"

#include "CablingVisitable.h"
#include "CablingVisitor.h"

using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;

class Ribbon : public PropertyObject, public Buildable, public Identifiable<int>, public CablingVisitable {

  typedef PtrVector<Module> Container;
  Container detectormodules_;

  Property<int, Default> nModulesPerRibbon;

public:

  Ribbon() :
            nModulesPerRibbon      ("nModulesPerRibbon"      , parsedAndChecked(), 6)
  {}

  void setup() {
  }

  Container& modules() { return detectormodules_; }
  const Container& modules() const { return detectormodules_; }
  int nModules() const { return detectormodules_.size(); }
  
  void check() override;
  void build();

  void addModule(Module& m) {}

  void accept(CablingVisitor& v) { 
    v.visit(*this); 
    for (Module& m : detectormodules_) { m.accept(v); }
  }

  void accept(ConstCablingVisitor& v) const { 
    v.visit(*this); 
    for (const auto& m : detectormodules_) { m.accept(v); }
  }

};



#endif
