// based on utf-8
// data structure finale in hdu not adoted
// created by octaycloud on 2021-12-10.

// infos and notes
// ver 0.4beta

#ifndef DATA_STRUCTURE_FINALE_FUNC_H
#define DATA_STRUCTURE_FINALE_FUNC_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <fstream>

#define MAX_NODE_NUM 1000
#define MAX_CH_ARRAY_NUM 1000

using namespace std;

// Huffman Coding encoding decoding system
typedef struct {
    char ch;
    int weight;
    int parent, lChild, rChild; // to locate
} HuffmanTreeNode;

typedef struct {
    HuffmanTreeNode *ht;
    int ht_size;
} HuffmanTree;

typedef struct {
    char ch;
    char *p_string;
} HuffmanCoderNote;

typedef struct {
    HuffmanCoderNote *hc;
    int hc_size;
} HuffmanCoder;

void Pre_HT(HuffmanTree &ht);

int Menu();

int Init_HT(HuffmanTree &ht);

void Create_HT(HuffmanTree &ht, int w[], char chs[], int n);

void Destroy_HT(HuffmanTree &ht);

int Select_min(HuffmanTree ht, int range, int &s1, int &s2);

void Print_HT_raw(HuffmanTree &ht);

void Print_HC_raw(HuffmanCoder &hc);

void Print_HT(HuffmanTree &ht, const string &print_command);

void Print_HT_weight(fstream &f, HuffmanTree &ht, int ind, int sh, int layer);

void Print_HT_ch(fstream &f, HuffmanTree &ht, int ind, int sh, int layer);

void Save_HT(HuffmanTree &ht);

void Load_HT(HuffmanTree &ht);

void Encoding(HuffmanCoder &hc, HuffmanTree &ht);

void Create_HC(HuffmanCoder &hc, HuffmanTree &ht);

void Destroy_HC(HuffmanCoder &hc);

void Encode(HuffmanCoder &hc);

void Decoding(HuffmanCoder &hc, HuffmanTree &ht);

void Print_CodeFile();

void Pre_HT(HuffmanTree &ht) {
    ht.ht_size = 0;
}

int Menu() {
    int dept_ch;    // in this .h dept_ch is set to int for pt.1's input
    // in another (of al) the variation dept_ch is char type for a wider enter especially 'I' or 'i'
    // however this adjustment is not friendly to char and weight input of pt.1

    cout << "Huffman Coding encoding decoding system " << endl;
    for (int i = 0; i < 55; i++)
        cout << "-"; // '-' * 55
    cout << endl;

    cout << endl
         << "1. I-Initialization " << endl;
    cout << endl
         << "2. E-Encoding " << endl;
    cout << endl
         << "3. D-Decoding " << endl;
    cout << endl
         << "4. P-Print " << endl;
    cout << endl
         << "5. T-Tree printing " << endl;

    cout << endl
         << "0. Q-Quit " << endl;
    for (int i = 0; i < 55; i++)
        cout << "-"; // '-' * 55
    cout << endl;

    cout << "please choose " << endl;
    cin >> dept_ch; // dept_ch firstly is an int type var, but we want to extend its support range
    switch (dept_ch) { // emm if someone like to enter letter you know...
        case 1:
            dept_ch = 1;
            break;
        case 2:
            dept_ch = 2;
            break;

        case 3:
            dept_ch = 3;
            break;

        case 4:
            dept_ch = 4;
            break;
        case 5:
            dept_ch = 5;
            break;
        case 0:
            dept_ch = 0;
            break;
        default:
            dept_ch = 100; // pitifully, dept_ch var is changed to char so 114514 cannot be its value
    }

    return (int) dept_ch; // return int for switch section in main
}

int Init_HT(HuffmanTree &ht) {
    int n;
    cout << "plz enter the num of nodes " << endl;
    cin >> n;
    char chs[MAX_NODE_NUM];
    int w[MAX_NODE_NUM];
    for (int i = 0; i < n; ++i) { // read from console
        cout << "plz enter the " << i + 1;
        if (((i + 1) % 10 == 1) && ((i + 1) != 11))
            cout << "st "; // more intuitive scripts
        else if (((i + 1) % 10 == 2) && ((i + 1) != 12))
            cout << "nd ";
        else if (((i + 1) % 10 == 3) && ((i + 1) != 13))
            cout << "rd ";
        else
            cout << "th ";
        cout << "char and weight " << endl;
        cin >> chs[i] >> w[i];
    }
    Create_HT(ht, w, chs, n);
    Save_HT(ht);
    return 1;
}

