#ifndef EffectGroup_h
#define EffectGroup_h

class EffectGroup {
  
  public:
        virtual Effect* draw(uint8_t micVal) = 0;
        
};

#endif
