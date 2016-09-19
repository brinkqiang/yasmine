//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex yasmine ecosystem (http://yasmine.seadex.de).                    //
// Copyright (C) 2016 Seadex GmbH                                                                   //
//                                                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://yasmine.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "log_level.hpp"

#include "base.hpp"


namespace sxy
{


std::string log_level_to_string( const log_level _log_level )
{
	std::string log_level_string = "???";

	switch( _log_level )
	{
	case ( log_level::LL_FATAL ):
	{
		log_level_string = "FATAL";
	}
	break;

	case ( log_level::LL_ERROR ):
	{
		log_level_string = "ERROR";
	}
	break;

	case ( log_level::LL_ASSERT ):
	{
		log_level_string = "ASSERT";
	}
	break;

	case ( log_level::LL_WARN ):
	{
		log_level_string = "WARN";
	}
	break;

	case ( log_level::LL_INFO ):
	{
		log_level_string = "INFO";
	}
	break;

	case ( log_level::LL_DEBUG ):
	{
		log_level_string = "DEBUG";
	}
	break;

	case ( log_level::LL_TRACE ):
	{
		log_level_string = "TRACE";
	}
	break;

	case ( log_level::LL_SPAM ):
	{
		log_level_string = "SPAM";
	}
	break;

	case ( log_level::LL_PROTOCOL ):
	{
		log_level_string = "PROTOCOL";
	}
	break;

	default:
		Y_ASSERT_NO_LOG( false, "Unknown log level!" );
		break;
	}

	return( log_level_string );
}


}