class Solution {
public:
    int reverse(int x) {
       int check = 0;
       while( x != 0){
        if( check > INT_MAX/10 || check < INT_MIN/10){
            return 0;
        }
        check = check *10 + x % 10 ;
        x /= 10 ;
       }
       return check;  
    }
};