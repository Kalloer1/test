import os
import shutil
import tkinter as tk
from tkinter import filedialog

def organize_files(source_dir):
    # 获取指定目录下的所有文件
    files = [f for f in os.listdir(source_dir) if os.path.isfile(os.path.join(source_dir, f))]
    
    # 遍历每个文件
    for filename in files:
        file_path = os.path.join(source_dir, filename)
        
        # 创建同名文件夹
        folder_name = os.path.splitext(filename)[0]  # 文件名作为文件夹名
        folder_path = os.path.join(source_dir, folder_name)
        
        if not os.path.exists(folder_path):
            os.mkdir(folder_path)
        
        # 移动文件到对应的文件夹中
        try:
            shutil.move(file_path, folder_path)
            print(f"Moved {filename} to {folder_name}/")
        except Exception as e:
            print(f"Failed to move {filename}: {str(e)}")
    
    # 文件整理完成后弹窗显示完成信息
    tk.messagebox.showinfo("完成", "文件整理完成！")

def select_directory():
    # 弹出文件夹选择对话框
    source_dir = filedialog.askdirectory()
    if source_dir:
        organize_files(source_dir)

# 创建GUI窗口
root = tk.Tk()
root.title("文件整理工具")

# 添加选择文件夹按钮
select_button = tk.Button(root, text="选择文件夹", command=select_directory)
select_button.pack(pady=20)

# 添加退出按钮
def exit_application():
    root.destroy()

exit_button = tk.Button(root, text="退出", command=exit_application)
exit_button.pack(pady=10)

# 运行主循环
root.mainloop()
