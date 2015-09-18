#include "Util.h"
#include <ctime>

namespace light{
  
long getNowSeconds(){
  return time(0);
}

bool checkArgs(const AddArgs& addArgs){
  if (addArgs.key.empty() || addArgs.value.empty()){
	return false;
  }
  return true;
}
}
