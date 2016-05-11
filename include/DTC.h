#ifndef DTC_H
#define DTC_H

#include <vector>
#include <string>
#include <memory>
#include <limits.h>

#include "global_funcs.h"
#include "Cable.h"
#include "Module.h"

#include "CablingVisitor.h"
#include "CablingVisitable.h"


using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;

class DTC : public PropertyObject, public Buildable, public Identifiable<int>, public Visitable {

  typedef PtrVector<Cable> Container;
  Container cables_;

  Property<int, Default> nCablesPerDTC;

public:

  Cable() :
            nCablesPerDTC      ("nCablesPerDTC"      , parsedAndChecked(), 1)
  {}

  void setup() {
  }


  const Container& cables() const { return cables_; }
  int nCables() const { return cables_.size(); }
  
  void check() override;
  void build();


  void accept(CablingVisitor& v) { 
    v.visit(*this); 
    for (auto& c : cables_) { c.accept(v); }
  }
  void accept(ConstCablingVisitor& v) const { 
    v.visit(*this); 
    for (const auto& c :cables_) { c.accept(v); }
  }

};



#endif
