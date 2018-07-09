#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

int a[50], b[50], m = 0;


int main() {
    std::ifstream fout("user_out");
    std::ifstream fans("answer");
    std::ifstream fin("input");

	int n, k;
	fin >> n >> k;
    std::string s1;
    std::getline(fout, s1);
    for(int i = 1;i <= n;i++)fin >> a[i];
    int pos = 0;char ch = -1;
    while(pos < (int)s1.length()){
    	while(pos < (int)s1.length() && !isdigit(ch))ch = s1[pos++];
    	int x = 0;
    	for(;isdigit(ch) && pos < (int)s1.length();ch = s1[pos++]){
    		x = (x << 1) + (x << 3) + (ch ^ 48);
    	}
    	b[++m] = x;
    }
    if(m != n){
    	std::cerr << "Output incorrect." << std::endl;
    	std::cout << 0 << std::endl;
        return 0;
    }

    std::cout << s1 << std::endl;
    //
}