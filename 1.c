bool operator < (const VectorElem &elem) const{
		int status1;
		int status2;
		int status3;
		for(int i = 6; i >= 0;  i--){
			if(num3[i] - '0' < elem.num3[i] - '0'){
				status3 = 1;
			}
			else if(num3[i] - '0' == elem.num3[i] - '0'){
				status3 = 3;
			}
			else {
				status3 = 0;
			}
		}
		for(int i = 2; i >= 0;  i--){
			if(num2[i] - '0' < elem.num2[i] - '0'){
				status2 = 1;
			}
			else if(num2[i] - '0' == elem.num2[i] - '0'){
				status2 = 3;
			}
			else {
				status2 = 0;
			}
		}
		for(int i = 2; i >= 0;  i--){
			if(num1[i] - '0' < elem.num1[i] - '0'){
				status1 = 1;
			}
			else if(num1[i] - '0' == elem.num1[i] - '0'){
				status1 = 3;
			}
			else {
				status1 = 0;
			}
		}
		if(status1 == 1){
			return true;
		}
		if(status1 == 3){
			if(status2 == 1 ){
				return true;
			}
			if(status2 == 3){
				if(status3 == 1){
					return true;
				}
			}
		}
        return false;
    };