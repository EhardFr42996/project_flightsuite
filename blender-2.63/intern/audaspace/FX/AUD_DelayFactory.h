/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * Copyright 2009-2011 Jörg Hermann Müller
 *
 * This file is part of AudaSpace.
 *
 * Audaspace is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * AudaSpace is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Audaspace; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file audaspace/FX/AUD_DelayFactory.h
 *  \ingroup audfx
 */


#ifndef __AUD_DELAYFACTORY_H__
#define __AUD_DELAYFACTORY_H__

#include "AUD_EffectFactory.h"

/**
 * This factory plays another factory delayed.
 */
class AUD_DelayFactory : public AUD_EffectFactory
{
private:
	/**
	 * The delay in samples.
	 */
	const float m_delay;

	// hide copy constructor and operator=
	AUD_DelayFactory(const AUD_DelayFactory&);
	AUD_DelayFactory& operator=(const AUD_DelayFactory&);

public:
	/**
	 * Creates a new delay factory.
	 * \param factory The input factory.
	 * \param delay The desired delay in seconds.
	 */
	AUD_DelayFactory(AUD_Reference<AUD_IFactory> factory, float delay = 0);

	/**
	 * Returns the delay in seconds.
	 */
	float getDelay() const;

	virtual AUD_Reference<AUD_IReader> createReader();
};

#endif //__AUD_DELAYFACTORY_H__
