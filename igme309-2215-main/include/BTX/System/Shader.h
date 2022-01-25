/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __SHADERCLASS_H_
#define __SHADERCLASS_H_

#include "BTX\System\SystemSingleton.h"
#include "BTX\system\ShaderCompiler.h"

namespace BTX
{

class BTXDLL Shader
{
	String m_sProgramName = "NULL";
	String m_sVertexShaderName = "NULL";
	String m_sFragmentShaderName = "NULL";
	GLuint m_nProgram = 0;
public:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	Shader(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Shader(const Shader& other);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Shader& operator=(const Shader& other);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Shader(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(Shader& other);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetProgramName(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetVertexShaderName(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFragmentShaderName(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetProgramID(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

protected:
	/*	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	
};

EXPIMP_TEMPLATE template class BTXDLL std::vector<Shader>;
EXPIMP_TEMPLATE template class BTXDLL std::vector<Shader*>;

} //namespace BTX

#endif //__SHADERCLASS_H__

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/