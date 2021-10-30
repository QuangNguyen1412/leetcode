// 2
// 1st: sum = 4; set = [4]; 
// 2nd: sum = 16; set = [4,16];
// 3rd: sum = 37; set = [4,16,37];
// 4st: sum = 58; set = [4,16,37,58];
// 5st: sum = 89; set = [4,16,37,58, 145];
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> set;
        while(1)
        {
            if ((n = getSumSquare(n)) == 1)
                break;
            if (set.find(n) != set.end())
                return false;
            else 
                set.insert(n);
        }
        return true;
    }
protected:
    // 19
    // 1st
    // remainer = 9; ret = 81; number = 1;
    // 2nd: remainer = 1; ret = 37; number = 0;
    // return 37
    int getSumSquare(int number)
    {
        int ret = 0;
        while (1)
        {
            int remainer = number % 10;
            ret += (remainer * remainer);
            if (!(number = number / 10))
                break;
        }
        return ret;
    }
};