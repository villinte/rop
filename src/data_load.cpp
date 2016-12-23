#include "data_load.h"
using namespace std;
namespace dataLoad{

  tinyxml2::XMLDocument monsters;
  
  void Init(){
    if(monsters.LoadFile("data/monsters.xml") == tinyxml2::XML_SUCCESS){
      // std::cout << "'monsters.xml' successfully loaded." << std::endl;
    }
    else{
      std::cout << "Failed to load monsters.xml" << std::endl;
    }
   
  }

  std::string getAttribute(std::string mon_name, std::string mon_element, std::string mon_attribute){
    	
    tinyxml2::XMLElement* root = monsters.FirstChildElement();
    if(root == NULL)
      {
	cerr << "Failed to load file: No root element." << endl;
      }
	
    for(tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
      {
	string elemName = elem->Value();
        const char* attr;
	if(elemName == "monster")
	  {
	    //cout << "Got monster" << endl;
			
	    attr = elem->Attribute("name");
	    std::string name = attr;
	    if(attr != NULL && name == mon_name){
	      //cout << "Got name: " << attr << endl;

	      for(tinyxml2::XMLElement* e = elem->FirstChildElement(mon_element.c_str()); e != NULL;
		  e = e->NextSiblingElement(mon_element.c_str()))
		{
		  //  cout << "Got " << mon_element << endl;
	
		  attr = e->Attribute(mon_attribute.c_str());
		  if(attr != NULL){
		    //cout << "Got " << mon_attribute << ": " << attr << endl;
		    return attr;
		  }
	        		
		}
	    }
	  }
	
      }

   
    return "UnknownAttribute";
  }
  
  
    
}
		  
