#include<iostream>
using namespace std;

class Rect {
private:
    int height, width;
public:
    Rect(int w, int h) {
        height = h;
        width = w;
    }
    ~Rect() {
        cout << "析构函数" << endl;
    }
    Rect(const Rect& r) {
        this->height = r.height;
        this->width = r.width;
    }
};