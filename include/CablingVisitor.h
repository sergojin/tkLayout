#ifndef CABLINGVISITOR_H
#define CABLINGVISITOR_H

class DTC;
class Cable;
class Ribbon;
class BarrelModule;
class EndcapModule;
class DetectorModule;

class CablingVisitor { 
public:
  virtual void visit(DTC&) {}
  virtual void visit(Cable&) {}
  virtual void visit(Ribbon&) {}
  virtual void visit(DetectorModule&) {}
};

class ConstCablingVisitor {
public:
  virtual void visit(const DTC&) {}
  virtual void visit(const Cable&) {}
  virtual void visit(const Ribbon&) {}
  virtual void visit(const DetectorModule&) {}
};

#endif
