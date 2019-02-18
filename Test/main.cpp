//
//  main.cpp
//  Test
//
//  Created by 皮明震 on 2019/2/18.
//  Copyright © 2019 皮明震. All rights reserved.
//

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <map>

using namespace std;

/**
 * 找到 字符串中的每一个s字符到达制定字符的最短距离nm，返回数组指针(最长为 1000)
 * @param str char const * 字符串常量
 * @param n short
 * @param findCh char
 * @return short *
 */
short * getCharMinDistance(char const * str, short n, char findCh) {
    
    short index = 0;

    short * result = (short *)malloc(sizeof(short) * n);
    memset(result, -1, sizeof(short) * n);

    short charFindMax = 0;

    for (int i = 0; i < n; i++) {
        charFindMax += *(str + i) == findCh;
    }
    
    short * findIndexArr = (short *)malloc(sizeof(short) * charFindMax);
    memset(findIndexArr, 0, sizeof(short) * charFindMax);
    
    for (int i = 0; i < n; i++) {
        if (*(str + i) == findCh) {
            findIndexArr[index++] = i;
        }
    }

    for (int i = 0; i < n; i++ ) {
        for(int j = 0; j < charFindMax; j++) {
            if (*(result + i) == -1) {
                *(result + i) = abs(i - *(findIndexArr + j));
            } else if (abs(i - *(findIndexArr + j)) < *(result + i)) {
                *(result + i) = abs(i - *(findIndexArr + j));
                // 找到最小的 跳出本次h循环
                if (*(result + i) == 0) {
                    break;
                }
            }
        }
    }
    free(findIndexArr);

    return result;
}

void testGetCharMinDistance() {
    string s = "joycastleisnotacastle";
    char c = 't';
    
    cout << "source : " << s << endl;
    cout << "find   : " << c << endl;

    // 最长为1000
    short n = (short)strlen(s.c_str());
    
    short * result = getCharMinDistance(s.c_str(), n, c);
    cout << endl;
    cout << "result : ";
    for(int i = 0; i < n; i++) {
        cout << *(result + i) << ", ";
    }
    
    free(result);
    
    cout << endl << endl;
}

struct Point {
    int x;
    int y;
};

/*
 * 获得两个数的最大公约数
 */
int gcd(int a, int b){
    return (b==0) ? a : gcd(b, a%b);
}

/**
 * 默认没有相同的点
 * 求斜率相同的点的个数的最大值就是
 * PS：如果是用户参与的点其实可以将斜率取一个 阀值 (这个阀值内的斜率都算是 )
 */
int getMaxPointsNumInline(vector<Point> & points) {
    int maxPointCount = 0;
    for(int i = 0; i < points.size(); i++){
        map<pair<int, int>, int> pointCountMap;

        for(int j = i + 1; j < points.size(); j++){
            int disX = points[i].x - points[j].x;
            int disY = points[i].y - points[j].y;
            int d = gcd(disX, disY);
            pointCountMap[{disX / d, disY / d}]++;
        }

        map<pair<int, int> ,int>::iterator it;
        for(it = pointCountMap.begin(); it != pointCountMap.end(); it++){
            maxPointCount = max(maxPointCount, it->second);
        }
    }
    return maxPointCount + 1;
}

void testGetMaxPointsNumInline() {
    vector<Point> vec;

    Point p1 = {1, 1};
    vec.push_back(p1);
    
    Point p2 = {2, 2};
    vec.push_back(p2);
    
    Point p3 = {3, 3};
    vec.push_back(p3);
    
    Point p4 = {13, 13};
    vec.push_back(p4);
    
    Point p5 = {30, 20};
    vec.push_back(p5);
    
    Point p6 = {13, 33};
    vec.push_back(p6);

    cout << "The max number of point in line: " << getMaxPointsNumInline(vec) << endl;
}

int main(int argc, const char * argv[]) {
    testGetCharMinDistance();
    cout << endl;
    testGetMaxPointsNumInline();
    return 0;
}

