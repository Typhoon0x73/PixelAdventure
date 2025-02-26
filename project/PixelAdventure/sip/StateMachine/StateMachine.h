#ifndef SIP_STATE_MACHINE_H_
#define SIP_STATE_MACHINE_H_
#pragma once

// INCLUDE
#include <memory>
#include <Siv3D.hpp>

namespace sip
{
	template<class T>
	class IState
	{
	public:
		virtual ~IState() = default;
		virtual bool onCreate() = 0;
		virtual void onUpdate() = 0;
		virtual void onRelease() = 0;
		virtual Optional<T> getNextState() const = 0;
	};

	template<class T>
	class IStateChanger
	{
	public:
		virtual ~IStateChanger() = default;
		virtual bool change(const T& next) = 0;
	};

	template<class State>
	class IStateCreator
	{
	public:
		virtual ~IStateCreator() = default;
		virtual State* create() = 0;
	};

	template<class T>
	class IStateMachine : public IStateChanger<T>
	{
	public:
		virtual ~IStateMachine() = default;
		virtual bool update() = 0;
	};

	template<class T, class StateBase = IState<T>>
	class StateMachine : public IStateMachine<T>
	{
	public:

		template<class State>
		class StateCreator : public IStateCreator<StateBase>
		{
		public:
			virtual StateBase* create() override
			{
				return new State();
			}
		};

	public:

		explicit StateMachine() {}
		virtual ~StateMachine() {}

		virtual bool change(const T& next) override
		{
			auto creatorItr = m_creatorTable.find(next);
			if (creatorItr == m_creatorTable.end())
			{
				return false;
			}
			if (m_pState)
			{
				m_pState->onRelease();
			}
			m_pState.reset(creatorItr->second->create());
			return m_pState->onCreate();
		}

		template<class State>
		StateMachine& add(const T& state)
		{
			m_creatorTable[state] = std::make_unique<StateCreator<State>>();
			return *this;
		}

		virtual bool update() override
		{
			if (m_pState == nullptr)
			{
				return false;
			}
			m_pState->onUpdate();
			const auto& nextStateOpt = m_pState->getNextState();
			if (nextStateOpt.has_value())
			{
				if (!change(*nextStateOpt))
				{
					return false;
				}
			}
			return true;
		}

	protected:

		std::unique_ptr<StateBase> m_pState;
		HashTable<T, std::unique_ptr<IStateCreator<StateBase>>> m_creatorTable;
	};

}

#endif // !SIP_STATE_MACHINE_H_
