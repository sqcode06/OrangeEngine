#pragma once

#include "Keys.h"

#include <functional>
#include <array>

namespace OrangeEngine
{
	enum class EventType
	{
		WindowResize = 0,
		WindowClose,

		KeyPressed,
		KeyReleased,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,

		EventsQuantity
	};

	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual EventType get_type() const = 0;
	};
	
	typedef std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsQuantity)> EventCallbackArray;

	class EventDispatcher
	{
	public:
		template<typename EventType>
		void add_event_listener(std::function<void(EventType&)> callback)
		{
			auto base_callback = [func = std::move(callback)](BaseEvent& e)
			{
				if (e.get_type() == EventType::type)
				{
					func(static_cast<EventType&>(e));
				}
			};
			m_event_callbacks[static_cast<size_t>(EventType::type)] = std::move(base_callback);
		}

		void dispatch(BaseEvent& event)
		{
			auto& callback = m_event_callbacks[static_cast<size_t>(event.get_type())];
			if (callback) callback(event);
		}

	private:
		EventCallbackArray m_event_callbacks;
	};

	struct EventMouseMoved : public BaseEvent
	{
		EventMouseMoved(const double newX, const double newY)
			:x(newX),
			 y(newY)
		{}

		virtual EventType get_type() const override
		{
			return type;
		}

		double x;
		double y;

		static const EventType type = EventType::MouseMoved;
	};

	struct EventWindowResize : public BaseEvent
	{
		EventWindowResize(const unsigned int newWidth, const unsigned int newHeight)
			:width(newWidth),
			 height(newHeight)
		{}

		virtual EventType get_type() const override
		{
			return type;
		}

		unsigned int width;
		unsigned int height;

		static const EventType type = EventType::WindowResize;
	};

	struct EventWindowClose : public BaseEvent
	{
		virtual EventType get_type() const override
		{
			return type;
		}

		static const EventType type = EventType::WindowClose;
	};

	struct EventKeyPressed : public BaseEvent
	{
		EventKeyPressed(const KeyCode keyCode, const bool isRepeated)
			:key_code(keyCode),
			 is_repeated(isRepeated)
		{}

		virtual EventType get_type() const override
		{
			return type;
		}

		KeyCode key_code;
		bool is_repeated;
		static const EventType type = EventType::KeyPressed;
	};

	struct EventKeyReleased : public BaseEvent
	{
		EventKeyReleased(const KeyCode keyCode)
			:key_code(keyCode)
		{}

		virtual EventType get_type() const override
		{
			return type;
		}

		KeyCode key_code;
		static const EventType type = EventType::KeyReleased;
	};
}