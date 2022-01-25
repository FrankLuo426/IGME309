/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/03
----------------------------------------------*/
#ifndef __OCTANTCLASS_H_
#define __OCTANTCLASS_H_

#include "BTX\BTX.h"

namespace BTX
{

//System Class
class Octant
{
	static uint m_uOctantCount; //will store the number of octants instantiated
	static uint m_uMaxLevel;//will store the maximum level an octant can go to
	static uint m_uIdealEntityCount; //will tell how many Entities this object will contain ideally (may have more or less)

	uint m_uID = 0; //Will store the current ID for this octant
	uint m_uLevel = 0; //Will store the current level of the octant
	uint m_uChildren = 0;// Number of children on the octant (either 0 or 8)

	float m_fSize = 0.0f; //Size of the octant

	ModelManager* m_pModelMngr = nullptr; //So we can draw boxes
	EntityManager* m_pEntityMngr = nullptr; //So we can read the information for each entity

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the octant
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the octant
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the octant
	
	Octant* m_pParent = nullptr;// Will store the address of the parent of current octant
	Octant* m_pChild[8] = {nullptr};//Will store the address of the children of the current octant

	std::vector<uint> m_EntityList; //List of Entities under this octant (their index under Entity Manager)

	Octant* m_pRoot = nullptr;//Root octant
	std::vector<Octant*> m_lChild; //list of nodes that contain objects (this will be applied to root only)
	
public:
	/*
	USAGE: Constructor for root only, will create an octant containing all Entities in the manager
	ARGUMENTS:
	- uint a_nMaxLevel = 2 -> Sets the maximum level of subdivision
	- uint nIdealEntityCount = 5 -> Sets the ideal level of objects per octant
	OUTPUT: class object
	*/
	Octant(uint a_nMaxLevel = 2, uint a_nIdealEntityCount = 5);

	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Octant(void);

	/*
	USAGE: Gets this octant's size
	ARGUMENTS: ---
	OUTPUT: size of octant
	*/
	float GetSize(void);

	/*
	USAGE: Gets the center of the octant in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the octant in global space
	*/
	vector3 GetCenterGlobal(void);

	/*
	USAGE: Gets the min corner of the octant in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMinGlobal(void);

	/*
	USAGE: Gets the max corner of the octant in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMaxGlobal(void);

	/*
	USAGE:	Asks if there is a collision with the Entity in the manager specified
			by its index
	ARGUMENTS:
	- int a_uRBIndex -> Index of the Entity in the Entity Manager
	OUTPUT: check of the collision
	*/
	bool IsColliding(uint a_uRBIndex);

	/*
	USAGE: Displays the Octant volume specified by octant ID
	ARGUMENTS:
	- uint a_nIndex -> Octant to be displayed.
	- vector3 a_v3Color -> Color of the volume to display.
	OUTPUT: ---
	*/
	void Display(uint a_nIndex, vector3 a_v3Color = C_YELLOW);

	/*
	USAGE: Displays this Octant volume in the color specified
	ARGUMENTS:
	- vector3 a_v3Color = Color of the volume to display.
	OUTPUT: ---
	*/
	void Display(vector3 a_v3Color = C_YELLOW);

	/*
	USAGE: Displays the non empty leaves in the octree
	ARGUMENTS:
	- vector3 a_v3Color -> Color of the volume to display.
	OUTPUT: ---
	*/
	void DisplayLeaves(vector3 a_v3Color = C_YELLOW);

	/*
	USAGE: Clears the list of entities under each tree node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearEntityList(void);

	/*
	USAGE: allocates 8 smaller octants in the child list of this node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Subdivide(void);

	/*
	USAGE: returns the child specified in the index
	ARGUMENTS: uint a_nChild -> index of the child (from 0 to 7)
	OUTPUT: Octant object (child in index) will return null if node is empty or index is larger than 7
	*/
	Octant* GetChild(uint a_nChild);

	/*
	USAGE: returns the parent of the octant
	ARGUMENTS: ---
	OUTPUT: Octant object (parent) nullptr if root
	*/
	Octant* GetParent(void);

	/*
	USAGE: Asks the Octant if it does not contain any children (its a leaf)
	ARGUMENTS: ---
	OUTPUT: It contains no children
	*/
	bool IsLeaf(void);

	/*
	USAGE: Asks the Octant if it contains more than this many Rigid Bodies
	ARGUMENTS:
	- uint a_nEntities -> Number of Entities to query
	OUTPUT: It contains at least this many Entities
	*/
	bool ContainsAtLeast(uint a_nEntities);

	/*
	USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void KillBranches(void);

	/*
	USAGE: Creates a tree using subdivisions, the max number of objects and levels
	ARGUMENTS: 
	- uint a_nMaxLevel -> Sets the maximum level of the tree while constructing it
	OUTPUT: ---
	*/
	void ConstructTree(uint a_nMaxLevel = 3);

	/*
	USAGE: Traverse the tree up to the leafs and sets the objects in them to the index
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AssignIDtoEntity(void);

	/*
	USAGE: Gets the total number of octants in the world
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	uint GetOctantCount(void);

private:
	/*
	USAGE: Constructor
	ARGUMENTS:
	- vector3 a_v3Center -> Center of the octant in global space
	- float a_fSize -> size of each side of the octant volume
	OUTPUT: class object
	*/
	Octant(vector3 a_v3Center, float a_fSize);

	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	Octant(Octant const& other);

	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	Octant& operator=(Octant const& other);

	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);

	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- Octant& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Octant& other);

	/*
	USAGE: creates the list of all leafs that contains objects.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ConstructList(void);
};//class

} //namespace BTX

#endif //__OCTANTCLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */