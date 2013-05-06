/*============================================================================
 * Name        	: Event.h
 * Author      	: Tojo Thomas tojohere@gmail.com
 * Description 	: This header file contains the implementation of
 * 				  Event template class which encapsulates the  Observer design pattern.
 * Date 	   	: 31-Mar-2009
 * Courtesy    	: From Patterns to Components [Doctoral thesis by Karine Arnout]
 * Signature   	: C++ programming using Eclipse and MinGW is a nice experience
 * ============================================================================
 */
#ifndef OBSERVER_EVENT_H_
#define OBSERVER_EVENT_H_
#include <vector>
/*
 * An Event component which encapsulates the Observer pattern.
 * Observer pattern is one among popular 23 design patterns listed by Gang of Four (GoF).
 * The Event class's object can be used in a subject class to represent an event of the subject.
 * Make this object public so that subscribers can easily subscribe to this event
 */
namespace GoFPatterns
{
	using namespace std;

	template<typename SourceType, typename EventArgType>
	class Event
	{
		protected:
			/**
			 * Event handler function pointer definition
			 * source 		- Subject - the object which fired the event.
			 * eventArg 	- The event argument
			 * context		- Context information, which a subscriber needs to get with an event notification
			 * 					Usually, this can be a pointer to the subscriber object itself.
			 */
			typedef void (*EventHandler)(SourceType *source, EventArgType eventArg,
					void* context);

			/**
			 * This inner class, for each EventHandler, stores the associated context information -
			 * pointer. This context pointer can be used to pass additional informations
			 * from the point of subscription to the event handler function.
			 * The best use of context pointer is to use the "this" pointer of subscriber itself.
			 */
			class SubscriberRecord
			{
				private:
					EventHandler handlerProc; // The event handler function pointer
					void *handlerContext; // pointer to context information
					SubscriberRecord(EventHandler handler, void* context = 0) :
						handlerProc(handler), handlerContext(context)
					{
					}
					friend class Event;
			};

		protected:
			vector<SubscriberRecord> Subscribers;
			SourceType *eventSource;

		public:
			/**
			 * Constructor - sets the Event source
			 */
			Event(SourceType *source) :
				eventSource(source)
			{
			}

			/**
			 * Virtual destructor - perform clean up if any.
			 */
			virtual ~Event()
			{
			}

			/**
			 * Operator used to subscribe a handler C# style event subscription
			 */
			void operator +=(EventHandler handler)
			{
				Subscribers.push_back(SubscriberRecord(handler));
			}

			/**
			 * Operator used to unsubscribe a handler C# style event subscription
			 */
			void operator -=(EventHandler handler)
			{
				typename vector<SubscriberRecord>::iterator itr = find(Subscribers.begin(),
						Subscribers.end(), SubscriberRecord(handler));
				if (itr != Subscribers.end())
				{
					Subscribers.erase(itr);
				}
			}

			/**
			 * Function used to subscribe a handler with optional context information
			 */
			void Subscribe(EventHandler handler, void* context = 0)
			{
				Subscribers.push_back(SubscriberRecord(handler, context));
			}

			/**
			 * Function used to unsubscribe a handler with optional context information
			 */
			void Unsubscribe(EventHandler handler, void* context = 0)
			{
				typename vector<SubscriberRecord>::iterator itr = find(Subscribers.begin(),
						Subscribers.end(), SubscriberRecord(handler, context));
				if (itr != Subscribers.end())
				{
					Subscribers.erase(itr);
				}
			}

			/**
			 * Fire the event and notify all observers with event argument, -
			 * source and context information if any provided.
			 */
			void FireEvent(EventArgType eventArg)
			{
				for (unsigned int i = 0; i < Subscribers.size(); i++)
				{
					Subscribers[i].handlerProc(eventSource, eventArg,
							Subscribers[i].handlerContext);
				}
			}
	};
}
#endif /* OBSERVER_EVENT_H_ */
