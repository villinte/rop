#include "state.h"
#include "sdl_wrapper.h"

namespace states{

  namespace{
    std::vector<std::unique_ptr<State>> _states;
  }

  void start(){
    while(!_states.empty() &&
	  !_states.back()->hasStarted()){
      auto& state = _states.back();
      state->setStarted();

      state->Init();
    }
  }
  
  void draw(){
    io::clear();
    if(!_states.empty()){
      auto drawFrom = end(_states);
      
      while(drawFrom != begin(_states)){
	--drawFrom;
	
	const auto& state_ptr = *drawFrom;

	if(!state_ptr->draw_overlayed()){
	  break;
	}
      }

      for(;drawFrom != end(_states); ++drawFrom){
	const auto& state_ptr = *drawFrom;
	state_ptr->Draw();
      }
    }
    io::flip();
  }

  void update(){
    if(!_states.empty()){
      _states.back()->Update();
    }
  }
  
  void push(std::unique_ptr<State> state){
    if(!_states.empty()){
      _states.back()->Pause();
    }

    _states.push_back(std::move(state));
        
  }
  
  void pop(){
    if(!_states.empty()){
      _states.back()->on_popped();
      _states.pop_back();
    
      if(!_states.empty()){
	_states.back()->Resume();
      }
    }
  }
  
  
  

  void popAll(){
    while(!_states.empty()){
      _states.back()->on_popped();
      _states.pop_back();
    }
  }

  bool is_empty(){
    return _states.empty();
  }

  bool is_current_state(const State& state){
    if(_states.empty ()){
      return false;
    }
    return &state == _states.back().get();
  }
  
}
