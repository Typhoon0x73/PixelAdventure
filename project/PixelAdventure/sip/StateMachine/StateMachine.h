#ifndef SIP_STATE_MACHINE_H_
#define SIP_STATE_MACHINE_H_
#pragma once

// INCLUDE
#include <memory>
#include <Siv3D.hpp>

namespace sip
{
	template<class T, class Data>
	class IState
	{
	public:
		virtual ~IState() = default;
		virtual bool onCreate() = 0;
		virtual void onUpdate() = 0;
		virtual void onRelease() = 0;
		virtual void setData(Data* pData) = 0;
		virtual Optional<T> getNextState() const = 0;
	};

	template<class T, class Data>
	class StateBase : public IState<T, Data>
	{
	public:
		StateBase() = default;
		virtual ~StateBase() = default;
		inline virtual void setData(Data* pData) { m_pData = pData; }

	protected:

		Data* m_pData{ nullptr };
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
		virtual void init(const T& init) = 0;
		virtual bool update() = 0;
	};

	template<class T, class Data>
	class StateMachine : public IStateMachine<T>
	{
	public:

		template<class Impl>
		class StateCreator : public IStateCreator<StateBase<T, Data>>
		{
		public:
			virtual StateBase<T, Data>* create() override
			{
				return new Impl();
			}
		};

	public:

		explicit StateMachine() = default;
		virtual ~StateMachine() = default;

		virtual void init(const T& init) override
		{
			m_pData = std::make_unique<Data>();
			change(init);
		}

		virtual bool change(const T& next) override
		{
			createState(next);
			m_pState->setData(m_pData.get());
			return m_pState->onCreate();
		}

		template<class Impl>
		StateMachine& add(const T& state)
		{
			m_creatorTable[state] = std::make_unique<StateCreator<Impl>>();
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

		virtual void createState(const T& next)
		{
			auto creatorItr = m_creatorTable.find(next);
			if (creatorItr == m_creatorTable.end())
			{
				return;
			}
			if (m_pState)
			{
				m_pState->onRelease();
			}
			m_pState.reset(creatorItr->second->create());
		}

	protected:

		std::unique_ptr<Data> m_pData{ nullptr };
		std::unique_ptr<StateBase<T, Data>> m_pState{ nullptr };
		HashTable<T, std::unique_ptr<IStateCreator<StateBase<T, Data>>>> m_creatorTable{};
	};

}

#endif // !SIP_STATE_MACHINE_H_
