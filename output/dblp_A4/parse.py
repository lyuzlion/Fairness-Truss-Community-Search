import glob

def calculate_average_delta():
    # 获取所有符合命名规则的文件
    file_pattern = "theta_8_q_*_R_*_gamma_20.txt"
    files = glob.glob(file_pattern)
    
    if not files:
        print("未找到符合格式的文件")
        return
    
    delta_values = []
    
    for filename in files:
        try:
            with open(filename, 'r') as f:
                delta_found = False
                for line in f:
                    if line.strip().startswith("attribute delta"):
                        try:
                            # 提取数值部分
                            value = int(line.split(":")[1].strip())
                            delta_found = True
                            if value >= 5:
                                continue
                            delta_values.append(value)
                            break
                        except (IndexError, ValueError) as e:
                            print(f"文件 {filename} 格式错误：{line.strip()}")
                if not delta_found:
                    print(f"警告：文件 {filename} 中未找到 attribute delta")
        except Exception as e:
            print(f"无法读取文件 {filename}: {str(e)}")
    
    if delta_values:
        average = sum(delta_values) / len(delta_values)
        print(f"\n解析完成，共处理 {len(files)} 个文件")
        print(f"有效数据文件：{len(delta_values)} 个")
        print(f"attribute delta 平均值：{average:.2f}")
    else:
        print("所有文件均未找到有效数据")

if __name__ == "__main__":
    calculate_average_delta()