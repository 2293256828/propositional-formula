#include <fstream>
#include <cstring>
#include <map>
#include "BinaryTree.h"
#include "stack.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

bool isValid(char ch) {
    return ch == '&' || ch == '|' || ch == '!' || ch == 'p' || ch == 'q' || ch == 'r' || ch == 'u' || ch == 'v' ||
           ch == 'w' || ch == 'x' || ch == 'y' || ch == '(' || ch == ')';
}
int priority(char op) {
    switch (op) {
        case '#':
            return -1;
        case '(':
            return 0;
        case '|':
            return 1;
        case '&':
            return 2;
        case '!':
            return 3;
        default:
            return -1;
    }
}
//	 ����׺���ʽ��Ϊ��׺���ʽ
string change(string pre) {
    static char post[100];
    int i = 0, j = 0;
    MyStack<char> stack;
    stack.init();
    stack.init();        // ��ʼ���洢��������ջ
    stack.push('#');    // ���Ȱѽ�����־��#������ջ��
    while (pre[i] != '#') {
        if ((pre[i] >= 'A' && pre[i] <= 'Z') || (pre[i] >= 'a' && pre[i] <= 'z')) // �����߼���Ԫֱ��д���׺���ʽ
        {
            post[j++] = pre[i];
        } else if (pre[i] == '(')    // �������������ñȽ�ֱ����ջ
            stack.push(pre[i]);
        else if (pre[i] == ')')  // ���������Ž����Ӧ�����ź�Ĳ�������������ջ�еģ�ȫ��д���׺���ʽ
        {
            while (stack.gettop() != '(') {
                post[j++] = stack.pop();

            }
            stack.pop(); // ����������ջ����׺���ʽ�в���С����
        } else if (isOperator(pre[i])) {
            while (priority(pre[i]) <= priority(stack.gettop())) {
                // ��ǰ�Ĳ�����С�ڵ���ջ�������������ȼ�ʱ����ջ��������д�뵽��׺���ʽ���ظ��˹���
                post[j++] = stack.pop();
            }
            stack.push(pre[i]);    // ��ǰ���������ȼ�����ջ�������������ȼ������ò�������ջ
        }
        i++;
    }
    while (stack.top) // �����еĲ����������׺���ʽ
    {
        post[j++] = stack.pop();
    }
    return post;
}
string ReadData(string location) {
    ifstream fin(location);
    string s;
    string expression;
    while (getline(fin, s)) {
        expression += s;
    }

    return expression;
}
string trim(string str) {
    string s;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ')continue;
        s += str[i];
    }
    return s;
}
bool filters(string str) {
    int match = 0;//ƥ������
    if(str.length()==0)cout<<"-2 filter error";
    if (str.length() == 1 &&!isValidLetter(str[0])|| !isValid(str[0]) || str[0] == ')') {
        cout << "-1 filter error ";
        return false;
    }//����<=1,),������Χ ����false
    if (str[0] == '(')match += 1;
    if (isOperator(str[str.length() - 1])) {
        cout << "0 filter error ";
        return false;
    }
    for (int i = 1; i < str.length(); i++) {
        if (!isValid(str[i])) {
            cout << "1st filter error ";
            return false;
        }
        if (str[i] == '!' && isValidLetter(str[i - 1])) {
            cout << "1.5th filter error ";
            return false;
        }//p!��
        if (isOperator(str[i - 1]) && ((isOperator(str[i])) || str[i] == ')') &&
            ((str[i - 1] != '&' && str[i - 1] != '|') || str[i] != '!')) {
            cout << "2nd filter error ";
            return false;
        } //!&|�������,���� &|!) false �ų�&!,|!
        if (str[i - 1] == '(' && (str[i] == '&' || str[i] == '|')) {
            cout << "3rd filter error ";
            return false;
        }//(&,(| false
        if (isValidLetter(str[i - 1]) && isValidLetter(str[i])) {
            cout << "4th filter error ";
            return false;
        }//����������Ԫ , false
        if (str[i] == '(') { match++; }
        else if (str[i] == ')') {
            if (str[i - 1] == '(') {
                cout << "5th filter error blank bracket\n ";
                return false;
            }//()
            match--;
            if (match < 0) {
                cout << "6th filter error  not matched bracket\n";
                return false;
            }//)(
        }
    }if(match!=0){cout<<" 6th filter error not matched bracket\n";}
    return match == 0;
}
/**
 * ��ӡһ�����
 * @param str
 * @param b
 */
