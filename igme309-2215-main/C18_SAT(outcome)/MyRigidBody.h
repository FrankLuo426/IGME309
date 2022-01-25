/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2021/06
----------------------------------------------*/
#ifndef __MYRIGIDBODY_H_
#define __MYRIGIDBODY_H_

#include "BTX\BTX.h"

namespace BTX
{

//System Class
class MyRigidBody : public RigidBody
{
	/*
	* This is only so we can use all the methods of RigidBody as the MyRigidBody class,
	* this means that we can debug as normal while having the same name.
	*/
public:
	/*
	Usage: Constructor
	Arguments: std::vector<vector3> a_pointList -> list of points to make the Rigid Body for
	Output: class object instance
	*/
	MyRigidBody(std::vector<vector3> a_pointList);
	/*
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyRigidBody(MyRigidBody const& other);
	/*
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyRigidBody& operator=(MyRigidBody const& other);
	/*
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyRigidBody(void);

private:
	/*
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

} //namespace BTX

#endif //__MYRIGIDBODY_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/