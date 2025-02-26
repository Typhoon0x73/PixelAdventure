#ifndef SIP_COLLISION_FUNCTION_H_
#define SIP_COLLISION_FUNCTION_H_
#pragma once

namespace sip::CollisionFunction
{
    template<class T1, class T2>
    static void Collision(T1& v1, T2& v2)
    {
        // 未定義の組み合わせでここに来た。
        // 完全特殊化して実装想定。
        __debugbreak();
    }
}

#endif //! SIP_COLLISION_FUNCTION_H_