# FTCS

数据集：每行两个数，代表边的两个端点，结点从0开始编号。

编译命令：`g++ main.cpp -o main "-Wl,--stack=1000000000"`

运行：`./main #dataset #F #q #attribute_range #gamma`

例如：`./main DBLP 500 2000 2 1`
