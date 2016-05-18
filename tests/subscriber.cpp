
/* Copyright (c) 2014, Human Brain Project
 *                     Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 *                     Stefan.Eilemann@epfl.ch
 */

#define BOOST_TEST_MODULE zeroeq_subscriber

#include "broker.h"

#include <servus/servus.h>

#ifdef ZEROEQ_USE_FLATBUFFERS
using namespace zeroeq::vocabulary;
#endif

BOOST_AUTO_TEST_CASE(construction)
{
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( ));
    BOOST_CHECK_NO_THROW(
                zeroeq::Subscriber subscriber( test::buildUniqueSession( )));
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost:1234" )));
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ),
                                           zeroeq::DEFAULT_SESSION ));

    zeroeq::Subscriber shared;
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( (zeroeq::Receiver&)shared ));
    BOOST_CHECK_NO_THROW(
                zeroeq::Subscriber( test::buildUniqueSession(), shared ));
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost:1234" ),
                                           shared ));
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ),
                                           zeroeq::DEFAULT_SESSION, shared ));
    BOOST_CHECK_NO_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost:1234" ),
                                           zeroeq::DEFAULT_SESSION, shared ));
}

BOOST_AUTO_TEST_CASE(invalid_construction)
{
    BOOST_CHECK_THROW( zeroeq::Subscriber subscriber( zeroeq::NULL_SESSION ),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( "" ),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" )),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ),
                                      zeroeq::NULL_SESSION ), std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ), "" ),
                       std::runtime_error );

    zeroeq::Subscriber shared;
    BOOST_CHECK_THROW( zeroeq::Subscriber subscriber( zeroeq::NULL_SESSION, shared ),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( "", shared ),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ), shared),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ),
                                        zeroeq::NULL_SESSION, shared ),
                       std::runtime_error );
    BOOST_CHECK_THROW( zeroeq::Subscriber( zeroeq::URI( "localhost" ), "", shared ),
                       std::runtime_error );
}

BOOST_AUTO_TEST_CASE(subscribe)
{
    zeroeq::Subscriber subscriber;
    ::test::SerializablePtr echoEvent = ::test::getFBEchoInEvent(
                    std::bind( &test::onEchoEvent, std::placeholders::_1 ));
    BOOST_CHECK( subscriber.subscribe( *echoEvent ));
}

BOOST_AUTO_TEST_CASE(unsubscribe)
{
    zeroeq::Subscriber subscriber;
    ::test::SerializablePtr echoEvent = ::test::getFBEchoInEvent(
                    std::bind( &test::onEchoEvent, std::placeholders::_1 ));
    BOOST_CHECK( subscriber.subscribe( *echoEvent ));
    BOOST_CHECK( subscriber.unsubscribe( *echoEvent ));
}

BOOST_AUTO_TEST_CASE(invalid_subscribe)
{
    zeroeq::Subscriber subscriber;
    ::test::SerializablePtr echo =
            ::test::getFBEchoInEvent( ::zeroeq::EventFunc( ));
    BOOST_CHECK( subscriber.subscribe( *echo ));
    BOOST_CHECK( !subscriber.subscribe( *echo ));
}

BOOST_AUTO_TEST_CASE(test_invalid_unsubscribe)
{
    zeroeq::Subscriber subscriber;
    test::Echo echo;
    BOOST_CHECK( !subscriber.unsubscribe( echo ));
    BOOST_CHECK( subscriber.subscribe( echo ));
    BOOST_CHECK( subscriber.unsubscribe( echo ));
    BOOST_CHECK( !subscriber.unsubscribe( echo ));
}


BOOST_AUTO_TEST_CASE(test_invalid_unsubscribe_different_event_objects)
{
    zeroeq::Subscriber subscriber;
    ::test::SerializablePtr echoEvent =
            ::test::getFBEchoInEvent( ::zeroeq::EventFunc( ));

    ::test::SerializablePtr emptyEvent =
            ::test::getFBEmptyInEvent( ::zeroeq::EventFunc( ));

    BOOST_CHECK( subscriber.subscribe( *echoEvent ));
    BOOST_CHECK( !subscriber.unsubscribe( *emptyEvent ));
}


BOOST_AUTO_TEST_CASE(not_implemented_servus)
{
    if( servus::Servus::isAvailable( ) )
        return;

    const zeroeq::URI uri( test::buildUniqueSession( ));
    BOOST_CHECK_THROW( zeroeq::Subscriber subscriber( uri ), std::runtime_error );
}
