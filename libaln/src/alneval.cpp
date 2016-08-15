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

// alneval.cpp
// eval support routines

///////////////////////////////////////////////////////////////////////////////
//  File version info:
// 
//  $Archive: /ALN Development/libaln/src/alneval.cpp $
//  $Workfile: alneval.cpp $
//  $Revision: 7 $
//  $Date: 7/17/07 5:21p $
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

static int ALNAPI ValidateALNEvalInfo(const ALN* pALN,
                                      const ALNDATAINFO* pDataInfo,
                                      const ALNCALLBACKINFO* pCallbackInfo,
                                      double* adblResult,
                                      int* pnStart, int* pnEnd);

// evaluation of ALN on data

ALNIMP int ALNAPI ALNEval(const ALN* pALN,
                          const ALNDATAINFO* pDataInfo,
                          const ALNCALLBACKINFO* pCallbackInfo,
                          double* adblResult,
                          int* pnStart, int* pnEnd)
{
	int nReturn = ValidateALNEvalInfo(pALN, pDataInfo, pCallbackInfo,
                                    adblResult, pnStart, pnEnd);
  if (nReturn == ALN_NOERROR)
  {
    nReturn = EvalTree(pALN->pTree, pALN, pDataInfo, pCallbackInfo,
                       adblResult, pnStart, pnEnd, FALSE);
  }
  
	return nReturn;
}


// validate params
static int ALNAPI ValidateALNEvalInfo(const ALN* pALN,
                                      const ALNDATAINFO* pDataInfo,
                                      const ALNCALLBACKINFO* pCallbackInfo,
                                      double* adblResult,
                                      int* pnStart, int* pnEnd)
{
  int nReturn = ValidateALNDataInfo(pALN, pDataInfo, pCallbackInfo);
  if (nReturn != ALN_NOERROR)
    return nReturn;
	
  if (adblResult == NULL)
    return ALN_GENERIC;

  return ALN_NOERROR;
}
