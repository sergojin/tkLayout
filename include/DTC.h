#ifndef DTC_H
#define DTC_H

#include <vector>
#include <string>
#include <memory>
#include <limits.h>

#include "global_funcs.h"
#include "Cable.h"
#include "Module.h"


using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;

class DTC : public PropertyObject, public Buildable, public Identifiable<int>, public CablingVisitable {

  typedef PtrVector<Cable> Container;
  Container cables_;

  Property<int, Default> nCablesPerDTC;

public:

  DTC() :
            nCablesPerDTC      ("nCablesPerDTC"      , parsedAndChecked(), 1)
  {}

  void setup() {
  }

  Container& cables() { return cables_; }
  const Container& cables() const { return cables_; }
  int nCables() const { return cables_.size(); }
  int maxCables() {return nCablesPerDTC(); }
  
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