void Create_HT(HuffmanTree &ht, int w[], char chs[], int n) {
    // n num of chars  w each weight
    if (n <= 1)
        return;

    ht.ht = new HuffmanTreeNode[2 * n - 1];
    ht.ht_size = 2 * n - 1;

    int i = 0; // def value
    int s1, s2;

    for (i = 0; i < n; ++i)
        ht.ht[i] = {chs[i], w[i], -1, -1, -1};
    // -1 means none

    for (; i < ht.ht_size; ++i) {
        Select_min(ht, i, s1, s2); // ref s1 s2 to store the least two weights' indexes
        ht.ht[s1].parent = ht.ht[s2].parent = i;
        ht.ht[i].lChild = s1;
        ht.ht[i].rChild = s2;
        ht.ht[i].weight = ht.ht[s1].weight + ht.ht[s2].weight;
        ht.ht[i].parent = -1;
        ht.ht[i].ch = '\0';
    }
    cout << "construction of Huffman Tree completed " << endl;
}

void Destroy_HT(HuffmanTree &ht) { // warning: this function can not be called to init or recreate
    delete[] ht.ht;
    ht.ht_size = 0;
}

int Select_min(HuffmanTree ht, int range, int &s1, int &s2) { // i hate
    s1 = 0;
    s2 = 0;
    for (int i = 0; i < range; ++i) {
        if (ht.ht[i].parent == -1) { // can be updated
            if (!s1 and ht.ht[s1].parent != -1)
                s1 = i; // case: index 0 cannot be selected
            else if (!s2 and ht.ht[s2].parent != -1)
                s2 = i;
            else if (!s1 and !s2)
                ht.ht[i].weight < ht.ht[s1].weight ? s1 : s2 = i;
            else if (ht.ht[i].weight < max(ht.ht[s1].weight, ht.ht[s2].weight)) // i can replace
                ht.ht[i].weight < ht.ht[s1].weight ? s1 : s2 = i;
        }
        // ht.ht[i].weight < ht.ht[s1].weight ? s1 : s2 = i;
        // means
        // if(ht.ht[i].weight < ht.ht[s1].weight) s1 = i; else s2 = i;
        // it is kinda rough, but its logic is simple to code
    }
    if (s1 > s2) { // make the least weight stored in s1
        int temp;
        temp = s1;
        s1 = s2;
        s2 = temp;
    }
    return !s1 and !s2 ? 0 : 1; // re 0 or non0
}

void Print_HT_raw(HuffmanTree &ht) {
    // setw(4) -> '\t' ->
    cout << endl
         << "index  ch  weight  left_child  right_child  parent" << endl;
    for (int i = 0; i < ht.ht_size; i++)
        cout << setw(4) << i << setw(4) << ht.ht[i].ch << setw(4) << ht.ht[i].weight << setw(4) << ht.ht[i].lChild
             << setw(4) << ht.ht[i].rChild << setw(4) << ht.ht[i].parent << endl;
}

void Print_HC_raw(HuffmanCoder &hc) {
    cout << endl
         << "ch  code" << endl;
    for (int i = 0; i < hc.hc_size; ++i)
        cout << setw(4) << hc.hc[i].ch << setw(20) << hc.hc[i].p_string << endl;
    // hfm tree which is matched with alphabet will be printed in a command console
}

void Print_HT(HuffmanTree &ht, const string &print_command) {
    int root_index = ht.ht_size - 1; // generally the root node is the last one.
    fstream f;                       // the file to store result of tree printing
    f.open("../TreePrint.txt", ios::out);
    if (!f.is_open()) {
        cout << "open file error " << endl;
        return;
    }

    for (int i = 0; i < ht.ht_size; i++)
        if (ht.ht[i].parent == -1)
            root_index = i;
    if (print_command == "weight")
        return Print_HT_weight(f, ht, root_index, 0, 0);
    else if (print_command == "ch")
        return Print_HT_ch(f, ht, root_index, 0, 0);

    f.close();
    cout << "saving of print_result completed " << endl;
}

void Print_HT_weight(fstream &f, HuffmanTree &ht, int ind, int sh, int layer) {
    // f reference: output to file
    // sh: 0 means root, 1 means lC, 2 means rC. This variance is used to control the output '/' or '\'.
    // why setw(4)? because '\t' is used to advance the output.
    // Change the '\t' and setw(4) if you want a tight typesetting。
    // root -> straightly, lC -> pre line '\', rC -> post line '/'.
    if (!ht.ht_size) {
        cout << "no Huffman tree exists " << endl;
        return;
    }

    // using the array to construct tree is kinda different to linked list
    if (ht.ht[ind].rChild != -1)
        Print_HT_weight(f, ht, ht.ht[ind].rChild, 2, layer + 1); // right center left
    switch (sh) {
        case 0:
            cout << setw(4) << ht.ht[ind].weight << endl;
            break;
        case 1:
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << '\\' << endl;
            f << '\\' << endl;
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << setw(4) << ht.ht[ind].weight << endl;
            f << setw(4) << ht.ht[ind].weight << endl;
            break;
        case 2:
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << setw(4) << ht.ht[ind].weight << endl;
            f << setw(4) << ht.ht[ind].weight << endl;
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << '/' << endl;
            f << '/' << endl;
            break;
        default:
            break;
    }
    if (ht.ht[ind].lChild != -1)
        Print_HT_weight(f, ht, ht.ht[ind].lChild, 1, layer + 1);
    // this func is over with silence return
}

