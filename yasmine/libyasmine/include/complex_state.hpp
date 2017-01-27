//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef COMPLEX_STATE_91053A02_65AF_40C3_B9F9_C283A743A85F
#define COMPLEX_STATE_91053A02_65AF_40C3_B9F9_C283A743A85F


#include "state.hpp"


namespace sxy
{


class complex_state_visitor;


class complex_state:
	public virtual state
{
public:
	complex_state()
	{
		// Nothing to do...
	}


	virtual ~complex_state() Y_NOEXCEPT Y_OVERRIDE
	{
		// Nothing to do...
	}


	Y_NO_COPY(complex_state)
	virtual void accept_complex_state_visitor( complex_state_visitor& _visitor ) const = 0;
};


}


#endif