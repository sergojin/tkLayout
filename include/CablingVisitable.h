/**
 *
 * @author Sergo Jindariani
 */

#ifndef CABLINGVISITABLE_H_
#define CABLINGVISITABLE_H_

#include "CablingVisitor.h"

class CablingVisitable {

public:
  CablingVisitable(){};
  virtual ~CablingVisitable(){};

  virtual void accept(CablingVisitor& v) = 0;
  virtual void accept(ConstCablingVisitor& v) const = 0;

};

#endif /* CABLINGVISITABLE_H_ */
