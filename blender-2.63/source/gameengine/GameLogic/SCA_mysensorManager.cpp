/*
 * Manager for 'always' events. Since always sensors can operate in pulse
 * mode, they need to be activated.
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


#include "SCA_mysensorManager.h"
#include "SCA_LogicManager.h"
#include <vector>
#include "SCA_ISensor.h"

using namespace std;

SCA_mySensorEventManager::SCA_mySensorEventManager(class SCA_LogicManager* logicmgr)
	: SCA_EventManager(logicmgr, MYSENSOR_EVENTMGR)
{
	//constructor code here
}



void SCA_mySensorEventManager::NextFrame()
{
	SG_DList::iterator<SCA_ISensor> it(m_sensors);
	for (it.begin();!it.end();++it)
	{
		(*it)->Activate(m_logicmgr);
	}
}
