#ifndef EffectGroup_h
#define EffectGroup_h

#include "Effect.cpp"

class EffectGroup {
  
  public:
        virtual Effect* effects() = 0;
        
};

#endif
