//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "fork_impl.h"

#include  <algorithm>

#include "const_vertex_visitor.h"
#include "vertex_visitor.h"
#include "pseudostate_visitor.h"
#include "transition_impl.h"
#include "state.h"
#include "state_machine_defect.h"
#include "region.h"


namespace sxy
{


fork_impl::fork_impl( const std::string& _name )
	: region_pseudostate_impl( _name )
{
	// Nothing to do...
}


fork_impl::~fork_impl() = default;


bool fork_impl::check( state_machine_defects& _defects ) const
{
	auto check_ok = true;

	// 15.3.8 Pseudostate -> Constraint [5]: Fork must have at least 2 outgoing transitions and exactly 1 incoming
	// transition.
	if( get_outgoing_transitions().size() < 2 )
	{
		_defects.push_back( std::make_unique< state_machine_defect >( *this,
				"Fork '%' has too few outgoing transitions! It has % transition(s).", get_name(),
				get_outgoing_transitions().size() ) );
		check_ok = false;
	}

	if( get_incoming_transitions().size() != 1 )
	{
		_defects.push_back( std::make_unique< state_machine_defect >( *this,
				"Fork '%' does not have exactly 1 incoming transition! It has % transition(s),", get_name(),
				get_outgoing_transitions().size() ) );
		check_ok = false;
	}

	// 15.3.8 Pseudostate -> Constraint [6]: All transitions outgoing a fork vertex must target states in different
	// regions of an state.
	// This check is not mandatory. The last LCA is the state machine itself. -> Jira[104] / Jira[103]
	// 15.3.14 Transition -> Constraint [1]: A fork segment must not have guards or triggers.
	for( const auto & transition : get_outgoing_transitions() )
	{
		if( transition->get_guard() )
		{
			_defects.push_back( std::make_unique< state_machine_defect >( *this,
					"Outgoing transition '%' of fork '%' has guard!", transition->get_name(), get_name() ) );
			check_ok = false;
		}
	}

	// transitions exiting pseudostates cannot have a trigger
	if( !pseudostate_impl::check( _defects ) )
	{
		check_ok = false;
	}

	// 15.3.14 Transition -> Constraint [3]: A fork segment must always target a state.
	for( const auto & transition : get_outgoing_transitions() )
	{
		const auto target_vertex = dynamic_cast< const state* >( &transition->get_target() );
		if( !target_vertex )
		{
			_defects.push_back( std::make_unique< state_machine_defect >( *this,
					"Fork '%' has outgoing transition ('%') that hasn't a state as target! Target vertex is '%'.", get_name(),
					transition->get_name(), target_vertex->get_name() ) );
			check_ok = false;
		}
		else
		{
			target_vertex->check( _defects );
		}
	}

	// 2 outgoing transitions cannot enter the same region
	std::set< const region* > target_regions;

	for( const auto transition : get_outgoing_transitions() )
	{
		auto target_region = transition->get_target().get_parent();
		const auto l_region = dynamic_cast< const region* >( target_region );
		if( l_region )
		{
			auto result = target_regions.insert( l_region );
			if( !result.second )
			{
				_defects.push_back( std::make_unique< state_machine_defect >( *this,
						"Fork '%' has outgoing transition(s) that has the same target region '%'.", get_name(),
						l_region->get_name() ) );
				check_ok = false;
				break;
			}
		}
	}

	auto transitions_kind = get_outgoing_transitions().front()->get_kind();

	for( const auto transition : get_outgoing_transitions() )
	{
		if( transitions_kind != transition->get_kind() )
		{
			_defects.push_back( std::make_unique< state_machine_defect >( *this,
					"Outgoing transitions of fork '%' have different kinds!", get_name() ) );
			check_ok = false;
			break;
		}
	}

	return( check_ok );
}


void fork_impl::accept_vertex_visitor( const_vertex_visitor& _visitor ) const
{
	_visitor.visit( *this );
}


void fork_impl::accept_vertex_visitor( vertex_visitor& _visitor )
{
	_visitor.visit( *this );
}


void fork_impl::accept_pseudostate_visitor( pseudostate_visitor& _visitor ) const
{
	_visitor.visit( *this );
}


void fork_impl::add_incoming_transition( transition& _incoming_transition )
{
	Y_ASSERT( vertex_impl::get_incoming_transitions().size() < 1, "Fork cannot have more than 1 incoming transition!" );
	vertex_impl::add_incoming_transition( _incoming_transition );
}


}
