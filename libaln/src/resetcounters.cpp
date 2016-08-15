// ALN Library
// Copyright (C) 1995 - 2010 William W. Armstrong.
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// 
// For further information contact 
// William W. Armstrong

// 3624 - 108 Street NW
// Edmonton, Alberta, Canada  T6J 1B4
// resetcounters.cpp

///////////////////////////////////////////////////////////////////////////////
//  File version info:
// 
//  $Archive: /ALN Development/libaln/src/resetcounters.cpp $
//  $Workfile: resetcounters.cpp $
//  $Revision: 8 $
//  $Date: 8/18/07 4:27p $
//  $Author: Arms $
//
///////////////////////////////////////////////////////////////////////////////

#ifdef ALNDLL
#define ALNIMP __declspec(dllexport)
#endif

#include <aln.h>
#include "alnpriv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// used to reset resp counters, eval flags, and other stats during training

void ALNAPI ResetCounters(ALNNODE* pNode, ALN* pALN, 
                          BOOL bMarkAsUseful /*= FALSE*/)
{
  ASSERT(pALN != NULL);
  ASSERT(pNode != NULL);

  // reset resp count, but save old value
  int nRespCount = NODE_RESPCOUNT(pNode);
  NODE_RESPCOUNT(pNode) = 0;
     
	// set last epoch resp count
	if (bMarkAsUseful)
  {
		NODE_RESPCOUNTLASTEPOCH(pNode) = pALN->nDim; 
    ASSERT(!NODE_ISUSELESS(pNode, pALN->nDim));
  }
	else
  {
		NODE_RESPCOUNTLASTEPOCH(pNode) = nRespCount;
  }

  if (NODE_ISMINMAX(pNode))
  {
  	// iterate over children
    ResetCounters(MINMAX_LEFT(pNode), pALN, bMarkAsUseful);
    ResetCounters(MINMAX_RIGHT(pNode), pALN, bMarkAsUseful);
  }
  else
  {
    ASSERT(NODE_ISLFN(pNode));
    if (LFN_CANSPLIT(pNode))
    {
      ASSERT(LFN_SPLIT(pNode));
      LFN_SPLIT_COUNT(pNode) = 0;
      LFN_SPLIT_SQERR(pNode) = 0.0;
      LFN_SPLIT_RESPTOTAL(pNode) = 0.0;
      LFN_SPLIT_T(pNode) = 0.0;
		}
  }
}
