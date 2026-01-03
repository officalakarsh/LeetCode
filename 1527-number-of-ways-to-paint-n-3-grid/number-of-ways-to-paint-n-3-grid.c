#define MOD 1000000007

int numOfWays(int n) {
    long long aba = 6;   
    long long abc = 6;  
    
    for (int i = 2; i <= n; i++) {
        long long newAba = (aba * 3 + abc * 2) % MOD;
        long long newAbc = (aba * 2 + abc * 2) % MOD;
        aba = newAba;
        abc = newAbc;
    }

    return (aba + abc) % MOD;
}
