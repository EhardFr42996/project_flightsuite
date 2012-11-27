/*
 * Always trigger
 *
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file gameengine/GameLogic/SCA_AlwaysSensor.cpp
 *  \ingroup gamelogic
 */


#if defined(WIN32) && !defined(FREE_WINDOWS)
// This warning tells us about truncation of __long__ stl-generated names.
// It can occasionally cause DevStudio to have internal compiler warnings.
#pragma warning( disable : 4786 )     
#endif

#include <unistd.h>

#include "SCA_mysensor.h"
#include "SCA_LogicManager.h"
#include "SCA_EventManager.h"

/* ------------------------------------------------------------------------- */
/* Native functions                                                          */
/* ------------------------------------------------------------------------- */

SCA_mySensor::SCA_mySensor(class SCA_EventManager* eventmgr,
								 SCA_IObject* gameobj)
	: SCA_ISensor(gameobj,eventmgr)
{
	//SetDrawColor(255,0,0);
	Init();
}

void SCA_mySensor::Init()
{
	m_myresult = true;
	fork();
	sleep (200);	


}

SCA_mySensor::~SCA_mySensor()
{
	/* intentionally empty */
}



CValue* SCA_mySensor::GetReplica()
{
	CValue* replica = new SCA_mySensor(*this);//m_float,GetName());
	// this will copy properties and so on...
	replica->ProcessReplica();

	return replica;
}



bool SCA_mySensor::IsPositiveTrigger()
{ 
	return (m_invert ? false : true);
}



bool SCA_mySensor::Evaluate()
{
	/* Nice! :) */
		//return true;
	/* even nicer ;) */
		//return false;
	
	/* nicest ! */
	bool result = m_myresult;
	m_myresult = false;
	return result;
}

#ifdef WITH_PYTHON

/* ------------------------------------------------------------------------- */
/* Python functions                                                          */
/* ------------------------------------------------------------------------- */

/* Integration hooks ------------------------------------------------------- */
PyTypeObject SCA_mySensor::Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"SCA_mySensor",
	sizeof(PyObjectPlus_Proxy),
	0,
	py_base_dealloc,
	0,
	0,
	0,
	0,
	py_base_repr,
	0,0,0,0,0,0,0,0,0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	0,0,0,0,0,0,0,
	Methods,
	0,
	0,
	&SCA_ISensor::Type,
	0,0,0,0,0,0,
	py_base_new
};

PyMethodDef SCA_mySensor::Methods[] = {
	{NULL,NULL} //Sentinel
};

PyAttributeDef SCA_mySensor::Attributes[] = {
	{ NULL }	//Sentinel
};

#endif

/* eof */