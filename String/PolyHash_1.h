/* 
    - Source: VNOI
    - Modified by WizardAP
    *) Verification: 
        - https://oj.vnoi.info/problem/substr
        - https://oj.vnoi.info/problem/dtksub
        - https://oj.vnoi.info/problem/vostr
*/


//// The larger the number of modules, the slower the program runs
///// WARNING ! : Please use "precompute" function , maybe you are wrong because you don't use that function( precompute's function) 
const int NMOD = 4;
const int base = 257;
const ll modulo[] = {(ll)1e9 + 2277, (ll)1e9 + 5277, (ll)1e9 + 8277, (ll)1e9 + 9277};
ll pw[NMOD][mxn];
void precompute(int Leng)
{
    for (int j = 0; j < NMOD; j++)
        for (int i = 0; i <= Leng; i++)
            pw[j][i] = i == 0 ? 1 : (pw[j][i - 1] * base) % modulo[j];
}
struct Hash
{
    ll value[NMOD];
    Hash()
    {
        memset(value, 0, sizeof value);
    }
    Hash(char c)
    {
        for (int j = 0; j < NMOD; j++) value[j] = c;
    }
    Hash operator+(const Hash &x) const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++) {
            res.value[j] = value[j] + x.value[j];
            if (res.value[j] >= modulo[j]) res.value[j] -= modulo[j];
        }
        return res;
    }
    Hash operator-(const Hash &x) const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++)
        {
            res.value[j] = value[j] - x.value[j];
            if (res.value[j] < 0) res.value[j] += modulo[j];
        }
        return res;
    }
    Hash operator*(ll k)const
    {
        Hash res;
        for (int j = 0; j < NMOD; j++)
            res.value[j] = 1ll * value[j] * k % modulo[j];
        return res;
    }
    bool operator<(const Hash &x)const
    {
        for (int j = 0; j < NMOD; j++)
            if (value[j] != x.value[j]) return (value[j] < x.value[j]);
        return false;
    }
    bool operator==(const Hash &x)const
    {
        for (int j = 0; j < NMOD; j++)
            if (value[j] != x.value[j]) return false;
        return true;
    }
    bool operator!=(const Hash &x)const
    {
        for (int j = 0; j < NMOD; j++) if (value[j] != x.value[j]) return true;
        return false;
    }
};

struct PolyHash
{
    vector<Hash> hash;
    int n;
    const Hash NO_OPERATION;
    void init_hash(const string &s)
    {
        n = (int)s.size();
        hash.resize(n + 1, NO_OPERATION);
        for (int i = 0; i < n; i++)
            hash[i + 1] = hash[i] * base + Hash(s[i]);
    }
    Hash gethash(int pos)
    {
        return hash[pos];
    }
    Hash gethash(int l, int r)
    {
        Hash res;
        for (int j = 0; j < NMOD; j++)
            res.value[j] = ((hash[r].value[j] - hash[l - 1].value[j] * pw[j][r - l + 1]) % modulo[j] + modulo[j]) % modulo[j];
        return res;
    }
};
