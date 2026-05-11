#include "util/keysyms.hpp"
#include <unordered_map>

struct Keyboard
{
    explicit Keyboard() = default;
    Keyboard(const Keyboard& other)            = delete;
    Keyboard(Keyboard&& other)                 = delete;
    Keyboard& operator=(const Keyboard& other) = delete;
    Keyboard& operator=(Keyboard&& other)      = delete;

    bool isKeyPressed(KeySym k);
    void keyPressed(KeySym k);
    void keyRelease(KeySym k);
    void resetKeyboard();
    
private:

    bool* getMapElement(KeySym k);

    std::unordered_map<KeySym, bool> m_pressedKeys {
      {  KS_0,  false } ,
      {  KS_1,  false } ,
      {  KS_2,  false } ,
      {  KS_3,  false } ,
      {  KS_4,  false } ,
      {  KS_5,  false } ,
      {  KS_6,  false } ,
      {  KS_7,  false } ,
      {  KS_8,  false } ,
      {  KS_9,  false } ,
      {  KS_A,  false } ,   
      {  KS_B,  false } ,   
      {  KS_C,  false } ,   
      {  KS_D,  false } ,   
      {  KS_E,  false } ,   
      {  KS_F,  false } ,   
      {  KS_G,  false } ,
      {  KS_H,  false } ,
      {  KS_I,  false } ,
      {  KS_J,  false } ,
      {  KS_K,  false } ,
      {  KS_L,  false } ,    
      {  KS_M,  false } ,    
      {  KS_N,  false } ,    
      {  KS_O,  false } ,    
      {  KS_P,  false } ,    
      {  KS_Q,  false } ,    
      {  KS_R,  false } ,    
      {  KS_S,  false } ,    
      {  KS_T,  false } ,    
      {  KS_U,  false } ,    
      {  KS_V,  false } ,    
      {  KS_W,  false } ,
      {  KS_X,  false } ,
      {  KS_Y,  false } ,
      {  KS_Z,  false } ,
      {  KS_RIGHT     ,  false } ,
      {  KS_LEFT      ,  false } ,
      {  KS_DOWN      ,  false } ,
      {  KS_UP        ,  false } ,
      {  KS_SPACE     ,  false } ,
      {  KS_ENTER     ,  false } ,
      {  KS_ESCAPE    ,  false } 
    };
};

