def anpai():
    weekday = { }#定义一个空的字典
    while 1:
        ifend = input("【输入【1】选择周末安排，输入【0】退出程序：】\n")
        if ifend == '1':
            print("【请开始规划你们的周末吧:】\n")
        else:
            return 


        print("--------------安排周六--------------\n")
        yueliupengfei = input("【这周是否约刘鹏飞：】\n(如果是输入1，否则0)\n")

        if yueliupengfei == '1':
            weekday["周六："] = "和小刘小两口约起来！"
            print("周六：和小刘小两口约起来！\n")
        elif yueliupengfei == '0':
            weekday["周六："] = "周六俩人待家里"
            print("周六：俩人待家里\n")

        print("--------------安排周天--------------\n")

        yuepengyou = input("【沙酱是否约朋友：】\n(如果是输入1，否则0)\n")

        if yuepengyou == '1':
            weekday["周日："] = "沙酱找朋友玩，栋酱回学校！"
            print("周日：沙酱找朋友玩，栋酱回学校！\n")
        elif yuepengyou == '0':
            weekday["周日："] = "周六俩人待家里！"
            print("周日：周六俩人待家里！\n")
    

        #输出字典，将周末的安排一起输入
        staday = "周六" + weekday["周六："] + "\n"
        sunday = "周日" + weekday["周日："] + "\n"
        print("------------周末安排总结------------\n")
        print(staday)
        print(sunday)
        

print("开启沙酱和栋酱的周末之旅吧!!!\n")
print("--------------------------------------\n")
anpai()