#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <memory>
#include <map>
#include <queue>
#include <time.h>
#include <math.h>
#include <cstdio>

using namespace std;
using lu_t = unsigned long int;

class Random
{
    
private:
    lu_t seed;
    lu_t init;
    

    lu_t mod_exp(lu_t base, lu_t exponent, lu_t mod)
    {
        if (mod == 1) return 0;    
        lu_t result = 1;
        base = base % mod;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
                result = (result * base) % mod;
            exponent = exponent >> 1;
            base = (base * base) % mod;
        }
        return result;
    }

    lu_t mod_exp_d(lu_t base, lu_t exponent, lu_t mod)
    {
        lu_t res = 1;
        for(int i = 0; i<exponent; i++)
            res *= res;
        return res % mod;
    }
public:
    lu_t a, b, m;
    lu_t count;

    lu_t oula(lu_t n)
    {
        lu_t rea=n;
        lu_t i;
        for(i=2; i*i<=n; i++)
            if(n%i==0)
            {
                rea=rea-rea/i;
                do
                    n/=i;
                while(n%i==0);
            }
        if(n>1)
            rea=rea-rea/n;
        return rea;
    }

    bool isp(lu_t num)
    {       
        if (num == 2 || num == 3)
            return true;
        if (num % 6 != 1 && num % 6 != 5)
            return false;
        lu_t tmp = (lu_t)sqrt(num);
        for(lu_t i = 5; i<=tmp; i++)
            if( num % i == 0 || num % (i+2) == 0)
                return false; 
        return true;
    }

    bool isrp(int a, int b)
    {
        if (a <= 0 || b <= 0 || a == b)
            return false;
        else if (a == 1 || b == 1)
            return true;
        else
        {            
            while (1)
            {
                int t = a % b;
                if (t == 0)
                {
                    break;
                }
                else
                {
                    a = b;
                    b = t;
                }
            }
            if (b > 1)
                return false;
            else
                return true;
        }
    }

    void set_seed(lu_t _seed)
    {
        seed = _seed;
        init = _seed;
    }

    unsigned long int rand_base64()
    {
        unsigned long long llrn;
        llrn = rand_base();
        llrn = llrn << 31;
        llrn |= rand_base();
        return llrn;
    }

    unsigned long int rand_seek64(lu_t idx)
    {
        unsigned long long llrn;
        llrn = rand_seek(idx*2-1);
        llrn = llrn << 31;
        llrn |= rand_seek(idx*2);
        return llrn;
    }

    unsigned int rand_base()
    {
        count++;
        seed = (a * seed + b) % m;
        return seed;
    }

    unsigned int rand_seek(lu_t idx)
    {
        lu_t x = (init * mod_exp(a, idx, m)) % m;
        lu_t tmpa = mod_exp(a, idx, m)-1;        
        lu_t tmpb = mod_exp(a-1, m-2, m);
        lu_t y = ((tmpa * tmpb) % m) * b;

        return (x + y) % m;
    }

    int get_seed()
    {
        return seed;
    }

    Random(lu_t _a = 214013l, lu_t _b = 2531011l, lu_t _m = 0x7FFFFFFF)
    {
        seed = init = -1; 
        a = _a;
        b = _b;
        m = _m;
        count=0;
    }
};



int main()
{
    Random A;
    A.set_seed(5);
    for(int i = 0; i<100; i++)
    {
        cout<<A.rand_base64()<<endl;
        cout<<A.rand_seek64(i+1)<<endl;
    }
    return 0;
}