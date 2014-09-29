#ifndef EffectGroup_h
#define EffectGroup_h

#include "FastLED.h"
#include "Effect.cpp"

class EffectGroup {
  
    private:
        char* _name;
        Effect** _effects;        
        
    public:



        EffectGroup(char* name, Effect** effects) : _name(name), _effects(effects) {}
        
        char* name() {
            return _name;
        }

        Effect** effects() {
            return _effects;
        }
};

#endif

