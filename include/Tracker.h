#ifndef TRACKER_H
#define TRACKER_H

#include <vector>
#include <string>
#include <memory>
#include <set>
#include <limits.h>

#include <boost/ptr_container/ptr_vector.hpp>

#include <TCanvas.h>

#include "global_funcs.h"
#include "Property.h"
#include "Barrel.h"
#include "Endcap.h"
#include "SupportStructure.h"
#include "Visitor.h"
#include "Visitable.h"

#include "TrackFinder.h"
#include "DTC.h"
#include "Cable.h"
#include "Ribbon.h"
#include "CablingVisitor.h"
#include "CablingVisitable.h"

using std::set;
using material::SupportStructure;

class Tracker : public PropertyObject, public Buildable, public Identifiable<string>, Clonable<Tracker>, Visitable {
  class ModuleSetVisitor : public GeometryVisitor {
  public:
    typedef set<Module*> Modules;
  private:
    Modules modules_;

  public:
    void visit(Module& m) override { modules_.insert(&m); }
    Modules& modules() { return modules_; }
    const Modules& modules() const { return modules_; }
    Modules::iterator begin() { return modules_.begin(); }
    Modules::iterator end() { return modules_.end(); }
    Modules::const_iterator begin() const { return modules_.begin(); }
    Modules::const_iterator end() const { return modules_.end(); }
  };

public:
  typedef PtrVector<Barrel> Barrels;
  typedef PtrVector<Endcap> Endcaps;
  typedef PtrVector<SupportStructure> SupportStructures;
  typedef ModuleSetVisitor::Modules Modules;
  typedef PtrVector<DTC> DTCs;
  typedef PtrVector<TrackFinder> TFs;

  ReadonlyProperty<double, Computable> maxR, minR;
  ReadonlyProperty<double, Computable> maxZ;
  ReadonlyProperty<double, Default> etaCut;
  ReadonlyProperty<bool, Default> servicesForcedUp;
  ReadonlyProperty<bool, Default> skipAllServices;
  ReadonlyProperty<bool, Default> skipAllSupports;

private:
  Barrels barrels_;
  Endcaps endcaps_;
  SupportStructures supportStructures_;
  DTCs dtcs_;
  TFs tfs_;

  ModuleSetVisitor moduleSetVisitor_;


  PropertyNode<string> barrelNode;
  PropertyNode<string> endcapNode;
  PropertyNodeUnique<string> supportNode;

  MultiProperty<set<string>, ','> containsOnly;

  Tracker(const Tracker&) = default;
public:

  Tracker() :
      barrelNode("Barrel", parsedOnly()),
      endcapNode("Endcap", parsedOnly()),
      supportNode("Support", parsedOnly()),
      etaCut("etaCut", parsedOnly(), 7.),
      servicesForcedUp("servicesForcedUp", parsedOnly(), true),
      skipAllServices("skipAllServices", parsedOnly(), false),
      skipAllSupports("skipAllSupports", parsedOnly(), false),
      containsOnly("containsOnly", parsedOnly())
  {}

  void setup() {
      maxR.setup([this]() { 
        double max = 0; 
        for (const auto& b : barrels_) max = MAX(max, b.maxR());
        for (const auto& e : endcaps_) max = MAX(max, e.maxR());
        return max;
      });
      minR.setup([this]() {
        double min = std::numeric_limits<double>::max(); 
        for (const auto& b : barrels_) min = MIN(min, b.minR());
        for (const auto& e : endcaps_) min = MIN(min, e.minR());
        return min;
      });
      maxZ.setup([this]() {
        double max = 0;
        for (const auto& b : barrels_) max = MAX(max, b.maxZ());
        for (const auto& e : endcaps_) max = MAX(max, e.maxZ());
        return max;
     });
  }

  void build();

  const Barrels& barrels() const { return barrels_; }
  const Endcaps& endcaps() const { return endcaps_; }

  const Modules& modules() const { return moduleSetVisitor_.modules(); }
  Modules& modules() { return moduleSetVisitor_.modules(); }

  DTCs& dtcs() { return dtcs_; }
  const DTCs& dtcs() const { return dtcs_; }

  TFs& tfs() { return tfs_; }
  const TFs& tfs() const { return tfs_; }
  
  void accept(GeometryVisitor& v) { 
    v.visit(*this); 
    for (auto& b : barrels_) { b.accept(v); }
    for (auto& e : endcaps_) { e.accept(v); }
  }

  void accept(ConstGeometryVisitor& v) const {
    v.visit(*this); 
    for (const auto& b : barrels_) { b.accept(v); }
    for (const auto& e : endcaps_) { e.accept(v); }
  }

  
  void accept(CablingVisitor& v) {
    v.visit(*this);
    for (auto& d : dtcs_) { d.accept(v); }
  }
  void accept(ConstCablingVisitor& v) const {
    v.visit(*this);
    for (const auto& d : dtcs_) { d.accept(v); }
  }
  


  std::pair<double, double> computeMinMaxEta() const; // pair.first = minEta, pair.second = maxEta (reversed with respect to the previous tkLayout geometry model)

  void createGeometry(bool) {}
  TCanvas* getGeomLite()   { return NULL; }
  TCanvas* getGeomLiteXY() { return NULL; }
  TCanvas* getGeomLiteYZ() { return NULL; }
  TCanvas* getGeomLiteEC() { return NULL; }
  
  SupportStructures& supportStructures() {return supportStructures_;}
};


#endif
