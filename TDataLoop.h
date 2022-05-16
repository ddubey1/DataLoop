#ifndef __TDATALOOP_H__
#define __TDATALOOP_H__

#include <iostream>

template<typename DataType>
class TDataLoop {
public:

  /**
   * \brief The default constructor
   *
   * \detail The default constructor creates an empty TDataLoop, i.e. start is nullptr and count is 0.
   */
  TDataLoop();
  
  /**
   * \brief An alternate constructor
   *
   * \detail This alternate constructor creates a TDataLoop with one node that contains the parameter value. The node is dynamically allocated and should be the start of the loop. Its next and prev fields should point to itself.
   *
   * \param[in] num The integer value to be added to the TDataLoop
   */
  TDataLoop(const DataType & val);
 
  /**
   * \brief The copy constructor
   *
   * \detail The copy constructor creates a copy of the parameter TDataLoop (rhs)
   *
   * \param[in] rhs A constant reference to the function input TDataLoop object
   */  
  TDataLoop(const TDataLoop & rhs);

  /**
   * \brief Overloaded operator= to assign a TDataLoop to another TDataLoop
   *
   * \detail This overloaded operator assigns the input TDataLoop (rhs) to the current TDataLoop (*this, the current object).
   *
   * \note If the current TDataLoop is not empty, this function releases formerly allocated memory as needed to avoid memory leaks. 
   *
   * \param[in] rhs A constant reference to the input TDataLoop object
   *
   * \return A reference to the updated TDataLoop object
   */
  TDataLoop & operator=(const TDataLoop & rhs); 


  /**
   * \brief The destructor
   *
   * \detail The destructor releases allocated memory as needed to avoid leaks.
   */
  ~TDataLoop();


  /**
   * \brief Overloaded operator== to check if two DataLoops are the same
   *
   * \detail This operator compares the current TDataLoop (*this) with the input TDataLoop (rhs). It returns true if both DataLoops are the same node by node, including the starting position and count. Otherwise, it returns false.
   *
   * \param[in] rhs A constant reference to a TDataLoop object to compare
   *
   * \return true if two DataLoops are the same node by node, else false
   */
  bool operator==(const TDataLoop & rhs) const;
  
  /**
   * \brief Overloaded operator+= to add a value to the end of this TDataloop
   *
   * \detail This operator takes an integer, creates a new _Node to hold it, and inserts that at the end of this TDataloop. In other words, the new node will be immediately before the start node, but the start is not changed. 
   *
   * \param[in] num A constant reference to an integer value
   *
   * \return A reference to this updated TDataLoop object with the new value added
   */  
  TDataLoop & operator+=(const DataType & val);


  /**
   * \brief Overloaded operator+ to concatenate copies of two DataLoops
   *
   * \detail This operator creates a third TDataLoop by concatenating copies of the current TDataLoop (*this) and the parameter TDataLoop (rhs), adding the rhs copy to the end of the current TDataLoop copy. The start position for the new TDataLoop should mimic the start of *this and the count should be updated as well. [Note that the original DataLoops are not affected.]
   *
   * \param[in] rhs A constant reference to a TDataLoop object to add to the end of *this
   *
   * \return A new TDataLoop object with the concatenated result
   */
  TDataLoop operator+(const TDataLoop & rhs);
  

  /**
   * \brief Overloaded operator^ to shift the start position in *this TDataLoop according to the parameter offset - forward for a positive value and backward for a negative value
   *
   * \detail This overloaded operator takes an integer and shifts the starting position forward (positive num) or backward (negative num) that many nodes, looping around as much as necessary. [A 0 offset does not make any changes, and no changes are made to an empty TDataLoop or one with only one _Node.]
   *
   * \param[in] offset The number of nodes/positions to move the start position, positive for forward shifting, negative for backward motion
   *
   * \return A reference to the updated TDataLoop object
   */  
  TDataLoop & operator^(int offset);


  /**
   * \brief Function splice to insert an entire TDataLoop into this one
   *
   * \detail This function inserts the entire parameter TDataLoop (rhs) into the current TDataLoop (*this) at the indicated position (pos), where 0 would indicate the starting position of the current TDataLoop and update `start` accordingly. An insert position of n would indicate that the start node of rhs comes after node n in the current TDataLoop (assuming you start counting nodes with 1). The values from the input TDataLoop (rhs) should be inserted in their current order, beginning with that object's starting node. The count for the current TDataLoop should be updated. If the indicated position is larger than the current count, effectively loop around as much as necessary to get to the indicated spot. This function must also reset the parameter TDataloop, making rhs an empty list, since both can't co-exist.
   *
   * \param[in] rhs A reference to a TDataLoop object to insert into *this
   *
   * \param[in] pos The insertion position 
   *
   * \return A reference to the updated TDataLoop object 
   */
  TDataLoop & splice(TDataLoop & rhs, size_t pos);


  /**
   * \brief Function length to report the number of nodes in *this TDataLoop
   *
   * \return The number of nodes
   */  
  int length() const { return count; }


  // Deletes the allocated memory in the current TDataLoop
  void clear();

  // Adds a node of value value at the end of the TDataLoop, just before start
  void add(DataType value);

  /**
   * \brief Overloaded output stream operator<< to print the TDataLoop
   *
   * \detail This operator prints the input TDataLoop (dl) to the ostream (os) in the format 
   * "-> data1 <--> data2 <--> ... <--> datax <-" where data1 is the value in the start node
   *   e.g. if we have a TDataLoop with three elements 32, 12, 20 starting at 12
   *        it will print "-> 12 <--> 20 <--> 32 <-"
   *   If the TDataLoop is empty, it prints ">no values<".
   *
   * \param[in] os A reference to the output stream object
   * \param[in] q A constant reference to the TDataLoop object to be printed
   *
   * \return A reference to the output stream object
   */
  template<typename U>
  friend std::ostream & operator<<(std::ostream & os, const TDataLoop<U> & dl);
  
private:
  friend struct TDataLoopTest;

  //template<typename DataType>
  struct _Node {
    DataType data;     ///< Integer node data
    _Node * next;  ///< A pointer to the next node
    _Node * prev;  ///< A pointer to the previous node
  };

  _Node * start;   ///< a pointer to the starting node position in the TDataLoop
  size_t count;   ///< the count of how many nodes/values are in the structure
};

#include "TDataLoop.inc"

#endif // __TDATALOOP_H__

