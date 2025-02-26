#ifndef SIP_ISCENE_H_
#define SIP_ISCENE_H_
#pragma once

// INCLUDE

namespace sip
{
    /**
    * @brief シーンインターフェース
    */
    class IScene
    {
    public:

		virtual ~IScene() = default;
        
        /**
        * @brief シーンを初期化する
        */
        virtual void init() = 0;

        /**
        * @brief シーンを更新する
        */
        virtual void update() = 0;
        
        /**
        * @brief シーンを解放する
        */
        virtual void release() = 0;

        /**
        * @brief フェードイン可能な状態かを返す
        */
        virtual bool isFadeInEnable() const = 0;
    };

}

#endif // !SIP_ISCENE_H_
