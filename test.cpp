#include <AVLIndex.h>

class RevStr{
    string str;
    public:
    RevStr(){

    }

    RevStr(string s){
        str = s;
        reverse(str.begin(), str.end());
    }
    const char* getCStr(){
        return str.c_str();
    }
};

int main(){

    AVLIndex<int, RevStr> index;
    for(int i=1; i<=100; i++){
        string str = "item_";
        index.add(i, RevStr(str + to_string(i)));
    }

    RevStr value;
    if(index.get(27, &value) == true)
        printf("value is %s\n", value.getCStr()); 
  
    index.remove(27);
    
    if(index.get(27, &value) == false)
      printf("Item Removed.\n");

}
