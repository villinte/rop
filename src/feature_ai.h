
class Actor;
class Game;
class Ai{
 public:
  virtual void Update(Actor *a) = 0;
  virtual ~Ai() {}
 protected:
  enum AiType {
    PLAYER
  };
};

class PlayerAi : public Ai{
 public:
  int Level;
  PlayerAi();
  ~PlayerAi();

  void Update(Actor *a);

 protected:
  void Input(Actor *a);
  bool Move(Actor *a, int targetX, int targetY);
};

