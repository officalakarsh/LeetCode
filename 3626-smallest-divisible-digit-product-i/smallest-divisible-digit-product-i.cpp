class Solution {
public:
    int smallestNumber(int n, int t) {
        while (true) {
            int x = n;
            int prod = 1;
            
            if (x == 0) prod = 0;
            while (x > 0) {
                prod *= (x % 10);
                x /= 10;
            }
            
            if (prod % t == 0) return n;
            n++;
        }
    }
};