#include <iostream>
#include <algorithm>
#include <cstdio>
#include <time.h>
#include <string.h>
using namespace std;

class VectorElem{
public:
	char* num0;
	char* num1;
	char* num2;
	char* num3;
	char* value;
	VectorElem(){
		this -> num0 = NULL;
		this -> num1 = NULL;
		this -> num2 = NULL;
		this -> num3 = NULL;
		this -> value = NULL;
	};
	bool operator < (const VectorElem &elem) const{
		int status0;
		int status1;
		int status2;
		for(int i = 6; i >= 0;  --i){
			if(this->num3[i] < elem.num3[i] ){
				status0 = -1;
			}
			else {
				if(this->num3[i]  >  elem.num3[i] ){
					status0 = 1;
				}
			
			else {
				if (status0 == 0){
					status0 = 0;
				}
			}
			}
		}
		for(int i = 2; i >= 0;  --i){
			if(this->num2[i]  < elem.num2[i] ){
				status1 = -1;
			}
			else {
				if(this->num2[i] > elem.num2[i] ){
					status1 = 1;
				}
			
			else {
				if(status1 == 0) {
					status1 = 0;
				}
			}
			}
		}
		for(int i = 2; i >= 0;  --i){
			if(this->num1[i]  < elem.num1[i] ){
				status2 = -1;
			}
			else {
				if(this->num1[i] > elem.num1[i] ){
					status2 = 1;
				}
			
			else {
				if(status1 == 0) {
					status2 = 0;
				}
			}
			}
		}
		if(status2 == -1){
			return true;
		}
		if(status2 == 0){
			if(status1 == -1 ){
				return true;
			}
			if(status1 == 0){
				if(status0 == -1){
					return true;
				}
			}
		}
		return false;
	};
	void print(){
		printf("+%s-%s-%s\t%s\n", num0, num2, num3, value);
	};
};

inline int GetDigit(char* A, int B){
	return A[B]-'0'; //+1
}

class Vector{
private:
	int capacity;
	void set_size(int new_size){
		int new_capacity = count_capacity(new_size);
		if(new_capacity != capacity){
			VectorElem *new_data = new VectorElem[new_capacity];
			for(int i = 0; i < size; i++){
				new_data[i] = data[i];
			}
			delete [] data;
			data = new_data;
		}
		size = new_size;
		capacity = new_capacity;
	};	
	static const int min_capacity = 2;
	int count_capacity(int new_size){
		int new_capacity = capacity;
		if(capacity < min_capacity){
			new_capacity = min_capacity;
		}
		if(new_size > new_capacity){
			new_capacity *= 2;
		}
		if((new_size*4 < new_capacity) && (new_capacity >= 2*min_capacity)){
			new_capacity /= 2;
		}
		return new_capacity;
	};
	VectorElem *data;
public:
	int size;
	VectorElem* begin(){
	    return data;
    };
    VectorElem* end(){
	    return data+size;
    };
	Vector(){
		capacity = min_capacity;
		size = 0;
		data = new VectorElem[capacity];
	};
	~Vector(){
		delete [] data;
		size = 0;
		capacity = 0;
	};
	void RadixSort();
	void push_back(VectorElem elem){
		set_size(size + 1);
		data[size - 1] = elem;
	};
	VectorElem pop_front(){
		VectorElem result = data[size - 1];
		set_size(size - 1);
		return result;
	};
	void print(){
		for(int i = 0; i < size; i++){
			data[i].print();
		}
	};
	
};

void Vector::RadixSort(){
		Vector tempVec;
		for(int i = 0; i < size; i++){
			VectorElem newElem;
			tempVec.push_back(newElem);
		}
		int R = 10;
		for(int d = 6; d >= 0; d--){
			int i, j;
			long int count[11];
				for(j = 0; j < R; j++){
					count[j] = 0;
				}
				for(i = 0; i < size; i++){
					count[GetDigit(data[i].num3, d) +1]++;
				}
				for(j = 1; j < R; j++){
					count[j] += count[j - 1];
				}
				for(i = 0; i < size; i++){
					tempVec.data[count[GetDigit(data[i].num3, d)]++] = data[i];
				}
				for(i = 0; i < size; i++){
					data[i] = tempVec.data[i];
				}
		}
		
		for(int d = 2; d >= 0; d--){
			int i, j;
			long int countnum2[11];
			long int countnum1[11];
				for(j = 0; j < R; j++){
					countnum2[j] = 0;
					countnum1[j] = 0;
				}
				for(i = 0; i < size; i++){
					countnum2[GetDigit(data[i].num2, d) +1]++;
					countnum1[GetDigit(data[i].num1, d) +1]++;
				}
				for(j = 1; j < R; j++){
					countnum2[j] += countnum2[j - 1];
					countnum1[j] += countnum1[j - 1];
				}
				
				for(i = 0; i < size; i++){
					//int tempy = GetDigit(data[i].num2, d);
					//tempVec.data[count[tempy]++] = data[i];
					tempVec.data[countnum2[GetDigit(data[i].num2, d)]++] = data[i];
					
				}
				for(i = 0; i < size; i++){
					
					tempVec.data[countnum1[GetDigit(data[i].num1, d)]++] = data[i];
				}
				for(i = 0; i < size; i++){
					data[i] = tempVec.data[i];
				}
		}
	}

int GetCapForChar(char* key){
	char* it = key;
	int i = 0;
	while (*it != '\0'){
		i++;
		it++;
	}
	int cap = 10;
	while (cap < i) {
		cap *= 2;
	}
	return cap;
}

int main(){
	Vector Vec;
	Vector stdVec;
	char value[2050];
	while(true){
		char* num0 = new char[4];
		char* num1 = new char[4];
		char* num2 = new char[4];
		char* num3 = new char[8];
		
		char test = scanf("+%[0-9]-%[0-9]-%[0-9]\t%s\n", num0, num2, num3, value);
		if(test == EOF){
			break;
		}
		VectorElem newElem;
		
		int cap4 = GetCapForChar(value);
		newElem.value = new char[cap4];
		sscanf(value, "%s", newElem.value);
		num1[0]=num0[0];
		num1[1]=num0[1];
		num1[2]=num0[2];
		if (num1[1] < '0' || num1[1] > '9'){
			num1[2] = num1[0];
			num1[0] = '0';
			num1[1] = '0';
		}
		if (num1[2] < '0' || num1[2] > '9'){
			num1[2] = num1[1];
			num1[1] = num1[0];
			num1[0] = '0';	
		}
		newElem.num0 = num0;
		newElem.num1 = num1;
		newElem.num2 = num2;
		newElem.num3 = num3;
		Vec.push_back(newElem);
		stdVec.push_back(newElem);
	}
	
	//clock_t t = clock();
	//Vec.RadixSort();
	//t = clock() - t;
    //t = float(t);
    //cout <<"Radix Sort:"<< t <<endl;
    //t = clock();
	sort(stdVec.begin(), stdVec.end());
	//t = clock() - t;
    //t = float(t);
    //cout <<"std Sort:"<< t <<endl;
	//Vec.print();
	stdVec.print();
	
	return 0;
}
