#pragma once

#include <vector>
#include <mutex>
#include <assert.h>

template<typename... Args>
class Event
{
public:
	Event() {}

	virtual ~Event()
	{
		for (size_t i = 0; i < myEventSubsribers.size(); i++)
		{
			delete myEventSubsribers[i];
		}

		myEventSubsribers.clear();
	}

	Event(const Event& aRhs)
	{
		std::lock_guard<std::mutex> Lock(myMutex);

		for (size_t i = 0; i < myEventSubsribers.size(); i++)
		{
			BaseEventSubscription* CopiedSubscriber = new BaseEventSubscription();
			&CopiedSubscriber = &myEventSubsribers[i];
			aRhs.myEventSubsribers.push_back(CopiedSubscriber);
		}
	}

	template<typename SubscriberType>
	void Register(SubscriberType* anObject, void(SubscriberType::* aFunctionPtr)(Args...))
	{
		std::lock_guard<std::mutex> Lock(myMutex);
		EventSubscription<SubscriberType, Args...>* Subscriber = new EventSubscription<SubscriberType, Args...>(anObject, aFunctionPtr);
		m_EventSubsribers.push_back(Subscriber);
	}

	void UnregisterAll()
	{
		std::lock_guard<std::mutex> Lock(myMutex);

		for (size_t i = 0; i < myEventSubsribers.size(); i++)
		{
			delete myEventSubsribers[i];
		}

		myEventSubsribers.clear();
	}

	void Dispatch(Args... someArgs)
	{
		std::lock_guard<std::mutex> Lock(myMutex);

		for (BaseEventSubscription<Args...>* Subscriber : myEventSubsribers)
		{
			if (Subscriber)
			{
				Subscriber->DispatchToSubscriber(someArgs...);
			}
		}
	}

private:
	template<typename... Args>
	class BaseEventSubscription
	{
	public:
		BaseEventSubscription() {}
		virtual ~BaseEventSubscription() {}

		virtual void DispatchToSubscriber(Args... someArguments) = 0;
	};

	template<typename Type, typename... Args>
	class EventSubscription : public BaseEventSubscription<Args...>
	{
	public:
		EventSubscription(Type* anObject, void(Type::* aFunctionPtr)(Args...)) { mySubscriber = anObject;  myFunctionPtr = aFunctionPtr; }
		virtual ~EventSubscription() {}

		virtual void DispatchToSubscriber(Args... someArgs) override
		{
			if (mySubscriber != nullptr && myFunctionPtr != nullptr)
			{
				(*mySubscriber.*myFunctionPtr)(someArgs...);
			}
		}

	private:
		Type* mySubscriber;
		void(Type::* myFunctionPtr)(Args...);
	};

private:
	std::vector<BaseEventSubscription<Args...>*> myEventSubsribers;
	std::mutex myMutex;
};
