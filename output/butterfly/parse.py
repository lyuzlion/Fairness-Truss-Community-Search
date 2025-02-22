import re

def parse_file(filename):
    data = {}
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            
            # 分割键值对
            if ':' not in line:
                continue
            
            key_part, value_part = line.split(':', 1)
            key = key_part.strip()
            value = value_part.strip()

            # 提取数值并转换类型
            numeric_match = re.match(r'^([+-]?\d+\.?\d*)(.*)', value)
            if numeric_match:
                number = numeric_match.group(1)
                # 转换数据类型
                if '.' in number:
                    try:
                        data[key] = float(number)
                    except ValueError:
                        data[key] = value
                else:
                    try:
                        data[key] = int(number)
                    except ValueError:
                        data[key] = value
            else:
                data[key] = value
            if key == 'attribute delta':
                return data[key]
    
    return data

# 使用示例
if __name__ == "__main__":
    mi = 100
    q = -1
    for i in range(1, 801):
        result = parse_file('theta_4_q_' + str(i) + '_R_10_gamma_1.txt')
        if result == 4:
            print(i)
        # if result < mi:
        #     mi = result
        #     q = i
    print(mi, q)