void TrueTable(string &str, int *b) {
    MyStack<char> si;
    si.init();
    map<char, int> map;
    int i;
    int cnt = 1;
    int ans;
    int len = str.length();
    for (i = 0; i < len; i++) {
        if (isValidLetter(str[i])) {
            if (map.count(str[i]) == 0) {//Ϊ��Ԫʱ,�ҵ�һ�γ���,��ô����map��
                si.push(b[cnt]);
                map.insert(make_pair(str[i], b[cnt]));
                cnt++;
            } else { si.push(map.find(str[i])->second); }//����ֱ���ó�
        } else if (str[i] == '&') {
            int x1 = si.gettop();
            si.pop();
            int x2 = si.gettop();
            si.pop();
            ans = x1 && x2;
            si.push(ans);
        } else if (str[i] == '|') {
            int x1 = si.gettop();
            si.pop();
            int x2 = si.gettop();
            si.pop();
            ans = x1 || x2;
            si.push(ans);
        } else if (str[i] == '!') {
            int x1 = si.gettop();
            si.pop();
            ans = !x1;
            si.push(ans);
        }

    }
    ans = si.gettop();
    si.pop();
    printf("%d\n", ans);
}
/**
 * �������,�����в�ͬ�ı�Ԫ����01���
 * @param step,���
 * @param n ��Ԫ������
 * @param b ���ÿ�ֵ�0,1��� ��Ϊ��ȫ�������,���Բ���Ҫ���Ƕ�Ӧ����
 * @param str
 */
void dfs(int step, int &n, int b[], string &str) {
    int i;
    if (step == n + 1) {//���һ�����
        for (i = 1; i <= n; i++)
            printf("%d ", b[i]);
        TrueTable(str, b);
        return;
    } else {
        for (i = 0; i <= 1; i++) {
            b[step] = i;
            dfs(step + 1, n, b, str);
        }
    }
    return;
}
/**
 * ͳ�Ʊ�Ԫ����
 * @param s
 * @param c ����ĳ����Ԫ�Ƿ����,c[0]=1,���������q
 * @return ��Ԫ������Ŀ
 */
