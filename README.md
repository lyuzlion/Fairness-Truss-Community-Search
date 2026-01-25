# FTCS

数据集格式：第一行两个数，分别代表节点最大编号 $n$ 和边数 $m$。接下来 $m$ 行，每行两个数 $u, v$，代表边的两个端点，点从 $1$ 开始编号。接下来一行 $n$ 个数，第 $i$ 个数代表点 $i$ 的属性，属性从 $0$ 开始编号。

请将数据集放在如下路径：`./Dataset/DataName/`，并将数据集命名为 `DataName.txt`。

编译命令：`g++ main.cpp -o main`

运行：`./main <dataset name> <theta> <q> <attribute range> <gamma>`

例如：`./main DBLP 500 40000 2 5`

例如：`./main com-lj.ungraph 100000 101000 2 1000`
