/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_WELD_UTIL_H
#define HKCD_PLANAR_GEOMETRY_WELD_UTIL_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>

/// Utility that welds together an array of planes
class hkcdPlanarGeometryWeldUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION, hkcdPlanarGeometryWeldUtil);
		typedef	hkcdPlanarGeometryPrimitives::Plane				Plane;

	public:

		/// Welds the given set of planes
		static void HK_CALL weldPlanes(const hkArray<Plane>& planesIn, hkArray<Plane>& weldedPlanesOut, hkArray<int>& remapTableOut);
};

#endif	//	HKCD_PLANAR_GEOMETRY_WELD_UTIL_H

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20130718)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
