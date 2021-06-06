# propositional-formula
输入命题公式,输出其二叉树表示、真值表、合/析取范式、主合/析取范式及公式类型

流程如下:

根据输入的文件名从文件读入逻辑表达式
由合取联结词“&”、析取联结词“|”、否定联结词“!”及命题变项 p、q、r、u、
v、w、x、y 组成，命题变项的个数不超过 8）。
（1）判断其是否为命题公式
（2）给出该命题公式的二叉树表示。
（3）构造该命题公式的TruthTable。
（4）根据（2）得到的二叉树、通过树的操作得到该逻辑表达式的 conjunctive normal form （之一） 及disjunctive normal form(之一)
（5）由该逻辑表达式的CNF及DNF得到该逻辑表达式的 major normal form（包括MCNF和MDNF）。
（6）通过主范式判断该命题公式的公式类型（tautology/satisfiable/contradictory）。