int count(string s, bool c[], int &n) {
    int num = 0;

    for (int i = 0; i < 8; i++) {
        c[i] = false;//��ֹ�ڴ���Ⱦ
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'p') {
            num++;
            if (c[0]) {
                continue;
            }
            c[0] = true;
            n++;
            continue;
        }
        if (s[i] == 'q') {
            num++;
            if (c[1]) {
                continue;
            }
            c[1] = true;
            n++;
            continue;
        }
        if (s[i] == 'r') {
            num++;
            if (c[2]) {
                continue;
            }
            c[2] = true;
            n++;
            continue;
        }
        if (s[i] == 'u') {
            num++;
            if (c[3]) {
                continue;
            }
            c[3] = true;
            n++;
            continue;
        }
        if (s[i] == 'v') {
            num++;
            if (c[4]) {
                continue;
            }
            c[4] = true;
            n++;
            continue;
        }
        if (s[i] == 'w') {
            num++;
            if (c[5]) {
                continue;
            }
            c[5] = true;
            n++;
            continue;
        }
        if (s[i] == 'x') {
            num++;
            if (c[6]) {
                continue;
            }
            c[6] = true;
            n++;
            continue;
        }
        if (s[i] == 'y') {
            num++;
            if (c[7]) {
                continue;
            }
            c[7] = true;
            n++;
            continue;
        }
    }
    return num <= 8 ? num : -1;

}
TreeNode *reconstructiveCNF(TreeNode *&root) {
    if (root->data == '!') {
        TreeNode *right = reconstructiveCNF(root->right);
        return NegationEmbed(root, right);
    }
    if (((root->left != nullptr && root->right != nullptr) && root->left->data == root->right->data)
         || (root->right != nullptr && root->data == '!' && root->right->data == '!')) {
        TreeNode *left = reconstructiveCNF(root->left);
        TreeNode *right = reconstructiveCNF(root->right);
        return Simplify(root, left, right);
    }
    if (root->data == '|' || root->data == '&') {
        TreeNode *left = reconstructiveCNF(root->left);
        TreeNode *right = reconstructiveCNF(root->right);
        return distributeCNF(root, left, right);
    }
    return root;
}
TreeNode *reconstructiveDNF(TreeNode *&root) {
    if (root->data == '!') {
        TreeNode *right = reconstructiveDNF(root->right);
        return NegationEmbed(root, right);
    }
    if (((root->left != nullptr && root->right != nullptr) && root->left->data == root->right->data)
        || (root->right != nullptr && root->data == '!' && root->right->data == '!')) {
        TreeNode *left = reconstructiveDNF(root->left);
        TreeNode *right = reconstructiveDNF(root->right);
        return Simplify(root, left, right);
    }

    if (root->data == '|' || root->data == '&') {
        TreeNode *left = reconstructiveDNF(root->left);
        TreeNode *right = reconstructiveDNF(root->right);
        return distributeDNF(root, left, right);
    }

    return root;
}
void CNFTree(TreeNode *&root) {
    while (true) {
        TreeNode *transformedRoot = reconstructiveCNF(root);
        if (root == transformedRoot) {
            break;
        }
        root = transformedRoot;
    }
}
void DNFTree(TreeNode *&root) {
    while (true) {
        TreeNode *transformedRoot = reconstructiveDNF(root);
        if (root == transformedRoot) {
            break;
        }
        root = transformedRoot;
    }
}
void backtrackCNF(string *&PCNF, string &s, int &begin, bool c[], int repeat[]) {
    bool p = s.find('p') == -1 && c[0] == 1;//����ȱ��ĳ����
    bool q = s.find('q') == -1 && c[1] == 1;
    bool r = s.find('r') == -1 && c[2] == 1;
    bool u = s.find('u') == -1 && c[3] == 1;
    bool v = s.find('v') == -1 && c[4] == 1;
    bool w = s.find('w') == -1 && c[5] == 1;
    bool x = s.find('x') == -1 && c[6] == 1;
    bool y = s.find('y') == -1 && c[7] == 1;

    if (!p && !q && !r && !u && !v && !w && !x && !y) {
        int val = 0;//�����ظ�
        val += s.find("!p") == -1 ? 0 : 1;
        val += s.find("!q") == -1 ? 0 : 2;
        val += s.find("!r") == -1 ? 0 : 4;
        val += s.find("!u") == -1 ? 0 : 8;
        val += s.find("!v") == -1 ? 0 : 16;
        val += s.find("!w") == -1 ? 0 : 32;
        val += s.find("!x") == -1 ? 0 : 64;
        val += s.find("!y") == -1 ? 0 : 128;//ֻҪ��֤��ͬ������������val��ͬ����,��һ����Ҫ����Щ��
        if (repeat[val] == 0) {
            repeat[val] = 1;
            if (s.find("!p") != -1 && (s[0] == 'p' || s.find("|p") != -1)) {
                return;
            } else if (s.find("!q") != -1 && (s[0] == 'q' || s.find("|q") != -1)) {
                return;
            } else if (s.find("!r") != -1 && (s[0] == 'r' || s.find("|r") != -1)) {
                return;
            } else if (s.find("!u") != -1 && (s[0] == 'u' || s.find("|u") != -1)) {
                return;
            } else if (s.find("!v") != -1 && (s[0] == 'v' || s.find("|v") != -1)) {
                return;
            } else if (s.find("!w") != -1 && (s[0] == 'w' || s.find("|w") != -1)) {
                return;
            } else if (s.find("!x") != -1 && (s[0] == 'x' || s.find("|x") != -1)) {
                return;
            } else if (s.find("!y") != -1 && (s[0] == 'y' || s.find("|y") != -1)) {
                return;
            }
            PCNF[begin] = s;
            begin++;
            return;
        }
        return;
    }
    if (p) {
        s += '|';
        s += 'p';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!p";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (q) {
        s += '|';
        s += 'q';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!q";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (r) {
        s += '|';
        s += 'r';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!r";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (u) {
        s += '|';
        s += 'u';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!u";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (v) {
        s += '|';
        s += 'v';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!v";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (w) {
        s += '|';
        s += 'w';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!w";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (x) {
        s += '|';
        s += 'x';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!x";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (y) {
        s += '|';
        s += 'y';
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "|!y";
        backtrackCNF(PCNF, s, begin, c, repeat);
        s = s.substr(0, s.length() - 3);
    }
}
void backtrackDNF(string *&PDNF, string &s, int &begin2, bool c[], int repeat[]) {
    bool p = s.find('p') == -1 && c[0] == 1;//����ȱ��ĳ����
    bool q = s.find('q') == -1 && c[1] == 1;
    bool r = s.find('r') == -1 && c[2] == 1;
    bool u = s.find('u') == -1 && c[3] == 1;
    bool v = s.find('v') == -1 && c[4] == 1;
    bool w = s.find('w') == -1 && c[5] == 1;
    bool x = s.find('x') == -1 && c[6] == 1;
    bool y = s.find('y') == -1 && c[7] == 1;
    if (!p && !q && !r && !u && !v && !w && !x && !y) {
        int val = 0;//�����ظ�
        val += s.find("!p") == -1 ? 0 : 1;
        val += s.find("!q") == -1 ? 0 : 2;
        val += s.find("!r") == -1 ? 0 : 4;
        val += s.find("!u") == -1 ? 0 : 8;
        val += s.find("!v") == -1 ? 0 : 16;
        val += s.find("!w") == -1 ? 0 : 32;
        val += s.find("!x") == -1 ? 0 : 64;
        val += s.find("!y") == -1 ? 0 : 128;//ֻҪ��֤��ͬ������������val��ͬ����,��һ����Ҫ����Щ��
        if (repeat[val] == 0) {
            repeat[val] = 1;
            if (s.find("!p") != -1 && (s[0] == 'p' || s.find("&p") != -1)) {
                return;
            } else if (s.find("!q") != -1 && (s[0] == 'q' || s.find("&q") != -1)) {
                return;
            } else if (s.find("!r") != -1 && (s[0] == 'r' || s.find("&r") != -1)) {
                return;
            } else if (s.find("!u") != -1 && (s[0] == 'u' || s.find("&u") != -1)) {
                return;
            } else if (s.find("!v") != -1 && (s[0] == 'v' || s.find("&v") != -1)) {
                return;
            } else if (s.find("!w") != -1 && (s[0] == 'w' || s.find("&w") != -1)) {
                return;
            } else if (s.find("!x") != -1 && (s[0] == 'x' || s.find("&x") != -1)) {
                return;
            } else if (s.find("!y") != -1 && (s[0] == 'y' || s.find("&y") != -1)) {
                return;
            }
            PDNF[begin2] = s;
            begin2++;
            return;
        }
        return;
    }
    if (p) {
        s += '&';
        s += 'p';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!p";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (q) {
        s += '&';
        s += 'q';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!q";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (r) {
        s += '&';
        s += 'r';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!r";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (u) {
        s += '&';
        s += 'u';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!u";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (v) {
        s += '&';
        s += 'v';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!v";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (w) {
        s += '&';
        s += 'w';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!w";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (x) {
        s += '&';
        s += 'x';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!x";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    } else if (y) {
        s += '&';
        s += 'y';
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 2);
        s += "&!y";
        backtrackDNF(PDNF, s, begin2, c, repeat);
        s = s.substr(0, s.length() - 3);
    }
}
int main() {
    cout<<"�����ļ�ȫ·����\n";
    string ss;
    cin>>ss;
    string s;
    s = ReadData(ss);
    s = trim(s);
    cout << "string has been trimmed\n";
    if (s.length() == 0) {
        cout << "blank file or file not exist\n";
        return 0;
    }
    cout << "Read Success:" + s + "\n";
    if (!filters(s)) {
        cout << "\nNO! wrong format,it is illegal ";
        return 0;
    }
    cout << "filters passed\n";
    s += "#";
    s = change(s);
    bool c[8];//c��ͳ������Щ��Ԫ
    int n = 0;//n�Ǳ�Ԫ������Ŀ
    int num = count(s, c, n);//num�Ǳ�Ԫ��Ŀ
    cout << "The kind of propositional arguments is:" << n << "\n";
    if (num == -1) {
        cout << "The number of propositional arguments exceeds 8,NO!\n";
        return 0;
    }
    cout << "it is legal,Yes!\n";
    cout << "The number of propositional arguments is:" << num << "\n";
    cout << "the postfix expression with # appended\t:";
    cout << s + "\n";
    TreeNode *root = createTree(s);
    TreeNode *root2 = createTree(s);
    cout << "�����������ӡ:\n";
    PrintTree(root, 1);
    cout << "Level order:\n";
    FloorTraverse(root);
    cout << "\nPreorder::\n";
    PreOrderPrint(root);
    cout << "\nInorder:\n";
    InOrderPrint(root);
    cout << "\nPostorder:\n";
    PostOrderPrint(root);
    cout << "\n" << "its true table is as follow:\n";
    if (c[0])cout << "p ";
    if (c[1])cout << "q ";
    if (c[2])cout << "r ";
    if (c[3])cout << "u ";
    if (c[4])cout << "v ";
    if (c[5])cout << "w ";
    if (c[6])cout << "x ";
    if (c[7])cout << "y ";
    cout << "\n";
    int b[100];
    dfs(1, n, b, s);
    cout << "CNFTree:\n";
    CNFTree(root);
    cout << '\n';
    PrintTree(root, 1);
    cout << "\nDNFTree:\n";
    DNFTree(root2);
    PrintTree(root2, 1);
    cout << "Trees have been reconstructed \n";
    cout << "The followings are CNF and DNF\n";
    string *back1 = new string[256];
    string *back2 = new string[256];
    int n1 = 0;
    changeBackCNF(root, back1, n1);
    int n2 = 0;
    changeBackDNF(root2, back2, n2);
    cout << "A CNF:\n";
    for (int i = 0; i < n1; i++) {
        cout << '(' << back1[i] << ')' << '&';
    }
    cout << '(' << back1[n1] << ')';
    cout << "\nA DNF:\n";
    for (int i = 0; i < n2; i++) {
        cout << '(' << back2[i] << ')' << '|';
    }
    cout << '(' << back2[n2] << ')';

    cout << "\nNow we turn them into PCNF and PDNF by backtrack\n";

    string *PCNF = new string[256];
    PCNF[0]="FLAG";
    int begin = 0;
    int repeat[256];
    for (int i = 0; i < 256; i++) {
        repeat[i] = 0;//��ֹ�ڴ���Ⱦ
    }
    for (int i = 0; i <= n1; i++) {
        backtrackCNF(PCNF, back1[i], begin, c, repeat);
    }
    cout << "PCNF:\n";
    bool Tautology = false;

        if (PCNF[0]=="FLAG") Tautology = true;
    if (!Tautology) {
        for (int i = 0; i < begin - 1; i++) {
            cout << '(' << PCNF[i] << ')' << '&';
        }
        cout << '(' << PCNF[begin - 1] << ')';
    } else cout << "1";
    bool Contradictory = false;
    string *PDNF = new string[256];
    PDNF[0]="FLAG";
    int begin2 = 0;
    int repeat2[256];
    for (int i = 0; i < 256; i++) {
        repeat2[i] = 0;//��ֹ�ڴ���Ⱦ
    }
    for (int i = 0; i <= n2; i++) {
        backtrackDNF(PDNF, back2[i], begin2, c, repeat2);
    }
    cout << "\nPDNF:\n";
        if (PDNF[0] == "FLAG")Contradictory = true;
    if (!Contradictory) {
        for (int i = 0; i < begin2 - 1; i++) {
            cout << '(' << PDNF[i] << ')' << '|';
        }
        cout << '(' << PDNF[begin2 - 1] << ')';
    } else cout << '0';
    if (Tautology)cout << "\nTautology!\n";
    else if (Contradictory)cout << "\nContradictory!\n";
    else cout << "\nSatisfiable but not Tautology!\n";
}
