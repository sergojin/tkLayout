#ifndef CABLINGVISITOR_H
#define CABLINGVISITOR_H

class Tracker;
class DTC;
class Cable;
class Ribbon;
class BarrelModule;
class EndcapModule;
class DetectorModule;
class GeometricModule;
class WedgeModule;

class CablingVisitor { 
public:
  virtual void visit(Tracker&) {}
  virtual void visit(DTC&) {}
  virtual void visit(Cable&) {}
  virtual void visit(Ribbon&) {}
  virtual void visit(DetectorModule&) {}
  virtual void visit(BarrelModule&) {}
  virtual void visit(EndcapModule&) {}
  virtual void visit(GeometricModule&) {}
  virtual void visit(WedgeModule&) {}

};

class ConstCablingVisitor {
public:
  virtual void visit(const Tracker&) {}
  virtual void visit(const DTC&) {}
  virtual void visit(const Cable&) {}
  virtual void visit(const Ribbon&) {}
  virtual void visit(const DetectorModule&) {}
  virtual void visit(const BarrelModule&) {}
  virtual void visit(const EndcapModule&) {}
  virtual void visit(const GeometricModule&) {}
  virtual void visit(const WedgeModule&) {}
};

#endif
