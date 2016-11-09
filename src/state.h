#ifndef STATE_H
#define STATE_H
#include <vector>
#include <memory>


class State{
 public:

  State(){}
  virtual ~State() {}

  virtual void Init() {};
  virtual void Pause() {};
  virtual void Resume() {};
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual bool draw_overlayed() const{
    return false;
  }
  virtual void on_popped() {};

  bool hasStarted() const{
    return _hasStarted;
  }
  
  void setStarted(){
    _hasStarted = true;
  }

 private:
  bool _hasStarted;
  
};

namespace states{

  void start();
  void draw();
  void update();
  void push(std::unique_ptr<State> state);
  void pop();
  void popAll();
  bool is_empty();
  bool is_current_state(const State& state);
  
}

#endif
