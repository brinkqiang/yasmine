//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016-2017 Seadex GmbH                                                              //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "simple_state_impl.hpp"

#include "log.hpp"
#include "behavior.hpp"


namespace sxy
{		 


simple_state_impl::simple_state_impl( const std::string& _name, behavior_uptr _do_action, behavior_uptr _entry_action,
	behavior_uptr _exit_action, const event_ids& _deferred_events, event_sptr _error_event )
	: simple_state_base( _name, sxy::move( _entry_action ), sxy::move( _exit_action ), _deferred_events, 
			_error_event ),
		do_( sxy::move( _do_action ) )		
{
	// Nothing to do...
}


simple_state_impl::~simple_state_impl() Y_NOEXCEPT
{
	// Nothing to do...
}


void simple_state_impl::execute_do_behavior( const event& _event, async_event_handler* const _async_event_handler,
	event_collector& _event_collector ) const
{
	Y_UNUSED_PARAMETER( _async_event_handler );	
	const behavior* const behavior = get_do();
	if( behavior )
	{
		Y_LOG( sxy::log_level::LL_TRACE, "Executing state's '%' do behavior.", get_name() );
		( *behavior )( _event, _event_collector );
	}
}


const behavior* simple_state_impl::get_do() const
{
	return( do_.get() );
}




}
