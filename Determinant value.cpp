// 高斯喬登消去法.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;
//記憶體清除
void cleanup(float** array, int hen) {
    for (int i = 0; i < hen; ++i) {
        delete[] array[i];
    }
    delete[] array;
}
//將數字對調
float** run1(float** array, int hen, int line, int x, int y) {
    //尋找不為0的數字
    int z = x;
    while (array[z][y] == 0) {
        z++;
        if (z == hen) return array;
    }
    float temp;
    for (int i = 0; i < line; i++) {
        temp = array[x][i];
        array[x][i] = array[z][i];
        array[z][i] = temp;
    }
    return array;

}
//判斷正負並把首位數變成1
float** run2(float** result1, int hen, int line, int x, int y) {
    float z = result1[x][y];
    if (z == 0) return result1;
    if (result1[x][y] != 1) {

        for (int i = 0; i < line; i++) {
            if (result1[x][i] != 0) result1[x][i] = result1[x][i] / z;
        }
    }/*
    else if (result1[x][y] != 1 and result1[x][y] < 0) {
        for (int i = 0; i < line; i++) {
            result1[x][i] = result1[x][i] / z;
        }
    }*/
    return result1;
}
//開始執行高斯和喬登
float** run3(float** result2, int hen, int line, int x, int y) {
    vector<int> sort;
    for (int i = 0; i < hen; i++) {
        if (i == x) i++;
        if (i == hen) return result2;

        int z = result2[i][y] / result2[x][y];

        if (z > 0) {
            for (int q = 0; q < line; q++) {
                sort.push_back(result2[x][q] * z);
                result2[i][q] = result2[i][q] - sort[q];
                //cout << "result2["<<i<<"]["<<q<<"] =" << result2[i][q] << "\n";
            }
            sort.clear();
        }
        else if (z < 0) {
            for (int q = 0; q < line; q++) {
                sort.push_back(result2[x][q] * -z);
                if (sort[q] != 0) result2[i][q] = sort[q] + result2[i][q];
                //cout << "result2[" << i << "][" << q << "] =" << result2[i][q] << "\n";
            }
            sort.clear();
        }
    }

    return result2;
}
int main() {

    int line, hen;
    cout << "直列橫行 (請以空格分開，以Enter結束)\n";
    cout << "請輸入陣列行和列: ";
    cin >> hen >> line;
    cout << hen << "行" << line << "列\n";
    //使用指標的指標 完成二維動態陣列
    //把array指向行
    float** array = new float* [hen];
    for (int i = 0; i < hen; i++) {
        //然後把array指向列 告訴系統每行有幾列
        array[i] = new float[line];
    }

    //把數值存入陣列裡面
    for (int i = 0; i < hen; i++) {
        cout << "請輸入第" << i + 1 << "行的數值: (請以空格分開，以Enter結束)\n";
        for (int j = 0; j < line; j++) {
            cin >> array[i][j];
        }
    }
    //此時[0][0]
    int y = 0;
    for (int x = 0; x < hen; x++) {
        //將整行數字對調
        float** result1 = run1(array, static_cast<int>(hen), static_cast<int>(line), x, y);
        //判斷正負並把首位數變成1
        float** result2 = run2(result1, static_cast<int>(hen), static_cast<int>(line), x, y);
        //開始執行高斯和喬登
        float** result3 = run3(result2, static_cast<int>(hen), static_cast<int>(line), x, y);
        y++;
    }
    //列印
    cout << "----------------------------------\n";
    for (int i = 0; i < hen; i++) {
        for (int j = 0; j < line; j++) {
            cout << array[i][j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << "----------------------------------\n";


    cleanup(array, hen);
}