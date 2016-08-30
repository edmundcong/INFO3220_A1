#ifndef PROTOTYPE_H
#define PROTOTYPE_H

/*
 * Abstract class for implementing the Prototype creational design pattern.
 */
class Prototype
{

public:
  /*
   * Clones the current object and returns a pointer to the clone.
   */
  virtual Prototype* clone() = 0;

  /*
   * Returns the prototypical instance for the current class.
   */
  static Prototype* getTypicalInstance();

};

#endif // PROTOTYPE_H
