# propositional-formula
输入命题公式,输出其二叉树表示、真值表、合/析取范式、主合/析取范式及公式类型<br>
[![Anurag's github stats](https://github-readme-stats.vercel.app/api?username=2293256828)](https://github.com/anuraghazra/github-readme-stats)
流程如下:<br>

根据输入的文件名从文件读入逻辑表达式<br>
由合取联结词“&”、析取联结词“|”、否定联结词“!”及命题变项 p、q、r、u、v、w、x、y 组成，命题变项的个数不超过 8）。<br>
（1）判断其是否为命题公式<br>
（2）给出该命题公式的二叉树表示。<br>
（3）构造该命题公式的TruthTable。\n
（4）通过树的操作得到该逻辑表达式的 conjunctive normal form （之一） 及disjunctive normal form(之一)<br>
（5）由该逻辑表达式的CNF及DNF得到该逻辑表达式的 major normal form（包括MCNF和MDNF）。<br>
（6）通过主范式判断该命题公式的公式类型（tautology/satisfiable/contradictory）。<br>


Input propositional formula, output binary tree representation, truth table, conjunctive/disjunctive normal form, principal conjunctive/disjunctive normal form and formula type
The process is as follows:
Reads a logical expression from a file based on the input file name
By conjunction connectors, disjunction coupling term "&" "|", no connectors "!"And propositional variables P, Q, R, U, V, W, X, Y, the number of propositional variables is not more than 8).
(1) Judge whether it is a propositional formula
(2) The binary tree representation of the propositional formula is given.
(3) construct the "TruthTable" of the proposition formula.\n (4) Get the conjunctive normal form(one) and disjunctive normal form(one) of the logical expression by the operation of the tree
(5) The major normal form of the logical expression (including MCNF and MDNF) is obtained from the CNF and DNF of the logical expression.
(6) through the main paradigm to determine whether the formula of proposition formula type (tautology/satisfiable/contradictory).
