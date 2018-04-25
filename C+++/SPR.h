//
//  SPR.hpp
//  C+++
//
//  Created by chenyanan on 2017/1/5.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#ifndef SPR_hpp
#define SPR_hpp

#include <algorithm>
#include "RCT.h"

template<typename T> class SPR;
template<typename T> void swap(SPR<T>& lhs, SPR<T>& rhs);

template <typename T>
class SPR {
public:
    ~SPR();
    
    SPR(const T& t) : _spr(new T(t)) {}
    SPR(SPR<T>&& spr) : _spr(spr._spr){spr._spr = nullptr;}
    SPR(const SPR<T>& spr) : _spr(spr._spr) {++(static_cast<const RCT*>(_spr)->_cnt);}
    SPR<T>& operator=(SPR<T> spr) const {swap(*this, spr); return *this;};
    
    const T* operator->() const {return _spr;}
    const T& operator*() const {return *_spr;}
    operator const T* () const {return _spr;}
    const T* getSPR() {return _spr;}
    
private:
    const T* _spr;
    friend void swap<T>(SPR<T>& lhs, SPR<T>& rhs);
};

template<typename T>
SPR<T>::~SPR() {
    if (_spr && --(static_cast<const RCT*>(_spr)->_cnt) == 0) {
        delete _spr; _spr = nullptr;
    }
}

template<typename T> void swap(SPR<T>& lhs, SPR<T>& rhs) {
    using std::swap;
    swap(lhs._spr, rhs._spr);
}

#endif /* SPR_hpp */
