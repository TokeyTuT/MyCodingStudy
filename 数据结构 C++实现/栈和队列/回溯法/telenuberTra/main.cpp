#include <iostream>
#include <vector>
#include <string>
// 映射常量定义

const std::string alphabetReflect[] = {"",   // 0
                                       "",   // 1
                                       "abc", // 2
                                       "def", // 3
                                       "ghi", //...
                                       "jkl",
                                       "mno",
                                       "pqrs",
                                       "tuv",
                                       "wxyz"}; // 这样就可以做到通过数字映射到字母

std::vector<std::string> result;
//string temp一定要定义在外面 否则每次递归的时候都会重置temp 丢失上一次的数据
std::string temp;

void backtracking(const std::string &number, int index)
{
    if (index == number.size())
    {
        result.push_back(temp);
        return;
    }

    else
    {
        int digital = number[index] - '0'; // 将string转为int类型 这里是ascii减0的ascii码
        // 存储digital对应的字符码
        std::string letters = alphabetReflect[digital];
        for (int i = 0; i < letters.size(); i++) //从零开始  不然会丢失下标为0的数据
        {
            temp.push_back(letters[i]);
            backtracking(number, index + 1);
            // 弹出
            temp.pop_back();
        }
    }

// using namespace std;
// const std::string letterMap[10] = {
//     "",     // 0
//     "",     // 1
//     "abc",  // 2
//     "def",  // 3
//     "ghi",  // 4
//     "jkl",  // 5
//     "mno",  // 6
//     "pqrs", // 7
//     "tuv",  // 8
//     "wxyz", // 9
};

// vector<string> result;
// string s;
// void backtracking(const string& digits, int index) {
//     if (index == digits.size()) {
//         result.push_back(s);
//         return;
//     }
//     int digit = digits[index] - '0';        // 将index指向的数字转为int
//     string letters = letterMap[digit];      // 取数字对应的字符集
//     for (int i = 0; i < letters.size(); i++) {
//         s.push_back(letters[i]);            // 处理
//         backtracking(digits, index + 1);    // 递归，注意index+1，一下层要处理下一个数字了
//         s.pop_back();                       // 回溯
//     }
// }
int main()
{
    std::string num = "23";
    // backtracking(num, 1);
    // string s;
    // getCombinations(num, 1, s);
    backtracking(num,0); // 从0开始遍历 而不是1
    for (std::vector<std::string>::iterator it = result.begin(); it != result.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}
