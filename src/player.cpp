#include "player.h"
#include "sdl_wrapper.h"
#include "game.h"
#include "entity.h"
#include "f_fighter.h"
#include "f_mortal.h"
#include "f_actor.h"
#include "f_container.h"

newPlayer::newPlayer(){
  nick = " ";
}

void newPlayer::Update(){

  if(nick == " "){
    nick = PlayerName::inputName();  
  }
  else{
    std::unique_ptr<Entity> pEntity(new Entity(P(0,0), nick, '@', White, "yourself."));
    Game::player = std::move(pEntity);
    std::string corpseName = "dead " + nick;
    Game::player->act = new PlayerActor(10);
    Game::player->mortal = new PlayerMortal(20, 0, corpseName);
    Game::player->fighter = new Fighter(10,0);
    Game::player->container = new Container(4);
    
    std::unique_ptr<State> playState(new GameState());
    states::push(std::move(playState));
  }
}

void newPlayer::Draw(){
    
}

namespace PlayerName{
  std::string inputName(){
    io::printMsg("Enter your name", 8, 8, 100, Green);
    std::string text;
  
    bool done = false;
    while(!done){
      SDL_Event event;
      if(SDL_PollEvent(&event)){
	switch(event.type){
	case SDL_QUIT:
	  done = true;
	  states::popAll();
	  break;
	case SDL_TEXTINPUT:
	  if(text.length() <= 20)
	    text += event.text.text;
	  break;
	case SDL_KEYDOWN:
	  if(event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0){
	    text.back() = ' ';
	    io::printMsg(text, 10, 10, 100, Green);
	    io::flip();
	    text.pop_back();
	  }
	  else if(event.key.keysym.sym == SDLK_RETURN){
	    done = true;
	    return text;
	  }
	  
	  break;
	}
      }
      io::printMsg(text, 10, 10, 100, Green);
      io::flip();
    }
    return " ";
  }
}
