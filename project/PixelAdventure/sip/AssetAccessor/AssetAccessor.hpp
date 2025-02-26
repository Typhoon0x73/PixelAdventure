/**!
* @file AssetAccessor.hpp
* @brief 簡易アセット管理クラス
* @author typhoon0x73
* @date 2025/02/21
*/
#ifndef SIP_ASSET_ACCESSOR_HPP_
#define SIP_ASSET_ACCESSOR_HPP_
#pragma once

// 
// 簡易使い方
// using AssetsAccessor = sip::AssetAccessor<Blob /* , etc... */>;
// AssetsAccessor accessor;
// accessor.getTable<Blob>()->add(U"fizz", U"buzz.bin");
// accessor.getTable<Blob>()->load(U"fizz");
// Blob* pFizz = accessor.getTable<Blob>()->getData(U"fizz");
// 

// INCLUDE
#include <Siv3D.hpp>

namespace sip
{

	/// @brief 基底アセットクラス
	/// @tparam T 管理したいクラス
	template< class T >
	class AssetBase : public IAsset
	{
	public:
		/// @brief コンストラクタ
		AssetBase();

		/// @brief デストラクタ
		virtual ~AssetBase() = default;

		/// @brief データへの生ポインタを取得します。
		/// @return データへのポインタ
		T* getData();

		/// @brief データへの生ポインタを取得します。
		/// @return データへのポインタ
		const T* getData() const;

	protected:

		/// @brief アセットデータ本体
		std::unique_ptr<T> m_pData;
	};

	/// @brief アセットクラス
	/// @tparam T 管理したいクラス
	/// @tparam ...Args 管理するクラスを生成するための情報
	template< class T, class... Args >
	class DataAsset : public AssetBase<T>
	{
	public:

		/// @brief データのロード時に呼び出される関数
		std::function<bool(DataAsset<T, Args...>&, const String&)> onLoad = DefaultLoad;

		/// @brief データのリリース時に呼び出される関数
		std::function<void(DataAsset<T, Args...>&)> onRelease = DefaultRelease;

		/// @brief コンストラクタ
		/// @param ...args 登録するデータの生成用引数
		explicit DataAsset(Args... args);

		/// @brief デストラクタ
		virtual ~DataAsset();

		/// @brief 指定したデータを直ちにロードします。
		/// @remark この関数はロード処理が終了するまで制御を返しません。
		/// @return ロードに成功した場合 true, それ以外の場合は false
		virtual bool load(const String& hint = {}) override;

		/// @brief 指定したデータの非同期ロードを開始します。
		virtual void loadAsync(const String& hint = {}) override;

		/// @brief 指定したデータのロードが完了するまで待機します。
		virtual void wait() override;

		/// @brief ロードしたデータをメモリ上から削除します。
		virtual void release() override;

		/// @brief 既定の読み込みを行う関数です。
		/// @param asset アセット本体
		/// @param hint ヒント
		/// @return ロードに成功した場合 true, それ以外の場合は false
		static bool DefaultLoad(DataAsset<T, Args...>& asset, const String&);

		/// @brief 既定のデータ解放を行う関数です。
		/// @param asset アセット本体
		static void DefaultRelease(DataAsset<T, Args...>& asset);

	private:

		/// @brief 非同期読み込み用タスク
		Optional<AsyncTask<void>> m_task;

		/// @brief データ生成用情報
		std::tuple<Args...> m_args;

	};

	/// @brief アセットデータ管理テーブルクラス
	/// @tparam T 管理するデータクラス
	template< class T >
	class AssetTable
	{
	public:

		/// @brief コンストラクタ
		AssetTable();

		/// @brief デストラクタ
		virtual ~AssetTable();

		/// @brief データを取得します。
		/// @param name 登録名
		/// @return データへの生ポインタ
		T* getData(AssetNameView name);

		/// @brief データを取得します。
		/// @param name 登録名
		/// @return データへの生ポインタ
		const T* getData(AssetNameView name) const;

		/// @brief データを登録します。
		/// @param name データの登録名
		/// @return 登録に成功した場合 true, それ以外の場合は false
		template<class... Args>
		bool add(AssetNameView name, Args... args);

		/// @brief 指定したデータが登録されているかを返します。
		/// @param name データ名
		/// @return 登録されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isRegistered(AssetNameView name) const;

		/// @brief 指定したデータを直ちにロードします。
		/// @param name データ名
		/// @remark この関数はロード処理が終了するまで制御を返しません。
		/// @return ロードに成功した場合 true, それ以外の場合は false
		bool load(AssetNameView name);

		/// @brief 指定したデータの非同期ロードを開始します。
		/// @param name データ名
		void loadAsync(AssetNameView name);

		/// @brief 指定したデータのロードが完了するまで待機します。
		/// @param name データ名
		void wait(AssetNameView name);

		/// @brief 指定したデータのロード処理が（成否にかかわらず）完了しているかを返します。
		/// @param name データ名
		/// @return ロード処理が（成否にかかわらず）完了している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isReady(AssetNameView name) const;

		/// @brief 指定したデータについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		/// @param name データ名
		void release(AssetNameView name);

		/// @brief すべてのデータについて、ロードしたデータをメモリ上から削除します。登録状態は維持されます。
		void releaseAll();

		/// @brief 指定したデータについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		/// @param name データ名
		void erase(AssetNameView name);

		/// @brief すべてのデータについて、ロードしたデータをメモリ上から削除し、登録も解除します。
		void clear();

		/// @brief 登録されているデータの情報一覧を取得します。
		/// @return 登録されているデータの情報一覧
		[[nodiscard]]
		HashTable<AssetName, AssetInfo> enumerate() const;

	private:

		/// @brief 管理テーブル
		HashTable<AssetName, std::unique_ptr<AssetBase<T>>> m_table;
	};

	/// @brief 各アセットへのアクセサクラス
	/// @tparam ...Types 各アセットのクラス
	template< class ... Types >
	class AssetAccessor
	{
	public:

		/// @brief コンストラクタ
		AssetAccessor();

		/// @brief デストラクタ
		virtual ~AssetAccessor() = default;

		/// @brief 指定したクラスのテーブルを取得します。
		/// @remark 初回呼び出し時はデータを作成し返します。
		/// @tparam T 指定クラス
		/// @return 指定クラスのテーブルへの生ポインタ
		template< class T >
		AssetTable<T>* getTable();

		/// @brief 指定したクラスのテーブルを取得します。
		/// @remark 初回呼び出し時はデータを作成し返します。
		/// @tparam T 指定クラス
		/// @return 指定クラスのテーブルへの生ポインタ
		template < typename T >
		const AssetTable<T>* getTable() const;

	private:

		/// @brief 各クラスのテーブルインスタンス
		std::tuple<std::unique_ptr<AssetTable<Types>>...> m_elements;

		/*! データタイプ置き換え */
		template < unsigned int Index >
		using ElementType = typename std::tuple_element<Index, decltype(m_elements)>::type;

		/*! エレメントチェック置き換え */
		template < typename T, unsigned int Index >
		using IsElement = std::is_same<ElementType<Index>, T>;

		/*! エレメントの検索構造体 */
		template < typename T, unsigned int Index = 0 >
		struct FindElement : public std::conditional_t<
			IsElement<T, Index>::value,
			std::integral_constant< decltype(Index), Index>,
			FindElement<T, Index + 1>
		> {};
	};

}

#include "AssetAccessor.ipp"

#endif // !SIP_ASSET_ACCESSOR_HPP_
