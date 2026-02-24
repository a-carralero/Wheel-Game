
#include "man/state_machine.hpp"
#include "util/menu.hpp"

int main(){
   StateMachine sm;
   sm.addState<Game>();
   while (sm.isAlive()){
      sm.update();
   }

   return 0;
}