// based on utf-8
// data structure finale in hdu
// created by octaycloud on 2021-12-10.

#include "func.h"

int main() {
    int dept_ch;
    string continue_string;
//    system("mode con cols=130 lines=60");
    HuffmanTree ht;
    HuffmanCoder hc;
    Pre_HT(ht);
    while (true) {
        dept_ch = Menu();
        switch (dept_ch) {
            case 1:
                Init_HT(ht);
                break;
            case 2:
                Encoding(hc, ht);
                break;
            case 3:
                Decoding(hc, ht);
                break;
            case 4:
                Print_CodeFile();
                break;
            case 5:
                Print_HT(ht, "ch");
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "invalid func " << endl;
                break;
        }
        cout << "enter any to continue" << endl;
        cin >> continue_string;
    }
    return 0;
}
