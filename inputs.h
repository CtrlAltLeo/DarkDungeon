#ifndef INPUTS
#define INPUTS

//#include <string>
//#include <iostream>

std::string get_player_action(){

  std::string in;
  getline(std::cin, in);

  std::string valid[6] = {"door", "talk", "fight", "help", "last", "stairs"};

  for (std::string s: valid){
    if (in == s){
      return in;
    }
  }

  return "FALSE";

}

int get_number(int low, int high){

  int in = -1;

  do {
    cout << "Input a number between " << low << " and " << high << endl;
    cin >> in;

  } while( in > high or in < low);

  return in;

}

bool get_bool(std::string question){

	cout << question << " (y/n)" << endl;
	
	string in;
	getline(cin, in);

	if (in[0] == 'y'){
		return true;
	}else{
		return false;
	}
	
}


#endif