void Print_HT_ch(fstream &f, HuffmanTree &ht, int ind, int sh, int layer) {
    // some node which has ch == '\0' will be output as '_'
    if (!ht.ht_size) {
        cout << "no Huffman tree exists " << endl;
        return;
    }

    if (ht.ht[ind].rChild != -1)
        Print_HT_ch(f, ht, ht.ht[ind].rChild, 2, layer + 1); // right center left
    switch (sh) {
        case 0:
            if (ht.ht[ind].ch != '\0') {
                cout << setw(4) << ht.ht[ind].ch << endl;
                f << setw(4) << ht.ht[ind].ch << endl;
            } else {
                cout << setw(4) << '_' << endl;
                f << setw(4) << '_' << endl;
            }
            break;
        case 1:
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << '\\' << endl;
            f << '\\' << endl;
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            if (ht.ht[ind].ch != '\0') {
                cout << setw(4) << ht.ht[ind].ch << endl;
                f << setw(4) << ht.ht[ind].ch << endl;
            } else {
                cout << setw(4) << '_' << endl;
                f << setw(4) << '_' << endl;
            }
            break;
        case 2:
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            if (ht.ht[ind].ch != '\0') {
                cout << setw(4) << ht.ht[ind].ch << endl;
                f << setw(4) << ht.ht[ind].ch << endl;
            } else {
                cout << setw(4) << '_' << endl;
                f << setw(4) << '_' << endl;
            }
            for (int i = 0; i < layer; i++) {
                cout << '\t';
                f << '\t';
            }
            cout << '/' << endl;
            f << '/' << endl;
            break;
        default:
            break;
    }
    if (ht.ht[ind].lChild != -1)
        Print_HT_ch(f, ht, ht.ht[ind].lChild, 1, layer + 1);
    // this func is over with silence return
}

void Save_HT(HuffmanTree &ht) {
    fstream f;

    f.open("../hfmTree.txt", ios::out); // due to clion ../ is needed
    if (!f.is_open()) {
        cout << "open file error" << endl;
        return;
    }

    f << ht.ht_size << endl;
    for (int i = 0; i < ht.ht_size; i++) {
        f << ht.ht[i].ch << ' ' << ht.ht[i].weight << ' ' << ht.ht[i].lChild << ' ' << ht.ht[i].rChild << ' '
          << ht.ht[i].parent << endl;
    }
    f.close();
    cout << "saving of Huffman Tree completed " << endl;
}

void Load_HT(HuffmanTree &ht) {
    fstream f;

    f.open("../hfmTree.txt", ios::in);
    if (!f.is_open()) {
        cout << "open file error " << endl;
        return;
    }

    f >> ht.ht_size;
    ht.ht = new HuffmanTreeNode[ht.ht_size];
    for (int i = 0; i < ht.ht_size; i++) {
        f >> ht.ht[i].ch >> ht.ht[i].weight >> ht.ht[i].lChild >> ht.ht[i].rChild >> ht.ht[i].parent;
    }
    cout << "loading of Huffman Tree completed " << endl;
}

void Encoding(HuffmanCoder &hc, HuffmanTree &ht) {
    if (!ht.ht_size)
        Load_HT(ht); // if func 1 has not been called
    Create_HC(hc, ht);
    Print_HC_raw(hc); // to check Create_HC function

    Encode(hc);
}

