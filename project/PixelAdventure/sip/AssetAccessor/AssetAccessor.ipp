
namespace sip
{

	template<class T>
	inline AssetBase<T>::AssetBase()
		: IAsset{}
		, m_pData{ nullptr }
	{
	}

	template<class T>
	inline T* AssetBase<T>::getData()
	{
		return m_pData.get();
	}

	template<class T>
	inline const T* AssetBase<T>::getData() const
	{
		return m_pData.get();
	}

	//------------------------------------------------------------

	template<class T, class ...Args>
	inline DataAsset<T, Args...>::DataAsset(Args ...args)
		: AssetBase<T>{}
		, m_args{ args... }
		, m_task{ none }
	{
	}

	template<class T, class ...Args>
	inline DataAsset<T, Args...>::~DataAsset()
	{
		release();
	}

	template<class T, class ...Args>
	inline bool DataAsset<T, Args...>::load(const String& hint)
	{
		if (IAsset::isUninitialized())
		{
			if (onLoad(*this, hint))
			{
				IAsset::setState(AssetState::Loaded);
				return true;
			}
			else
			{
				IAsset::setState(AssetState::Failed);
				return false;
			}
		}

		if (IAsset::isAsyncLoading())
		{
			wait();
		}

		return IAsset::isLoaded();
	}

	template<class T, class ...Args>
	inline void DataAsset<T, Args...>::loadAsync(const String& hint)
	{
		if (IAsset::isUninitialized())
		{
			IAsset::setState(AssetState::AsyncLoading);

			m_task = Async([this, hint = hint]()
			{
			IAsset::setState(onLoad(*this, hint) ? AssetState::Loaded : AssetState::Failed);
			});
		}
	}

	template<class T, class ...Args>
	inline void DataAsset<T, Args...>::wait()
	{
		if (!m_task.has_value())
		{
			return;
		}
		if (m_task->isValid())
		{
			m_task->get();
		}
	}

	template<class T, class ...Args>
	inline void DataAsset<T, Args...>::release()
	{
		if (IAsset::isUninitialized())
		{
			return;
		}

		if (IAsset::isAsyncLoading())
		{
			wait();
		}

		onRelease(*this);

		IAsset::setState(AssetState::Uninitialized);
	}

	template<class T, class ...Args>
	inline bool DataAsset<T, Args...>::DefaultLoad(DataAsset<T, Args...>& asset, const String&)
	{
		if (asset.m_pData != nullptr)
		{
			return true;
		}
		auto loadFunc = [&](Args... args)
			{
				asset.m_pData = std::make_unique<T>(args...);
			};
		std::apply(loadFunc, asset.m_args);
		return true;
	}

	template<class T, class ...Args>
	inline void DataAsset<T, Args...>::DefaultRelease(DataAsset<T, Args...>& asset)
	{
		if (asset.m_pData == nullptr)
		{
			return;
		}
		asset.m_pData.reset();
	}

	//------------------------------------------------------------

	template<class T>
	inline AssetTable<T>::AssetTable()
		: m_table{}
	{
	}

	template<class T>
	inline AssetTable<T>::~AssetTable()
	{
		clear();
	}

	template<class T>
	inline T* AssetTable<T>::getData(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return nullptr;
		}
		return it->second->getData();
	}

	template<class T>
	inline const T* AssetTable<T>::getData(AssetNameView name) const
	{
		return const_cast<AssetTable<T>*>(this)->getData(name);
	}

	template<class T>
	template<class ...Args>
	inline bool AssetTable<T>::add(AssetNameView name, Args ...args)
	{
		if (isRegistered(name))
		{
			return false;
		}
		m_table[name] = std::make_unique<DataAsset<T, Args...>>(args...);
		return true;
	}

	template<class T>
	inline bool AssetTable<T>::isRegistered(AssetNameView name) const
	{
		return m_table.contains(name);
	}

	template<class T>
	inline bool AssetTable<T>::load(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return false;
		}
		return it->second->load();
	}

	template<class T>
	inline void AssetTable<T>::loadAsync(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return;
		}
		it->second->loadAsync();
	}

	template<class T>
	inline void AssetTable<T>::wait(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return;
		}
		it->second->wait();
	}

	template<class T>
	inline bool AssetTable<T>::isReady(AssetNameView name) const
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return false;
		}
		return it->second->isFinished();
	}

	template<class T>
	inline void AssetTable<T>::release(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return;
		}
		it->second->release();
	}

	template<class T>
	inline void AssetTable<T>::releaseAll()
	{
		for (auto&& [name, asset] : m_table)
		{
			asset->release();
		}
	}

	template<class T>
	inline void AssetTable<T>::erase(AssetNameView name)
	{
		auto it = m_table.find(name);
		if (it == m_table.end())
		{
			return;
		}
		it->second->release();
		m_table.erase(it);
	}

	template<class T>
	inline void AssetTable<T>::clear()
	{
		releaseAll();
		m_table.clear();
	}

	template<class T>
	inline HashTable<AssetName, AssetInfo> AssetTable<T>::enumerate() const
	{
		HashTable<AssetName, AssetInfo> result;

		result.reserve(m_table.size());

		for (auto&& [name, asset] : m_table)
		{
			result.emplace(name, AssetInfo{ asset->getState(), asset->getTags() });
		}

		return result;
	}

	//------------------------------------------------------------

	template<class ...Types>
	inline AssetAccessor<Types...>::AssetAccessor()
		: m_elements{}
	{
	}

	template<class ...Types>
	template<class T>
	inline AssetTable<T>* AssetAccessor<Types...>::getTable()
	{
		constexpr unsigned int INDEX = FindElement<std::unique_ptr<AssetTable<T>>>::value;
		auto& result = std::get<INDEX>(m_elements);
		if (result == nullptr)
		{
			result = std::make_unique<AssetTable<T>>();
		}
		return result.get();
	}

	template<class ...Types>
	template<typename T>
	inline const AssetTable<T>* AssetAccessor<Types...>::getTable() const
	{
		return const_cast<AssetAccessor*>(this)->getTable<T>();
	}

}