void Create_HC(HuffmanCoder &hc, HuffmanTree &ht) {
    hc.hc_size = (ht.ht_size + 1) / 2;
    hc.hc = new HuffmanCoderNote[hc.hc_size];
    char *cd = new char[hc.hc_size];
    cd[hc.hc_size - 1] = '\0'; // actually cd is kinda string
    cout << "each char with Huffman code" << endl;
    for (int i = 0; i < hc.hc_size; ++i) {
        int start = hc.hc_size - 1;
        hc.hc[i].ch = ht.ht[i].ch;
        int c, f; // c current f further
        // f to prospect each node's parent and c is valued to f for judgement whether c is lC or not
        for (c = i, f = ht.ht[i].parent; f != -1; c = f, f = ht.ht[f].parent)
            // if f -1 means it's a root node
            if (ht.ht[f].lChild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        hc.hc[i].p_string = new char[hc.hc_size - start]; // wara sugiru

        cout << "the " << i + 1;
        if (((i + 1) % 10 == 1) && ((i + 1) != 11))
            cout << "st "; // more intuitive scripts
        else if (((i + 1) % 10 == 2) && ((i + 1) != 12))
            cout << "nd ";
        else if (((i + 1) % 10 == 3) && ((i + 1) != 13))
            cout << "rd "; // this section wo3 ku1 si3
        else
            cout << "th ";
        cout << "char " << ht.ht[i + 1].ch << " code "; // char cout over
        for (int j = start; j < hc.hc_size; ++j) {
            cout << cd[j];
            hc.hc[i].p_string[j - start] = cd[j];
        }
        cout << endl;
    }
    cout << endl;
    delete[] cd;
}

void Destroy_HC(HuffmanCoder &hc) {
    for (int i = 0; i < hc.hc_size; ++i)
        delete[] hc.hc[i].p_string;
    delete[] hc.hc;
}

void Encode(HuffmanCoder &hc) {
    fstream f_in, f_out;
    char ch[MAX_CH_ARRAY_NUM]; // u can also use string type and its functions in c++

    f_in.open("../ToBeTran.txt", ios::in);
    if (!f_in.is_open()) {
        cout << "open file error " << endl;
        return;
    }
    f_in >> ch;
    f_out.open("../CodeFile.txt", ios::out);
    if (!f_out.is_open()) {
        cout << "open file error " << endl;
        return;
    }

    // remember 2 print it once
    //    for (int i = 0; i < strlen(ch); i++)
    //        for (int j = 0; j < hc.hc_size; j++)
    //            if (ch[i] == hc.hc[j].ch)
    //                for (int k = 0; hc.hc[j].p_string[k]; k++) {
    //                    cout << hc.hc[j].p_string[k];
    //                    f_out.put(hc.hc[j].p_string[k]);
    //                    break;
    //                }

    for (int i = 0; i < strlen(ch); i++)
        for (int j = 0; j < hc.hc_size; j++)
            if (ch[i] == hc.hc[j].ch) {
                // this section's function can be seen as
                // output some string
                cout << hc.hc[j].p_string;
                f_out << hc.hc[j].p_string;
                break;
            }

    cout << endl;
    f_out.put('\0');

    cout << "code writing completed " << endl;
    f_in.close();
    f_out.close();
}

void Decoding(HuffmanCoder &hc, HuffmanTree &ht) {
    char ch[MAX_CH_ARRAY_NUM];
    int i = 0;
    int root = ht.ht_size - 1; // in an array the root is in the last node
    // this parameter will be used in next stage of decoding

    fstream f_cf;
    f_cf.open("../CodeFile.txt", ios::in);
    if (!f_cf.is_open()) {
        cout << "open file error " << endl;
        return;
    }
    f_cf >> ch;
    f_cf.close();

    fstream f_tf;
    f_tf.open("../TextFile.txt", ios::out);
    if (!f_tf.is_open()) {
        cout << "open file error " << endl;
        return;
    }

    cout << "read CodeFile.txt completed with code " << ch << endl
         << "the result is following ";

    int p = root;
    int pre = -1; // pre proc
    while (i < strlen(ch)) { // u can use for loop if u like
        while (p != -1) {
            if (ch[i] == '0') { // 0 means left branch
                pre = p;
                p = ht.ht[p].lChild;
            } else {
                pre = p;
                p = ht.ht[p].rChild;
            }
            i++;
        }
        cout << ht.ht[pre].ch;
        f_tf.put(ht.ht[pre].ch);

        i--;
        pre = -1;
        p = root;
    }

    //    for (; i < strlen(ch); cout << ht.ht[pre].ch, i--, pre = -1, p = root)
    //        for (; p != -1; i++)
    //            if (ch[i] == '0') {
    //                pre = p;
    //                p = ht.ht[p].lChild;
    //            } else {
    //                pre = p;
    //                p = ht.ht[p].rChild;
    //            }

    cout << endl;
    f_tf.put('\0');
    f_tf.close();
}

void Print_CodeFile() {
    fstream f_cf;
    char ch[MAX_CH_ARRAY_NUM]; // u can also use string type and its functions in c++

    f_cf.open("../CodeFile.txt", ios::in);
    if (!f_cf.is_open()) {
        cout << "open file error " << endl;
        return;
    }
    f_cf >> ch;
    f_cf.close();

    fstream f_cp;
    f_cp.open("../CodePrint.txt", ios::out);
    if (!f_cp.is_open()) {
        cout << "open file error " << endl;
        return;
    }

    for (int i = 0; ch[i]; i++) {
        cout << ch[i];
        f_cp.put(ch[i]);
        if ((i + 1) % 50 == 0)
            cout << endl;
    }
    cout << endl;
    f_cp.put('\0');

    cout << "print result saving completed" << endl;
    f_cp.close();
}

#endif //DATA_STRUCTURE_FINALE_FUNC_H
